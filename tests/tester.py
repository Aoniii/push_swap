#!/usr/bin/env python3
import argparse
import random
import signal
import subprocess

GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"

INT_MIN = -2147483648
INT_MAX = 2147483647

CHECKER = "./resources/checker_linux"

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


def default():
    out, err, code = run(["./push_swap", "1", "1"])
    check(
        "duplicate",
        err == "Error\n" and out == "" and code is not None and code >= 0,
        f"stdout={out!r} stderr={err!r} {describe(code)}",
    )

    out, err, code = run(["./push_swap", ""])
    check(
        "empty argument",
        err == "Error\n" and code is not None and code >= 0,
        f"stderr={err!r} {describe(code)}",
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
    else:
        if opts.attempts:
            benchmark(opts.size, opts.attempts)
        else:
            benchmark(opts.size)
