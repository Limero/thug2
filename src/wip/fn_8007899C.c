// WIP DRAFT (non-matching) — hand-reconstructed from the retail bytes.
// family=m2c range=0x8007899C-0x80078C5C size=704B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKed 2026-10-05 (w_8007899C): best measured 20.0% (score_wip.py, default
// -O2 -G0 -mcpu=750 -fno-common), verdict DIFF.  Body below is the best found;
// it is a correct, semantics-complete reconstruction (see the header notes) —
// do NOT "simplify" it back to the m2c decode.  Residual + what was ruled out
// is recorded in the PARK note at the bottom of this file.
//
// Semantics recovered (all from the retail bytes, no callers exist in the DOL):
//   fn_8007899C(u32 *base, s32 srcW, s32 srcH, Px *dst, s32 dstW, s32 dstH)
//   - 6 register params, no stack args (nothing written above r8 before the
//     call to fn_80078948); frame locals start at 0x8(r1).
//   - fn_80078948 (matched, src/fn_80078948.c) fetches the 2x2 texel quad
//     around a fractional source position into a 16-byte 4xRGBA out block that
//     lives in this frame at 0x8(r1) and is read back with 16 individual lbz.
//   - the two fixed-point steps are
//       r14 = (s32)((f32)(f64)(u32)srcW / (f32)(f64)(u32)dstW * *(f32*)0x80295838)
//       r15 = (s32)((f32)(f64)(u32)srcH / (f32)(f64)(u32)dstH * *(f32*)0x80295838)
//     (the 0x43300000/0x5830(r11) + `fsub 2^52` + `frsp` dance is the ngccc
//     (f32)(f64)(u32)x idiom, recipes §6gj table — note u32, NOT s32: the s32
//     form adds an `xoris rX,rX,0x8000` that want does not have).
//   - bilinear blend of the 4 texels with 1/1024 fixed-point weights,
//     +0x200 rounding, then `>> 10`, stored as 4 bytes r,g,a,b (that store
//     order is what retail emits: stb 0, stb 1, stb 3, stb 2).
//   - the 12-instruction `do { ... } while (r9 != -1)` block right after the
//     prologue is dead code in retail too and must be reproduced literally.
//
// The frame-resident locals (arg copies + sp3C) are declared `volatile`
// because retail stores them in the prologue and reloads them at every use;
// without the qualifier ProDG hoists them into callee-saved registers and
// the whole register allocation shifts (that change alone was worth ~3.5
// points and removed a spurious `mfcr r12`/`stw`/`mtcrf` CR-save triple).
#include "types.h"

typedef struct { u8 r, g, b, a; } Px;

