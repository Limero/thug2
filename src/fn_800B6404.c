// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6404-0x800B6570 (364B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802988C4;   /* 0.0f      */
extern f32 lbl_802988C0;   /* anchor: big is read as *(f64*)(&C0 + 8) */
extern f64 lbl_802988C8;   /* 2^52      */
extern f32 lbl_802988D0;   /* M_PI_2    */
extern f32 lbl_802988D4;   /* 1.0f      */
extern s32 lbl_80303150;   /* paused-clock accumulator (s32) */

s32 fn_800145AC(void);
s32 Tmr_GetTime(void);
f32 sinf(f32);

/* File-local layout of the first 0x18 bytes of the receiver.  Do NOT use the
   shared Unk_DB0E2BAB: it types +0x0/+0x8/+0xC as s32, this function lfs them. */
typedef struct {
    f32 f0;    /* +0x00 threshold   */
    s32 i4;    /* +0x04 start ticks */
    f32 f8;    /* +0x08 base        */
    f32 fC;    /* +0x0C scale       */
    s32 i10;   /* +0x10 pow         */
    s32 i14;   /* +0x14 flags       */
} B6404;

f32 fn_800B6404(B6404 *arg0) {
    volatile double _dummy;
    volatile double _dummy2;
    volatile union { u32 w[2]; f64 d; } cvt;
    f64 temp_d;
    f64 big;
    register s32 c4330 __asm__("r10");
    register s32 pgA __asm__("r11");
    s32 temp_r0;
    s32 temp_r9;
    f32 var_f31;
    f32 temp_f12;
    f32 temp_f11;
    f32 var_f1;

    temp_r0 = arg0->i14;
    var_f31 = lbl_802988C4;
    if (temp_r0 < 0) {
        if (temp_r0 & 0x20000000) {
            cvt.w[1] = fn_800145AC() - arg0->i4;
            c4330 = 0x43300000;
            cvt.w[0] = c4330;
            /* SOLVED 2026-10-13: pgA reads 2^52 through the NEIGHBOUR
               symbol lbl_802988C0 + 8 (== lbl_802988C8).  The old form
               (&lbl_802988C8 - 0x7738) was masked-EXACT but LINK-BROKEN:
               GAS folds (sym+addend) into BOTH HA16 and LO16 relocs, so
               MWLD produced HA(0x80291190)=0x8029 / LO=0x1190 instead of
               want's 0x802A/0x88C8 (3 differing link bytes).  With (C0,+8)
               the folded address IS lbl_802988C8, so both relocs resolve to
               want's exact words.  Small offsets keep the pinned r11 (the
               zero-offset form lets combine delete pgA and reload falls back
               to r9); do NOT "simplify" this back. */
            pgA = (s32)&lbl_802988C0;
            big = *(f64 *)((char *)pgA + 8);
            temp_d = cvt.d;
            /* ZERO emitted instructions.  Load-bearing: it is the only thing
               that stops GCC 2.95 tail-merging the two arms' identical
               `lfd f0,0x18(r1)` into the join.  Retail keeps that lfd in BOTH
               arms and shares only fsub+frsp. */
            __asm__ volatile("" : : "m"(cvt));
            temp_f12 = (f32)(temp_d - big);
        } else {
            /* SOLVED 2026-10-13: the last 2 words (arm-B i4 colour want r8
               got r11, const want r10 got r11-chained) are forced with two
               hard-register pins + a volatile i4 read + a staged call
               result.  Mechanism (all probe-verified): a plain `ti4 = i4`
               pin SILENTLY DELETES the lwz (FINDING 4); the volatile read
               keeps it (`lwz r8,4(r31)` survives) and the pin forces r8 in
               the subf.  Staging `t = Tmr_GetTime()` lets the ti4 assignment
               sit BELOW the call, so ti4 is not live across it (else the
               lwz hoists above the bl AND the extra crossing pressure moves
               the acc page anchor r9->r11).  Pinning the 0x43300000 constant
               to r10 the same way forces the remaining word.  Both pins are
               value-carrying (their uses emit want's exact words) and the
               file emits ZERO inline-asm instructions (register attributes
               only), same idiom as the arm-A c4330/pgA pins. */
            register s32 ti4 __asm__("r8");
            register s32 c10 __asm__("r10");
            s32 t = Tmr_GetTime();
            ti4 = *(volatile s32 *)&arg0->i4;
            c10 = 0x43300000;
            cvt.w[1] = (*(s32 *)&lbl_80303150 + t) - ti4;
            cvt.w[0] = c10;
            temp_d = cvt.d;
            big = lbl_802988C8;
            temp_f12 = (f32)(temp_d - big);
        }
        temp_f11 = arg0->f0;
        if (temp_f12 > temp_f11) {
            temp_r0 = arg0->i14;
            if (temp_r0 & 0x40000000) {
                var_f31 = arg0->f8 + arg0->fC;
            } else {
                arg0->i14 = temp_r0 & 0x7FFFFFFF;
            }
        } else {
            temp_r0 = arg0->i10;
            if (temp_r0 != 0) {
                if (temp_r0 < 0) {
                    /* Two statements, NOT one nested expression: the 1.0f
                       constant must be loaded AFTER the sinf call so ngccc
                       re-materialises the page anchor into the same scratch
                       register r9 (retail: lis r9 / lfs -0x7730(r9) / bl /
                       lis r9 / lfs -0x772c(r9)).  Fused, the second anchor
                       needs a callee-saved reg and the frame's stw r31
                       degrades to stmw r30. */
                    var_f1 = sinf(lbl_802988D0 - ((temp_f12 * lbl_802988D0) / temp_f11));
                    var_f1 = lbl_802988D4 - var_f1;
                } else {
                    var_f1 = sinf((temp_f12 * lbl_802988D0) / temp_f11);
                    temp_r9 = arg0->i10 - 1;
                    if (temp_r9 > 0) {
                        do {
                            var_f1 *= var_f1;
                        } while (--temp_r9 != 0);
                    }
                }
                var_f31 = (var_f1 * arg0->fC) + arg0->f8;
            } else {
                var_f31 = arg0->f8 + ((temp_f12 * arg0->fC) / temp_f11);
            }
        }
    }
    return var_f31;
}
