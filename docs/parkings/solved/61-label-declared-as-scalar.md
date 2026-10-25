# 61 — declare the label as its real **object**, not as an address

**Status: SOLVED (2026-09-15) — 1 function promoted byte-identical
(`fn_800A3C50`, 75.9 → 100). The rewrite is *not* a general win: see below.**
Scanner: `tools/label_scalar_scan.py`.

## Symptom

A global read arrives late and via a full address materialisation: want materialises the 0x8030-page high half and the 0x802A-page high half, loads the global directly with a non-zero displacement, completes the second address, stores it to the object field, copies the object into the next argument register and branches, while got materialises the 0x802A page first, homes arg0, completes the address, materialises the 0x8030 page, stores through it, copies the object, loads the global with a zero displacement sunk below the store, and then branches. The load's byte encoding is the same size but the **scheduling** changed: with
an explicit address materialisation the load cannot be hoisted above the
unrelated `stw`.

## Root cause

m2c always declares a symbol it only knows as an address:

```c
extern char lbl_80301A78[];
...
fn_800A5B18(*(s32 *)&lbl_80301A78, arg0);
```

When the symbol is really a **scalar object**, declaring it as such and reading
it directly folds the address computation into the load and frees the
scheduler:

```c
extern s32 lbl_80301A78;
...
fn_800A5B18(lbl_80301A78, arg0);
```

Note that the store statement stays where it was in the source — the point is
that the *load* is now a simple scalar read that MWCC is willing to hoist.

## Scanner and the honest result

`tools/label_scalar_scan.py` finds every label the draft uses **only** through
`*(T *)&lbl_X` (no bare `lbl_X` / `(s32)lbl_X` uses, otherwise the address is
genuinely needed), rewrites both the declaration and the expressions, and A/Bs.

Run over the 410 no-park drafts that qualify (37 of them scoring ≥ 30%):
**37 attempts, 35 "same", 2 worse, 0 better.** The rewrite only changes codegen
when the load has an unrelated store to hoist past; in a plain load/compare
context ngccc already emits the same words. So this is a *diagnosis* for a
scheduling-shaped residual, not a sweep.

**Detection shortcut** for the next occurrence: the diff has the *same base
register* but WANT's `lwz` uses a non-zero displacement and GOT's uses 0, with
GOT's `lis`/`addi` pair present immediately before. Grep the draft for
`*(s32 *)&lbl_` / `*(u32 *)&lbl_` / `*(f32 *)&lbl_`.

## Relation to other docs

- Doc 51 — raw literals vs registered `lbl_*` symbols (the opposite direction:
  adding a symbol). This one is about *how* the symbol is declared.
- Doc 53 — field-width retypes. Same "the declaration decides the load
  encoding" idea, one level down.
- Doc 58 — m2c's duplicated `extern char lbl_X[];` is the tell that m2c thinks
  the symbol plays two roles. A label that is *both* stored as an address and
  read as a scalar cannot use this recipe; leave it as `char[]`.
