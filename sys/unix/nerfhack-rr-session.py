#!/usr/bin/env python3
"""Run one command attached to a real pty, teeing its output to a log file.

--debug:fuzzer drives ordinary NerfHack turns by hijacking command choices
internally rather than reading them from stdin, but a few outer
meta-prompts (the post-death "Do you want to keep the save file?"
question, --More--, etc.) are real terminal reads outside that hook and
would otherwise hang an unattended session forever. There is a real pty
here (NetHack's tty port requires one), just nothing to type into it, so
whenever the child goes quiet for a couple of seconds this sends a bare
Enter to take whatever default is offered. That never fires during actual
play, since the fuzzer keeps the screen busy.

Usage: nerfhack-rr-session.py <logfile> <command> [args...]

Exits with the child's own exit status, or 128+signum if it died from a
signal (SIGABRT from a panic/ASAN/UBSAN abort, SIGSEGV, etc.) - the same
convention the calling shell loop already keys crash detection off of.

A SIGTERM/SIGINT to this process (e.g. the calling loop being stopped)
is forwarded to the child before exiting - rr is a ptrace tracer with
exit-kill semantics, so killing it takes its nerfhack tracee down too.
Without this, the shell loop's own trap has no way to reach a foreground
child it isn't directly wait()ing on, and the session would be silently
orphaned, left running in the background indefinitely.
"""
import signal
import sys

import pexpect

IDLE_TIMEOUT = 2  # seconds of silence before assuming something is stuck


def main():
    if len(sys.argv) < 3:
        print(f"usage: {sys.argv[0]} <logfile> <command> [args...]",
              file=sys.stderr)
        return 2

    logpath = sys.argv[1]
    argv = sys.argv[2:]

    with open(logpath, "wb") as logfile:
        child = pexpect.spawn(argv[0], argv[1:], timeout=None)
        child.logfile_read = logfile

        def forward_and_exit(signum, _frame):
            try:
                child.kill(signum)
            except OSError:
                pass
            sys.exit(128 + signum)

        signal.signal(signal.SIGTERM, forward_and_exit)
        signal.signal(signal.SIGINT, forward_and_exit)

        while True:
            try:
                child.expect(pexpect.EOF, timeout=IDLE_TIMEOUT)
                break
            except pexpect.TIMEOUT:
                try:
                    child.send("\r")
                except OSError:
                    break
        child.close()

    if child.signalstatus is not None:
        return 128 + child.signalstatus
    return child.exitstatus if child.exitstatus is not None else 1


if __name__ == "__main__":
    sys.exit(main())
