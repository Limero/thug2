// PARKED 2026-10-05: DIFF 2.19%, object 2012 B vs want
// 2136 B (124 B short). Untouched except two access-width
// fixes that are codegen-neutral (kept because they are the honest types).
// family=m2c range=0x8008BA68-0x8008C2C0 size=2136B
//
// SEMANTICS (from want): builds a particle/render descriptor - a ~320-byte
// local block (a struct at r1+0x08 whose +0 is a `QB_PARTICLE` tag built with
// `lis/ori`, plus byte fields at +4/+5/+6, a u16 at +0x24, a u16 at +0x30 and
// 22 `stfs` slots from +0x38 up), seeds it from arg0->unk0x178/0x179 (bytes),
// arg0->unk0x17C (word) and arg0->unk0x94, and pushes it into the renderer
// through fn_800231C4 / fn_8001E6F0 / fn_8001FAA4 / fn_8001F2D8 / fn_8001F0A0.
//
// THE PRIMARY BLOCKER IS NOT CODEGEN - IT IS THE CALL STRUCTURE.
// want contains SIX calls in 534 instructions (0x800231c4, 0x8001e6f0,
// 0x8001faa4, 0x8001f0a0, 0x8001f2d8 x2). This body emits THIRTY-NINE `bl`s:
// 8 to fn_8001F0F8, 8 to fn_8001F1D4, 5 to fn_8001F200, plus the 6 that are
// real. Lines ~287-308 of the draft are two near-identical blocks of eight
// `fn_8001F0F8(x,y,z) / fn_8001F1D4(x) / fn_8001F200(x,y)` pairs - i.e. a
// repeated "push three params, push one, push two" sequence. m2c invented
// three different callee addresses for what is almost certainly ONE helper
// called from a loop or from a merged tail block, so this function cannot
// match until that sequence is re-derived from want rather than from m2c.
// Note also that the draft passes floats through `*(s32 *)&lbl_...` casts
// (e.g. `fn_8001F200(*(s32 *)&lbl_80296BA0, ...)`) to a callee declared
// `void fn_8001F200(s32, s32)`; the real helpers are float-taking (fn_8001F0F8
// alone does `fmr f31,f2` after saving f30/f31), so all of these prototypes are
// wrong and must be harvested from the callee prologues + the `fN` setup
// before the call (recipes 4q / 6h).
//
// SECONDARY BLOCKER: the frame. want is `stwu r1,-0x1a8` with 0x140 bytes of
// locals and 18 saved GPRs (`stmw r14,0x148`); this body is `-0x90` with ~40
// bytes of locals. The draft declares the locals with want's stack offsets in
// their names (sp8..sp130) but m2c also emitted twelve `static s32 sp98..spD0`
// FILE-SCOPE statics, which live in .bss and so cost no frame. Converting those
// twelve to real locals was measured and makes things WORSE (object 2012 ->
// 1920 B, 2.19% -> 1.04%), so the missing 280 bytes are NOT simply those
// twelve words - something else (a large address-taken aggregate, most likely)
// has to be identified first.
//
// NOTES: `arg0+0x178` and `arg0+0x179` are read as BYTES in want
// (`lbz r11,0x178(r31)` / `lbz r10,0x179(r31)`), not words; the draft read
// words and truncated into `u8` locals. Fixed to `*(u8 *)`, which is
// codegen-neutral (2.19% either way) but stops m2c's wrong access width from
// misleading the next reader. arg0+0x17C IS a word (`lwz r10,0x17c(r31)`) and
// the draft already had that right.
extern char lbl_80296B9C[];
extern char lbl_80296BA0[];
extern char lbl_80296BB8[];
#include "qb_constants.h"
static s32 sp98;
static s32 sp9C;
static s32 spA0;
static s32 spA8;
static s32 spAC;
static s32 spB0;
static s32 spB8;
static s32 spBC;
static s32 spC0;
static s32 spC8;
static s32 spCC;
static s32 spD0;

