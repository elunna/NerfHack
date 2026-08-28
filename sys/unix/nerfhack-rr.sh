#!/bin/sh
# nerfhack-rr.sh - record a NerfHack fuzzing session with rr, then replay it.
#
# Starts the game with the built-in fuzz tester enabled from the very first
# turn (--debug:fuzzer), recorded under rr. The fuzzer plays randomly until
# it triggers an impossible() panic, which makes an ideal, self-contained
# stopping point for a recording. Once rr record exits (whether from a
# panic or a manual interrupt), this drops straight into `rr replay` so you
# can reverse-debug the run that led there.
#
# Usage:
#   sys/unix/nerfhack-rr.sh [rr-record-options]
#
# Any arguments are forwarded to `rr record` itself (e.g. -h/--chaos to
# randomize scheduling, or -n/--no-syscall-buffer), not to the game.
#
# Requires:
#   - rr (https://rr-project.org/) - Linux only, needs hardware
#     performance-counter access. If you hit a perf_event_paranoid error,
#     follow the fix rr prints (usually lowering
#     /proc/sys/kernel/perf_event_paranoid via sysctl).
#   - a source-tree install (see sys/unix/hints/include/dirs-perms.500):
#       sh sys/unix/setup.sh sys/unix/hints/linux.500
#       make fetch-lua && make all && make install

set -e

if ! command -v rr >/dev/null 2>&1; then
    echo "nerfhack-rr.sh: rr is not installed or not on PATH." >&2
    echo "See https://rr-project.org/ for installation instructions." >&2
    exit 1
fi

REPO_ROOT=$(git rev-parse --show-toplevel 2>/dev/null) || {
    echo "nerfhack-rr.sh: must be run from within the NerfHack git repository" >&2
    exit 1
}

if [ ! -x "$REPO_ROOT/playground/nerfhack" ]; then
    echo "nerfhack-rr.sh: $REPO_ROOT/playground/nerfhack not found." >&2
    echo "Build and install first:" >&2
    echo "  sh sys/unix/setup.sh sys/unix/hints/linux.500   # or macOS.500" >&2
    echo "  make fetch-lua && make all && make install" >&2
    exit 1
fi

cd "$REPO_ROOT"

# Capture the trace directory rr actually used (via -p) instead of trusting
# `rr replay`'s no-argument "latest-trace" default, which is a global
# pointer shared by every rr session on the machine, not just this one. If a
# recording fails to complete, latest-trace is left pointing at whatever rr
# session last succeeded - possibly an old, unrelated trace - and replaying
# that silently is confusing at best.
tracedir_file=$(mktemp)
trap 'rm -f "$tracedir_file"' EXIT

# rr record's exit status mirrors the recorded program's exit status, and a
# fuzzer crash (the case we most want to replay) is exactly that: a non-zero
# exit. So don't let a "failure" here abort the script - always fall through
# and check whether a trace directory actually got produced.
set +e
rr record -p 3 3>"$tracedir_file" "$@" playground/nerfhack -D -u wizard --debug:fuzzer 2>err.log
set -e

trace_dir=$(cat "$tracedir_file")
if [ -z "$trace_dir" ] || [ ! -d "$trace_dir" ]; then
    echo "nerfhack-rr.sh: rr record did not produce a trace directory." >&2
    echo "See err.log for the game's stderr output." >&2
    exit 1
fi

exec rr replay "$trace_dir"