void fn_80078948(Px *arg0, u32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void fn_8007899C(u32 *arg0, s32 arg1, s32 arg2, Px *arg3, s32 arg4, s32 arg5) {
    volatile s32 sp3C;
    volatile s32 sp38;
    volatile s32 sp34;
    volatile s32 sp30;
    volatile s32 sp2C;
    volatile s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    Px sp0[4];
    Px *dst;
    s32 var_r19;
    s32 var_r20;
    s32 var_r12;
    s32 var_r16;
    s32 var_r10;
    s32 var_r9;
    s32 var_r9_2;
    s32 temp_r14;
    s32 temp_r15;
    s32 temp_r18;
    s32 temp_r17;
    f32 temp_f9;

    var_r19 = 0;
    sp28 = (s32) arg0;
    sp2C = arg1;
    var_r20 = 0;
    sp30 = arg2;
    var_r12 = 0;
    sp34 = arg4;
    var_r9 = 1;
    sp38 = arg5;
    do {
        var_r9_2 = 1;
loop_2:
        if (var_r9_2 != 0) {
            var_r9_2 -= 1;
            goto loop_2;
        }
        var_r9 -= 1;
    } while (var_r9 != -1);
    temp_r14 = (s32) (((f32) (f64) (u32) sp2C / (f32) (f64) (u32) sp34) * temp_f9);
    temp_r15 = (s32) (((f32) (f64) (u32) sp30 / (f32) (f64) (u32) sp38) * temp_f9);
    var_r10 = 0;
    temp_f9 = *(f32 *) 0x80295838;
    dst = arg3;
    while (var_r10 < sp38) {
        sp3C = var_r10 + 1;
        var_r12 = (var_r12 & 0xFFFF) | ((var_r20 >> 10) << 16);
        temp_r18 = var_r20 & 0x3FF;
        if ((s32) sp34 != 0) {
            var_r16 = sp34;
            do {
                temp_r17 = var_r19 & 0x3FF;
                var_r12 = (var_r12 & 0xFFFF0000) | ((var_r19 >> 10) & 0xFFFF);
                fn_80078948(&sp0[0], (u32 *) sp28, var_r12 >> 16, (s16) var_r12, sp2C, sp30);
                var_r19 += temp_r14;
                sp18 = ((0x400 - temp_r17) * (0x400 - temp_r18)) >> 10;
                sp1C = ((0x400 - temp_r18) * temp_r17) >> 10;
                sp20 = ((0x400 - temp_r17) * temp_r18) >> 10;
                sp24 = (temp_r17 * temp_r18) >> 10;
                dst->r = ((sp18 * sp0[0].r) + (sp1C * sp0[1].r) + (sp20 * sp0[2].r) + (sp24 * sp0[3].r) + 0x200) >> 10;
                dst->g = ((sp18 * sp0[0].g) + (sp1C * sp0[1].g) + (sp20 * sp0[2].g) + (sp24 * sp0[3].g) + 0x200) >> 10;
                dst->b = ((sp18 * sp0[0].b) + (sp1C * sp0[1].b) + (sp20 * sp0[2].b) + (sp24 * sp0[3].b) + 0x200) >> 10;
                dst->a = ((sp18 * sp0[0].a) + (sp1C * sp0[1].a) + (sp20 * sp0[2].a) + (sp24 * sp0[3].a) + 0x200) >> 10;
                dst += 1;
                var_r16 -= 1;
            } while (var_r16 != 0);
        }
        var_r10 = sp3C;
        var_r19 = 0;
        var_r20 += temp_r15;
    }
}

// PARKED 2026-10-05 (w_8007899C): 20.0%, verdict DIFF, object 700B vs 704B.
//
// RESIDUAL (all of it is register-allocation / frame-slot placement, not
// semantics — the instruction *shapes* line up from the dead loop onward):
//  1. FRAME is -0x88, want is -0x98.  Want's local pool is 0x08..0x4f and is
//     laid out in exact declaration order:
//       0x08 sp0[4]  0x18 sp18  0x1c sp1C  0x20 sp20  0x24 sp24
//       0x28 arg0 0x2c arg1 0x30 arg2 0x34 arg4 0x38 arg5
//       0x3c sp3C  0x40 var_r12  0x48 the (f64) cast temp
//     Got's pool is 0x0c..0x3f (args 0x0c-0x1c, sp0 at 0x20, temp at 0x30,
//     f64 at 0x38).  4 words are missing: want homes the four blend weights
//     (sp18..sp24) in the frame; ProDG keeps them in registers for this body.
//  2. Because of (1) every `lbz/stw/lwz disp(r1)` in the blend differs by the
//     slot shift, so the otherwise-correct 34-word tail
//     0x80078BA0..0x80078C24 (mullw/add/addi 0x200/srawi/stb 0,1,3,2/addi r31)
//     is only correct in the non-volatile variant.
//  3. Got is missing the `lwz r12, 0x40(r1)` reload after `addi r31,r31,4`
//     (the 1-word size shortfall): with the args homed, ProDG re-derives
//     var_r12 from var_r20 each iteration (`rlwinm r0,r16,0x16,0x10,0x1f`)
//     instead of keeping it loop-carried in r12 across the call.
//  4. `cmpwi r9,0` in want uses cr0; got picks cr4 (a consequence of (3)/CR
//     allocation, not of the source).
//
// RULED OUT:
//  * `(f32)(f64)(s32)x` — adds `xoris rX,rX,0x8000` + the 2^52+2^31 pool that
//    want lacks; `(u32)` is right (recipes §6gj table).  Confirmed by .rodata
//    contents, not guessed.
//  * `(s8)` casts on the four dst stores — emit 4 extra `extsb` (measured).
//  * `volatile` on the four weights — emit the 4 matching stores PLUS 4
//    reloads: 764B, 7.4%.
//  * Weight array `s32 w[4]` instead of four scalars — homes the weights and
//    gets the frame to -0x98 (measured), but moves sp0 to 0x30 and the args to
//    0x0c, i.e. 13.6%; with `sp0` declared first it is size-exact (704B) but
//    only 16.5%.
//  * Flag ladder on the best body: -fno-schedule-insns 1.2%, -fno-gcse 7.6%,
//    -fno-thread-jumps / -fno-expensive-optimizations / -fno-caller-saves 20.0%
//    (no change), -fno-omit-frame-pointer worse.  Default -O2 is best; no
//    FLAG line is load-bearing.
//  * m2c's `temp_cr0_eq` boolean — forces `mfcr r12` + `stw r12,0x4c` at entry
//    and `mtcrf 8,r12` at exit (3 extra words).  Isolated by bisection: the
//    CR save needs the live call to fn_80078948 *and* a loop-carried
//    var_r20; dropping either removes it, no flag short of -fno-gcse (which
//    then wrecks everything else) does.
//  * Declaring `dst = arg3` before vs after the float preamble, making sp3C
//    non-volatile, and `volatile s32 sp40` with explicit save/restore around
//    the call: all measured, none beat 20.0%.
//  * Twin/near-twin search (tools/twin_scan.py, tools/near_twin_scan.py) and a
//    grep for the `0x400 -` blend idiom in src/: no matched sibling exists.
//  * No caller of fn_8007899C exists anywhere in main.dol (scanned every
//    section for `bl`), so the 6-arg signature is inferred from retail alone.
//
// Remaining blocker is ProDG's local-slot allocation, which is driven by the
// hashed variable identities, not by declaration order: no C-level lever found
// reproduces want's slot map while keeping the same instruction sequence.