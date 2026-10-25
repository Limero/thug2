// PARKED 2026-10-30: FAIL -> 3.2% (index-aligned; object is still
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 2.7435% -> 3.0178% per-object flags: -mps-float -> -O1 -mps-float
// 106 instructions SHORT of want, so per AGENTS §6cs-1/§6es that number is a
// lower bound and not a real measurement).
//
// FLAG: -O1
// ===========================================================================
// 0x8011ADD4 -- 2916 B / 729 instructions.  Gekko PAIRED-SINGLE throughout.
// ===========================================================================
// NOT MATCHABLE IN ONE ROUND.  Everything below is ground truth hand-decoded
// from the DOL, so a follow-up session does not have to repeat
// any of it.
//
// ---- Gekko PS encoding (PROVEN, corrects older notes) ---------------------
// Compiling one builtin per TU with `ngccc -O2 -G0 -mcpu=750 -fno-common
// -mps-float` and reading the object gives:
//     opcode = bits 31..26   (4 = PS arith, 56 = psq_l, 60 = psq_st)
//     frD    = bits 25..21
//     frA    = bits 20..16
//     frB    = bits 15..11
//     Rc     = bits 10..6
//     XO     = bits  5..1      <-- NOT bits 21..30, which is what several
//     bit 0  = 0                     older project notes assume
//   XO: 8=ps_mr(Rc2)/ps_nabs(Rc1)/ps_abs(Rc4)/ps_neg(Rc8), 10=sum0, 11=sum1,
//       12=muls0, 13=muls1, 14=madds0, 15=madds1, 16=merge(Rc16..19 =
//       merge00/01/10/11), 18=div, 20=sub, 21=add, 23=sel, 24=res, 25=mul,
//       26=rsqrte, 28=msub, 29=madd, 30=nmsub, 31=nmadd.
//   Worked examples from this function (raw word -> decoded pair op):
//       0x11AD0372 yields a pair multiply of f13 by f0, and 0x1000681C a
//       multiply-add-sub of f0 by f13; 0x11AD02BA yields a pair multiply-add
//       of f13 by f10 plus f0, and 0x10C05090 a pair move of f0 into f6;
//       0x10000014 is a pair sum and 0x10000034 a pair reciprocal-sqrt.
//   Capstone prints essentially ALL of these as AltiVec (`vmsumshm`,
//   `vmhaddshs`, `xxsel`, `xxperm`, `maddhd`, `xsdivsp`, `xssubsp`, ...).
//   THEY ARE ALL WRONG -- this function contains ZERO genuine VMX words, so
//   doc-29 must never be cited for it.  Use tools/ps_disasm.py / a raw-word
//   decode, never tools/disasm.py (which also stalls at the first PS word).
//
// ---- frame / ABI ---------------------------------------------------------
//   Want allocates a 0x220 frame with 18 FPR saves (f14-f31 at 0x190-0x218),
//   7 GPR saves (r25 up at 0x174) and the LR slot at 0x224 above the frame top;
//   the locals region is r1+0x08-r1+0x16C (0x164 B) with the GPR save area at
//   0x174 and the FPR area at 0x190-0x220.
//   Param homes (this fixes the m2c signature, which had the float LAST):
//     the first three args home to r25/r30/r27, the float to f30, and the
//     last three args to r29/r28/r31,
//     => (arg0, arg1, arg2, FLOAT, arg3, arg4, arg5)
//
// ---- callee signatures (all audited from their own prologiles this round) -
//   0x80119470 s32  (void)              -- global mode test, no arg reg read
//   0x8011976C void (void*)             -- memset(p, 0, 0x14)
//   0x80119BF8 s32  (void*)             -- reads r3+4 only; m2c invented 3 extra
//   0x80024660 void*(void*)             -- adds 0x68 to the incoming r3 and returns: MATRIX GETTER
//   0x800246AC void*(void*)             -- adds 0x78 to the incoming r3 and returns
//   0x801196B8 f32  (void*)             -- max|f| over 2 or 5 floats
//   0x8011970C s32  (void*)             -- tests v[0],v[1] == 0 then 0x14
//   0x8011AC40 void (void*, void*, void*)  -- writes 5 floats to arg2
//   0x80270CA4 f32  (f32)               -- sqrtf
//
// ---- constants (all .rodata2 data:float, page 0x8029D540) ---------------
//   lbl_8029D540 = 0.0f   lbl_8029D544 = 1.05f  lbl_8029D548 = 1.0f
//   lbl_8029D54C = 3.0f   lbl_8029D550 = 0.25f  lbl_8029D554 = 100.0f
//   lbl_8029D558 = 0.5f   lbl_80302C3C = .data f32
//
// ---- stack map (already implemented as the L[] array + #defines) ---------
//   0x08..0x17  5 floats: fn_8011AC40's output vector (r31 = r1+8)
//   0x18..0x27  4 floats: -(fn_800246AC(r28))[0..3]   (a translation)
//   0x28..0x37  4 floats: -(fn_800246AC(r28))[0x20..0x2C]
//   0x38..0x77  16 floats: the 4x4 matrix  (sp38..sp74)
//   0x78..0xC7  20 floats: result block  (sp78..spC4)
//   0xC8        scalar   (spC8)   0xD4 0xD8 0xE0  (spD4/spD8/spE0)
//   0xE8..0x117 12 floats: cofactors   (spE8..sp114)
//   0x124 scalar (sp124)   0x128..0x15F 14 floats: normalise block (sp128..sp15C)
//   Unused words (0xCC,0xD0,0xDC,0xE4,0x118..0x123,0x160..0x16B) are the
//   holes the want never touches; the #defines leave them in place so every
//   offset stays exact.
//
// ---- control flow (from the want, branch targets decoded) -----------------
//   if (fn_80119470() != 0)            -> return 1
//   fn_8011976C(arg1);
//   if (fn_80119BF8(arg0) != 0)        -> return 1
//   if (arg4 == 0) { arg4 = fn_8005DEB4(arg2, 0); if (!arg4) return 1; }
//   <PS dot-product block, 0x8011AE98..0x8011AEE4>
//   if (arg5 == 0) { if (f30 == 0.0f) f30 = lbl_80302C3C; }
//   else           { <PS> f30 = spB8 + spC0; }          // NOT fabs(spB8)
//   if (!(spB8 > f30)) { if (spB8*1.05f > f30) return 0; return 1; }
//   f11 = spB8 / f30;  spC8 = 1.05f;                     // seeded before switch
//   switch (arg3) 0: ((1-t)*3 + (1-t*t)) * 0.25 * 100
//                 1: (1-t) * 100
//                 2: (1-t)^2 * 100
//                 3: sqrtf(1-t) * 100
//                 default: leave 1.05f
//   mode = arg1->unk0x14;
//   if (mode < 0)  return 1;
//   if (mode <= 1) -> 0x8011B070  SMALL 2x2 path, then RETURNS at 0x8011B8D8
//   if (mode == 2) -> 0x8011B29C  BIG 4x4 PS matrix path, then the shared
//                    fn_8011AC40 + 5-iteration loops + fn_8011970C tail
//   else           return 1;
//   NOTE: the two paths do NOT converge.  The 4x4 code (0x8011B324..0x8011B7E0,
//   ~350 instructions) is reachable ONLY from mode==2.  m2c's nesting makes
//   it look shared, which is why a naive reading of the draft over-estimates
//   how much of the body is common.
//
// ---- WHAT WAS FIXED THIS ROUND (semantic, no asm) ------------------------
//  1. COMPILE: `sqrtf()` with no argument (m2c dropped the whole sum-of-squares
//     loop).  Restored from 0x8011B888..0x8011B8AC: sum arg1->v[0..4]^2 into a
//     running f1 seeded with 0.0f, then sqrtf of it.
//  2. Signature: the float is the FOURTH parameter (param-home prologue).
//  3. Callee arity/prototypes: fn_80119BF8 is 1-arg (m2c passed 4),
//     fn_801196B8 is 1-arg and takes arg1 (m2c passed arg0+arg1 at one site
//     and a spurious second fabs at the other), fn_80024660/AC are 1-arg
//     pointer getters (m2c passed 4 to one), fn_8011AC40 is 3-arg.
//     This removed 4 spurious crclr cr1eq and fixed the arg-setup windows.
//  4. STATICS-DCE (§6j-4): all ~90 stack slots were file-scope `static`, so the
//     object had frame 0x98 and was 1456 B.  They are now the L[] frame array
//     with the want's exact r1 offsets: frame 0x98 -> 0x250, object
//     1456 B -> 2492 B, and the FPR save block now starts at f14 as in want.
//  5. Two m2c `if (0 != 0)` / `if (0 > x)` DCE'd control blocks restored from
//     the want's fcmpu+ble pairs (0x8011AF50, 0x8011B0E4, 0x8011B7F4).
//
// ---- RESIDUAL / WHY IT IS PARKED ----------------------------------------
//  * The object is 106 instructions (424 B) SHORT of want, so the index-aligned
//    3.2% is a floor, not a score.  Attribution:
//      - 45 `0;` statements x 2 words = 90 words.  Per §6ec-1 / §6fd these are
//        MISSING PAIRED-SINGLE PAIR COPIES (psq_l+psq_st), not dead code: the
//        want has 77 psq_l/psq_st words.  Each is one `*(__ps_t *)dst =
//        *(__ps_t *)src;` and needs `-mps-float` (the flag is now on the
//        header, measured inert today because the body has no `__ps_t` yet).
//      - ~16 words: the ps_add/ps_madd/ps_sum0 normalisation blocks that m2c
//        emitted as nothing at all.
//  * Frame 0x250 vs want 0x220: 56 B of extra spill slots (0x170..0x1A8) and
//    6 GPR saves instead of 7.  Both are consequences of the m2c body having
//    ~50 named `temp_f*` locals that want keeps in FPRs; they only resolve
//    once the PS body is real.  Per §6fr/§6fk the frame is coupled to the
//    callee-saved register COUNT, so do not chase it with pad/dummy levers.
//  * Private `.rodata` 0x10 B = {0.0f, 0.0f, 0x4330000080000000} -- the
//    doc-14 int->f64 conversion pool.  Even at EXACT this file would be
//    EXACT-in-wip and NOT promote-clean until fix_fp_pool.py retargets it
//    (§4n / docs/parkings/solved/14).  Writing 0.0f as `lbl_8029D540` did not
//    shrink it, so the pool is fed by a conversion elsewhere in the body.
//
// ---- LEVERS ALREADY TRIED (do not repeat) -------------------------------
//   * `volatile double _dummy` / frame pads: NOT applicable, want is
//     8-aligned (0x220) and the body already produces the full +8 FPR headroom
//     on its own (0x98 -> 0x250 with no dummies at all).
//   * `-mps-float` on the whole body: measurably INERT today (2492 B with and
//     without) -- re-measure after the `__ps_t` copies are restored (§6bx).
//   * Frame-size sweep on the L[] array (L[68..89]): Gsave moves in ~8 B steps
//     but never lands on 0x174 because the 56 B of extra spill is not the
//     array's size.  86 is the minimum that keeps every #define in range.
//   * No pins, no barriers, no flags beyond -mps-float were used: per §6ea and
//     §6ef a 3% body with a 106-word length deficit is a SEMANTIC problem and
//     every allocation lever is inert until the length is right.
//
// ---- SUGGESTED NEXT STEPS ------------------------------------------------
//  1. Decode the 45 `0;` sites against the want's 77 psq pairs and write them
//     as `*(__ps_t *)dst = *(__ps_t *)src;` (8 bytes = ONE __ps_t in cc1, so a
//     16-byte copy is TWO assignments -- §6dq-1).
//  2. Rebuild the mode==2 4x4 path as a paired-single matrix inverse in a
//     __ps_t-typed frame struct; m2c's scalar expression decomposition of the
//     cofactors is semantically right (it reads the same 0x38..0x77 slots) but
//     the emission shape is `fmsubs`/`fnmadds` contraction, which only comes
//     out of PS `ps_madd`/`ps_msub`, not from scalar C.
//  3. Only then chase the frame / the 7th GPR save.
//
// family=m2c range=0x8011ADD4-0x8011B938 size=2916B
// FLAG: -mps-float
#include "types.h"
#include "structs.h"

