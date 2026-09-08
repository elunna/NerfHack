#!/bin/sh
# nerfhack-rr-fuzz.sh - run unattended, looping NerfHack fuzzing sessions
# under rr, each one capped at a fixed number of turns.
#
# Each iteration starts the built-in fuzzer (--debug:fuzzer) under `rr
# record`, with -@ so every session gets a random role/race/gender/align
# instead of blocking on the interactive "Shall I pick a character for
# you?" prompt, and NH_FUZZER_MAXTURNS set so the game exits cleanly on its own
# once it hits the turn cap (see the iflags.debug_fuzzer check in
# src/allmain.c's moveloop_core()) instead of running forever. ASAN/UBSAN
# are told to abort() on error so their reports are exit-code visible the
# same way impossible()-triggered panics already are.
#
# A session's exit status decides its fate:
#   - exit 0 (turn cap hit, or the fuzzer character otherwise reached a
#     normal game-over): nothing interesting happened, so the trace and
#     logs are discarded and only a one-line summary is kept.
#   - a fatal signal (impossible() -> panic() -> abort(), an ASAN/UBSAN
#     abort, or a raw crash signal): the trace, a combined session.log,
#     and a non-interactive gdb backtrace (via `rr replay`) are all kept
#     under fuzz-sessions/<session-id>/ for later review.
#
# Usage:
#   sys/unix/nerfhack-rr-fuzz.sh [rr-record-options]
#
# Any arguments are forwarded to `rr record` itself (e.g. -h/--chaos), not
# to the game. Runs until interrupted (Ctrl-C) - for a bounded run, wrap it:
#   timeout 24h sys/unix/nerfhack-rr-fuzz.sh
#
# Tune via environment:
#   NH_FUZZER_MAXTURNS   turns per session before a clean reset (default 50000;
#                        kept modest since a crash trace at the cap takes this
#                        long to replay to the crash point when reproducing)
#   FUZZ_SESSIONS_DIR    where session directories are kept
#                         (default: <repo>/fuzz-sessions)
#
# Requires the same things as nerfhack-rr.sh (rr, a source-tree install).

set -eu

if ! command -v rr >/dev/null 2>&1; then
    echo "nerfhack-rr-fuzz.sh: rr is not installed or not on PATH." >&2
    echo "See https://rr-project.org/ for installation instructions." >&2
    exit 1
fi

PYTHON3=$(command -v python3) || {
    echo "nerfhack-rr-fuzz.sh: python3 is not installed or not on PATH." >&2
    exit 1
}

if ! "$PYTHON3" -c 'import pexpect' >/dev/null 2>&1; then
    echo "nerfhack-rr-fuzz.sh: python3 module 'pexpect' is required (pip install pexpect)." >&2
    exit 1
fi

# NetHack's tty port needs a usable terminfo entry; a cron/systemd-timer
# environment (or this script's own test runs) may have no TERM at all,
# or "dumb", either of which fails at startup before fuzzing ever begins.
case "${TERM:-}" in
    "" | dumb) TERM=xterm-256color ;;
esac
export TERM

REPO_ROOT=$(git rev-parse --show-toplevel 2>/dev/null) || {
    echo "nerfhack-rr-fuzz.sh: must be run from within the NerfHack git repository" >&2
    exit 1
}

if [ ! -x "$REPO_ROOT/playground/nerfhack" ]; then
    echo "nerfhack-rr-fuzz.sh: $REPO_ROOT/playground/nerfhack not found." >&2
    echo "Build and install first:" >&2
    echo "  sh sys/unix/setup.sh sys/unix/hints/linux.500   # or macOS.500" >&2
    echo "  make fetch-lua && make all && make install" >&2
    exit 1
fi

cd "$REPO_ROOT"

: "${NH_FUZZER_MAXTURNS:=50000}"
: "${FUZZ_SESSIONS_DIR:=$REPO_ROOT/fuzz-sessions}"
BACKTRACE_GDB="$REPO_ROOT/sys/unix/nerfhack-rr-backtrace.gdb"
SUMMARY_LOG="$FUZZ_SESSIONS_DIR/fuzz-summary.log"
# A session that dies by signal (the crashes this whole loop exists to
# find) skips the normal end-of-game cleanup and leaves its save/level
# files behind as playground/<uid>wizard.*. Left in place, the next
# session then blocks on "Old game in progress?" - which the pty
# keepalive answers with its displayed default, Cancel - turning every
# session after a crash into an instant no-op until removed.
SAVE_GLOB="$REPO_ROOT/playground/$(id -u)wizard".*

