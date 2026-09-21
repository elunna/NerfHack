#!/bin/sh
# Copyright (c) Erik Lunna, 2025-2026.
# NetHack may be freely redistributed.  See license for details.
#
# Run the Lua test scripts in test/ against the installed game.
#
# Each script needs a live game -- a hero, a level, an inventory -- but no
# input, so the game runs them itself: NH_LUA_TESTS names the files to run
# once the first turn is reached, NH_LUA_TESTS_OUT names a file to write
# "PASS <file>" / "FAIL <file>" lines to, and the game then exits.  That
# replaces the old routine of copying the scripts into the playground
# directory and typing #wizloadlua at each of them in turn.
#
# Each script gets its own game, because several of them are destructive:
# test_lev.lua rebuilds the current level once per special level, test_des
# and test_sel reset it repeatedly, testmove pushes keys into the command
# queue.  One failure therefore can't take the rest down with it.
#
# Usage:
#   sh sys/unix/nerfhack-lua-tests.sh [file.lua ...]
#
# With no arguments it runs every test/*.lua.  Exit status is 0 when they
# all pass.  nerfhack-rr-fuzz.sh runs this at startup; set
# FUZZ_SKIP_LUA_TESTS=1 there to skip it.
#
# Environment:
#   LUA_TESTS_DIR     where the scripts live (default: <repo>/test)
#   LUA_TEST_TIMEOUT  seconds to allow one script (default: 300)
#   NERFHACKOPTIONS   rcfile (default: the fuzzing one, which selects tty)
#   NERFHACK_BIN      game to run (default: <repo>/playground/nerfhack), so
#                     a fresh build can be checked without installing it

set -u

PYTHON3=$(command -v python3) || {
    echo "nerfhack-lua-tests.sh: python3 is not installed or not on PATH." >&2
    exit 1
}

REPO_ROOT=$(git rev-parse --show-toplevel 2>/dev/null) || {
    echo "nerfhack-lua-tests.sh: must be run from within the NerfHack git repository" >&2
    exit 1
}

: "${NERFHACK_BIN:=$REPO_ROOT/playground/nerfhack}"
if [ ! -x "$NERFHACK_BIN" ]; then
    echo "nerfhack-lua-tests.sh: $NERFHACK_BIN not found; build and install first." >&2
    exit 1
fi

cd "$REPO_ROOT"

# the tty port needs a usable terminfo entry even with nobody watching
case "${TERM:-}" in
    "" | dumb) TERM=xterm-256color ;;
esac
export TERM

: "${LUA_TESTS_DIR:=$REPO_ROOT/test}"
: "${LUA_TEST_TIMEOUT:=300}"
: "${NERFHACKOPTIONS:=$REPO_ROOT/sys/unix/nerfhack-fuzz.nerfhackrc}"
export NERFHACKOPTIONS
# These scripts create objects and levels and then the game exits without
# tearing any of it down, so the leak checker has plenty to say and none
# of it is about the tests.  Leaks are the fuzzer's job, not this suite's.
ASAN_OPTIONS="detect_leaks=0:${ASAN_OPTIONS:-}"
export ASAN_OPTIONS

# a crashed or interrupted run leaves save/level files that would make the
# next game stop at "Old game in progress?"
SAVE_GLOB="$REPO_ROOT/playground/$(id -u)wizard".*
SAVEFILE_GLOB="$REPO_ROOT/playground/save/$(id -u)wizard"*
clean_saves() {
    rm -f $SAVE_GLOB $SAVEFILE_GLOB 2>/dev/null || true
}

if [ "$#" -gt 0 ]; then
    tests=$*
else
    tests=$(ls "$LUA_TESTS_DIR"/*.lua 2>/dev/null)
fi
if [ -z "$tests" ]; then
    echo "nerfhack-lua-tests.sh: no test scripts found in $LUA_TESTS_DIR" >&2
    exit 1
fi

workdir=$(mktemp -d "${TMPDIR:-/tmp}/nerfhack-lua-tests.XXXXXX")
trap 'rm -rf "$workdir"' EXIT INT TERM

passed=0
failed=0
failed_names=""

for t in $tests; do
    name=$(basename "$t")
    resfile="$workdir/result"
    logfile="$workdir/log"
    rm -f "$resfile" "$logfile"
    clean_saves

    NH_LUA_TESTS="$t" NH_LUA_TESTS_OUT="$resfile" \
    timeout "$LUA_TEST_TIMEOUT" \
        "$PYTHON3" "$REPO_ROOT/sys/unix/nerfhack-rr-session.py" \
        "$logfile" \
        "$NERFHACK_BIN" -D -u wizard -@ -p Valkyrie -r Human \
        >/dev/null 2>&1
    status=$?

    # the result file is the source of truth; the exit status tells us
    # about the game rather than about the test
    if [ -s "$resfile" ] && grep -q "^PASS " "$resfile"; then
        echo "PASS  $name"
        passed=$((passed + 1))
    elif [ -s "$resfile" ] && grep -q "^FAIL " "$resfile"; then
        echo "FAIL  $name"
        sed 's/\x1b\[[0-9;?]*[a-zA-Z]//g' "$logfile" 2>/dev/null \
            | tr -d '\r' | grep -a -o "Lua error:[^)]*)" | head -1 \
            | sed 's/^/        /'
        failed=$((failed + 1))
        failed_names="$failed_names $name"
    else
        # no verdict at all: the game never reached the first turn, was
        # killed by the timeout, or died on the way
        if [ "$status" -gt 128 ]; then
            echo "CRASH $name (signal $((status - 128)))"
        else
            echo "ERROR $name (no result, exit $status)"
        fi
        failed=$((failed + 1))
        failed_names="$failed_names $name"
    fi
done

clean_saves
echo "lua tests: $passed passed, $failed failed"
if [ "$failed" -gt 0 ]; then
    echo "failing:$failed_names"
    exit 1
fi
exit 0
