#!/usr/bin/env python3
"""Tester for push_swap.

Usage (from the root of the project):
    ./tests/tester.py                         error cases, valid cases,
                                              permutations and benchmarks
    ./tests/tester.py norminette              norminette on every .c and .h file
    ./tests/tester.py valgrind                error and valid cases under valgrind
    ./tests/tester.py benchmark SIZE [TRIES]  sort TRIES random lists of SIZE numbers
"""

import argparse
import os
import random
import shutil
import signal
import subprocess
import tempfile
from itertools import permutations

GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"

INT_MIN = -2147483648
INT_MAX = 2147483647

# Checker provided by 42, used as the reference to know if a list is sorted
CHECKER = "./resources/checker_linux"

# Maximum number of moves allowed by the subject for each size
MAX_MOVES = {
    3: 3,
    5: 12,
    100: 700,
    500: 5500,
}

# Valgrind writes its report in a file instead of stderr, so stderr only
# contains what push_swap prints ("Error\n" or nothing).
# --error-exitcode=42 replaces the exit code of push_swap when a leak or a
# memory error is found, so the "code == 0" / "code == 1" checks fail by
# themselves. --errors-for-leak-kinds=all also counts "still reachable"
# memory (memory not freed before exit()).
VALGRIND_LOG = os.path.join(tempfile.gettempdir(), "push_swap_valgrind.log")
VALGRIND = [
    "valgrind",
    "--leak-check=full",
    "--show-leak-kinds=all",
    "--errors-for-leak-kinds=all",
    "--error-exitcode=42",
    f"--log-file={VALGRIND_LOG}",
]

# Set to True by the "valgrind" mode
use_valgrind = False

passed = 0
failed = 0


def run(cmd, stdin="", timeout=5):
    """Run cmd (a list) and return (stdout, stderr, code).
    code: >= 0 normal exit, < 0 killed by a signal, None on timeout."""
    try:
        r = subprocess.run(
            cmd, input=stdin, capture_output=True, text=True, timeout=timeout
        )
        return r.stdout, r.stderr, r.returncode
    except subprocess.TimeoutExpired:
        return "", "", None


def run_push_swap(args, stdin=""):
    """Run ./push_swap, under valgrind if the valgrind mode is enabled.
    The checker of 42 always uses run(): we don't test its leaks."""
    if use_valgrind:
        # Valgrind makes the program 20 to 50 times slower
        return run(VALGRIND + ["./push_swap"] + args, stdin, timeout=30)
    return run(["./push_swap"] + args, stdin)


def valgrind_log():
    """Return the report of the last valgrind run, to show it in a KO.
    The banner (everything up to "Parent PID") is skipped, and the "==PID== "
    prefix is removed from every line to keep the report readable."""
    if not use_valgrind:
        return ""
    with open(VALGRIND_LOG) as f:
        lines = f.read().splitlines()
    for i, line in enumerate(lines):
        if "Parent PID" in line:
            lines = lines[i + 1 :]
            break
    lines = [
        line.split("== ", 1)[-1] if line.startswith("==") else line for line in lines
    ]
    return "\n" + "\n".join("      " + line for line in lines if line.strip("= "))


def describe(code):
    """Turn an exit code into a readable text (exit 1, SIGSEGV, TIMEOUT)."""
    if code is None:
        return "TIMEOUT"
    if code < 0:
        return signal.Signals(-code).name
    return f"exit {code}"


def check(name, ok, detail=""):
    """Print OK or KO for a test, detail is only shown on a KO."""
    global passed, failed
    if ok:
        passed += 1
        print(f"{GREEN}[OK]{RESET} {name}")
    else:
        failed += 1
        print(f"{RED}[KO]{RESET} {name}  {detail}")


