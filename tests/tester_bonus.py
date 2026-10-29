#!/usr/bin/env python3
"""Tester for the bonus checker of push_swap.

Build it first with "make bonus". Usage (from the root of the project):
    ./tests/tester_bonus.py                      every test below, except valgrind
    ./tests/tester_bonus.py norminette           norminette on every .c and .h file
    ./tests/tester_bonus.py valgrind             handwritten cases under valgrind
    ./tests/tester_bonus.py random SIZE [TRIES]  TRIES random lists of SIZE numbers
                                                 with random instructions

Most tests compare ./checker with the checker of 42 (checker_linux): for the
same arguments and the same instructions, both must print the same thing on
stdout and stderr. The exit code is not compared (the subject doesn't define
it, checker_linux exits 255 on error), we only check that ./checker didn't
crash, time out or leak.
"""

import argparse
import random
from itertools import permutations

# The helpers, the cases on the arguments and the counters are shared with
# the tester of push_swap, so they're imported instead of copied.
# Python finds tester.py because it is in the same folder as this script.
import tester
from tester import (
    CHECKER,
    ERROR_CASES,
    INT_MAX,
    INT_MIN,
    VALGRIND,
    VALID_CASES,
    check,
    describe,
    run,
    valgrind_log,
)

BONUS = "./checker"

INSTRUCTIONS = ["sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"]

# (name, arguments, instructions given on stdin): invalid instructions,
# ./checker must print the same thing as checker_linux ("Error\n" on stderr)
INSTRUCTION_ERROR_CASES = [
    ("unknown instruction", ["2", "1"], "foo\n"),
    ("uppercase", ["2", "1"], "SA\n"),
    ("space after", ["2", "1"], "sa \n"),
    ("space before", ["2", "1"], " sa\n"),
    ("tab after", ["2", "1"], "sa\t\n"),
    ("too long", ["2", "1"], "saa\n"),
    ("too short", ["2", "1"], "s\n"),
    ("4 letters", ["2", "1"], "rrrr\n"),
    ("two on one line", ["2", "1"], "sa sb\n"),
    ("empty line", ["2", "1"], "\n"),
    ("empty line after valid", ["2", "1"], "sa\n\n"),
    ("empty line between valid", ["3", "2", "1"], "sa\n\nra\n"),
    ("error after valid", ["2", "1"], "sa\nfoo\n"),
    ("valid after error", ["2", "1"], "foo\nsa\n"),
    ("windows line ending", ["2", "1"], "sa\r\n"),
    # checker_linux refuses an instruction that isn't followed by "\n"
    ("no newline at the end", ["2", "1"], "sa"),
]

# (name, arguments, instructions): valid instructions, including the ones
# that do nothing (swap or push from an empty stack)
INSTRUCTION_CASES = [
    ("no instruction, sorted", ["1", "2"], ""),
    ("no instruction, not sorted", ["2", "1"], ""),
    ("sorted after sa", ["2", "1"], "sa\n"),
    ("not sorted after sa", ["1", "2"], "sa\n"),
    ("stack b not empty", ["1", "2"], "pb\n"),
    ("everything in b", ["1", "2", "3"], "pb\npb\npb\n"),
    ("push back from b", ["1", "2", "3"], "pb\npb\npa\npa\n"),
    ("pa with b empty", ["1", "2"], "pa\n"),
    ("sb with b empty", ["1", "2"], "sb\n"),
    ("ss with b empty", ["1", "2"], "ss\n"),
    ("rb with b empty", ["1", "2"], "rb\n"),
    ("rrb with b empty", ["1", "2"], "rrb\n"),
    ("rr with b empty", ["1", "2", "3"], "rr\n"),
    ("rrr with b empty", ["1", "2", "3"], "rrr\n"),
    ("sb with one in b", ["1", "2"], "pb\nsb\npa\n"),
    ("pb with a empty", ["1"], "pb\npb\npa\n"),
    ("one number, every instruction", ["42"], "\n".join(INSTRUCTIONS) + "\n"),
    ("rotate back", ["3", "1", "2"], "ra\nrra\n"),
    ("full rotation", ["1", "2", "3"], "ra\nra\nra\n"),
    ("int limits", ["2147483647", "-2147483648"], "sa\n"),
    ("single string", ["3 2 1"], "sa\nrra\n"),
]


def run_bonus(args, stdin=""):
    """Run ./checker, under valgrind if the valgrind mode is enabled."""
    if tester.use_valgrind:
        return run(VALGRIND + [BONUS] + args, stdin, timeout=30)
    return run([BONUS] + args, stdin)


def exited(code):
    """True if the program ended by itself: no timeout, no crash, and no
    valgrind error (valgrind replaces the exit code by 42)."""
    if code is None or code < 0:
        return False
    return not (tester.use_valgrind and code == 42)


def compare(name, args, stdin):
    """Give the same input to ./checker and checker_linux, they must print the
    same thing on stdout and stderr."""
    out, err, code = run_bonus(args, stdin)
    r_out, r_err, _ = run([CHECKER] + args, stdin)
    check(
        name,
        out == r_out and err == r_err and exited(code),
        f"stdout={out!r} stderr={err!r} {describe(code)}, "
        f"expected stdout={r_out!r} stderr={r_err!r}{valgrind_log()}",
    )


