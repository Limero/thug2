// WIP DRAFT (non-matching) — body hand-reconstructed from the retail
// disassembly (the old m2c draft was structurally wrong end to end).
// family=m2c range=0x80042F44-0x80043800 size=2236B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (structural-reconstruction, 10.4% masked / DIFF).
// The whole function was re-derived from the retail bytes and the semantics are
// believed correct; what is left is register allocation + scheduling.
//
// EXACT already: prologue (18 insns) and epilogue, frame -0x118, `stw r12,0x90`
// (CR), `stmw r23,0x94` (r23..r31), `stfd f20..f31, 0xb8..0x110`, `stw r0,0x11c`,
// every local slot (outv r1+0x8, spC 0xc/+0xf, sp10 0x10, sp14 0x14, sp18 0x18,
// lt1 0x1c, lt2 0x20), the f64-conversion scratch at 0x88/0x8c, and all 52 call
// sites in retail order.
//
// (a) LENGTH: 556 insns vs want 559 — 3 words short, and got emits 2 words
//     retail does not, so the streams drift from 0x80042FFC onwards.
//     * MISSING, entry block: `mr r30,r9` (after `addi r9,r31,0x128`) and
//       `mr r27,r11` (after `addi r11,r31,0x88`).  Retail keeps a+0x128 in r30
//       and a+0x88 in r27 and spills the just-computed base through r9/r11
//       because r9/r11 are reused as the .rodata2 pool base right after; ngccc
//       instead materialises a+0x128 straight into r28 and a+0x88 into r27 and
//       never needs the copy.  Not expressible from C.
//     * MISSING, loop preheader: `mr r23,r30` (retail re-homes a+0x128 into
//       r23 because r30 becomes the handle inside the loop) and `fmr f25,f9`
//       (retail loads 0.5f into f9 for the two fmadds and copies it to the
//       cross-call home f25; here one register f27 serves both, so GCC emits
//       no copy).  Tried both variants of the 0.5f source spelling
//       (`chalf` local vs the raw symbol, local before/after/inside the two
//       fmadds) — the local form is one word better and is what is kept.
//     * EXTRA, two windows got spends a word retail does not: one between
//       `bl fn_800586cc` and `bl fn_80058b80`, one between `bl fn_80058b48`
//       and `bl fn_80058e40` (block1b).
// (b) REGISTER CHOICE: even where the instruction is the same, ngccc picks a
//     different register — flag in r25 vs r26, a+0x88/a+0x128 in r27/r28 vs
//     r27/r30(+r23 in the loop), 0.0f in f12 vs f31, the two pool bases in
//     r9/r10/r11 vs r9/r10/r11 but at different points.  ~498 of 556 words
//     still differ, nearly all of them scheduling/allocation inside the four
//     repeated "set handle / out-param / 6 calls / flag" blocks.
// (c) Ruled out: flags (the draft's stale `-fno-rerun-cse-after-loop` is gone;
//     no flag moves it), pins, store/statement order, `volatile` on the whole
//     frame, dead-scalar padding (dead scalars get NO frame slot at all), and
//     a `char _pad[]` as a *separate* local — see the FRAMING note below.
//
// REUSABLE (frame sizing, verified): ngccc hands the FIRST slot after the
// `volatile` local to any *separate* addressable local, so a standalone
// `char _pad[N]` always lands at r1+0xc and shoves the real scalars to the top
// of the frame.  Declaring the pad as the LAST MEMBER of the struct that holds
// the real locals puts it at r1+0x24 (after them) instead, which is the only
// way found to grow `LOCAL_SIZE` without moving `outv`/`spC`/... — retail has
// ~24 words of dead locals there (r1+0x24..0x87, no code) and the pad
// reproduces them.  Also note the pool at 0x802924D8 is 0x4330000000000000
// (u32 cast) while 0x802924F0 is 0x4330000080000000 (s32 cast), so the four
// byte scalings are `(u8)` and the two loop scalings are `(s32)i`.
#include "types.h"

// .rodata2 pool constants
extern f32 lbl_802924C8;   /* -200.0f */
extern f32 lbl_802924CC;   /*  648.0f */
extern f32 lbl_802924D0;   /*    0.0001f */
extern f32 lbl_802924E0;   /*    0.0f */
extern f32 lbl_802924E4;   /*    0.5f */
extern f32 lbl_802924E8;   /*    0.005f */
extern f32 lbl_802924F8;   /*    0.01f */