# (name, arguments): push_swap must print "Error\n" on stderr and exit 1
ERROR_CASES = [
    ("duplicate", ["1", "1"]),
    ("empty argument", [""]),
    ("alphabetic", ["1", "2", "3a"]),
    ("int overflow", ["2147483648"]),
    ("int underflow", ["-2147483649"]),
    ("only sign", ["-"]),
    ("double negative", ["--1"]),
    ("positive", ["+1"]),
    ("padding with zeros", ["0001"]),
    ("duplicate + padding with zeros", ["0001", "01"]),
    ("negative + padding with zeros", ["-0001"]),
    ("single string padded with zeros", ["3 002 1"]),
    ("mixed format", ["3 2", "1"]),
    ("plus zero", ["+0"]),
    ("double zero", ["00"]),
    ("duplicate in single string", ["1 2 1"]),
    ("vertical tab", ["\v1"]),
    ("newline separator", ["1\n2"]),
    ("only sign in single string", ["1 - 2"]),
]

# (name, arguments, expected stdout): push_swap must exit 0 with nothing on
# stderr. If the expected stdout is None, the output depends on the
# algorithm, so we only ask the checker of 42 if the list ends up sorted.
VALID_CASES = [
    ("negative", ["-1"], ""),
    ("padding with whitespace", ["   1"], ""),
    ("already sorted", ["1", "2", "3", "4", "5"], ""),
    ("no argument", [], ""),
    ("two numbers", ["2", "1"], None),
    ("three numbers", ["3", "1", "2"], None),
    ("int limits", ["2147483647", "-2147483648", "0"], None),
    ("single string", ["3 2 1"], None),
    ("single string with negative", ["3 -2 1"], None),
    ("all negative", ["-1", "-3", "-2"], None),
    ("zero", ["0", "1"], ""),
    ("space before negative", [" -1"], ""),
    ("space after negative", ["-1 "], ""),
    ("negative and positive", ["1", "-1"], None),
    ("single string with outer spaces", [" 2 1 "], None),
    ("int limits swapped", ["2147483647", "-2147483648"], None),
]


def test_norminette():
    """Run norminette on every .c and .h file of the project (libft included).
    Only one line is printed, plus the norm errors of the files in error."""
    print("Norminette:")

    if shutil.which("norminette") is None:
        check(
            "norminette", False, "norminette is not installed (pipx install norminette)"
        )
        return

    out, err, code = run(["norminette", "."], timeout=60)
    lines = out.splitlines()
    # Each file gives a "file.c: OK!" or "file.c: Error!" line, followed by
    # its errors, so every line that isn't "OK!" is worth showing
    files = [line for line in lines if line.endswith((": OK!", ": Error!"))]
    errors = [line for line in lines if not line.endswith(": OK!")]

    check(
        f"{len(files)} files checked",
        code == 0 and not errors,
        f"{describe(code)}\n"
        + "\n".join("      " + line for line in errors + err.splitlines()),
    )


def test_errors():
    """Every invalid input must give "Error\n" on stderr and nothing on stdout."""
    print("Error:")

    for name, args in ERROR_CASES:
        out, err, code = run_push_swap(args)
        check(
            name,
            err == "Error\n" and out == "" and code == 1,
            f"stdout={out!r} stderr={err!r} {describe(code)}{valgrind_log()}",
        )


def test_valid():
    """Every valid input must be sorted, or give the exact expected output."""
    print("\nValid:")

    for name, args, output in VALID_CASES:
        out, err, code = run_push_swap(args)
        if output is None:
            c_out, _, _ = run([CHECKER] + args, stdin=out)
            ok = c_out == "OK\n"
        else:
            ok = out == output
        check(
            name,
            ok and err == "" and code == 0,
            f"stdout={out!r} stderr={err!r} {describe(code)}{valgrind_log()}",
        )