mkdir -p "$FUZZ_SESSIONS_DIR"

stop=0
child_pid=""
# A trap only runs between commands; it doesn't touch a foreground child
# the shell is already blocked on inside wait, and that child (the
# python3 session helper, and rr/nerfhack under it) would otherwise be
# abandoned running in the background once this script exits. Run it in
# the background instead and explicitly signal it here so it can shut
# its own child down too (see nerfhack-rr-session.py).
on_signal() {
    stop=1
    [ -n "$child_pid" ] && kill -TERM "$child_pid" 2>/dev/null
}
trap on_signal INT TERM

n=0
echo "nerfhack-rr-fuzz.sh: looping in $FUZZ_SESSIONS_DIR (turn cap $NH_FUZZER_MAXTURNS); Ctrl-C to stop after the current session." >&2

while [ "$stop" -eq 0 ]; do
    n=$((n + 1))
    session_id=$(date +%Y%m%d-%H%M%S)-$(printf '%05d' "$n")
    session_dir="$FUZZ_SESSIONS_DIR/$session_id"
    trace_dir="$session_dir/trace"
    mkdir -p "$session_dir"

    rm -f $SAVE_GLOB

    # NetHack's tty port needs a real pty (a plain pipe on stdin won't do),
    # and --debug:fuzzer's internal command-choice hijacking doesn't cover
    # every outer meta-prompt (post-death "Do you want to keep the save
    # file?", --More--, etc.) - those are real terminal reads that would
    # hang the loop forever with nobody there to answer them. The Python
    # helper allocates the pty and sends a bare Enter whenever the child
    # goes quiet, which only ever fires on one of these stuck prompts.
    set +e
    "$PYTHON3" "$REPO_ROOT/sys/unix/nerfhack-rr-session.py" \
        "$session_dir/session.log" \
        rr record \
        -v "NH_FUZZER_MAXTURNS=$NH_FUZZER_MAXTURNS" \
        -v "ASAN_OPTIONS=abort_on_error=1:${ASAN_OPTIONS:-}" \
        -v "UBSAN_OPTIONS=abort_on_error=1:${UBSAN_OPTIONS:-}" \
        -o "$trace_dir" \
        "$@" \
        playground/nerfhack -D -u wizard -@ --debug:fuzzer &
    child_pid=$!
    wait "$child_pid"
    status=$?
    child_pid=""
    set -e

    # A fatal signal (impossible() -> panic() -> abort(), an ASAN/UBSAN
    # abort, or a raw SIGSEGV/etc.) surfaces here as the traditional shell
    # convention of exit status 128+signum, i.e. > 128. A plain nonzero
    # exit() (e.g. the game failing to start at all in a tty-less
    # environment) is not a fuzzing find and would otherwise flood the
    # session directory with noise, so only signal deaths count as crashes.
    # A deliberate stop (on_signal killed this very session to shut down)
    # isn't a finding either, however it exited.
    if [ "$status" -le 128 ] || [ "$stop" -eq 1 ]; then
        echo "$(date -Iseconds)  $session_id  exit=$status  clean" >>"$SUMMARY_LOG"
        rm -rf "$session_dir"
        continue
    fi

    echo "$(date -Iseconds)  $session_id  exit=$status  CRASH" >>"$SUMMARY_LOG"
    echo "nerfhack-rr-fuzz.sh: crash in $session_id (exit $status), see $session_dir" >&2

    if [ -d "$trace_dir" ]; then
        # -batch (and -x as a debugger-option after --) run before rr's
        # own local .gdbinit gets to issue its "target remote" - the
        # commands need to go in over stdin instead, exactly as if typed
        # at the interactive prompt, so they run after that connection is
        # up. -q suppresses replaying the tracee's own screen output,
        # which otherwise dwarfs the actual gdb transcript.
        timeout "${BACKTRACE_TIMEOUT:-900}" rr replay -q "$trace_dir" \
            <"$BACKTRACE_GDB" >"$session_dir/backtrace.txt" 2>&1 || true
    else
        echo "nerfhack-rr-fuzz.sh: no trace directory produced for $session_id" \
            >"$session_dir/backtrace.txt"
    fi
done

echo "nerfhack-rr-fuzz.sh: stopped after $n session(s). Summary: $SUMMARY_LOG" >&2