void fn_8001F200(s32, s32);
void fn_800231C4(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8008BA68(void *arg0) {
    f32 sp130;
    f32 sp128;
    f32 sp120;
    f32 sp118;
    f32 sp114;
    f32 sp10C;
    s32 sp104;
    s32 sp100;
    s32 spF8;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    s8 sp3E;
    s16 sp38;
    s8 sp37;
    s8 sp36;
    s8 sp35;
    s8 sp34;
    u8 sp2F;
    u8 sp2E;
    s16 sp2C;
    s32 sp28;
    s8 spE;
    s8 spD;
    s8 spC;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f11_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f29;
    f32 temp_f31;
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f12;
    f32 var_f13;
    f32 var_f13_2;
    f32 var_f13_3;
    f32 var_f30;
    s16 var_r8;
    s32 *var_r12;
    s32 *var_r27;
    s32 *var_r28;
    s32 temp_r0;
    s32 temp_r10;
    s32 var_ctr;
    s32 var_r7;
    u8 temp_r10_2;
    u8 temp_r10_3;
    u8 temp_r11;
    u8 temp_r9;
    u8 temp_r9_2;
    void *var_r10;
    void *var_r11;
    void *var_r8_2;

    temp_r10 = *(s32 *)((char *)arg0 + (s32)0x17C);
    sp8 = QB_PARTICLE;
    spD = 1;
    var_r8 = 0x60;
    spE = 2;
    spC = 1;
    sp28 = temp_r10;
    if (temp_r10 != 0) {
        var_r8 = 0x61;
    }
    temp_r10_2 = *(u8 *)((char *)arg0 + (s32)0x179);
    sp2C = var_r8;
    sp38 = 0;
    sp3E = 0;
    sp2E = *(u8 *)((char *)arg0 + (s32)0x178);
    sp36 = 0x80;
    sp34 = 0x80;
    sp35 = 0x80;
    sp2F = temp_r10_2;
    sp37 = 0xFF;
    fn_800231C4(&sp8, &sp28, 1, 1, 0, 0, 0, temp_r10_2);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    sp48 = *(s32 *)((char *)0x8037B674 + (s32)0x20);
    sp4C = *(s32 *)((char *)0x8037B674 + (s32)0x24);
    sp50 = *(s32 *)((char *)0x8037B674 + (s32)0x28);
    sp54 = *(f32 *)&lbl_80296B9C;
    if ((s32) *(s32 *)((char *)arg0 + (s32)0x17C) != 0) {
        fn_8001F2D8(3, 9, 1, 0xB, 1, 0xD, 1);
    } else {
        fn_8001F2D8(2, 9, 1, 0xB, 1);
    }
    temp_r0 = *(s32 *)((char *)arg0 + (s32)0x94);
    if (temp_r0 > 0) {
        fn_8001F0A0(0x80, 0, (temp_r0 * 4) & 0xFFFC);
    }
    var_r7 = 0;
    var_r8_2 = *(s32 *)((char *)arg0 + (s32)0x124);
    var_r10 = *(s32 *)((char *)arg0 + (s32)0x100);
    var_r11 = var_r8_2 + ((*(s32 *)((char *)arg0 + (s32)0x170) - 1) * 3 * *(s32 *)((char *)arg0 + (s32)0x84) * 4);
    if ((s32) *(s32 *)((char *)arg0 + (s32)0x94) > 0) {
        temp_f29 = *(f32 *)&lbl_80296BA0;
        do {
            var_f30 = *(s32 *)((char *)var_r10 + (s32)0x28) / *(s32 *)((char *)var_r10 + (s32)0x2C);
            if ((s32) *(s32 *)((char *)arg0 + (s32)0x134) != 0) {
                sp58 = *(s32 *)((char *)var_r8_2 + (s32)0x0);
                sp5C = *(s32 *)((char *)var_r8_2 + (s32)0x4);
                sp60 = *(s32 *)((char *)var_r8_2 + (s32)0x8);
                *(s32 *)((char *)&sp58 + 0xC) = temp_f29;
                var_f13 = *(s32 *)((char *)var_r11 + (s32)0x4);
                var_f12 = *(s32 *)((char *)var_r11 + (s32)0x8);
                sp68 = *(s32 *)((char *)var_r11 + (s32)0x0);
            } else {
                temp_f11 = *(s32 *)((char *)arg0 + (s32)0x28);
                temp_f10 = *(s32 *)((char *)arg0 + (s32)0x2C);
                temp_f9 = *(s32 *)((char *)arg0 + (s32)0x30);
                sp58 = *(s32 *)((char *)var_r8_2 + (s32)0x0) + temp_f11;
                sp5C = *(s32 *)((char *)var_r8_2 + (s32)0x4) + temp_f10;
                sp60 = *(s32 *)((char *)var_r8_2 + (s32)0x8) + temp_f9;
                *(s32 *)((char *)&sp58 + 0xC) = temp_f29;
                var_f13 = *(s32 *)((char *)var_r11 + (s32)0x4) + temp_f10;
                sp68 = *(s32 *)((char *)var_r11 + (s32)0x0) + temp_f11;
                var_f12 = *(s32 *)((char *)var_r11 + (s32)0x8) + temp_f9;
            }
            sp6C = var_f13;
            sp70 = var_f12;
            *(s32 *)((char *)&sp68 + 0xC) = temp_f29;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            sp10C = *(s32 *)&lbl_80296BA0;
            0;
            0;
            0;
            0;
            0;
            0;
            if (0 > *(s32 *)&lbl_80296B9C) {
                0;
                0;
                sp114 = *(s32 *)&lbl_80296BA0;
                0;
            }
            temp_f13 = *(s32 *)((char *)var_r10 + (s32)0x18);
            var_ctr = 4;
            temp_f0 = ((*(s32 *)((char *)var_r10 + (s32)0x20) - temp_f13) * var_f30) + temp_f13;
loop_15:
            var_ctr -= 1;
            if (var_ctr != 0) {
                goto loop_15;
            }
            sp128 = temp_f0;
            sp130 = temp_f0;
            sp118 = temp_f0;
            sp120 = temp_f0;
            temp_f31 = *(s32 *)((char *)arg0 + (s32)0x110);
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            if (0 != 0) {
                if (var_f30 < temp_f31) {
                    var_f30 /= temp_f31;
                    var_r27 = *(s32 *)((char *)arg0 + (s32)0x114);
                    var_r28 = *(s32 *)((char *)arg0 + (s32)0x118);
                } else {
                    var_r27 = *(s32 *)((char *)arg0 + (s32)0x118);
                    var_r28 = *(s32 *)((char *)arg0 + (s32)0x11C);
                    var_f30 = (var_f30 - temp_f31) / (temp_f29 - temp_f31);
                }
            } else {
                var_r27 = *(s32 *)((char *)arg0 + (s32)0x114);
                var_r28 = *(s32 *)((char *)arg0 + (s32)0x11C);
            }
            temp_f11_2 = *(s32 *)((char *)arg0 + (s32)0xF4);
            temp_f5 = *(s32 *)&lbl_80296B9C;
            temp_f6 = *(f32 *)&lbl_80296BB8;
            var_r12 = &spF8;
loop_22:
            sp100 = *((s32 *)var_r27);
            sp104 = *((s32 *)var_r28);
            var_r27 += 4;
            var_r28 += 4;
            temp_r10_3 = (u8) sp100 + (s32) ((f32) (f64) ((u8) sp104 - (u8) sp100) * var_f30);
            *(s32 *)((char *)var_r12 + (s32)0x0) = temp_r10_3;
            temp_r9 = *(s32 *)((char *)&sp100 + 0x1);
            *(u8 *)((char *)var_r12 + (s32)0x1) = (u8) (temp_r9 + (s32) ((f32) (f64) (*(u8 *)((char *)&sp104 + 0x1) - temp_r9) * var_f30));
            temp_r11 = *(s32 *)((char *)&sp100 + 0x2);
            *(u8 *)((char *)var_r12 + (s32)0x2) = (u8) (temp_r11 + (s32) ((f32) (f64) (*(u8 *)((char *)&sp104 + 0x2) - temp_r11) * var_f30));
            temp_r9_2 = *(s32 *)((char *)&sp100 + 0x3);
            *(s8 *)((char *)var_r12 + (s32)0x3) = (s8) (temp_r9_2 + (s32) ((f32) (f64) (*(s8 *)((char *)&sp104 + 0x3) - temp_r9_2) * var_f30));
            temp_f0_2 = temp_f11_2 * *(f32 *)((char *)arg0 + (s32)0x68) * (f32) (f64) temp_r10_3;
            var_f13_2 = temp_f5;
            if (!(temp_f0_2 < temp_f5)) {
                var_f13_2 = temp_f0_2;
                if (temp_f0_2 > temp_f6) {
                    var_f13_2 = temp_f6;
                }
            }
            var_f13_3 = *(s32 *)&lbl_80296B9C;
            *(s32 *)((char *)var_r12 + (s32)0x0) = (u8) (s32) var_f13_2;
            temp_f12 = *(f32 *)&lbl_80296BB8;
            temp_f0_3 = temp_f11_2 * *(f32 *)((char *)arg0 + (s32)0x6C) * (f32) (f64) *(u8 *)((char *)var_r12 + (s32)0x1);
            if (!(temp_f0_3 < var_f13_3)) {
                var_f13_3 = temp_f0_3;
                if (temp_f0_3 > temp_f12) {
                    var_f13_3 = temp_f12;
                }
            }
            temp_f11_3 = *(s32 *)&lbl_80296B9C;
            *(u8 *)((char *)var_r12 + (s32)0x1) = (u8) (s32) var_f13_3;
            temp_f12_2 = *(f32 *)&lbl_80296BB8;
            temp_f13_2 = temp_f11_2 * *(f32 *)((char *)arg0 + (s32)0x70) * (f32) (f64) *(u8 *)((char *)var_r12 + (s32)0x2);
            if (temp_f13_2 < temp_f11_3) {
                var_f0 = temp_f11_3;
            } else {
                var_f0 = temp_f13_2;
                if (temp_f13_2 > temp_f12_2) {
                    var_f0 = temp_f12_2;
                }
            }
            *(u8 *)((char *)var_r12 + (s32)0x2) = (u8) (s32) var_f0;
            var_r12 += 4;
            if (var_r12 <= (s32 *) (&spF8 + 4)) {
                goto loop_22;
            }
            if ((s32) *(s32 *)((char *)arg0 + (s32)0x17C) != 0) {
                fn_8001F0F8(sp98, sp9C, spA0);
                fn_8001F1D4(spF8);
                temp_f1 = *(s32 *)&lbl_80296B9C;
                fn_8001F200(temp_f1, temp_f1);
                fn_8001F0F8(spA8, spAC, spB0);
                fn_8001F1D4(spF8);
                fn_8001F200(*(f32 *)&lbl_80296BA0, *(s32 *)&lbl_80296B9C);
                fn_8001F0F8(spB8, spBC, spC0);
                fn_8001F1D4(*(s32 *)((char *)&spF8 + 0x4));
                temp_f1_2 = *(f32 *)&lbl_80296BA0;
                fn_8001F200(temp_f1_2, temp_f1_2);
                fn_8001F0F8(spC8, spCC, spD0);
                fn_8001F1D4(*(s32 *)((char *)&spF8 + 0x4));
                fn_8001F200(*(s32 *)&lbl_80296B9C, *(f32 *)&lbl_80296BA0);
            } else {
                fn_8001F0F8(sp98, sp9C, spA0);
                fn_8001F1D4(spF8);
                fn_8001F0F8(spA8, spAC, spB0);
                fn_8001F1D4(spF8);
                fn_8001F0F8(spB8, spBC, spC0);
                fn_8001F1D4(*(s32 *)((char *)&spF8 + 0x4));
                fn_8001F0F8(spC8, spCC, spD0);
                fn_8001F1D4(*(s32 *)((char *)&spF8 + 0x4));
            }
            var_r7 += 1;
            var_r10 += 0x30;
            var_r8_2 += 0xC;
            var_r11 += 0xC;
        } while (var_r7 < (s32) *(s32 *)((char *)arg0 + (s32)0x94));
    }
    if (*(s32 *)((char *)arg0 + (s32)0x94) > 0) {
        fn_8001F0F4();
    }
}