/* arg1: 5 floats at 0..0x10 plus a mode word at 0x14 (fn_8011976C memsets
   0x14 bytes of it; fn_801196B8 walks 2 or 5 of the floats depending on
   0x14; fn_8011970C tests 0 and 1 for zero). */
typedef struct {
    f32 v[5];
    s32 unk0x14;
} A1_t;

/* Real signatures, audited from each callee's own prologue.
   fn_80024660/AC are 1-arg MATRIX GETTERS (`addi r3,r3,0x68/0x78; blr`). */
extern s32  fn_80119470(void);
extern void fn_8011976C(void *);
extern s32  fn_80119BF8(void *);
extern void *fn_80024660(void *);
extern void *fn_800246AC(void *);
extern f32  fn_801196B8(void *);
extern s32  fn_8011970C(void *);
extern void fn_8011AC40(void *, void *, void *);
extern s32  fn_8005DEB4(s32, s32);

extern const f32 lbl_8029D540; /* 0.0f  */
extern const f32 lbl_8029D544; /* 1.05f */
extern const f32 lbl_8029D548; /* 1.0f  */
extern const f32 lbl_8029D54C; /* 3.0f  */
extern const f32 lbl_8029D550; /* 0.25f */
extern const f32 lbl_8029D554; /* 100.0f*/
extern const f32 lbl_8029D558; /* 0.5f  */
extern f32 lbl_80302C3C;

