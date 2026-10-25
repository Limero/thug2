# 54 — The copy mwcc ate: `var = temp; if (…) var = NULL;` coalescing

**Status: SOLVED (implementation recipe), lever now closed at the
all-or-nothing granularity.**

Promoted 2026-09-13 by this lever alone or in combination:

| fn | size | was | fix |
|---|---|---|---|
| `fn_80031FC4` | 136B | 73.5% | if/else form (both arms of the loop) **+** `s16 unk0x8` local vt |
| `fn_80015A58` | 80B | 60.0% | if/else form alone |
| `fn_801C26D8` | 240B | 11.7% | if/else form (4 instances) **+** s16 vt **+** explicit `(char *)arg0 + 0x34` base local |

## What it is

m2c transcribes the ubiquitous "walk a singly-linked list, stop at the sentinel,
NULL-clamp the cursor" idiom as two statements:

```c
var_r11 = temp_r9;
if ((s32) temp_r9->unk0x4 == -1) {
    var_r11 = NULL;
}
```

mwcc's register allocator **coalesces** `var_r11` and `temp_r9` into the *same*
pseudo-register, because after the copy the two are indistinguishable while the
`if` does not fire. The copy disappears, the function compiles 8 bytes shorter
than retail, and every diff from that point on is shifted.

Retail keeps both registers (`lwz r9, …; lwz r0, …; mr r11, r9`). The source
shape that forbids the coalesce is the **if/else** form:

```c
if ((s32) temp_r9->unk0x4 == -1) {
    var_r11 = NULL;
} else {
    var_r11 = temp_r9;
}
```

This is the *opposite* of recipe 50 (pin the argument registers), where the
coalesce is what you want. Here the coalesce is what retail's compiler *did not*
do, and no flag brings the copy back.

## Sweep

`/tmp/ifelse_sweep.py` rewrites **every** instance of the pattern in a draft and
scores it. Over the 211 drafts that carry the pattern: **1 EXACT, 18 improved
≥1 point, 20 rewritten bodies worth keeping** (written back).

`/tmp/ifelse_subset.py` then tried every *subset* of a draft's instances (2-4
instances each): **0 further EXACT, 2 improvements**. Conclusion: the transform
is all-or-nothing per draft, and this lever is **closed**.

## Caveat — the mis-ordered form is sometimes correct

`fn_8001517C` (63.3%) is the counter-example. Its draft contains

```c
var_r3 = temp_r0;                    /* m2c order — copy FIRST */
temp_r0 = *(s32 *)((char *)var_r31 + (s32)lbl_803C9C38);
```

which is use-before-def in C, yet it is the *only* form that reproduces
retail's `lwzx r0, r31, r29; mr r3, r0`. "Fixing" the order and the if/else form
both drop it to 26-29% (116B / 124B against a 120B want). As with every source
shape recipe: re-score, never assume.

## Related

- recipe 50 (`/tmp` docs, WIP.md) — the argument-register pin, which *causes*
  the coalesce deliberately.
- `docs/parkings/solved/53-field-width-retype.md` — the `s16` local vt that
  combined with this lever on two of the three promotions. These two levers
  appear together often: the same m2c draft that lost the copy also widened a
  field.
