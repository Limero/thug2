# 53 — Field-width retype (loader/store mnemonic mismatch at identical regs+disp)

**Status: OPEN as a lever, SOLVED for its first two members.**
`fn_8001CF80` (144B) and `fn_801980C4` (204B) both promoted 2026-09-13 by this
lever alone; a census says **193 of the 3,567 non-promoted drafts** carry at
least one such diff.

## What it is

The want and got words differ, but the *registers and displacement are
identical* — only the mnemonic differs, and it differs only in width:

| want | got | meaning |
|---|---|---|
| `lha rX, off(rY)` | `lwz rX, off(rY)` | retail reads an **s16** field; we read s32 |
| `lhz` / `lbz` / `lfs` | `lwz` | retail reads u16 / u8 / float |
| `sth` / `stb` | `stw` | retail writes u16 / u8 |

`classify.py` only labels a draft `WIDTH` when **every** diff is of this kind,
which is why the lever looked tiny (1 draft). Widening the criterion to "at
least one width diff" gives the real numbers:

```
drafts with >=1 width diff: 193
kinds: lha->lwz  61   stw->lwz 25   lwz->stw 17   stb->stw 16   lbz->lwz 15
       lhz->lwz  14   sth->stw  7   stw->stb  5   lbz->lhz  4   stb->lwz  4 ...
```

`lha->lwz` (61 drafts) is the dominant one: **retail loads a 2-byte field where
we load a 4-byte one.**

## How to fix it — retype the VARIABLE, never cast the use site

The m2c draft reads the field through a shared `Unk_XXXXXXXX` type whose member
is `s32`. The shared type cannot be edited (recipe 47: `Unk_2EF06E12` has 2,041
users, `Unk_C8FEE62D` 1,314). So declare a **local** type for the variable in
question and use it for that variable only.

### Case A — `fn_8001CF80` (19/19 width, 47.2% -> 100%)

A 4-iteration zero-fill of a 0x1E-byte PAD state block. Retail emits
nine byte/halfword stores for the low bytes (offsets 0x0 as halfword then 0x2 through 0xA as bytes) followed by nine halfword stores from 0xC through 0x1C.

m2c had every one of the 19 stores as `*(s32 *)((char *)p + off) = 0;` (and
three of them as `->unk0xN` members). Changing each store to the width retail
uses — `*(u16 *)` at 0x0/0xC/0xE/…/0x1C and `*(u8 *)` at 0x2…0xA — is the whole
fix; nothing else moved. The loop control already matched (`li r11,4; mtctr`).

### Case B — `fn_801980C4` (84.3% -> 100%)

Two call sites do `((s32 (*)(void *, s32))temp->unk0xC)(obj + temp->unk0x8, 3)`.
`Unk_2EF06E12::unk0x8` is `s32`, so ngccc emitted `lwz r3, 8(r9)` where retail
has `lha r3, 8(r9)` — the frame offset is an **s16**. A local type fixes both
sites at once:

```c
typedef struct {
    char pad0x0[0x8];
    s16  unk0x8;        /* retail: lha */
    char pad0xA[0x2];
    s32  unk0xC;        /* the callee pointer */
} Unk_801980C4_vt;
...
Unk_801980C4_vt *temp_r9_2;      /* was Unk_2EF06E12 * */
```

84.3% -> 88.2% from the retype alone. The remaining six words were two
`lwz / lwz / mr` rotations, closed with two other levers (below).

## Two companion levers that closed fn_801980C4

- **Pin the scratch whose load retail keeps in its own register.** Without
  `register Unk_2EF06E12 *temp_r11 __asm__("r11")` ngccc coalesces the load
  straight into the copy's home (`lwz r30, 0xc(r31); mr r11,r30`) instead of
  retail's `lwz r11, 0xc(r31); mr r30,r11`. The pin forces the split
  (88.2% -> 94.1%). Same shape as recipe 50.
