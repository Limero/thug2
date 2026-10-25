# 48 — Call-store tail: return-register `mr` interleaved into zero-store group

**Status: SOLVED (2026-09-24 audit).** `fn_8000D0A4` is promoted in
`src/fn_8000D0A4.c` as byte-identical, including the full linked DOL. The
root cause below is corrected: this is a one-list right-rotation emission,
not two scheduler lists. Distinct from doc 09 (GCC hoists ONE store out of
source order) — here the WHOLE tail store-group reorders AND a
`mr r3,r30` (the return-self) lands between two members of the same group.

## The shape

After the alloc call and global-image write, the tail is a run of zero-stores
to low offsets plus a return of `self`. Want issues the alloc call, stores the call result to offset 0x14 of the self register, materialises the global-image base, stores self through it, zeroes a scratch register, stores zero to offset 0x23C first (out of ascending order), then homes the return value with a copy of self into r3 interleaved at that point, and follows with the ascending zero-stores to offsets 8, 0xC and 0x10 before the epilogue. The historical WIP build from the old source order instead started the ascending group at 0x10, jumped to 0x23C, continued with 8 and 0xC, and placed the return-self copy after all stores.

## Why the original analysis missed it

The pre-solution text below is retained for diagnostic history. It wrongly
concluded that retail had two independent store lists:

- GC stores to the SAME structure are scheduled by **ascending address** within
  one independent store-list. Retail's group is NOT ascending: it opens at
  `0x23c`, then `8`, `0xc`, `0x10` — a "high-water first then low group" shape
  that fits **two** store-lists (the 0x23c field standalone, then 8/c/10), with
  the `mr r3,r30` return-value home inserted between them.
- ngccc folds `8/0xc/0x10` AND `0x23c` into one list and emits ascending
  `0x10, 0x23c, 8, 0xc`, hoisting the `mr r3,r30` return-home to AFTER every
  store.
- Source shapes tried and rejected (all 19/23, size-exact 92B):
  - stores written in retail's exact 0x23c,8,c,10 order;
  - a `return r; char *r = self;` early-return-copy to move the `mr` earlier;
  - a `Sub {a,b,c,d} *s = (Sub*)(self+8)` struct field zero-fill;
  - plain ascending stores.
- The `0x23c` field being a lone far-away member is the tell — retail treated
  it as its own future list.

## Known members / scale

- **fn_8000D0A4** (92B, 23/23 = 100%) — allocator ctor: calls
  `fn_80009A44`/`fn_8000EAF4`, writes the global image `lbl_802FFE84`, then the
  zero-store tail. Promoted in `src/fn_8000D0A4.c`. Its
  sibling fn_8000D100 (the destructor, already a registered split) is matched.

## Closure and reusable rule

The winning source order is:

```c
self->unk0x8 = 0;
self->unk0xC = 0;
self->unk0x10 = 0;
self->unk0x23C = 0;
return self;
```

ProDG emits this four-store, same-base, same-value run rotated right by one,
then positions the return copy after the first rotated store: the written source order of offsets 8, 0xC, 0x10, 0x23C is emitted as 0x23C first, then the return-home copy, then 8, 0xC, 0x10.

The old source order was `[23c, 8, c, 10]`; its natural rotation was
`[10, mr, 23c, 8, c]`, hence the 19/23 residual. An exhaustive 24-order
matrix confirmed that the corrected order is unique.

No flags, barriers, `volatile`, register pins, frame padding, or inline
assembly are needed. The promoted source was independently re-scored as
masked `EXACT 100.0%`, and isolated relocation/link simulation resolves all
23 words, including both call targets and the `lbl_802FFE84` address pair.