/* Frame slots: every m2c "spNN" name is its true r1 offset (r1+0x08 is
   L[0]); per §6q-86 / §6de every gap is an explicit pad in a hand-written
   field-layout struct, here flattened to one word array with the unused words
   left in place so the offsets stay exact. */
#define __sp8_0 L[0]
#define __sp8_4 L[1]
#define __sp8_8 L[2]
#define spC L[1]
#define sp14 L[3]
#define sp18 L[4]
#define sp1C L[5]
#define sp20 L[6]
#define sp24 L[7]
#define sp28 L[8]
#define sp2C L[9]
#define sp30 L[10]
#define sp34 L[11]
#define sp38 L[12]
#define sp3C L[13]
#define sp40 L[14]
#define sp44 L[15]
#define sp48 L[16]
#define sp4C L[17]
#define sp50 L[18]
#define sp54 L[19]
#define sp58 L[20]
#define sp5C L[21]
#define sp60 L[22]
#define sp64 L[23]
#define sp68 L[24]
#define sp6C L[25]
#define sp70 L[26]
#define sp74 L[27]
#define sp78 L[28]
#define sp7C L[29]
#define sp80 L[30]
#define sp84 L[31]
#define sp88 L[32]
#define sp8C L[33]
#define sp90 L[34]
#define sp94 L[35]
#define sp98 L[36]
#define sp9C L[37]
#define spA0 L[38]
#define spA4 L[39]
#define spA8 L[40]
#define spAC L[41]
#define spB0 L[42]
#define spB4 L[43]
#define spB8 L[44]
#define spBC L[45]
#define spC0 L[46]
#define spC4 L[47]
#define spC8 L[48]
#define spD4 L[51]
#define spD8 L[52]
#define spE0 L[54]
#define spE8 L[56]
#define spEC L[57]
#define spF0 L[58]
#define spF4 L[59]
#define spF8 L[60]
#define spFC L[61]
#define sp100 L[62]
#define sp104 L[63]
#define sp108 L[64]
#define sp10C L[65]
#define sp110 L[66]
#define sp114 L[67]
#define sp124 L[71]
#define sp128 L[72]
#define sp12C L[73]
#define sp130 L[74]
#define sp134 L[75]
#define sp138 L[76]
#define sp13C L[77]
#define sp140 L[78]
#define sp144 L[79]
#define sp148 L[80]
#define sp14C L[81]
#define sp150 L[82]
#define sp154 L[83]
#define sp158 L[84]
#define sp15C L[85]

