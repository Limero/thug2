# 63 — `switch` case **bodies** are emitted in source order, not case-value order

**Status: SOLVED (2026-09-16) — 1 function promoted byte-identical
(`fn_8021F990`, 67.4 → 100). Took two full sweeps of the draft's residual to
find; the tell is a *correct decision tree* with a *wrong body layout*.**

## Symptom

The draft's decision tree is byte-for-byte right — same first pivot, same
`ble`/`blt`, same `b` to the epilogue — but every branch **target** is wrong,
and the mismatch is concentrated in the last third of the function. Both sides test case value 2 first with an equal branch, then diverge on the less-or-equal target slot, then test 5 and 9 with equal branches to different body slots. Both trees are structurally identical, so `diff_near.py` reports a long run of
`DIFF` lines that look like a tail shift — but the *bodies* at those targets
are the same statements, just laid out in a different order.

## Root cause

MWCC emits `switch` **case bodies in the order the `case` labels are written in
the source**, not in ascending case-value order. Retail's function declares its
cases in a non-monotonic order, and the emitted layout follows it:

| layout slot (want) | case | body |
|---|---|---|
| right after the tree | `0`, `1` (shared, fallthrough) | `fn_8021F964(p); fn_8021FA48(p,0);` |
| +0x20 | `9` | `fn_8021F964(p);` |
| +0x2C | `5` | `fn_8021F964(p); fn_80131008(p->unk0x1F4,0,0,0,0);` |
| +0x50 | `2` | `fn_80137B54(mgr, 6);` |

i.e. the original source had `case 0: case 1:` first, then `case 9`, then
`case 5`, then `case 2`. Writing the cases in ascending order (the natural m2c
output) emits them `{0,1}, 2, 5, 9` and only reaches **69.6 %**.

Only some permutations are reachable from a given tree: for this function
`(0/1, 9, 5, 2)` and `(5, 2, 0/1, 9)` both score EXACT, while
`(0/1, 2, 9, 5)` stays at 69.6 % and `(9, 5, 2)` alone collapses to 26.1 %
(that last one also drops the shared `0/1` body). So the layout is not free —
but non-monotonic declaration order **is** legal and sometimes required.

## Second defect in the same draft: a missing shared case body

The parked draft had no `case 0`/`case 1` at all: it used `default:` to carry
the `fn_8021F964 + fn_8021FA48(p, 0)` body and listed only cases 2, 5, 9.
want's tree tests `2` first, then `ble`, then inside the low half does
`cmpwi r3, 0; blt <epilogue>` — a *range* test, which is what a shared
`case 0: case 1:` body compiles to. Everything else is an **empty default**
(there is no `default:` statement block in retail; the `b` at the end of the
tree goes straight to the epilogue). Re-spelling it as

```c
switch (temp_r3) {
case 0:
case 1:
    fn_8021F964(temp_r31);
    fn_8021FA48(temp_r31, 0);
    break;
case 9: ...    /* then 5, then 2 — the exact source order above */
}
```

produced the match. Note that this also means the `default:` arm must be
omitted entirely rather than written as `default: break;`.

## Cheapest tell

A `switch` draft whose tree matches instruction-for-instruction but whose
`beq`/`ble`/`b` *targets* all differ, with the mismatched words confined to the
body region — that is this issue, not a tail shift. Confirm with
`tools/want_vs_got.py <addr>`: the tree lines show no `!!` while the branch
words do.

## How to sweep

There is no scanner yet. The cheap heuristic is: take the case values from the
draft's `switch`, and if the draft's tree already matches want exactly, brute
force the body order (`k!` for `k` bodies, usually ≤ 4 → ≤ 24 compiles,
parallelisable, ~4 s each). Two extra rules cut the space hard:

- group contiguous arms that share a body (`case 0: case 1:`) into one slot;
- always also try the ascending order *and* the exact reverse — retail's order
  is frequently "whatever the original author typed", which is rarely sorted.

## Second form: the case label **SET** picks the compare-tree pivots

**`fn_801BE820` PROMOTED (98.5 → 100) — same day, same family, opposite
lever.** There the tree's *semantics* were already right but every pivot
compare word differed: want pivots on 8 toward the left subtree while got scans from the top pivoting on 0xC toward the default.

want tests 8 first, then `cmpwi r29,0xa; ble default`, then `cmpwi r29,0xc;
bgt default` — a **balanced** tree. got scanned from the top instead. The
draft's switch had

```c
case 5 ... 6:  X = C4C8; break;
case 7 ... 8:  X = C4CC; break;
case 0xB ... 0xC: X = C4D0; break;
default:       X = C4B4; break;
```

Retail **also listed `case 9:` / `case 10:` falling through into the default
body**. That changes the expanded key set from six keys `{5,6,7,8,11,12}` to
eight `{5,6,7,8,9,10,11,12}`, which moves the balanced-tree root from the
5th key to the 4th (`8`) and the right subtree's pivot to `10` — exactly
want's words. Adding the two arms fixes all four words:

```c
case 9:
case 10:
default:
    X = lbl_802AC4B4;
    break;
```

So the diagnostic is the mirror image of the first form:

| symptom | cause |
|---|---|
| tree matches, every branch **target** differs | case bodies in the wrong **order** (see above) |
| tree has the right semantics but different **pivots** | the case label **set** is wrong — look for arms that share an existing body |

Four spellings were EXACT (`case 9: case 10:` before or after the ranges,
`case 9 ... 10:`, and dropping `default:` entirely), so the mechanism is the
key count, not the placement. Ten permutations of the *declaration order*
(reversed, mid-first, last-first, `case 5: case 6:` split forms, one label per
value) all stayed between 82.0 % and the 98.5 % baseline — declaration order
does **not** move the pivots, it only reorders the bodies, which is the first
table's effect and does not apply when the bodies already sit in the right
place. `case 5 ... 6:` and `case 5: case 6:` compile identically, so ranges are
expanded before the tree is built.

## Relation to other docs

- Doc 05 — m2c's corrupt drafts. This is the opposite case: the draft is
  *semantically* right and only the layout is wrong.
- Doc 56 / doc 60 — the two prototype/argument-shape defects that this draft
  had already been fixed through (21.2 → 24 → 53.2 → 67.4 %). Those scores were
  all measured **with the wrong case order**, so the 67.4 % park note was
  really two independent defects stacked.
