### what these are

Lua scripts that exercise parts of the game no amount of random play
reaches reliably: the des-file commands, the selection and object APIs,
the config parser, wishing, shop pricing, hero movement, and that every
special level in `dat/` still builds.

### how to run them

    sh sys/unix/nerfhack-lua-tests.sh              # all of them
    sh sys/unix/nerfhack-lua-tests.sh test/test_sel.lua   # just one

Each script needs a live game but no input, so the game runs them itself:
`NH_LUA_TESTS` names the files to run once the first turn is reached,
`NH_LUA_TESTS_OUT` names a file to write `PASS <file>` / `FAIL <file>`
lines to, and the game then exits, 0 if everything passed.  Each script
gets its own game, because several are destructive: `test_lev.lua`
rebuilds the current level once per special level, `test_des.lua` and
`test_sel.lua` reset it repeatedly, `testmove.lua` pushes keys into the
command queue.

`sys/unix/nerfhack-rr-fuzz.sh` runs the suite once at startup and records
the result in its summary log; set `FUZZ_SKIP_LUA_TESTS=1` to skip it.

Useful variables:

 * `NERFHACK_BIN` -- game to run, so a fresh build can be checked without
   installing it (default: `playground/nerfhack`)
 * `LUA_TESTS_DIR` -- where the scripts live (default: `test/`)
 * `LUA_TEST_TIMEOUT` -- seconds allowed per script (default: 300)

Note that `test_lev.lua` loads level files the same way the game does, so
it reads the *installed* data.  Editing something in `dat/` has no effect
on it until the data files are rebuilt and installed.

### running one by hand

Still possible, and no longer needs the files copied anywhere: start the
game in wizard mode and use the `#wizloadlua` extended command with the
script's full path.  A failure shows up as an `impossible` and in
`paniclog`.

### writing one

Signal a failure with `error("what went wrong")`; the game turns that
into an `impossible` and the runner reports the file as FAIL.  Anything
the sandbox offers is available, including `require("<name>")`, which
loads a Lua file from the game's own data by name the way the level
loader does, for a dlb build as well as a plain one.