def test_sort(nums):
    """Sort nums with push_swap, check the result with the checker of 42.
    Return the number of moves, or None if the list is not sorted."""
    args = [str(n) for n in nums]
    out, err, code = run_push_swap(args)
    if code is None or code < 0 or err:
        check(
            f"{len(nums)} numbers", False, f"push_swap: {describe(code)} stderr={err!r}"
        )
        return None

    c_out, c_err, _ = run([CHECKER] + args, stdin=out)
    moves = len(out.splitlines())
    ok = c_out == "OK\n"
    check(
        f"{len(nums)} numbers, {moves} moves",
        ok,
        f"checker={c_out.strip() or c_err.strip()!r} args={' '.join(args)}",
    )
    return moves if ok else None


def benchmark(size, tries=10):
    """Sort `tries` random lists of `size` unique numbers, print the stats."""
    results = []
    for _ in range(tries):
        # range() is lazy, so this doesn't build a list of 4 billion numbers
        nums = random.sample(range(INT_MIN, INT_MAX), size)
        moves = test_sort(nums)
        if moves is not None:
            results.append(moves)

    if results:
        avg = sum(results) / len(results)
        print(
            f"\n{size} numbers: {len(results)}/{tries} successful, "
            f"min {min(results)}, avg {avg:.1f}, max {max(results)}"
        )

    # The evaluation looks at the worst case, not the average, so the max
    # must stay under the limit of the subject (only for sizes that have one)
    limit = MAX_MOVES.get(size)
    if limit is not None and results:
        check(
            f"max {max(results)} moves <= limit {limit}",
            max(results) <= limit,
            f"{sum(m > limit for m in results)}/{len(results)} sorts over the limit",
        )


def test_permutations(size):
    """Test every possible order of 1..size, with the move limit of the
    subject if there is one. Only one line is printed, plus the failures."""
    limit = MAX_MOVES.get(size)
    total = 0
    worst = 0
    errors = []

    for perm in permutations(range(1, size + 1)):
        args = [str(n) for n in perm]
        total += 1

        out, err, code = run_push_swap(args)
        if code != 0 or err:
            errors.append(f"{' '.join(args)}: {describe(code)} stderr={err!r}")
            continue

        c_out, _, _ = run([CHECKER] + args, stdin=out)
        moves = len(out.splitlines())
        worst = max(worst, moves)

        if c_out != "OK\n":
            errors.append(f"{' '.join(args)}: checker={c_out.strip()!r}")
        elif limit is not None and moves > limit:
            errors.append(f"{' '.join(args)}: {moves} moves (limit {limit})")

    check(
        f"all {total} permutations of {size}, worst {worst} moves"
        + (f" (limit {limit})" if limit else ""),
        not errors,
        f"{len(errors)} failed",
    )
    # Show only the first failures, with the arguments to reproduce them
    for e in errors[:10]:
        print(f"      {e}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # No mode given (opts.mode is None) runs the default full test suite
    sub = parser.add_subparsers(dest="mode")

    sub.add_parser("norminette", help="norminette on every .c and .h file")
    sub.add_parser("valgrind", help="error and valid cases under valgrind")

    bench = sub.add_parser("benchmark", help="sort TRIES random lists of SIZE numbers")
    bench.add_argument("size", type=int, help="size of the list to be benchmarked")
    bench.add_argument(
        "tries", type=int, nargs="?", default=10, help="number of attempts"
    )

    opts = parser.parse_args()

    if opts.mode == "norminette":
        test_norminette()
    elif opts.mode == "valgrind":
        # Module level, so no "global" is needed to change it
        use_valgrind = True
        test_errors()
        test_valid()
    elif opts.mode == "benchmark":
        benchmark(opts.size, opts.tries)
    else:
        test_errors()
        test_valid()

        print("\nPermutations:")
        for size in range(1, 6):
            test_permutations(size)

        for s in [100, 500]:
            print(f"\n{s} numbers (limit {MAX_MOVES[s]}):")
            benchmark(s)

    # Printed at the very end so it counts every test of the mode
    print(f"\n{passed} OK, {failed} KO")
