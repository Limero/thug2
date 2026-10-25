// === PARKED 2026-10-01 — DIFF 48.4% (194/406 masked words), object
// 1636B vs want 1624B.  NOT promotable: object is 12B too long and ~200 words
// still differ.  Structure is byte-for-byte right from the entry through the
// 15 `fn_800A9E80` calls, all four SCALE_BYTE blocks and the CVT region; the
// residue is (a) prologue/epilogue colouring, (b) reload register choice in the
// SCALE/CVT blocks, (c) three extra words in the `mag`/atan2f tail.
//
// WHAT WAS TRIED (each measured with tools/test_wip_drafts.py --addr 0x800AA1F4):
//   22.66%  draft as inherited (r28/r29 arg pair, 0x20 frame, fused if/else)
//   30.79%  + `register ... __asm__("r31"/"r30")` pins on arg0/arg1   (+8.1)
//   43.60%  + empty `__asm__("")` in both arms of SCALE_BYTE's if/else (+12.8)
//   48.41%  + `!(ts_ <= ...)` for the FIRST trailing guard's 3rd disjunct (+4.8)
//   49.39%  (dropped the named s32 r3..r6 temporaries) — NOT taken: it CSEs the
//            four byte loads and emits `mr r9,r0` instead of want's
//            `li rN,1; cmpwi r0,0; bne; li rN,0`, so it scores 1 word better
//            by accident while being structurally further from want.
//
// LOAD-BEARING FIXES (keep them):
//   1. arg0/arg1 pinned to r31/r30.  Unpinned GCC gives the pair r28/r29, which
//      also drags the prologue to `stmw r28` + a 0x20 frame (stmw r28 reserves
//      r28..r31 = 16B; `stmw r30` reserves 8B, so want's frame is 0x18).
//   2. `__asm__("")` (EMPTY string, ZERO instructions emitted) inside both arms
//      of `if (v_ > 0) { t_ = v_ - 0x32; } else { t_ = v_ + 0x32; }`.  Left
//      plain, GCC *fuses* the if/else into `addi t,v,+0x32; ble SKIP;
//      addi t,v,-0x32`; want emits the unfused `ble L; addi -0x32; b J;
//      L: addi +0x32; J:`.  Reproducible in isolation with a 15-line probe.
//   3. Third disjunct of the guard is `!(ts_ <= ...)`, not `ts_ > ...`.  With
//      the positive spelling GCC has to materialise the float compare
//      (fcmpu cr7 / cror / mfcr / rlwinm / cmpwi / beq = 6 words); with the
//      negated `<=` it branches straight off `fcmpu cr0` + `ble` like want.
//      Measured on guard 1 only: keeping guard 2 positive is 1 word smaller and
//      0.12pt better, but want branches there too — both spellings are
//      semantically identical, so the cheaper one is kept.
//
// WHY IT IS STILL STUCK (the mechanism, not the flags):
//   * Prologue: want never mentions r28/r29 at all — its scratch pool is the
//     volatiles {r0,r3,r4,r7,r8,r9,r10,r11}.  With the args pinned, GCC's reload
//     picks r28/r29 as the two SCALE-block scratch regs (see `xoris r29,r0` +
//     `lis r28,0x4330` where want has `xoris r0,r0` + `lis r8,0x4330`).  That
//     is ~8 words per SCALE block and pulls the frame to 0x20.
//   * Want keeps 0x43300000 in one register across all four CVT blocks
//     (`lis r0,0x4330` hoisted once, then `stw r0,8(r1)` x3) where GOT
//     rematerialises `lis r28,0x4330` per block: 3 extra words, and they are
//     exactly the size overshoot.
//   * Want carries 5 dead `mr` (r11,r8,r7 <- r10 in the first CVT block, one
//     `mr r10,r9` per trailing guard).  These are ProDG reload artifacts of a
//     pseudo whose only use was folded away; they only appear when the
//     allocation lands the way it does in want, so they cannot be requested
//     directly.
//   * The DI-mode store is always split (hi at +8 first, then lo at +0xc) by
//     GCC regardless of source spelling — `w[2]` union, named hi/lo struct
//     fields, and two-then-one store order all give the identical bytes, so
//     want's `stw 0xc` before `stw 8` is not reachable from C here.
//   * No flag moved it: -fno-schedule-insns/-insns2/-gcse/-sched-interblock/
//     -sched-spec/-expensive-optimizations/-thread-jumps/-strength-reduce/
//     -branch-count-reg are all <= the default on this body.
//
// NOT TRIED: pinning the SCALE-block scratch values with further
// `register ... __asm__("rN")` locals (r0/r8), and rebuilding the union as a
// `volatile f64` + `"m"`-pinned pad.  Both are the next things to try.
//
// Original DOL notes (hand-decoded, all verified against
// config/G2TE52/symbols.txt): every `lis` in this function is `lis rX,0x802A`
// so the rodata operands live at 0x8029_83xx (the 16-bit displacement
// 0x8348 is NEGATIVE, and the borrow lands the page on 0x8029, not 0x802A):
//   0x80298340 f32 0.0            (zero case + the `== 0.0f` compares)
//   0x80298348 f64 2^52 + 2^31    (the `cvt.d - ` subtract)
//   0x80298350 f32 77.0           (divisor)
//   0x80298354 f32 0.001          (`mag > `)
//   0x80298358 f32 127.0
//   0x8029835C f32 45.0, 0x80298360 f32 150.0   (the 45*150 guard)
//   0x80298368 f64 2^52           (the trailing-guard subtract)
//   0x80298370 f32 3.14159274
// Also: ngccc emits `(u32)x ^ 0x80000000` as `xoris rd,ra,0x8000` (the
// immediate is the constant >> 16), so the `^ 0x80000000` spelling below is
// correct and must NOT be "fixed" to `^ 0x8000`.
//
// WIP DRAFT (non-matching) — hand reconstruction from disassembly.
// family=m2c range=0x800AA1F4-0x800AA84C size=1624B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern f32 lbl_80298340;
extern f64 lbl_80298348;
extern f32 lbl_80298350;
extern f32 lbl_80298354;
extern f32 lbl_80298358;
extern f32 lbl_8029835C;
extern f32 lbl_80298360;
extern f64 lbl_80298368;
extern f32 lbl_80298370;

