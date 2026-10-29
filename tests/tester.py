#!/usr/bin/env python3
import argparse
import random
import signal
import subprocess
from itertools import permutations

GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"

INT_MIN = -2147483648
INT_MAX = 2147483647

CHECKER = "./resources/checker_linux"

MAX_MOVES = {
    3: 3,
    5: 12,
    100: 700,
    500: 5500,
}

passed = 0
failed = 0


def run(cmd, stdin="", timeout=5):
    try:
        r = subprocess.run(
            cmd, input=stdin, capture_output=True, text=True, timeout=timeout
        )
        return r.stdout, r.stderr, r.returncode
    except subprocess.TimeoutExpired:
        return "", "", None


def describe(code):
    if code is None:
        return "TIMEOUT"
    if code < 0:
        return signal.Signals(-code).name
    return f"exit {code}"


def check(name, ok, detail=""):
    global passed, failed
    if ok:
        passed += 1
        print(f"{GREEN}[OK]{RESET} {name}")
    else:
        failed += 1
        print(f"{RED}[KO]{RESET} {name}  {detail}")


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


def default():
    print("Error:")

    for name, args in ERROR_CASES:
        out, err, code = run(["./push_swap"] + args)
        check(
            name,
            err == "Error\n" and out == "" and code is not None and code == 1,
            f"stdout={out!r} stderr={err!r} {describe(code)}",
        )

    print("\nValid:")

    for name, args, output in VALID_CASES:
        out, err, code = run(["./push_swap"] + args)
        if output is None:
            c_out, _, _ = run([CHECKER] + args, stdin=out)
            ok = c_out == "OK\n"
        else:
            ok = out == output
        check(
            name,
            ok and err == "" and code is not None and code == 0,
            f"stdout={out!r} stderr={err!r} {describe(code)}",
        )

    print(f"\n{passed} OK, {failed} KO")


def test_sort(nums):
    args = [str(n) for n in nums]
    out, err, code = run(["./push_swap"] + args)
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
    results = []
    for _ in range(tries):
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


def test_permutations(size):
    limit = MAX_MOVES.get(size)
    total = 0
    worst = 0
    errors = []

    for perm in permutations(range(1, size + 1)):
        args = [str(n) for n in perm]
        total += 1

        out, err, code = run(["./push_swap"] + args)
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
    for e in errors[:10]:
        print(f"      {e}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "size",
        type=int,
        nargs="?",
        default=None,
        help="size of the list to be benchmarked",
    )
    parser.add_argument(
        "attempts",
        type=int,
        nargs="?",
        default=None,
        help="number of attempts",
    )
    opts = parser.parse_args()

    if opts.size is None:
        default()

        print("\nPermutations:")
        for size in range(1, 6):
            test_permutations(size)

        size = [100, 500]
        for s in size:
            limit = MAX_MOVES.get(s)
            print(f"\n{s} numbers (limit {limit}):")
            benchmark(s)
    else:
        if opts.attempts:
            benchmark(opts.size, opts.attempts)
        else:
            benchmark(opts.size)