/* 0x48-byte record returned by fn_800503BC */
typedef struct Rec {
    f32 unk0x0;
    char pad0x4[0x14];
    f32 unk0x18;
    f32 unk0x1C;
    char pad0x20[0xC];
    f32 unk0x2C;
    f32 unk0x30;
    char pad0x34[0x14];
} Rec;

/* block built by fn_800501B0; the per-frame word lives at +0x4B8 */
typedef struct Blk {
    char pad0x0[0x4B8];
    u32 unk0x4B8;
} Blk;

/* the same 4 bytes are read as a word (lwz +0x40) and as a byte (lbz +0x43) */
typedef union Word4 {
    u32 w;
    u8 b[4];
} Word4;

/* sub-object at this+0x88 */
typedef struct P88 {
    char pad0x0[0x3C];
    f32 unk0x3C;
    Word4 unk0x40;
} P88;

/* sub-object at this+0x128 */
typedef struct S128 {
    f32 unk0x0;
    char pad0x4[0x1C];
    s32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
    f32 unk0x30;
    char pad0x34[0x8];
    f32 unk0x3C;
} S128;

typedef struct A {
    char pad0x0[0xC];
    u32 unk0xC;
    char pad0x10[0x78];
    P88 s88;
    char pad0xCC[0x5C];
    S128 s128;               /* this+0x128 */
    char pad0x168[0x10];
    f32 unk0x178;
    f32 unk0x17C;
    char pad0x180[0x4];
    f32 unk0x184;
    char pad0x188[0x8];
    s32 unk0x190;
    char pad0x194[0x4];
    s32 unk0x198;
    void **unk0x19C;
    void **unk0x1A0;
    s32 unk0x1A4;
    Blk *unk0x1A8;
    s32 unk0x1AC;
    f32 unk0x1B0;
    f32 unk0x1B4;
    Word4 unk0x1B8;
    s32 unk0x1BC;
    char pad0x1C0[0x4];
    s32 unk0x1C4;
    f32 unk0x1C8;
    f32 unk0x1CC;
} A;

/* one frame object so the stack slots land at r1+8..r1+0x20 with the
   dead tail filling r1+0x24..r1+0x87 (retail has no code for that tail) */
typedef struct F42F44 {
    volatile s32 outv;
    s32 spC;
    f32 sp10;
    f32 sp14;
    s32 sp18;
    s32 lt1;
    s32 lt2;
} F42F44;

void fn_800501B0(void *);
s32 fn_800503BC(s32, s32);
s32 fn_800421D4(void *);
void fn_800586CC(void *, void *, void *, void *);
void fn_80058B48(void *, u32);
void fn_80058B80(void *, u32);
void fn_80058BB8(void *, s32);
void fn_80058CC8(void *, f32, f32);
void fn_80058D04(void *, f32, f32);
void fn_80058D40(void *, f32, f32, f32);
void fn_80058D80(void *, f32);
void fn_80058DC0(void *, s32);
void fn_80058E00(void *, s32 *, s32);
void fn_80058E40(void *, u32);