s32 fn_800145AC(void);
f32 atan2f(f32, f32);
f32 sqrtf(f32);
f32 fn_800AAA08(s32, s32, s32, s32);
void fn_800A9E80(void *, s32);

typedef struct {
    char pad0x0[0x1];
    u8 unk0x1; u8 unk0x2; u8 unk0x3; u8 unk0x4;
    u8 unk0x5; u8 unk0x6; u8 unk0x7; u8 unk0x8;
    u8 unk0x9; u8 unk0xA; u8 unk0xB; u8 unk0xC;
    u8 unk0xD; u8 unk0xE; u8 unk0xF; u8 unk0x10;
    char pad0x11[0x2];
    u8 unk0x13; u8 unk0x14; u8 unk0x15; u8 unk0x16;
    char pad0x17[0x5];
    s32 unk0x1C;
} Arg1;

typedef struct {
    char pad0x0[0x244];
    f32 unk0x244; f32 unk0x248; f32 unk0x24C; f32 unk0x250;
    f32 unk0x254; f32 unk0x258; f32 unk0x25C; f32 unk0x260;
    f32 unk0x264; f32 unk0x268; f32 unk0x26C; f32 unk0x270;
    s32 unk0x274; s32 unk0x278;
    char pad0x27C[0x4];
} Arg0;

#define SCALE_BYTE(dst, b) \
    { \
        s32 v_ = (s32)(b) - 0x80; \
        if (v_ == 0) { \
            (dst) = lbl_80298340; \
        } else { \
            s32 t_; \
            if (v_ == -0x80) v_ = -0x7F; \
            if (v_ > 0) { t_ = v_ - 0x32; __asm__(""); } else { __asm__(""); t_ = v_ + 0x32; } \
            cvt.w[1] = (u32)t_ ^ 0x80000000; \
            cvt.w[0] = 0x43300000; \
            (dst) = (f32)(cvt.d - lbl_80298348) / lbl_80298350; \
        } \
    }

#define CVT_BYTE(dst, b) \
    cvt.w[1] = (u32)((s32)(b) - 0x80) ^ 0x80000000; \
    cvt.w[0] = 0x43300000; \
    (dst) = (f32)(cvt.d - lbl_80298348);

