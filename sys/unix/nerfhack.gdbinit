# NerfHack GDB init script
#
# Debugging helper for running NerfHack under GDB from a source-tree
# ("playground") install. Intended to be loaded via sys/unix/nerfhack-gdb.sh,
# which cd's to the repository root first so the relative paths below
# resolve correctly.

set auto-load safe-path /

set logging file error.txt

#export ASAN_OPTIONS="log_path=asan"

# Debug in wizmode
set args -D -u wizard 2>err.log

# Steps to restore a saved game for debugging:
#   1. Get the compressed save file
#   2. Put it in playground/var/save (or wherever HACKDIR resolved to for
#      your build - see sys/unix/hints/include/dirs-perms.500)
#   3. Name it 1000wizard

# To debug a restored game instead of starting a new one, replace the
# 'set args' line above with something like:
#   set args -u <username> 2>err.log
#
# To attach to an already-running process instead:
#   gdb -p $(pidof nerfhack)

file playground/nerfhack

run
