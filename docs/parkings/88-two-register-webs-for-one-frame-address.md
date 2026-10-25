# Issue 88 — Forcing two register webs for one frame address

**Status: SOLVED 2026-10-05 (verified on fn_8018C080, DIFF 2.7% -> NEAR 51.9%).**

## The problem

Some want bodies keep two different registers holding the same stack address. The classic shape is a short-lived web used for the entry stores and a long-lived web used as a call argument: the frame address at offset 8 is computed into r30 as web A, later copied via r30 into r26 as web B, the entry stores use web A at offsets 8 and 4 through r30, the call argument moves web B, and the final store uses web B at offset 8 through r26.

ngccc sees one value, allocates one register, and emits one `addi`. The
object is then **one instruction short**, which pins the strictly-positional
scorer near 0% even when 80+ instructions are byte-identical — so this
usually presents as "DIFF ~2%" rather than "one word missing".

## The fix

Declare a **second named pointer** and copy between them with an ordinary
**assignment statement**, not a second declarator initialiser:

```c
s32 fn_X(...) {
    struct { ... } local, *p = &local, *q;   /* q has NO initialiser */
    ...
    q = p;                                    /* FIRST statement of the body */
    ...
}
```

`p` then dies after its last use while `q` stays live across every call, so
the ranges genuinely overlap and the allocator cannot coalesce them.

## What does NOT work (measured, do not repeat)

| Attempt | Result |
|---|---|
| `local, *p = &local, *q = &local;` (two initialisers) | folded — 1 register |
| copy placed anywhere other than **before** the first branch | folded, frame regresses to 0x40 / `stmw r27` |
| copy placed after the entry stores / after a call / after the loop head | 736B, 2.7% — worse |
| both pointers declared without initialisers, assigned late | 736B, 2.7% |
| copy routed through a `char *` bridge to defeat CSE | folded |
| swapping which pointer feeds the stores vs the arguments | no effect |
| declaration-order permutations of the surrounding locals | no effect |

## The load-bearing detail

**Placement of the copy statement is the whole trick.** It must be the first
statement of the function body — *before* the first `if`/branch. If it lands
after a branch, the address is born inside the arm, the two ranges stop
overlapping, and you are back to one register and a short object.

A second, **syntactically redundant** copy of the same assignment may also be
required: with two copies the object is size-exact and 51.9%; deleting one of
them drops it to 20% with a 736B object and a 0x48 frame. Redundant copies of
a never-modified pointer are the intended mechanism, not an oversight — do
not "clean them up". Verify by deletion before removing any of them.

## Why it is not a universal recipe

The fix works when the address is passed to **two or more callees**, which is
what genuinely splits the live ranges across call boundaries. Where the
address is never passed to any call, both spellings have identical fully
overlapping ranges and ngccc coalesces them unconditionally — see the
re-confirmation note in `src/wip/fn_8013AE40.c`, where 11 spellings of this
recipe all fold back to one register.

## Side effect worth knowing

Producing the extra callee-saved GPR **also fixes the frame size for free**.
On fn_8018C080 the frame went 0x40 -> 0x38 and the save area from
`stmw r27,0x2c` to `stmw r26,0x20` as a direct consequence — no separate
frame-padding work was needed. If you are fighting a frame-size wall on a
body that also wants two webs for one address, fix the web first.