- **Hoist a condition's load above the copy it feeds.** Retail emits
  `lwz r9,0x18(r3); lwz r0,4(r9); mr r31,r9; cmpwi r0,-1`. Writing
  `var_r31 = temp_r9; temp_r9 = arg0->unk0x18;` (m2c's order) puts the `mr`
  first; *swapping* the two lines makes ngccc coalesce `r31 <- r9` and collapses
  the whole function to **7.8%**. Writing the swap **plus** a pin on `temp_r9`
  recovers the shape:
  ```c
  temp_r9 = arg0->unk0x18;
  { s32 t4 = (s32)temp_r9->unk0x4; var_r31 = temp_r9; if (t4 == -1) var_r31 = NULL; }
  ```
  The named `t4` is what keeps the `lwz r0,4(r9)` **before** the `mr`; without
  it the load coalesces onto the copy's register (`lwz r0,4(r31)`) and the
  `cmpwi` lands last. 94.1% -> 100%.

## How to find candidates

The census is cheap and reusable (it reuses `classify.py`'s helpers):

```
tools/venv/bin/python /tmp/width_scan.py      # writes /tmp/width_scan.out
```

For a single draft, `tools/which_words.py 0xADDR` prints the raw words; a width
diff is obvious because the two words share every bit except the opcode's low
6 bits (power-of-two load/store opcodes are adjacent).

## Caveats

- The width diff is usually **necessary but not sufficient**: only 1 of the 193
  drafts was width-only. The other 192 have 8-1,200 further diffs. Do the retype
  (it is mechanical and always correct), but do not expect the draft to fall.
- `stw->lwz` / `lwz->stw` (42 drafts) look like this census but are **not**
  width problems — they are a load and a store of the same slot emitted in the
  opposite order, i.e. the store-order family (doc 09).

## 2026-09-13 — two more members, both via the same "retype the variable" rule

### Case C — `fn_8006FD50` (216B, 66.7% -> 100%)

Three independent defects, only the second of which is a width issue:

1. the first list node was loaded as `*(char *)(*(s32 *)((char *)arg0 + 0x3C) + 0xC)`
   — an `lbz` + `extsb` pair where retail has a single `lwz`. The field holds a
   **pointer**; changing the cast's pointee to `Unk_2EF06E12 **` is the fix;
2. the dispatch frame offset is `s16` (retail `lha r3, 8(r9)`), so
   `temp_r9_2/3/4` became a local `Unk_6FD50_vt` with `s16 @0x8`, `s32 @0xC`
   (recipe 56);
3. two pins (`temp_r9 -> r9`, `temp_r9_2 -> r9`) **plus** a named temporary for
   each null-check's load, written *before* the `var = temp` copy, so ngccc
   emits `lwz r0,4(r9); mr r31,r9` rather than `mr r31,r9; lwz r0,4(r31)`.
   Note the local struct needs an explicit `char pad0x0[4]; s32 unk0x4;` before
   the `s16` field — struct member *names* do not set offsets.

### Case D — `fn_8007EAE8` (300B, 64.0% -> 100%)

The same `lha` on a dispatch offset (`s16 @0x8`), plus two m2c transcription
errors that are not width issues at all:

- `fn_80009A78` is **1-arg** (`s32`) and m2c called it with two
  (`arg2, var_r3*4`) — doc 52's phantom self-arg;
- `*((s32 *)var_r29 + arg0->unk0x20)` scales the base by 4; retail does
  `lwz r9,0x20(r30); stwx r0,r29,r9`, so the source must be the byte-offset
  form with the operands in the other order: `*(s32 *)(var_r29 + arg0->unk0x20)`.

Residual after those was two register colours, closed with pins on
`temp_r11 -> r11` and `var_r9 -> r9` (the loop needs retail's r9=node /
r11=var split) plus the left-to-right null-check ordering.

### Case E — `fn_801C26D8` (240B, 11.7% -> 100%)

A **twin** of `fn_80031FC4` (same 0x28/0x34 walker, two loops), promoted with
three levers stacked:

1. doc 54's if/else copy form on all four null-clamp sites (11.7% -> 83.3%);
2. the local vt for the dispatch frame: `s16 @0x8` on the `unk0xC`-chain
   (`lha r3, 8(r9)` where `Unk_2EF06E12::unk0x8` is s32);
3. an explicit base local for the second loop. Retail emits
   `addi r30, r3, 0x34` and addresses through r30, so r30 must be the
   *offset* pointer, not `arg0` — writing
   `var_r30 = (char *)arg0 + 0x34; temp_r9_4 = *(s32 *)((char *)var_r30 + 0xC);`
   also fixed m2c's scaling bug (recipe 64: `*(s32 *)((s32 *)arg0 + 0x34)` reads
   `arg0 + 0xD0`, not `arg0 + 0x34`).

### Case F (open) — `fn_801A27CC` (188B, 62.5% -> 87.2%)

Not yet promoted, recorded because it needed **four** independent fixes and the
residue is instructive:

- s16 local vt for the `unk0x58` dispatch offset;
- a real prototype `void fn_801A362C(void *, s32);` — without it mwcc emits the
  varargs `crclr cr1eq` and the entire tail shifts;
- recipe 64 on the `lbl_80305EAC` access (`0x388` bytes, not `0x388` words);
- recipe 65: the callee returns `u64`, so `+ 1` must land on r4 (the low word),
  not r3 — declaring `u64 fn_8001448C(void)` was worth +6.3 points on its own.

Residual is six register colours (`temp_r9` wants r9; the `0x388` load wants
r9). Pinning `temp_r9` to r9 **regresses to 20.8%** (frame grows to 192B) — a
colour the pin cannot reach.

## Addendum 2026-09-15 — two more members, and a *different* defect that looks like one

**Member 3: `fn_8004CDAC` (132B, 97.0 → 100, promoted).** The pointer in
`temp_r10 + temp_r9->unk0x10` is walked with `lha r3, 0x10(r9)` — the offset
field is **signed 16-bit**. `temp_r9` is typed with the shared `Unk_C8FEE62D`
header (whose `unk0x10` is `s32`), so a local view type does it without touching
any shared header:

```c
typedef struct { char pad0x0[0x10]; s16 unk0x10; s32 unk0x14; } View4CDAC;
...
temp_r9 = (View4CDAC *)((Unk_C7387A53 *)temp_r10)->unk0x2C;
```

`unk0x14` stays `lwz` — only the addend field is narrow. This is the same
"local s16 view type" trick `fn_800685A4` needed.

**Member 4: `fn_800685A4` (116B, 89.7 → 93.1, still parked at 2 words).**
`temp_r9->unk0x8` is added to a pointer and loaded with `lha`, so
`{ char pad[8]; s16 unk0x8; s32 unk0xC; }` is the right view. Residual is
unrelated: the `arg0->unk0xC != 0` test homes in r0 instead of the DOL's r4
(8 alternative condition spellings + 6 flag combos all stay at 93.1).

## The look-alike: m2c *scales* a byte offset through a pointer cast

Three drafts were stuck on a diff that reads like a field-width problem but is
not. m2c writes

```c
*(s32 *)((s32 *)(fn_X(...)) + 0xC) = 1;      /* (s32 *) + 0xC  ==  +0x30 bytes! */
```

when the DOL uses the **byte** displacement `0xC`: want stores with displacement 0xC off the call-result base while got stores with displacement 0x30 (which equals 0xC scaled by the 4-byte element size).

The `(T *)` cast makes the `+N` pointer arithmetic, so it is scaled by
`sizeof(T)`. Fix: do the arithmetic on the integer-returning call —
`*(s32 *)(fn_X(...) + 0xC)` — so `+N` is plain integer addition. Promoted:
`fn_80171868` (89.7 → 100, `+0xC` had become `+0x30`) and `fn_8018694C`
(89.3 → 100, `+0x18` had become `+0x60`); `fn_80185D70` (33.3 → 100) is the
same bug in its `lwz r3,0x18(r3)`.

**Detection shortcut:** if a diff shows the *same base register and a
displacement that is a clean multiple of 4* (0xC vs 0x30, 0x18 vs 0x60), suspect
this and not a width problem — grep the draft for `(s32 *)` / `(T *)` casts
applied to a call result before `+`.
