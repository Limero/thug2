// WIP DRAFT (non-matching) - hand semantic reconstruction.
// Remaps a curve: y = (2*x - base) * m + base, clamped to a floor, where m
// is picked per-value from one of two coefficient tables; then mirrors the
// whole table through arg0->unk0x10 and fires a vcall.
// family=m2c range=0x8005B68C-0x8005B7C4 size=312B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATUS 2026-10-04: 14.1% (was ~5% for the m2c husk), size exact 312B.
// The structure is now right; every branch in the want is reproduced.
// Fixes already in, all load-bearing:
//   * the constant table is a STRUCT of three f32* (`lbl_80364C38+0x10/0x14/
//     0x18`), selected by field offset, not three separate globals. Retail
//     computes the base once (`addi r5, r11, 0x4c38`) and then does
//     `lwz r9,0x14(r5)` / `lwz r9,0x18(r5)` in the two arms.
//   * the loop is a dual induction variable: an INDEX (r6) for the bound test
//     and a BYTE OFFSET (r7, +=4) for both the table read and the store
//     (`lfsx f13,r7,r9` / `stfsx f0,r7,r11`). Retail also keeps a third
//     `slwi r10,r6,2` for the clamp store. Writing the loop as a plain
//     `f32 *dst` pointer walk loses the `lfsx`/`stfsx` indexed pair (3.5%).
//   * `arg0->unk0x10` is re-LOADED each iteration (`lwz r11,0x10(r8)` twice),
//     so the field must be read through the struct, never hoisted to a local.
//   * the first value goes through a named `f32 v` local so the `lfs` of the
//     field precedes the `lfs` of the comparison constant (want: f13 = field,
//     f0 = lbl_802935AC; inlining the field pushes the constant first, 9%).
//
// PARKED 2026-10-04 - the residual is FPR/loop-scheduling, not semantics:
//   * retail recomputes `f0 = x + x` INSIDE each arm of the multiplier select
//     and keeps the arm's constant in f13; hoisting `2*x` into a local moves
//     it before the `fcmpu` (10.3% vs 14.1%) -- and restoring the per-arm form
//     re-orders the whole clamp block, so the two forms trade words.
//   * retail's clamp is `fcmpu f0,f13 / bge / stfs` on a value just STORED to
//     0xc(r8) and RE-LOADED (`lfs f0,0xc(r8)`); keeping the stored value in a
//     register (which is what the natural C does) drops the reload.
//   * ngccc picks `mtctr`/`bdnz` for the counted loop when the bound is a
//     plain local, and `cmplw`/`blt` when it is not; forcing either way moves
//     the whole tail.
// This is the same FPR-allocation wall as fn_800A95EC (docs/parkings/15,
// recipe-51 family): not reachable from C without register pins, i.e. asm.
// Best body preserved below.
typedef struct B5B68C {
    char pad0[4];
    f32 unk0x4;
    char pad8[4];
    f32 unk0xC;
    f32 *unk0x10;
    void *unk0x18;
} B5B68C;

typedef struct Tab5B68C {
    char pad0[0x10];
    f32 *unk0x14;
    f32 *unk0x18;
} Tab5B68C;

typedef struct VT5B68C {
    char p0[0x48];
    s16 o1;
    char p1[2];
    void *f1;
} VT5B68C;

extern f32 lbl_802935AC;
extern f32 lbl_802935B0;
extern f32 lbl_802935B4;
extern f32 lbl_80364C44;
extern f32 lbl_80364C48;
extern s32 lbl_8030047C;
extern Tab5B68C lbl_80364C38;

void fn_8005B68C(B5B68C *arg0) {
    Tab5B68C *tab;
    f32 mul;
    f32 v;
    s32 i;
    s32 off;
    s32 n;
    VT5B68C *vt;

    v = arg0->unk0x4;
    if (v <= lbl_802935AC) {
        mul = lbl_80364C44;
    } else {
        mul = lbl_80364C48;
    }
    arg0->unk0xC = (v + v - lbl_802935B0) * mul + lbl_802935B0;
    if (arg0->unk0xC < lbl_802935B4) {
        arg0->unk0xC = lbl_802935B4;
    }
    n = lbl_8030047C;
    i = 0;
    off = 0;
    while (i < n) {
        tab = &lbl_80364C38;
        if (arg0->unk0x4 <= lbl_802935AC) {
            mul = *(f32 *)((char *)tab->unk0x14 + off);
        } else {
            mul = *(f32 *)((char *)tab->unk0x18 + off);
        }
        arg0->unk0x10[i] =
            (arg0->unk0x4 + arg0->unk0x4 - lbl_802935B0) * mul + lbl_802935B0;
        if (arg0->unk0x10[i] < lbl_802935B4) {
            arg0->unk0x10[i] = lbl_802935B4;
        }
        i += 1;
        off += 4;
    }
    vt = (VT5B68C *)arg0->unk0x18;
    ((void (*)(void *, s32, s32))vt->f1)((char *)arg0 + vt->o1, 1, 1);
}