void fn_800AA1F4(Arg0 *_a0, Arg1 *_a1) {
    register Arg0 *arg0 __asm__("r31") = _a0;
    register Arg1 *arg1 __asm__("r30") = _a1;
    union { u32 w[2]; f64 d; } cvt;
    f32 x; f32 y; f32 xy; f32 mag;
    s32 r3; s32 r4; s32 r5; s32 r6;
    fn_800A9E80((char *)arg0 + 4, arg1->unk0x7 ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x28, arg1->unk0x8 ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x4C, arg1->unk0x6 ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x70, arg1->unk0x5 ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x190, arg1->unk0xC ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x16C, arg1->unk0xA ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x1D8, arg1->unk0xB ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x1B4, arg1->unk0x9 ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x94, arg1->unk0xD ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x100, arg1->unk0xE ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0xB8, arg1->unk0xF ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x124, arg1->unk0x10 ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0xDC, (arg1->unk0x1C & 0x200) ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x148, (arg1->unk0x1C & 0x400) ? 0xFF : 0);
    fn_800A9E80((char *)arg0 + 0x220, (arg1->unk0x1C & 0x100) ? 0xFF : 0);

    SCALE_BYTE(arg0->unk0x254, arg1->unk0x1);
    SCALE_BYTE(arg0->unk0x258, arg1->unk0x2);
    SCALE_BYTE(arg0->unk0x25C, arg1->unk0x3);
    SCALE_BYTE(arg0->unk0x260, arg1->unk0x4);

    CVT_BYTE(x, arg1->unk0x13); arg0->unk0x244 = x;
    CVT_BYTE(y, arg1->unk0x14); arg0->unk0x248 = y;
    xy = x * x + y * y;
    CVT_BYTE(arg0->unk0x24C, arg1->unk0x15);
    CVT_BYTE(arg0->unk0x250, arg1->unk0x16);
    arg0->unk0x268 = sqrtf(xy);
    arg0->unk0x264 = atan2f(arg0->unk0x244, -arg0->unk0x248);
    mag = sqrtf(arg0->unk0x24C * arg0->unk0x24C + arg0->unk0x250 * arg0->unk0x250);
    arg0->unk0x270 = mag;
    if (mag > lbl_80298354) {
        arg0->unk0x26C = atan2f(arg0->unk0x24C, -arg0->unk0x250);
    } else {
        r3 = arg1->unk0x7 ? 1 : 0;
        r4 = arg1->unk0x8 ? 1 : 0;
        r5 = arg1->unk0x6 ? 1 : 0;
        r6 = arg1->unk0x5 ? 1 : 0;
        if (r3 || r4 || r5 || r6) {
            arg0->unk0x26C = fn_800AAA08(r3, r4, r5, r6);
            arg0->unk0x270 = lbl_80298358;
        } else {
            arg0->unk0x270 = lbl_80298340;
            arg0->unk0x26C = lbl_80298340;
        }
    }
    if (arg0->unk0x274 != 0
        && (arg0->unk0x270 == lbl_80298340
            || !(__builtin_fabsf(arg0->unk0x26C) < (lbl_8029835C * lbl_80298360))
            || !({ f32 ts_;
                 cvt.w[0] = 0x43300000; cvt.w[1] = (u32)fn_800145AC();
                 ts_ = (f32)(cvt.d - lbl_80298368);
                 cvt.w[0] = 0x43300000; cvt.w[1] = (u32)arg0->unk0x274;
                 !(ts_ <= (f32)(cvt.d - lbl_80298368)); }))) {
        arg0->unk0x274 = 0;
    }
    if (arg0->unk0x278 != 0
        && (arg0->unk0x270 == lbl_80298340
            || !((lbl_80298370 - __builtin_fabsf(arg0->unk0x26C)) < (lbl_8029835C * lbl_80298360))
            || ({ f32 ts_;
                 cvt.w[0] = 0x43300000; cvt.w[1] = (u32)fn_800145AC();
                 ts_ = (f32)(cvt.d - lbl_80298368);
                 cvt.w[0] = 0x43300000; cvt.w[1] = (u32)arg0->unk0x278;
                 ts_ > (f32)(cvt.d - lbl_80298368); }))) {
        arg0->unk0x278 = 0;
    }
}
