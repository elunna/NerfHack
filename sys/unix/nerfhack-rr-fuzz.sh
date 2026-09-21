#!/bin/sh
# Copyright (c) Erik Lunna, 2025-2026.
# NetHack may be freely redistributed.  See license for details.
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
#   NH_FUZZER_LEAKCHECK  turns between mid-session LeakSanitizer checks
#                        (default 1000; also runs on every level change;
#                        0 disables) -- a leak is then fatal within that
#                        window instead of only being reported at exit
#   NH_FUZZER_SAVERESTORE
#                        turns between save-and-restore cycles (default
#                        2500; 0 disables): the game saves itself and exits
#                        with status 7, and the same session is relaunched
#                        so it restores the save (a fresh rr trace per
#                        launch: trace, trace-r1, trace-r2, ...).  Nothing
#                        else exercises restoring a long session's state.
#   NH_FUZZER_PROFILES   directory of scenario profiles (default:
#                        sys/unix/fuzz-profiles): Lua scripts the game runs
#                        on turn 1 and after every level change to seed the
#                        level with the things that profile wants exercised.
#                        Sessions rotate through the profiles plus one
#                        unseeded baseline; the summary line names the
#                        profile.  Set to an empty string to disable.
#                        A profile can also end the game -- let deaths
#                        stand (nh.fuzz_die) or walk the hero out of the
#                        dungeon (nh.fuzz_escape), see fuzz-profiles/README:
#                        the dump files are written beside the trace
#                        (NH_FUZZER_DUMPLOG names them), a cleanly ended
#                        session's are kept as dumplogs/<session>.{txt,html},
#                        and the summary line gets
#                        end=died|escaped|ascended|turncap.
#   FUZZ_SKIP_LUA_TESTS  set to 1 to skip the Lua test suite that otherwise
#                        runs once at startup (sys/unix/nerfhack-lua-tests.sh,
#                        the scripts in test/).  They exercise the des-file
#                        commands, the selection and object APIs and every
#                        special level, which random keystrokes never reach;
#                        a failure is reported and fuzzing continues.
#   FUZZ_FLAP_LIMIT      stop the loop once this many sessions in a row have
#                        exited nonzero within FUZZ_FLAP_SECONDS (default
#                        5; 0 disables) of starting.  A session that ends
#                        that fast never got to fuzz anything: the wizard
#                        save slot is held by another game ("There is
#                        already a game in progress under your name"), rr
#                        can't record any more, the install is broken, or
#                        the game crashes before turn 1 every time.  Left
#                        alone, the loop would spin through thousands of
#                        useless sessions until someone noticed.
#   FUZZ_FLAP_SECONDS    the "that fast" threshold (default 10)
#   FUZZ_SESSIONS_DIR    where session directories are kept
#                         (default: <repo>/fuzz-sessions)
#   NERFHACKOPTIONS      rcfile used for every session (default:
#                        sys/unix/nerfhack-fuzz.nerfhackrc, a minimal config
#                        independent of any player's own $HOME/.nerfhackrc,
#                        so fuzzing runs stay representative of ordinary
#                        play instead of one player's customizations);
#                        set to your own path (or a bare "@filename") to
#                        override
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
: "${NH_FUZZER_LEAKCHECK:=1000}"
: "${NH_FUZZER_SAVERESTORE:=10000}"
: "${NH_FUZZER_PROFILES=$REPO_ROOT/sys/unix/fuzz-profiles}"
: "${FUZZ_SESSIONS_DIR:=$REPO_ROOT/fuzz-sessions}"
: "${FUZZ_FLAP_LIMIT:=5}"
: "${FUZZ_FLAP_SECONDS:=10}"
: "${NERFHACKOPTIONS:=$REPO_ROOT/sys/unix/nerfhack-fuzz.nerfhackrc}"
BACKTRACE_GDB="$REPO_ROOT/sys/unix/nerfhack-rr-backtrace.gdb"
SUMMARY_LOG="$FUZZ_SESSIONS_DIR/fuzz-summary.log"
# A session that dies by signal (the crashes this whole loop exists to
# find) skips the normal end-of-game cleanup and leaves its save/level
# files behind as playground/<uid>wizard.*. Left in place, the next
# session then blocks on "Old game in progress?" - which the pty
# keepalive answers with its displayed default, Cancel - turning every
# session after a crash into an instant no-op until removed.
SAVE_GLOB="$REPO_ROOT/playground/$(id -u)wizard".*
# the real save file, left behind by a save-and-restore cycle that never
# got restored (crash, shutdown); a new session must start from scratch
SAVEFILE_GLOB="$REPO_ROOT/playground/save/$(id -u)wizard"*

