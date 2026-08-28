#!/bin/sh
# nerfhack-gdb.sh - launch NerfHack under GDB using a source-tree install.
#
# Locates the repository root, changes into it (so the relative paths in
# nerfhack.gdbinit resolve correctly regardless of where this script was
# invoked from), and starts GDB with the debug session pre-configured to
# run the game in wizard mode.
#
# Usage:
#   sys/unix/nerfhack-gdb.sh
#
# Requires a source-tree install (see sys/unix/hints/include/dirs-perms.500):
#   sh sys/unix/setup.sh sys/unix/hints/linux.500   # or macOS.500
#   make fetch-lua
#   make all
#   make install

set -e

REPO_ROOT=$(git rev-parse --show-toplevel 2>/dev/null) || {
    echo "nerfhack-gdb.sh: must be run from within the NerfHack git repository" >&2
    exit 1
}

GDBINIT="$REPO_ROOT/sys/unix/nerfhack.gdbinit"
if [ ! -f "$GDBINIT" ]; then
    echo "nerfhack-gdb.sh: cannot find $GDBINIT" >&2
    exit 1
fi

if [ ! -x "$REPO_ROOT/playground/nerfhack" ]; then
    echo "nerfhack-gdb.sh: $REPO_ROOT/playground/nerfhack not found." >&2
    echo "Build and install first:" >&2
    echo "  sh sys/unix/setup.sh sys/unix/hints/linux.500   # or macOS.500" >&2
    echo "  make fetch-lua && make all && make install" >&2
    exit 1
fi

cd "$REPO_ROOT"
exec gdb -x "$GDBINIT" "$@"