void fn_80042F44(A *a) {
    F42F44 fr;
    s32 *b1;
    s32 *b2;
    s32 *b3;
    char _pad[0x5c];
    s32 flag;
    s32 i;
    void *h;
    Rec *rec;
    f32 f22, f23, f28, f29, f30, f31, x, y, sp14r;
    f32 c0001, c0005, c001, chalf;

    if (a->unk0x190 != 0) {
        P88 *in = (P88 *)((char *)a + 0x88);
        S128 *g = (S128 *)((char *)a + 0x128);
        flag = 0;
        if (g->unk0x28 < lbl_802924C8 || g->unk0x28 > lbl_802924CC) {
            flag = 1;
        }
        if (a->unk0x1A4 != 0) {
            fr.spC = in->unk0x40.w;
            if (g->unk0x0 >= lbl_802924D0) {
                *((u8 *)&fr.spC + 3) =
                    (s8)((f32)(f64)(u32)in->unk0x40.b[3] * g->unk0x0);
                fn_80058E40(a->unk0x19C[0], a->unk0x1C4);
            } else {
                *((u8 *)&fr.spC + 3) = 0;
                fn_80058E40(a->unk0x19C[0], a->unk0x1C4);
            }
            fr.sp10 = lbl_802924E0;
            fr.sp14 = lbl_802924E0;
            if (g->unk0x3C != lbl_802924E0) {
                fn_800586CC(a->unk0x198, a->unk0x190, &fr.sp10, &fr.sp14);
            }
            x = g->unk0x2C * fr.sp10;
            sp14r = fr.sp14;
            y = g->unk0x30 * fr.sp14;
            f29 = y * lbl_802924E4;
            f30 = x * lbl_802924E4;
            if (a->unk0x1C8 < lbl_802924E0) {
                f30 = lbl_802924E0;
            } else if (a->unk0x1C8 > lbl_802924E0) {
                f30 = x;
            }
            if (a->unk0x1CC < lbl_802924E0) {
                f29 = lbl_802924E0;
            } else if (a->unk0x1CC > lbl_802924E0) {
                f29 = g->unk0x30 * sp14r;
            }
            fn_80058B80(a->unk0x19C[0], a->unk0x198);
            fn_80058CC8(a->unk0x19C[0], g->unk0x24, g->unk0x28);
            fr.outv = fr.spC;
            fn_80058E00(a->unk0x19C[0], (s32 *)&fr.outv, a->unk0x1BC);
            if (a->unk0xC & 0x1000000) {
                fn_80058D40(a->unk0x19C[0], in->unk0x3C, f30, f29);
            } else {
                fn_80058D40(a->unk0x19C[0], g->unk0x3C, f30, f29);
            }
            fn_80058D04(a->unk0x19C[0], g->unk0x2C, g->unk0x30);
            fn_80058BB8(a->unk0x19C[0], a->unk0x190);
            if (a->unk0xC & 0x80000) {
                s32 flg;
                flg = 0;
                fn_80058DC0(a->unk0x19C[0], g->unk0x20);
                h = a->unk0x19C[0];
                if ((a->unk0xC & 0x100000) || (fn_800421D4(a) != 0)) {
                    flg = 1;
                }
                fn_80058B48(h, flg);
            } else {
                s32 flg;
                flg = 0;
                fn_80058D80(a->unk0x19C[0], a->unk0x184);
                h = a->unk0x19C[0];
                if ((flag != 0) || (fn_800421D4(a) != 0)) {
                    flg = 1;
                }
                fn_80058B48(h, flg);
            }
            if (a->unk0x1AC != 0) {
                b3 = &fr.sp18;
                fr.sp18 = a->unk0x1B8.w;
                if (g->unk0x0 >= lbl_802924D0) {
                    *((u8 *)b3 + 3) =
                        (s8)((f32)(f64)(u32)a->unk0x1B8.b[3] * g->unk0x0);
                    fn_80058E40(a->unk0x1A0[0], a->unk0x1C4);
                } else {
                    *((u8 *)b3 + 3) = 0;
                    fn_80058E40(a->unk0x1A0[0], a->unk0x1C4);
                }
                fn_80058B80(a->unk0x1A0[0], a->unk0x198);
                fn_80058CC8(a->unk0x1A0[0], g->unk0x24 + a->unk0x1B0,
                            g->unk0x28 + a->unk0x1B4);
                fr.outv = fr.sp18;
                fn_80058E00(a->unk0x1A0[0], (s32 *)&fr.outv, a->unk0x1BC);
                if (a->unk0xC & 0x1000000) {
                    fn_80058D40(a->unk0x1A0[0], in->unk0x3C, f30, f29);
                } else {
                    fn_80058D40(a->unk0x1A0[0], g->unk0x3C, f30, f29);
                }
                fn_80058D04(a->unk0x1A0[0], g->unk0x2C, g->unk0x30);
                fn_80058BB8(a->unk0x1A0[0], a->unk0x190);
                if (a->unk0xC & 0x80000) {
                    s32 flg;
                    flg = 0;
                    fn_80058DC0(a->unk0x1A0[0], g->unk0x20);
                    h = a->unk0x1A0[0];
                    if ((a->unk0xC & 0x100000) || (fn_800421D4(a) != 0)) {
                        flg = 1;
                    }
                    fn_80058B48(h, flg);
                } else {
                    s32 flg;
                    flg = 0;
                    fn_80058D80(a->unk0x1A0[0], a->unk0x184 - lbl_802924E8);
                    h = a->unk0x1A0[0];
                    if ((flag != 0) || (fn_800421D4(a) != 0)) {
                        flg = 1;
                    }
                    fn_80058B48(h, flg);
                }
            }
        }
        if (a->unk0x1A8 != NULL) {
            fn_800501B0(a->unk0x1A8);
            f22 = g->unk0x2C * a->unk0x178 * lbl_802924E4 + g->unk0x24;
            f23 = g->unk0x30 * a->unk0x17C * lbl_802924E4 + g->unk0x28;
            c0001 = lbl_802924D0;
            c0005 = lbl_802924E8;
            c001 = lbl_802924F8;
            b1 = &fr.lt1;
            b2 = &fr.lt2;
            chalf = lbl_802924E4;
            for (i = 1; i < a->unk0x1A4; i++) {
                rec = (Rec *)fn_800503BC(a->unk0x1A8, i - 1);
                fr.lt1 = a->unk0x1A8->unk0x4B8;
                *((u8 *)b1 + 3) = (s8)((f32)(f64)(u32)*((u8 *)b1 + 3) * rec->unk0x0);
                x = a->unk0x17C * rec->unk0x30;
                y = a->unk0x178 * rec->unk0x2C;
                y = y * chalf + rec->unk0x18;
                x = x * chalf + rec->unk0x1C;
                x = x * g->unk0x30;
                y = y * g->unk0x2C;
                f30 = g->unk0x2C * rec->unk0x2C;
                f31 = g->unk0x30 * rec->unk0x30;
                f28 = f22 - y;
                f29 = f23 - x;
                fn_80058E40(a->unk0x19C[i], a->unk0x1C4);
                fn_80058CC8(a->unk0x19C[i], f28, f29);
                fr.outv = fr.lt1;
                fn_80058E00(a->unk0x19C[i], (s32 *)&fr.outv, a->unk0x1BC);
                fn_80058D04(a->unk0x19C[i], f30, f31);
                fn_80058D80(a->unk0x19C[i],
                            a->unk0x184 - (f32)(f64)(s32)i * c001);
                fn_80058B80(a->unk0x19C[i], a->unk0x198);
                fn_80058BB8(a->unk0x19C[i], a->unk0x190);
                {
                    s32 flg = 0;
                    h = a->unk0x19C[i];
                    if ((flag != 0) || (fn_800421D4(a) != 0)) {
                        flg = 1;
                    }
                    fn_80058B48(h, flg);
                }
                if (a->unk0x1AC != 0) {
                    s32 flg;
                    fr.lt2 = a->unk0x1B8.w;
                    if (g->unk0x0 >= c0001) {
                        fn_80058E40(a->unk0x1A0[i], a->unk0x1C4);
                        *((u8 *)b2 + 3) = (s8)((f32)(f64)(u32)a->unk0x1B8.b[3] * g->unk0x0);
                    } else {
                        fn_80058E40(a->unk0x1A0[i], a->unk0x1C4);
                        *((u8 *)b2 + 3) = 0;
                    }
                    flg = 0;
                    fn_80058CC8(a->unk0x1A0[i], a->unk0x1B0 * f30 + f28,
                                a->unk0x1B4 * f31 + f29);
                    fr.outv = fr.lt2;
                    fn_80058E00(a->unk0x1A0[i], (s32 *)&fr.outv, a->unk0x1BC);
                    fn_80058D04(a->unk0x1A0[i], f30, f31);
                    fn_80058D80(a->unk0x1A0[i],
                                a->unk0x184 - ((f32)(f64)(s32)i * c001) -
                                    c0005);
                    fn_80058B80(a->unk0x1A0[i], a->unk0x198);
                    fn_80058BB8(a->unk0x1A0[i], a->unk0x190);
                    h = a->unk0x1A0[i];
                    if ((flag != 0) || (fn_800421D4(a) != 0)) {
                        flg = 1;
                    }
                    fn_80058B48(h, flg);
                }
            }
        }
    }
}