mkdir -p "$FUZZ_SESSIONS_DIR"

# The Lua test scripts check things the fuzzer's random keystrokes never
# reach -- the des-file commands, the selection and object APIs, and that
# every special level still builds.  Run them once before settling into the
# fuzzing loop; report a failure but keep going, since a broken test script
# is not a reason to stop looking for crashes.
if [ "${FUZZ_SKIP_LUA_TESTS:-0}" != "1" ] \
   && [ -x "$REPO_ROOT/sys/unix/nerfhack-lua-tests.sh" ]; then
    echo "nerfhack-rr-fuzz.sh: running the Lua test suite" >&2
    lua_tests_log="$FUZZ_SESSIONS_DIR/lua-tests.log"
    if sh "$REPO_ROOT/sys/unix/nerfhack-lua-tests.sh" >"$lua_tests_log" 2>&1; then
        echo "$(date -Iseconds)  lua-tests  $(tail -1 "$lua_tests_log")" \
            >>"$SUMMARY_LOG"
    else
        echo "$(date -Iseconds)  lua-tests  FAILED  $(tail -2 "$lua_tests_log" | tr '\n' ' ')" \
            >>"$SUMMARY_LOG"
        echo "nerfhack-rr-fuzz.sh: Lua tests failed, see $lua_tests_log" >&2
    fi
    sed 's/^/  /' "$lua_tests_log" >&2
fi

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

# The flap guard (see FUZZ_FLAP_LIMIT above).  Called after every session
# with its exit status and wall-clock seconds; a nonzero exit that came
# almost at once counts, anything else resets the count.  Once the limit
# is reached the session directory is left in place, the last lines the
# game or rr printed are shown (that is where "There is already a game in
# progress" or rr's own complaint ends up) and the loop stops.
flap_check() {
    _status=$1 _elapsed=$2
    if [ "$FUZZ_FLAP_LIMIT" -le 0 ] || [ "$stop" -ne 0 ] \
       || [ "$_status" -eq 0 ] || [ "$_elapsed" -ge "$FUZZ_FLAP_SECONDS" ]; then
        flaps=0
        return 0
    fi
    flaps=$((flaps + 1))
    [ "$flaps" -lt "$FUZZ_FLAP_LIMIT" ] && return 0
    echo "$(date -Iseconds)  flap-guard  stopped: $flaps sessions in a row exited nonzero within ${FUZZ_FLAP_SECONDS}s (last: $session_id exit=$_status)" \
        >>"$SUMMARY_LOG"
    echo "nerfhack-rr-fuzz.sh: stopping - the last $flaps sessions all exited nonzero within ${FUZZ_FLAP_SECONDS}s, so nothing is being fuzzed." >&2
    echo "nerfhack-rr-fuzz.sh: last session: $session_id (exit $_status), kept in $session_dir" >&2
    if [ -s "$session_log" ]; then
        echo "nerfhack-rr-fuzz.sh: its last output was:" >&2
        sed 's/\x1b\[[0-9;?]*[a-zA-Z]//g' "$session_log" | tr -d '\r' \
            | grep -a -v '^[[:space:]]*$' | tail -6 | sed 's/^/  | /' >&2
    fi
    if [ "$_status" -gt 128 ]; then
        echo "nerfhack-rr-fuzz.sh: it died by signal before turn 1; see $session_dir/backtrace.txt" >&2
    else
        echo "nerfhack-rr-fuzz.sh: usual causes: another wizard-mode game holds playground/$(id -u)wizard.* (a hand-run -D game), rr can't record (kernel/perf change), or a stale install." >&2
    fi
    exit 1
}

