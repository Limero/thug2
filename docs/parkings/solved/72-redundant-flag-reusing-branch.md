# doc 72 — the redundant flag-reusing branch that `dom` always folds

**Status:** SOLVED for the one known member (fn_8009EF74, 156B, EXACT) by a
1-instruction inline-asm wedge. Read this before parking any function whose
*only* residual is a conditional branch aimed at the immediately-following
block — i.e. a branch that "can never fail".

## The shape

WANT ends a comparison sequence with a branch that **re-tests the CR bit the
preceding compare left live**, in a position where the condition is provably
true:

```
    cmpwi  r3, 0
    bne    <body>        ; not taken on the fall-through path
    li     r31, 0
    beq    +16           ; <-- ALWAYS taken: re-uses CR0.EQ from the cmpwi
```

Every C spelling that reproduces the surrounding 39-word layout still lets
GCC's `dom`/jump-threading fold the `beq` into the unconditional `b` it
implies: the block it targets (`li r31,0`) has a **single predecessor**, so
the condition is a compile-time constant.

Observed once in the whole retail `.text` (3× the general
`op16; li; op16 same-CR-bit` quad, the other two in unmatched fn_800211D8);
the ~2000 general same-CR-bit pairs in the DOL are all Metrowerks SDK code at
0x8024xxxx+, i.e. a different compiler.

## The fix (1 instruction, 2.6%)

Keep GCC's CFG blind to the one branch: a `goto` places the target arm
out-of-line exactly as an `else` would, so GCC sees `li r31,0` falling
straight into the target label and needs no jump of its own — then supply the
branch by hand:

```c
    if (guard) goto unlink9;      /* or: else { ...; goto unlink9; } */
    var_r31 = 0;
unlink9:
    ...
    __asm__ volatile("beq 1f");   /* retail's redundant flag-reusing branch */
    __asm__("1:\n\t");            /* re-define the join label INSIDE the asm */
```

Two details that will each cost you a cycle if you miss them:

* **A plain C label does not work.** GCC drops a label with no RTL reference
  to it, leaving an UNDEF symbol that will not link — hence
  `__asm__("1:")` to re-define the join inside the asm stream.
* The reloc form is identical to GCC's own branches (R_PPC_REL14 within
  `.text`), so the object links and promotes normally; runtime semantics are
  unchanged (the branch is always taken on the reachable path).

## Exhausted alternatives (do not re-run)

19 pure-C shapes: both polarities, `else if`, `goto done`, two `if`s, comma
`||`, `switch`, early return, re-test via a second pointer, inner-`if`-with-
-return, `do..while(0)` / `while(1)` / `for(;;)` around the tail and around the
unlinked arm, `do..while(node.obj != NULL)`. Each either keeps the layout with
`b` (97.4%) or moves the `li r31,0` out of position (46–85%). 37-flag sweep
(11 exist in ProDG, all 97.4%; `-fno-schedule-insns` 74.4%).

## Relation to the "want keeps dead insns" family

This is AGENTS §6x-89 seen from the *branch* side: there the residual is an
extra data insn the compiler proves dead; here it is an extra *control* insn
the compiler proves constant. Both mean "no C spelling exists", and both are
escapable with a one-instruction `__asm__` wedge (cf. AGENTS §6y-140 `"=r"`
wedges, §73-183 `mr %0,%1` wedges). Keep the wedge under the 30% ASM_FUNC law
and disclose the share in the draft header.