def short(text, limit=80):
    """Cut a long text (500 arguments...) so a KO stays readable."""
    return text if len(text) <= limit else text[:limit] + "..."


def test_arg_errors():
    """The checker must refuse the same arguments as push_swap.
    They are compared with the rules of push_swap, not with checker_linux,
    because checker_linux accepts some of them ("+1", "0001", "3 2" "1")."""
    print("Argument errors:")

    for name, args in ERROR_CASES:
        out, err, code = run_bonus(args, "sa\n")
        check(
            name,
            err == "Error\n" and out == "" and exited(code),
            f"stdout={out!r} stderr={err!r} {describe(code)}{valgrind_log()}",
        )


def test_valid_args():
    """For each valid case of push_swap, give the output of push_swap to both
    checkers: they must both answer OK."""
    print("\nValid arguments:")

    for name, args, _ in VALID_CASES:
        # push_swap is not run under valgrind: only the checker is tested here
        instructions, _, _ = run(["./push_swap"] + args)
        out, err, code = run_bonus(args, instructions)
        r_out, _, _ = run([CHECKER] + args, instructions)
        # Without arguments, both checkers print nothing
        expected = "OK\n" if args else ""
        check(
            name,
            out == r_out == expected and err == "" and exited(code),
            f"stdout={out!r} stderr={err!r} {describe(code)}, "
            f"checker_linux={r_out!r}{valgrind_log()}",
        )


def test_instruction_errors():
    print("\nInstruction errors:")

    for name, args, stdin in INSTRUCTION_ERROR_CASES:
        compare(name, args, stdin)


def test_instructions():
    print("\nInstructions:")

    for name, args, stdin in INSTRUCTION_CASES:
        compare(name, args, stdin)


def test_permutations(size):
    """Give the output of push_swap for every order of 1..size to both
    checkers. Only one line is printed, plus the failures."""
    total = 0
    errors = []

    for perm in permutations(range(1, size + 1)):
        args = [str(n) for n in perm]
        total += 1
        instructions, _, _ = run(["./push_swap"] + args)
        out, err, code = run_bonus(args, instructions)
        r_out, r_err, _ = run([CHECKER] + args, instructions)
        if out != r_out or err != r_err or not exited(code):
            errors.append(
                f"{' '.join(args)}: stdout={out!r} {describe(code)}, expected {r_out!r}"
            )

    check(f"all {total} permutations of {size}", not errors, f"{len(errors)} failed")
    # Show only the first failures, with the arguments to reproduce them
    for e in errors[:10]:
        print(f"      {e}")


def test_random(size, tries=10):
    """For `tries` random lists of `size` numbers, compare both checkers with:
    - the output of push_swap (must be OK)
    - random valid instructions (most likely KO, stack b often not empty)"""
    errors = []

    for _ in range(tries):
        # range() is lazy, and INT_MAX + 1 so that INT_MAX can be picked too
        args = [str(n) for n in random.sample(range(INT_MIN, INT_MAX + 1), size)]
        instructions, _, _ = run(["./push_swap"] + args)
        moves = [
            random.choice(INSTRUCTIONS) for _ in range(random.randint(0, size * 3))
        ]

        for kind, stdin in [
            ("push_swap output", instructions),
            ("random instructions", "".join(m + "\n" for m in moves)),
        ]:
            out, err, code = run_bonus(args, stdin)
            r_out, r_err, _ = run([CHECKER] + args, stdin)
            if out != r_out or err != r_err or not exited(code):
                errors.append(
                    f"{kind}: stdout={out!r} stderr={err!r} {describe(code)}, "
                    f"expected {r_out!r} {r_err!r}\n"
                    f"        args={short(' '.join(args))}\n"
                    f"        instructions={short(' '.join(stdin.split()))}"
                )

    check(
        f"{tries} random lists of {size} numbers, push_swap output + random instructions",
        not errors,
        f"{len(errors)} failed",
    )
    # Only the first failures: with long lists, more would flood the terminal
    for e in errors[:3]:
        print(f"      {e}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # No mode given (opts.mode is None) runs the default full test suite
    sub = parser.add_subparsers(dest="mode")

    sub.add_parser("norminette", help="norminette on every .c and .h file")
    sub.add_parser("valgrind", help="handwritten cases under valgrind")

    rand = sub.add_parser("random", help="TRIES random lists of SIZE numbers")
    rand.add_argument("size", type=int, help="size of the lists")
    rand.add_argument("tries", type=int, nargs="?", default=10, help="number of lists")

    opts = parser.parse_args()

    if opts.mode == "norminette":
        tester.test_norminette()
    elif opts.mode == "random":
        test_random(opts.size, opts.tries)
    else:
        if opts.mode == "valgrind":
            # Set in the tester module: run_bonus() and valgrind_log() read it there
            tester.use_valgrind = True
        test_arg_errors()
        test_valid_args()
        test_instruction_errors()
        test_instructions()

        # Too slow under valgrind, and the handwritten cases already cover it
        if opts.mode is None:
            print("\nPermutations:")
            for size in range(1, 6):
                test_permutations(size)

            print("\nRandom:")
            for size in [5, 100, 500]:
                test_random(size)

    # The counters live in the tester module, because check() comes from there
    print(f"\n{tester.passed} OK, {tester.failed} KO")
