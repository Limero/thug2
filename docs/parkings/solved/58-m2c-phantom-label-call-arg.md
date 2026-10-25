# 58 — m2c reads a label address as a *call argument*

**Status: SOLVED (2026-09-15) — 5 functions promoted byte-identical to the
retail DOL in one session, 16 more drafts improved 2–50 points.**
Scanner: `tools/label_call_arg_scan.py`.

## Symptom

A small "constructor / register-a-vtable" style function decompiles with one
statement too many:

```c
extern char lbl_802988F8[];
extern char lbl_802988F8[];          /* <-- m2c emitted it TWICE */

void fn_800B2B3C(Unk_B6E8234C *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_802988F8;
    fn_800551D4(arg0->unk0x210);
    ...
}
```

The tell in the object code is **one extra word before a `bl`** — a register
copy the DOL does not have: want materialises the two label high halves into r9 and r11, completes both low halves, stores each to its struct field (offsets 0x1A8 and 8), and branches with no argument setup at all, while got emits zero-page high halves, completes them, performs the same two field stores, and then copies a register into r3 before the branch.

Two independent damages:

1. An extra `mr r3, r11` (plus the second register's own `lis/addi`), i.e. the
   draft sets up an argument retail never passes — retail's `bl` has **no
   argument setup at all**, so r3 still holds `arg0` at the call.
2. Because m2c now needs the label address in *two* live registers, the two
   struct-field stores get the opposite register assignment.

## Root cause

m2c reads the `lis`+`addi` pair that materialises `lbl_X` for the
`arg0->unkNNN = (s32)lbl_X;` store a second time, and decides the *next*
`bl` consumed it. It therefore appends `(s32)lbl_X` to the call's argument
list. Retail compiled one address materialisation feeding exactly two uses:
the store, and nothing else — the call takes zero (or fewer) arguments.

The **duplicated `extern char lbl_X[];`** line is the cheapest tell: m2c emits
one declaration per role it believes the symbol plays. 71 no-park drafts in
this tree carry a duplicated label `extern`.

## Fix

Delete the `(s32)lbl_*` argument from the call's argument list and drop the
matching parameter from the callee's prototype:

```c
    arg0->unk0x18 = (s32)lbl_802988F8;
    fn_8004F2C4();                    /* was: fn_8004F2C4((s32)lbl_802988F8); */
```

Both edits are needed: leaving `s32 fn_8004F2C4(s32);` in place with an
argument-less call compiles, but the declaration also has to lose the param so
later drafts do not re-introduce the argument. The scanner A/B tests both
("proto" and "noproto") and keeps whichever is better.

## Members promoted (DOL `cmp`-verified byte-identical)

| fn | size | score | notes |
|---|---|---|---|
| `fn_80062988` | 76B | 40 → 100 | field store + zero-arg call + `if (arg1 & 1) fn_80009AAC(arg0)` |
| `fn_8009DEF8` | 76B | 40 → 100 | same shape, `unk0x8` instead of `unk0xBC` |
| `fn_801A38A0` | 60B | 40 → 100 | also `return arg0;` (want's `mr r3, r30` tail) |
| `fn_8002DCCC` | 92B | 42.9 → 100 | object-header variant: `unk0x14 = lbl` then the ctor call |
| `fn_8019D388` | 52B | 84.6 → 100 | *not* this recipe — see below |

`fn_8019D388` is listed because it was fixed in the same pass by the sibling
observation: hoisting a **global deref into a local** above an unrelated store
makes MWCC issue the load early and reuse the register for the `+8`:

```c
    s32 g = *(s32 *)lbl_80303148;   /* lwz r11,0x3148(r9) now issues FIRST  */
    arg0->unk0x58 = arg1;           /* ... before this store                */
    fn_8000A578(g + 8, arg0->unk0x1C);   /* addi r3,r11,8 off the live global */
```

Its stale `-fno-schedule-insns2` header flag was *masking* that fix (84.6 with
the flag, 100 without — the doc-55 lesson again).

## Members improved but not closed

`fn_8002E050` 20.5→83.3, `fn_800500B8` 33.3→85.7, `fn_80066998` 33.3→85.7,
`fn_80032328` 30.8→72.0, `fn_80203810` 40.0→68.4, `fn_8007ABB8` 40.0→63.2,
`fn_800F1F74` 39.0→61.5 (the "argument" is the `sprintf` **format** string),
`fn_8004238C` 32.1→46.2, `fn_80045FA8` 25.0→40.0, `fn_8022E16C` 35.3→36.9,
`fn_8016A480` 23.7→25.0, `fn_80018098` 14.3→19.4, `fn_801B2B10` 12.1→12.8,
`fn_80234444` 3.9→4.8, `fn_8023D8E4` 21.3→22.2, `fn_80145C14` 9.6→10.1.

## Automation

```bash
# rank candidates: every draft that duplicates an extern char lbl_*[] declaration
printf '0x800500B8\n...' | tools/venv/bin/python tools/label_call_arg_scan.py
```

`tools/label_call_arg_scan.py` walks every call in a draft, finds arguments
that are *entirely* `(s32)lbl_XXXXXXXX` (optionally `&`-taken), removes the
argument by rebuilding the call from its top-level argument list, and scores
both the plain and the prototype-adjusted variant. Improving bodies are written
to `/tmp/label_call_<ADDR>.c` (best-per-address) for `apply_better.py`-style
splicing.

**Do not apply blindly:** of 71 duplicated-extern drafts only 16 improved —
the same argument pattern also appears where the label genuinely *is* the
argument (e.g. a `SomeRegistry_Register((s32)lbl_...)` helper). Always A/B.

## Relation to other docs

- Doc 52 (m2c spurious call args) — the general family. This doc is the
  sub-case where the phantom argument is the `lis/addi` pair of a **label**
  read for a *store*, and where the store's register assignment is collateral
  damage. Doc 52's `tools/label_arg_scan.py` matches the *trailing* literal
  forms; `label_call_arg_scan.py` handles any argument position and rebuilds
  the argument list, so it also catches mid-list occurrences.

## Addendum 2026-09-15 (h) — what is left after the phantom argument goes

Four of the drafts that the phantom-argument fix took to 83–86% closed with a
**second, unrelated** edit. Both shapes recur, so check for them immediately
after any doc-58 fix:

1. **The two field stores are in the opposite *source* order.** Once the bogus
   argument stops forcing the label into two live registers, the only residual
   is which statement comes first: want stores the 0x1A8-label register to offset 0x1A8 first and the 0x8-label register to offset 8 second, while got emits the same two stores in the opposite order with the register assignment following its own source order. Retail materialises the first store's address first, so the `arg->unk0x1A8 = …`
   statement must come **before** the `arg->unk0x8 = …` one
   (`fn_800500B8`, `fn_80066998` → 100). The same "which of two independent
   stores is sunk" question closed `fn_8002E050` (83.3 → 100): retail emits
   `arg0->unk0x14 = lbl_80291AA8;` **after** the two self-link stores.
2. **A missing prototype on a *different* callee** (doc 56) — `fn_80032328`,
   `fn_80203810` and `fn_800B2B3C` all still carried one extra `crclr cr1eq`
   word for their trailing call (`fn_800320D8`, `fn_8009F558`); declaring it was
   the whole difference. See the doc-56 addendum for the automated sweep.

One more distinct variant: `fn_80185D70` (33.3 → 100) passes a literal in
**r5**, not r3 — retail keeps the incoming r3/r4 untouched, so the wrapper
itself must be declared `(s32 a, s32 b)` and forward them, and m2c's
`(s32 *)X + 0x18` had **scaled** the offset to 0x60 (`lwz r3,0x60(r3)`) where
the DOL loads the byte offset 0x18. Do the offset arithmetic on an integer, not
a pointer.
