*This project has been created as part of the 42 curriculum by snourry.*

# PUSH_SWAP

## Description

Push_swap is an algorithmic project whose goal is to sort a stack of integers using a limited set of instructions (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr), while minimizing the total number of operations. The push_swap program takes a list of integers as arguments representing stack a, and outputs to standard output the sequence of instructions needed to sort it in ascending order.
</br>
The project also includes a bonus program checker, which reads a list of instructions from standard input and verifies whether they correctly sort the given stack.

## Instructions

### Prerequisites

- A C compiler (`cc` / `gcc`)
- `make`

### Compilation

```bash
# Compile the main program
make

# Compile the checker (bonus)
make bonus
```

### Usage

```bash
# Sort a list of integers
./push_swap 4 67 3 87 23

# Count the number of operations
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

# Verify the sort with the checker
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG

# 100 random numbers between 1 and 1000
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l

# 500 random numbers between 1 and 5000
ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' '); ./push_swap $ARG | wc -l

# With verification via Checker
ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' '); ./push_swap $ARG | ./checker $ARG
```

### Cleanup

```bash
make clean    # Remove object files
make fclean   # Remove object files and executables
make re       # Full recompilation
```

## Resources

- [Push_swap Visualizer](https://push-swap-visualizer.vercel.app/) — Visualization tool to observe the sorting behavior
