// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011B9F4-0x8011BC18 (548B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* arg2 layout recovered from fn_8011A4E4's promoted prototype (FlagV):
   f32 x,y,z then s32.  The want reads it with lfs at 0x0/0x4/0x8 and lwz at 0xC. */
typedef struct { f32 f0; f32 f4; f32 f8; s32 iC; } B50Arg2;
/* fn_80119B24 result: f32 at 0x10, s32 at 0x1C (fn_8011A4E4's SrcV). */
typedef struct { char p0[0x10]; f32 f10; char p14[8]; s32 i1C; } B50Src;
/* fn_801195DC ctor writes offset 0x14 -> 0x18-byte iterator. */
typedef struct { char p[0x18]; } B50It;
/* arg3's 0xA0 vector pair: identical to the promoted fn_800CD008's
   Unk_A2289594 (arg1 there) which carries __ps_t at 0xA0 and 0xA8. */
typedef struct { char p[0xA0]; __ps_t unk0xA0; __ps_t unk0xA8; } B50VecA0;
/* two __ps_t = the 16B value copied from arg3+0xA0. */
typedef struct { __ps_t q[2]; } B50P16;
/* fn_8011A4E4's DstV out-param. */
typedef struct { s32 i0; f32 f4, f8, fC, f10, f14, f18, f1C, f20, f24; s32 i28; } B50Dst;

s32 fn_80119470(void);
s32 fn_80119B24(s32, s32);
B50It *fn_801195DC(B50It *);
s32 fn_8005DEB4(void *, s32);
s32 fn_800CD0E0(Unk_FFAD6788 *, void *, Unk_EA529D06 *);
s32 fn_800CD008(Unk_EA529D06 *, Unk_A2289594 *, void *);
void fn_8011ADD4(s32, void *, B50Arg2 *, s32, s32, void *, f32);
void fn_8011976C(void *);
s32 fn_8011970C(void *);
s32 fn_80119A08(s32, s32);
void fn_8011A4E4(s32, void *, B50Src *, B50Arg2 *);
void *fn_800145AC(void);
void fn_800CD3A0(Unk_FFAD6788 *, void *, s32);
void fn_80119640(void *, s32);
void fn_80119668(void *, f32);
s32 fn_8011A56C(s32, s32, void *, s32, f32, B50Arg2 *, s32);
void fn_8011A0A0(s32, s32, s32, void *);
void Script_GetInteger(s32, s32);
extern f32 lbl_8029D55C;
extern bool lbl_802FFE58;

s32 fn_8011B9F4(s32 arg0, s32 arg1, B50Arg2 *arg2, void *arg3, s32 arg4, s32 arg5) {
    B50It sp8;
    B50P16 sp20;
    B50Arg2 sp30;
    B50Dst sp40;
    B50Src *temp_r3;
    s32 temp_r3_2;
    void *var_r24;
    s32 var_r31;
    f32 temp_f0;
    f32 var_f1;

    if (fn_80119470() != 0) {
        return 0;
    }
    temp_r3 = (B50Src *)fn_80119B24(arg0, arg1);
    if (temp_r3 == NULL) {
        return 0;
    }
    fn_801195DC(&sp8);
    sp20.q[0] = ((B50VecA0 *)arg3)->unk0xA0;
    sp20.q[1] = ((B50VecA0 *)arg3)->unk0xA8;
    temp_r3_2 = fn_8005DEB4(&sp20, 0);
    if (temp_r3_2 != 0) {
        if (fn_800CD0E0(arg3, temp_r3_2, &sp20) != 0) {
            var_r24 = &sp20;
        } else {
            var_r24 = NULL;
        }
        fn_800CD008(&sp30, arg3, temp_r3_2);
        temp_f0 = arg2->f8;
        if (temp_f0 == lbl_8029D55C) {
            var_f1 = temp_r3->f10;
        } else {
            var_f1 = temp_f0;
        }
        fn_8011ADD4(arg0, &sp8, &sp30, arg2->iC, temp_r3_2, var_r24, var_f1);
    } else {
        fn_8011976C(&sp8);
    }
    if ((fn_8011970C(&sp8) != 0) && (arg5 == 0)) {
        if ((arg4 == 0) && (temp_r3->i1C != 0)) {
            var_r31 = fn_80119A08(arg0, arg1);
            fn_8011A4E4(arg0, &sp40, temp_r3, arg2);
            fn_800CD3A0(arg3, &sp40, fn_800145AC());
            goto block_20;
        }
        fn_80119640(&sp8, 2);
        return 0;
    }
    fn_80119668(&sp8, arg2->f4);
    var_r31 = fn_8011A56C(arg0, arg1, &sp8, 0, arg2->f0, arg2, 0);
    if (lbl_802FFE58 == 0) {
        Script_GetInteger(QB_UNKNOWN_0x6D2E270E, 0);
    }
    if (arg4 == 0) {
        fn_8011A0A0(arg0, var_r31, arg1, arg3);
        if (lbl_802FFE58 == 0) {
            Script_GetInteger(QB_UNKNOWN_0x6D2E270E, 0);
        }
    }
block_20:
    fn_80119640(&sp8, 2);
    return var_r31;
}

// ---------------------------------------------------------------------------
// SOLVED (was 97.1%, 4 residual words).  Both residuals were 2-word swaps
// inside one basic block, i.e. ngccc ready-list tie-breaks, and both were
// caused by the CALLER declaring the wrong return type for a callee whose
// result is discarded -- see notes 7a/7b at the top of this file.  Fixing the
// two prototypes (nothing else changed) took it to 100.0%.
//
// Still ruled out (all measured, all worse -- do not retry):
//  * psq copy placed BEFORE `fn_801195DC(&sp8)`: 552B (+1 word), the ctor call
//    gets resequenced and a duplicate `addi r3,r1,8` is born.
//  * whole-16B-struct copy `sp20 = *(B50P16 *)(arg3+0xA0)`: gives the correct
//    `addi r30` before `addi r3` but the copy degenerates to lwz/stw + an
//    extra `addi r9`: 568B.
//  * hoisting `&sp20` into a `void *p20` temp: psq copy degrades to a word
//    move (532B) or p20 gets its own callee-saved reg (556B).
//  * `var_r24 = &sp20;` before the ctor: pins var_r24 to r29 and adds a second
//    test/branch (556B).
//  * `B50It sp8[1]` + array decay instead of `&sp8`: byte-identical, no change.
//  * `-fno-schedule-insns2`: 93.4%.  `-fno-crossjumping`: compile FAIL.
//    `-fno-delayed-branch`: identical.
//  * fn_8011A4E4 param-type variants (8 tried, `void*`/`B50Dst*` in any slot):
//    no effect -- the RETURN type is what matters there, not the params.