n=0
flaps=0 # consecutive sessions that exited nonzero almost at once
nprof_total=0
if [ -n "$NH_FUZZER_PROFILES" ] && [ -d "$NH_FUZZER_PROFILES" ]; then
    for p in "$NH_FUZZER_PROFILES"/*.lua; do
        [ -f "$p" ] && nprof_total=$((nprof_total + 1))
    done
fi
echo "nerfhack-rr-fuzz.sh: looping in $FUZZ_SESSIONS_DIR (turn cap $NH_FUZZER_MAXTURNS, rcfile $NERFHACKOPTIONS, $nprof_total profiles); Ctrl-C to stop after the current session." >&2

while [ "$stop" -eq 0 ]; do
    n=$((n + 1))
    session_id=$(date +%Y%m%d-%H%M%S)-$(printf '%05d' "$n")
    session_dir="$FUZZ_SESSIONS_DIR/$session_id"
    trace_dir="$session_dir/trace"
    mkdir -p "$session_dir"

    rm -f $SAVE_GLOB
    rm -f $SAVEFILE_GLOB

    # scenario profile for this session: round-robin through the profile
    # directory, with slot 0 as the unseeded baseline
    profile=""
    if [ "$nprof_total" -gt 0 ]; then
        slot=$((n % (nprof_total + 1)))
        i=0
        for p in "$NH_FUZZER_PROFILES"/*.lua; do
            [ -f "$p" ] || continue
            i=$((i + 1))
            [ "$i" -eq "$slot" ] && profile="$p"
        done
    fi
    profile_name=$(basename "${profile:-none}" .lua)
    echo "$profile_name" >"$session_dir/profile"

    # NetHack's tty port needs a real pty (a plain pipe on stdin won't do),
    # and --debug:fuzzer's internal command-choice hijacking doesn't cover
    # every outer meta-prompt (post-death "Do you want to keep the save
    # file?", --More--, etc.) - those are real terminal reads that would
    # hang the loop forever with nobody there to answer them. The Python
    # helper allocates the pty and sends a bare Enter whenever the child
    # goes quiet, which only ever fires on one of these stuck prompts.
    saveat=$NH_FUZZER_SAVERESTORE
    restarts=0
    session_log="$session_dir/session.log"
    session_start=$(date +%s)
    while :; do
        set +e
        "$PYTHON3" "$REPO_ROOT/sys/unix/nerfhack-rr-session.py" \
            "$session_log" \
            rr record \
            -v "NH_FUZZER_MAXTURNS=$NH_FUZZER_MAXTURNS" \
            -v "NH_FUZZER_LEAKCHECK=$NH_FUZZER_LEAKCHECK" \
            -v "NH_FUZZER_SETUP=$profile" \
            -v "NH_FUZZER_SAVEAT=$saveat" \
            -v "NH_FUZZER_DUMPLOG=$session_dir/dumplog" \
            -v "NERFHACKOPTIONS=$NERFHACKOPTIONS" \
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
        # the game saved itself: relaunch the same session so it restores
        # (each launch gets its own trace so a crash during or after the
        # restore is recorded from the start of that process)
        if [ "$status" -eq 7 ] && [ "$stop" -eq 0 ] && [ "$restarts" -lt 200 ]; then
            restarts=$((restarts + 1))
            saveat=$((saveat + NH_FUZZER_SAVERESTORE))
            trace_dir="$session_dir/trace-r$restarts"
            session_log="$session_dir/session-r$restarts.log"
            continue
        fi
        break
    done
    elapsed=$(( $(date +%s) - session_start ))

    # A fatal signal (impossible() -> panic() -> abort(), an ASAN/UBSAN
    # abort, or a raw SIGSEGV/etc.) surfaces here as the traditional shell
    # convention of exit status 128+signum, i.e. > 128. A plain nonzero
    # exit() (e.g. the game failing to start at all in a tty-less
    # environment) is not a fuzzing find and would otherwise flood the
    # session directory with noise, so only signal deaths count as crashes.
    # A deliberate stop (on_signal killed this very session to shut down)
    # isn't a finding either, however it exited.
    # how the session ended: a dumplog means the game really ended, and the
    # fuzzer announces in the session log whether a profile let a death
    # stand or walked the hero out (nh.fuzz_die / nh.fuzz_escape)
    ending=turncap
    if [ -s "$session_dir/dumplog.txt" ]; then
        if grep -a -q 'You ascend to the status of Demigod' "$session_log" 2>/dev/null; then
            ending=ascended
        else
            case "$(grep -a -o 'Fuzzer: \(letting this death stand\|escape armed\|forcing the escape\|ascension armed\)' "$session_log" 2>/dev/null | tail -1)" in
                *"death stand"*) ending=died ;;
                *escape*) ending=escaped ;;
                *ascension*) ending=ascended ;;
                *) ending=ended ;;
            esac
        fi
    fi

    if [ "$status" -le 128 ] || [ "$stop" -eq 1 ]; then
        echo "$(date -Iseconds)  $session_id  exit=$status  clean  profile=$profile_name  restores=$restarts  end=$ending" >>"$SUMMARY_LOG"
        # keep the end-of-game dump files (small) for a look at their
        # formatting; everything else about a clean session goes
        if [ -s "$session_dir/dumplog.txt" ]; then
            mkdir -p "$FUZZ_SESSIONS_DIR/dumplogs"
            mv "$session_dir/dumplog.txt" "$FUZZ_SESSIONS_DIR/dumplogs/$session_id.txt"
            [ -s "$session_dir/dumplog.html" ] \
                && mv "$session_dir/dumplog.html" "$FUZZ_SESSIONS_DIR/dumplogs/$session_id.html"
        fi
        rm -f $SAVEFILE_GLOB
        # (session_dir is still here for the guard's diagnostic if it fires)
        flap_check "$status" "$elapsed"
        rm -rf "$session_dir"
        continue
    fi

    echo "nerfhack-rr-fuzz.sh: crash in $session_id (exit $status), see $session_dir" >&2
    # keep the save file the crashed process was restored from (or was
    # about to leave behind) next to the trace for reproduction
    for f in $SAVEFILE_GLOB; do
        [ -f "$f" ] && mv "$f" "$session_dir/"
    done

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

    # the first frame of the backtrace that isn't the abort/sanitizer/
    # panic plumbing, so the summary shows at a glance which sessions of
    # a batch died the same way
    top=$(awk '
        /^#[0-9]+ / {
            if (match($0, / in [A-Za-z_][A-Za-z_0-9]*/)) {
                fn = substr($0, RSTART + 4, RLENGTH - 4)
                if (fn ~ /^(raise|abort|panic|impossible|NH_abort|NH_panictrace_libc|panictrace_handler|_start|main)$/ || fn ~ /^__/)
                    next
                loc = ""
                if (match($0, / at [^ ]+:[0-9]+/))
                    loc = substr($0, RSTART + 4, RLENGTH - 4)
                print fn (loc != "" ? "@" loc : "")
                exit
            }
        }' "$session_dir/backtrace.txt" 2>/dev/null)
    echo "$(date -Iseconds)  $session_id  exit=$status  CRASH  profile=$profile_name  restores=$restarts  end=$ending  top=${top:-?}" >>"$SUMMARY_LOG"
    flap_check "$status" "$elapsed"
done

echo "nerfhack-rr-fuzz.sh: stopped after $n session(s). Summary: $SUMMARY_LOG" >&2