/* ABI order recovered from the want's param-home prologue:
   mr r25,r3 / mr r30,r4 / mr r27,r5 / fmr f30,f1 / mr r29,r6 / mr r28,r7 /
   mr r31,r8  ->  the float is the FOURTH parameter.  m2c had it last. */
s32 fn_8011ADD4(void *arg0, A1_t *arg1, s32 arg2, f32 farg0, s32 arg3, s32 arg4, s32 arg5) {
    f32 L[0x164 / 4];   /* r1+0x08 .. r1+0x16C: the real frame */
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f15;
    f32 temp_f16;
    f32 temp_f17;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f8;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f11;
    f32 var_f30;
    s32 temp_r0;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_r0;
    s32 var_r28;
    s32 var_r3;
    s32 var_r9;
    s32 i;
    f32 sqsum;
    s32 var_r9_2;
    CStruct *temp_r3;
    Unk_C7387A53 *temp_r3_2;

    var_f30 = farg0;
    var_r28 = arg4;
    var_r3 = 1;
    if (fn_80119470() != 0) {
        return var_r3;
    }
    fn_8011976C(arg1);
    /* want: mr r3,r25 ; bl fn_80119BF8 -- ONE arg (it reads r3+4 only).
       m2c invented three extra args, which cost a crclr cr1eq and shifted
       the whole arg-setup window. */
    if (fn_80119BF8(arg0) != 0) {
        return var_r3;
    }
    if (var_r28 == 0) {
        var_r28 = fn_8005DEB4(arg2, 0);
        if (var_r28 == 0) {
            return var_r3;
        }
    }
    {
    fn_80024660((void *)var_r28);
                0;
                0;
                0;
                0;
                0;
                if (arg5 != 0) {
                    fn_80024660((void *)var_r28);
                    0;
                    0;
                    0;
                    0;
                    0;
                    var_f30 = spB8 + spC0;
                } else if (var_f30 == lbl_8029D540) {
                    var_f30 = lbl_80302C3C;
                }
                0;
                /* m2c rendered this test as the constant `0 != 0` and DCE'd the
                   whole arm (§6eh).  Recovered from the want: at 0x8011AF50 a
                   float compare of spB8 (f31, loaded from 0xb8(r1) — NOT an
                   absolute value) against the limit, with an unordered-OR and
                   a no-overflow branch to 0x8011AF78; at 0x8011AF60 the
                   result is zeroed, at 0x8011AF68 spB8 scaled by 1.05f is
                   compared against the limit with a greater-than branch to
                   the epilogue returning 0, and 0x8011AF74 branches to
                   0x8011B8D8 returning 1. */
                if (!(spB8 > var_f30)) {
                    var_r3 = 0;
                    if ((spB8 * lbl_8029D544) > var_f30) {
                        return 0;
                    }
                    return 1;
                }
                {
                    /* 0x8011AF7C fdivs f11,f31,f30 ; 0x8011AF80/0x8011AF88
                       lfs+stfs -> spC8 is seeded with 1.05f before the switch. */
                    temp_f11 = spB8 / var_f30;
                    spC8 = lbl_8029D544;
                    switch (arg3) {                 
                    case 0:
                        temp_f13 = lbl_8029D548;
                        spC8 = (((temp_f13 - temp_f11) * lbl_8029D54C) + (temp_f13 - (temp_f11 * temp_f11))) * lbl_8029D550 * lbl_8029D554;
                        break;
                    case 1:
                        var_f0 = lbl_8029D548 - temp_f11;
block_21:
                        spC8 = var_f0 * lbl_8029D554;
                        break;
                    case 2:
                        temp_f0 = lbl_8029D548 - temp_f11;
                        var_f0 = temp_f0 * temp_f0;
                        goto block_21;
                    case 3:
                        spC8 = sqrtf(lbl_8029D548 - temp_f11) * lbl_8029D554;
                        break;
                    }
                    temp_r0 = arg1->unk0x14;
                    if (temp_r0 >= 0) {
                        if (temp_r0 > 1) {
                            if (temp_r0 != 2) {

                            } else {
                                temp_f31 = fabs(spC8);
                                if (temp_f31 > fabs(fn_801196B8(arg1))) {
                                    fn_800246AC((void *)var_r28);
                                    var_ctr = 4;
                                    do {
                                        var_ctr -= 1;
                                    } while (var_ctr != 0);
                                    var_ctr_2 = 4;
                                    0;
                                    0;
                                    0;
                                    0;
                                    0;
                                    0;
                                    do {
                                        var_ctr_2 -= 1;
                                    } while (var_ctr_2 != 0);
                                    spF8 = sp68 * sp54;
                                    spE8 = sp68 * sp60;
                                    temp_f12 = (sp48 * sp70) - (sp68 * sp50);
                                    spF4 = sp6C * sp54;
                                    sp104 = temp_f12;
                                    temp_f28 = (sp58 * sp74) - (sp68 * sp64);
                                    temp_f17 = (sp5C * sp74) - (sp6C * sp64);
                                    temp_f27 = (sp5C * sp70) - (sp6C * sp60);
                                    temp_f24 = (sp58 * sp70) - spE8;
                                    temp_f5 = (sp4C * sp74) - spF4;
                                    spEC = temp_f24;
                                    temp_f3 = (sp48 * sp74) - spF8;
                                    temp_f29 = (sp60 * sp74) - (sp70 * sp64);
                                    temp_f4 = (sp4C * sp70) - (sp6C * sp50);
                                    temp_f25 = (sp48 * sp64) - (sp58 * sp54);
                                    temp_f16 = (sp4C * sp64) - (sp5C * sp54);
                                    temp_f8 = (sp50 * sp74) - (sp70 * sp54);
                                    temp_f10 = (sp50 * sp64) - (sp60 * sp54);
                                    sp110 = sp48 * sp5C;
                                    temp_f9 = (sp58 * sp6C) - (sp68 * sp5C);
                                    temp_f30 = (sp48 * sp6C) - (sp68 * sp4C);
                                    sp10C = sp5C * sp50;
                                    spFC = sp40 * temp_f3;
                                    sp108 = (sp38 * temp_f5) - (sp3C * temp_f3);
                                    sp100 = (sp38 * temp_f8) - spFC;
                                    spF0 = (sp50 * temp_f9) + ((sp48 * temp_f27) - (sp4C * temp_f24));
                                    spAC = (sp40 * temp_f9) + ((sp38 * temp_f27) - (sp3C * spEC));
                                    temp_f15 = (sp48 * sp60) - (sp58 * sp50);
                                    temp_f26 = (sp54 * spEC) + ((sp48 * temp_f29) - (sp50 * temp_f28));
                                    temp_f12_2 = (sp54 * temp_f27) + ((sp4C * temp_f29) - (sp50 * temp_f17));
                                    sp78 = temp_f12_2;
                                    temp_f1 = (sp54 * temp_f9) + ((sp48 * temp_f17) - (sp4C * temp_f28));
                                    spB0 = -((sp40 * temp_f30) + ((sp38 * temp_f4) - (sp3C * temp_f12)));
                                    sp9C = -((sp44 * temp_f9) + ((sp38 * temp_f17) - (sp3C * temp_f28)));
                                    sp84 = -((sp44 * ((sp4C * sp60) - sp10C)) + ((sp3C * temp_f10) - (sp40 * temp_f16)));
                                    sp98 = temp_f1;
                                    spA0 = (sp44 * temp_f30) + sp108;
                                    spA4 = -((sp44 * (sp110 - (sp58 * sp4C))) + ((sp38 * temp_f16) - (sp3C * temp_f25)));
                                    sp94 = (sp44 * temp_f15) + ((sp38 * temp_f10) - (sp40 * temp_f25));
                                    sp7C = -((sp44 * temp_f27) + ((sp3C * temp_f29) - (sp40 * temp_f17)));
                                    sp8C = (sp44 * spEC) + ((sp38 * temp_f29) - (sp40 * temp_f28));
                                    var_f11 = -((sp44 * sp104) + sp100);
                                    sp80 = (sp44 * temp_f4) + ((sp3C * temp_f8) - (sp40 * temp_f5));
                                    sp90 = var_f11;
                                    sp88 = -temp_f26;
                                    spA8 = -spF0;
                                    temp_f0_2 = sp4C;
                                    temp_f24_2 = (temp_f0_2 * sp60) - sp10C;
                                    sp114 = temp_f24_2;
                                    temp_f6 = sp44 * spF0;
                                    temp_f1_2 = ((sp40 * temp_f1) + ((sp38 * temp_f12_2) - (sp3C * temp_f26))) - temp_f6;
                                    sp124 = temp_f6;
                                    spB4 = (sp40 * (sp110 - (sp58 * temp_f0_2))) + ((sp38 * temp_f24_2) - (sp3C * temp_f15));
                                    temp_f0_3 = lbl_8029D548;
                                    if (temp_f1_2 != temp_f0_3) {
                                        temp_f0_4 = temp_f0_3 / temp_f1_2;
                                        if (temp_f0_4 != lbl_8029D548) {
                                            sp148 = temp_f0_4;
                                            sp128 = temp_f0_4;
                                            sp130 = temp_f0_4;
                                            sp140 = temp_f0_4;
                                            0;
                                            0;
                                            var_f11 = 0;
                                            0;
                                            0;
                                            0;
                                            0;
                                            0;
                                        }
                                    }
                                    0;
                                    0;
                                    0;
                                    0;
                                    fn_80024660((void *)var_r28);
                                    0;
                                    0;
                                    0;
                                    0;
                                    sp28 = (sp14 * sp68) + ((__sp8_8 * sp58) + ((__sp8_0 * sp38) + (spC * sp48)));
                                    sp2C = (sp14 * sp6C) + ((__sp8_8 * sp5C) + ((__sp8_0 * sp3C) + (spC * sp4C)));
                                    sp30 = (sp14 * sp70) + ((__sp8_8 * sp60) + ((__sp8_0 * sp40) + (spC * sp50)));
                                    sp34 = (sp14 * sp74) + ((__sp8_8 * sp64) + ((__sp8_0 * sp44) + (spC * sp54)));
                                    0;
                                    temp_f31_2 = lbl_8029D540;
                                    if (temp_f31_2 > lbl_8029D540) {
                                        sp15C = lbl_8029D548;
                                    }
                                    fn_8011AC40(arg0, (void *)&__sp8_8, (void *)&sp78);
                                    var_ctr_3 = 5;
                                    var_r9 = 0;
                                    do {
                                        temp_f13_2 = *((s32 *)var_r9 + (s32)&sp78);
                                        if (temp_f13_2 > temp_f31_2) {
                                            temp_f13_3 = spC8 * temp_f13_2;
                                            if (temp_f13_3 > arg1->v[var_r9 / 4]) {
                                                arg1->v[var_r9 / 4] = temp_f13_3;
                                            }
                                        }
                                        var_r9 += 4;
                                        var_ctr_3 -= 1;
                                    } while (var_ctr_3 != 0);
                                    if (fn_8011970C(arg1) == 0) {
                                        var_ctr_4 = 5;
                                        do {
                                            var_ctr_4 -= 1;
                                        } while (var_ctr_4 != 0);
                                        sqsum = 0.0f;
                                        for (i = 0; i < 5; i++) {
                                            sqsum = arg1->v[i] * arg1->v[i] + sqsum;
                                        }
                                        temp_f1_3 = sqrtf(sqsum);
                                        var_r9_2 = 0;
                                        var_ctr_5 = 5;
                                        do {
                                            arg1->v[var_r9_2 / 4] = (spC8 * arg1->v[var_r9_2 / 4]) / temp_f1_3;
                                            var_r9_2 += 4;
                                            var_ctr_5 -= 1;
                                        } while (var_ctr_5 != 0);
                                    }
                                }
                            }
                        } else {
                            temp_f31_3 = fabs(spC8);
                            if (temp_f31_3 > fn_801196B8(arg1)) {
                                fn_80024660((void *)var_r28);
                                0;
                                0;
                                0;
                                temp_f31_4 = lbl_8029D540;
                                0;
                                0;
                                if (spC8 > lbl_8029D540) {
                                    spD4 = lbl_8029D548;
                                }
                                temp_r3 = fn_800246AC((void *)var_r28);
                                sp18 = -temp_r3->unk0x0;
                                sp1C = -temp_r3->unk0x4;
                                sp24 = -temp_r3->unk0xC;
                                sp20 = -temp_r3->unk0x8;
                                temp_f11_2 = lbl_8029D548;
                                0;
                                temp_f0_5 = (spD8 + temp_f11_2) * lbl_8029D558;
                                temp_f0_6 = temp_f11_2 - temp_f0_5;
                                temp_f10_2 = (temp_f11_2 - (temp_f0_6 * temp_f0_6)) * spC8;
                                temp_f1_4 = (temp_f11_2 - (temp_f0_5 * temp_f0_5)) * spC8;
                                if ((s32) arg1->unk0x14 == 1) {
                                    var_r0 = 0;
                                    if (temp_f10_2 > arg1->v[0]) {
                                        arg1->v[0] = temp_f10_2;
                                        var_r0 = 1;
                                    }
                                    if (temp_f1_4 > arg1->v[1]) {
                                        arg1->v[1] = temp_f1_4;
                                        var_r0 = 1;
                                    }
                                    if (var_r0 != 0) {
                                        temp_r3_2 = fn_800246AC((void *)var_r28);
                                        sp2C = -temp_r3_2->unk0x24;
                                        sp30 = -temp_r3_2->unk0x28;
                                        sp34 = -temp_r3_2->unk0x2C;
                                        sp28 = -temp_r3_2->unk0x20;
                                        0;
                                        if (spE0 < temp_f31_4) {
                                            arg1->v[0] = (f32) -arg1->v[0];
                                        }
                                    }
                                } else {
                                    if (temp_f10_2 > arg1->v[0]) {
                                        arg1->v[0] = temp_f10_2;
                                    }
                                    if (temp_f1_4 > arg1->v[1]) {
                                        arg1->v[1] = temp_f1_4;
                                    }
                                }
                            }
                        }
                    }
                }
block_62:
            var_r3 = 1;
        }
    return var_r3;
}
