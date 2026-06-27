## Design Decisions

### Binary Search: Division vs Manual Bit-Shifting

In standard C, the midpoint for a half-open interval is typically calculated using signed division:

```c
const int *mid = begin + (end - begin) / 2;
```

In this repository, **I chose to explicitly use a bitwise right-shift operator instead**:

```c
const int *mid = begin + ((end - begin) >> 1);
```

#### The Why..?

1. **The Rounding Penalty:** Because `(end - begin)` yields a signed integer (`ptrdiff_t`), C requires division to truncate towards zero (e.g., `-1 / 2 = 0`). Since an arithmetic right shift (`sar` in x86_64) rounds towards negative infinity, the compiler must generate a sign-check and an addition instruction to protect `/ 2` from negative inputs, resulting in a 4-instruction block.

2. **Loop Guard Safety:** The loop guard `while (begin < end)` naturally guarantees that the pointer difference is always strictly positive inside the loop body. The negative-rounding trap is mathematically impossible.

3. **Compiler Blind Spot:** Because of pointer-to-integer divisions under the hood, static compiler analyzers often fail to propagate this positive-range guarantee and still generate the safety check for `/ 2`.

4. **1-Instruction Optimization:** By writing `((end - begin) >> 1)`, we tell the compiler we guarantee a positive input. It bypasses the safety checks and compiles the operation down to a single, 1-cycle instruction:
   ```assembly
   sar rax, 1
   ```
