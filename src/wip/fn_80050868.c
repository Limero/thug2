// WIP DRAFT (non-matching) - hand-rebuilt skeleton of THUG2's skeletal
// ray/bone cast at 0x80050868 (6624 B, 1656 insns, prologue saves 18 FPRs
// and the whole CR file).
// family=m2c range=0x80050868-0x80052248 size=6624B
// INERT: not registered in splits.txt/configure.py - never compiled by the
// build, not counted in objdiff progress.  activate via tools/wip.py.
//
// WHAT THIS FUNCTION IS (recovered from the DOL, both arms):
//   for every bone i of `arg2`:
//     A = world[i]        (fn_80036960 -> skel->unk0x4, 64 B stride)
//     B = local[i]        (fn_8003A428(skel->unk0x8), 64 B stride)
//     3 point/vector transforms of the ray segment through A, arg3 and A
//     radius = bone->unk0x28 * max3(node+0x10,+0x14,+0x18), scaled by farg0
//              when farg0 > lbl_80292EC8, plus farg1
//     fn_80006FA8 builds a bone frame (position + cross product + radius)
//     fn_80007090 ray-capsule test -> t; keep the smallest t
//   arg4 != 0 short-circuits to a single bone (fn_80036810 lookup).
//
// FIXED (each verified against the DOL, not guessed):
//  * callee SIGNATURES - m2c had wrong or missing return types, so every
//    call site was shaped wrong:
//      fn_80036960  returns a POINTER (`lwz r3,4(r3)`)      - m2c: void
//      fn_8003A428  returns a POINTER (`lwz r3,0x58c(r3)`)  - m2c: no
//                   prototype at all -> implicitly int, which lost the
//                   `+ idx*64` local-matrix array base
//      fn_80036854  2-arg pointer getter, 32 B element stride
//      fn_80036810  2-arg s32 (linear search of skel->unk0x18 by +0, -1 miss)
//      fn_80036968  s32 count getter (skel->unk0x14)
//      fn_8003A344  2-arg s32.  WANT sets only r3/r4 before the bl; the three
//                   trailing `0,0,0` args m2c invented cost four extra `li`
//      fn_80006FA8  4-arg (r3,r4,r5,f1) - phantom 5th arg dropped
//      fn_80007090  5-arg s32; only r3 and r7(arg4) are read, the dead args
//                   are kept deliberately (AGENTS.md 6t-3)
//      sqrtf  f32 -> f32
//  * the three 64-byte matrix slots (r1+0x08 / 0x48 / 0x88) were an
//    `Unk_59AB5482` struct OVERLAID by 30+ scalar locals of the same names, so
//    m2c used two identifiers for one stack slot (`sp8.unk0x8` and the
//    file-scope `static s32 sp14` are both r1+0x10).  One flat f32[16] each.
//  * 15 file-scope `static s32 spN` -> real f32 locals (r1+0x14/0x1c/0x24/
//    0x30/0x34/0x44 are inside matrix A; the rest at 0x168/0x170/0x180/
//    0x220/0x228/0x238/0x278/0x280/0x288), so they live on the stack again
//    instead of in .bss.
//  * parameter roles, from the prologue: r7 is a 4x4 float matrix (`arg3`,
//    16 lfs at +0x0..+0x3c in BOTH arms); r8 is the branch selector AND the
//    `f32 *` out-time slot (`cmpwi cr4,r18,0`, `stfs f1,0(r18)`); r9 is the
//    `s32 *` out-hit slot (`stw r20,0(r17)`).
//  * bogus `sp31C` (r1+0x31c is the saved CR word, not a local) removed.
//
// REMAINING BLOCKERS - each one alone is fatal for a byte-exact match:
//  1. doc-30 self-targeting `bdnz .` windows, FIVE of them (0x80050968,
//     0x800509b8, 0x8005123c, 0x80051258, 0x80051264): an empty counted loop
//     whose delay slot carries the first real instruction.  Every plain-C
//     loop form compiles forward-displaced; the only known fix is the
//     `bdnz $` volatile-asm window (docs/parkings/30), which this
//     reconstruction is not permitted to use.
//  2. the 262 psq_l/psq_st paired-single copies that build the three local
//     matrices (0x80050968-0x80050a48, 0x80051278-0x8005219c).  PROVEN
//     unreachable from plain C with this compiler: a minimal probe shows
//     `__ps_t *a = A; a[k] = src[k];` is copy-propagated away (the pair load
//     is forwarded to the consumer, no psq_st emitted) and `volatile __ps_t`
//     does not help; the only surviving C route is a function-PARAMETER
//     destination (cf. promoted src/fn_800063B8.c, dst == arg1) or an
//     inline-asm `"m"` pin.  Here the destination is a local.
//  3. 18 callee-saved FPRs (f14..f31 at stfd 0x368..0x3f0) plus
//     `mfcr r12` / `stw r12,0x31c(r1)` / `mtcrf` CR save spanning a body with
//     15 calls: doc-28 CR liveness with 18 exactly-live FPR webs.
//  4. ~390 scalar fmadds/fmuls whose operand order and FPR colouring must all
//     land exactly, on a 0x3f8 frame carrying 187 distinct stack offsets.
//  5. m2c additionally DROPPED ~30 straight-line instructions that no
//     postprocessor recovered; each such gap is left in the body as a
//     `/* N straight-line instruction(s) m2c dropped ... */` marker so the
//     hole is explicit rather than hidden behind an inert `0;` statement.
//
// Verdict: PARKED.  Multi-session rebuild; do NOT re-run the flag / permutation
// / register-pin levers, none of them can address items 1-4 above.
//
// MEASURED (tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80050868):
//   verdict DIFF, and the byte score is honestly unchanged (~0% either way:
//   0.45% before, 0.24% after - both are noise, the streams
//   diverge from word 0 because of blockers 1-2).  What DID improve is the
//   body itself, which is no longer the m2c statics-DCE husk:
//     compiled 3328 B / 832 insns vs want 6624 B / 1656 insns
//     frame 0x344 vs want 0x3f8            (was 0x288 at session start)
//     50 distinct r1 displacements vs want's 187 - the missing 137 are
//     exactly the slots the dropped psq pair copies would have filled
//   so the gap is now honestly attributed rather than papered over.
// Side-by-side residual: tools/venv/bin/python tools/want_got.py 0x80050868
#include "types.h"
#include "structs.h"

/* --- symbols ------------------------------------------------------------- */
extern char lbl_80292EC8[];      /* f32 hit epsilon                          */
extern f32 lbl_80292ECC;          /* second word of the same constant pair   */
extern s32 lbl_80302E98[];        /* per-bone 4-float record, 16 B stride    */
extern s32 lbl_80364638[];        /* per-bone 16 B record, indexed by idx*16  */

/* --- callees: signatures read off the callee prologues -------------------- */
s32 fn_8003A344(void *skel, s32 idx);       /* skel->unk0x108[idx] -> id      */
void *fn_8003A428(void *skel);              /* skel->unk0x58c                 */
void *fn_80036810(void *skel, s32 key);     /* linear search, -1 if absent    */
void *fn_80036854(void *skel, s32 idx);     /* skel->unk0x18 + idx*32         */
s32 fn_80036968(void *skel);                /* skel->unk0x14 = bone count     */
void *fn_80036960(void *skel);              /* skel->unk0x4  = world matrix[] */
void *fn_80006FA8(void *dst, void *a, void *b, f32 radius);
s32 fn_80007090(void *seg, void *a, s32 b, void *c, f32 *out_t);
f32 sqrtf(f32 v);

/* arg3 is a 4x4 row-major float matrix: 16 lfs at +0x0..+0x3c in both arms. */
typedef struct {
    f32 m00, m01, m02, m03;
    f32 m10, m11, m12, m13;
    f32 m20, m21, m22, m23;
    f32 m30, m31, m32, m33;
} Mat44;

s32 fn_80050868(s32 **arg0, void *arg1, Unk_9994C3F5 *arg2, Mat44 *arg3,
                s32 arg4, f32 *arg5, s32 *arg6, f32 farg0, f32 farg1) {
    /* r1+0x08 / 0x48 / 0x88 - the three 64-byte matrix slots. */
    f32 A[16];
    f32 B[16];
    f32 C[16];
    /* r1+0x148 / 0x14c / 0x150 / 0x158 - pointers to the matrices, stored as
       data and re-read later (want: stw r29,0x148(r1); stw r28,4(r25)). */
    f32 *mp0;
    f32 *mp1;
    f32 *mp2;
    f32 *mp3;
    f32 *mptr[2];              /* r1+0x150 / 0x154 - matrix pointer pair  */
    f32 **sp2F4;               /* r1+0x2f4 - biased view of mptr[0]        */
    f32 *arg3p;
    void *tmpw;              /* fn_80036960() base; the pair copies that
                              * consume it are blocker #2 below   */
    f32 *sp314;
    f32 *sp310;
    f32 *sp30C;
    f32 *sp308;
    f32 *sp304;
    s32 sp2FC;
    f32 *sp2F8;
    f32 sp2EC;
    f32 sp2E8;
    f32 sp2E4;
    f32 sp2E0;
    f32 sp2DC;
    f32 sp2D8;
    f32 sp2D4;
    f32 sp2D0;
    f32 sp2CC;
    f32 sp2C8;
    f32 sp2C4;
    f32 sp2C0;
    f32 sp2BC;
    f32 sp2B8;
    f32 sp2B4;
    f32 sp2B0;
    f32 sp2AC;
    f32 sp2A8;
    f32 sp2A4;
    f32 sp29C;
    f32 sp298;
    f32 sp294;
    f32 sp290;
    f32 sp274;
    f32 sp270;
    f32 sp278;
    f32 sp280;
    f32 sp288;
    f32 sp26C;
    f32 sp264;
    f32 sp260;
    f32 sp25C;
    f32 sp258;
    f32 sp254;
    f32 sp250;
    f32 sp24C;
    f32 sp248;
    f32 sp244;
    f32 sp240;
    void *sp218;
    f32 sp214;
    f32 sp220;
    f32 sp228;
    f32 sp238;
    f32 sp1FC;
    f32 sp1F8;
    f32 sp1F4;
    f32 sp1F0;
    f32 sp1EC;
    f32 sp1E8;
    f32 sp1E4;
    f32 sp1E0;
    f32 sp1DC;
    f32 sp1D8;
    f32 sp1D4;
    f32 sp1D0;
    f32 sp1CC;
    f32 sp1C8;
    f32 sp1BC;
    f32 sp1B8;
    f32 sp1B0;
    f32 sp1A8;
    f32 sp1A0;
    f32 sp19C;
    f32 sp198;
    f32 sp190;
    f32 sp18C;
    f32 sp188;
    f32 sp17C;
    f32 sp164;
    f32 sp168;
    f32 sp170;
    f32 sp180;
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    Unk_59AB5482 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp2C;
    f32 sp28;
    f32 sp20;
    f32 sp18;
    f32 spC;
    Unk_59AB5482 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f13_4;
    f32 temp_f13_5;
    f32 temp_f13_6;
    f32 temp_f14;
    f32 temp_f15;
    f32 temp_f16;
    f32 temp_f17;
    f32 temp_f18;
    f32 temp_f19;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f23;
    f32 temp_f23_2;
    f32 temp_f23_3;
    f32 temp_f23_4;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f25;
    f32 temp_f25_2;
    f32 temp_f25_3;
    f32 temp_f25_4;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f3_4;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f4_4;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f5_4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f6_4;
    f32 temp_f6_5;
    f32 temp_f6_6;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f13;
    f32 var_f1;
    f32 var_r20;
    s32 temp_r19;
    s32 temp_r22;
    s32 k;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_r21;
    s32 var_r30;
    CStruct *temp_r11;
    void *temp_r28;
    void *temp_r3_3;
    Unk_C7387A53 *temp_r4;

    temp_r19 = arg2->unk0x8;
    sp15C = farg0;
    sp160 = farg1;
    temp_r22 = fn_8003A428(temp_r19);
    if (arg4 == 0) {
        var_r21 = 0;
        var_r20 = *(f32 *)&lbl_80292EC8;
        var_r30 = 0;
        sp164 = var_r20;
        /* 2 straight-line instruction(s) m2c dropped and no
           postprocessor recovered: psq_l/psq_st pair copies and
           their ps_* arithmetic.  Blocker #2 in the header. */
loop_20:
        temp_r3 = fn_80036968(arg2);
        if (var_r30 < temp_r3) {
            temp_r28 = fn_80036854(arg2, var_r30);
            tmpw = fn_80036960(arg2);
            var_ctr = 4;
            do {
                var_ctr -= 1;
            } while (var_ctr != 0);
            /* WANT 0x80050968-0x800509b4: the 64-byte world-matrix copy
               A <- world[bone] - eight psq_l/psq_st pairs, i.e. eight
               8-byte __ps_t element copies out of a returned pointer. */
            for (k = 0; k < 8; k++) {
                ((__ps_t *)A)[k] = ((__ps_t *)tmpw)[var_r30 * 8 + k];
            }
            var_ctr_2 = 4;
            do {
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
            /* WANT 0x800509b8-0x80050a44: the 64-byte local-matrix copy
               B <- local[bone], same eight-pair shape. */
            for (k = 0; k < 8; k++) {
                ((__ps_t *)B)[k] = ((__ps_t *)temp_r22)[var_r30 * 8 + k];
            }
            temp_f23 = B[1];
            /* 4 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            sp188 = B[4];
            /* 8 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            temp_f24 = -sp168;
            temp_f8 = -sp170;
            B[12] = temp_f24;
            sp17C = temp_f8;
            B[13] = temp_f8;
            temp_f25 = -sp180;
            B[14] = temp_f25;
            B[1] = B[4];
            temp_f12 = B[8];
            sp18C = B[2];
            C[5] = (B[3] * A[13]) + ((temp_f12 * A[9]) + ((B[0] * A[1]) + (B[4] * A[5])));
            temp_f2 = B[6];
            C[4] = (B[3] * A[12]) + ((temp_f12 * A[8]) + ((B[0] * A[0]) + (B[4] * A[4])));
            temp_f7 = temp_f2 * A[4];
            temp_f13 = temp_f2 * A[5];
            B[4] = temp_f23;
            B[2] = temp_f12;
            B[8] = sp18C;
            sp190 = B[9];
            sp1A8 = temp_f7;
            sp1B0 = temp_f13;
            sp1B8 = (temp_f25 * A[8]) + ((temp_f24 * A[0]) + (sp17C * A[4]));
            B[6] = B[9];
            B[9] = temp_f2;
            sp1BC = (temp_f25 * A[9]) + ((temp_f24 * A[1]) + (sp17C * A[5]));
            temp_f5 = (B[0] * A[2]) + (sp188 * A[7]);
            temp_f6 = B[5] * A[4];
            sp198 = temp_f5;
            sp19C = temp_f6;
            temp_f13_2 = B[5] * A[5];
            C[7] = (B[3] * A[15]) + ((temp_f12 * A[11]) + temp_f5);
            C[6] = (B[3] * A[14]) + ((temp_f12 * A[10]) + ((B[0] * A[2]) + (sp188 * A[6])));
            C[8] = (B[7] * A[12]) + ((sp190 * A[8]) + ((temp_f23 * A[0]) + temp_f6));
            C[9] = (B[7] * A[13]) + ((sp190 * A[9]) + ((temp_f23 * A[1]) + temp_f13_2));
            sp1A0 = temp_f13_2;
            C[11] = (B[7] * A[15]) + ((sp190 * A[11]) + ((temp_f23 * A[2]) + (B[5] * A[7])));
            C[13] = (B[11] * A[13]) + ((B[10] * A[9]) + ((sp18C * A[1]) + temp_f13));
            C[10] = (B[7] * A[14]) + ((sp190 * A[10]) + ((temp_f23 * A[2]) + (B[5] * A[6])));
            C[12] = (B[11] * A[12]) + ((B[10] * A[8]) + ((sp18C * A[0]) + temp_f7));
            C[15] = (B[11] * A[15]) + ((B[10] * A[11]) + ((sp18C * A[2]) + (temp_f2 * A[7])));
            spCC = (B[15] * A[13]) + sp1BC;
            spC8 = (B[15] * A[12]) + sp1B8;
            C[14] = (B[11] * A[14]) + ((B[10] * A[10]) + ((sp18C * A[2]) + (temp_f2 * A[6])));
            temp_f6_2 = (temp_f25 * A[11]) + ((temp_f24 * A[2]) + (sp17C * A[7]));
            /* 1 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            spD4 = (B[15] * A[15]) + temp_f6_2;
            sp1C8 = temp_f6_2;
            spD0 = (B[15] * A[14]) + ((temp_f25 * A[10]) + ((temp_f24 * A[2]) + (sp17C * A[6])));
            /* 2 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            temp_f25_2 = arg3->m10;
            temp_f12_2 = arg3->m00;
            sp1CC = temp_f12_2;
            /* 1 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            temp_f17 = arg3->m20;
            /* 1 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            temp_f20 = arg3->m30;
            /* 1 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            C[0] = (B[3] * temp_f20) + ((B[2] * temp_f17) + ((B[0] * temp_f12_2) + (B[1] * temp_f25_2)));
            temp_f23_2 = arg3->m11;
            temp_f19 = arg3->m12;
            temp_f15 = arg3->m13;
            sp1D0 = arg3->m01;
            temp_f18 = arg3->m02;
            sp1DC = arg3->m03;
            sp1E4 = B[9] * temp_f25_2;
            temp_f3 = arg3->m21;
            sp1D4 = temp_f3;
            sp1F0 = B[9] * temp_f23_2;
            temp_f16 = arg3->m22;
            temp_f22 = arg3->m23;
            sp1D8 = arg3->m31;
            temp_f14 = arg3->m32;
            sp1E0 = arg3->m33;
            sp1E8 = (B[8] * sp1CC) + sp1E4;
            sp1F4 = (B[8] * sp1D0) + sp1F0;
            sp1FC = (B[8] * temp_f18) + (B[9] * temp_f19);
            sp1F8 = (B[10] * temp_f3) + sp1F4;
            sp1EC = (B[10] * temp_f17) + sp1E8;
            C[11] = (B[11] * sp1E0) + ((B[10] * temp_f22) + ((B[8] * sp1DC) + (B[9] * temp_f15)));
            C[3] = (B[3] * sp1E0) + ((B[2] * temp_f22) + ((B[0] * sp1DC) + (B[1] * temp_f15)));
            C[7] = (B[7] * sp1E0) + ((B[6] * temp_f22) + ((B[4] * sp1DC) + (B[5] * temp_f15)));
            C[2] = (B[3] * temp_f14) + ((B[2] * temp_f16) + ((B[0] * temp_f18) + (B[1] * temp_f19)));
            C[5] = (B[7] * sp1D8) + ((B[6] * temp_f3) + ((B[4] * sp1D0) + (B[5] * temp_f23_2)));
            C[6] = (B[7] * temp_f14) + ((B[6] * temp_f16) + ((B[4] * temp_f18) + (B[5] * temp_f19)));
            C[4] = (B[7] * temp_f20) + ((B[6] * temp_f17) + ((B[4] * sp1CC) + (B[5] * temp_f25_2)));
            sp214 = (B[12] * sp1DC) + (B[13] * temp_f15);
            C[10] = (B[11] * temp_f14) + ((B[10] * temp_f16) + sp1FC);
            C[1] = (B[3] * sp1D8) + ((B[2] * temp_f3) + ((B[0] * sp1D0) + (B[1] * temp_f23_2)));
            C[12] = (B[15] * temp_f20) + ((B[14] * temp_f17) + ((B[12] * sp1CC) + (B[13] * temp_f25_2)));
            C[13] = (B[15] * sp1D8) + ((B[14] * sp1D4) + ((B[12] * sp1D0) + (B[13] * temp_f23_2)));
            C[8] = (B[11] * temp_f20) + sp1EC;
            C[9] = (B[11] * sp1D8) + sp1F8;
            C[15] = (B[15] * sp1E0) + ((B[14] * temp_f22) + sp214);
            C[14] = (B[15] * temp_f14) + ((B[14] * temp_f16) + ((B[12] * temp_f18) + (temp_f8 * temp_f19)));
            /* 11 straight-line instruction(s) m2c dropped and no
               postprocessor recovered: psq_l/psq_st pair copies and
               their ps_* arithmetic.  Blocker #2 in the header. */
            if (var_r30 != 0) {
                fn_8003A344(temp_r19, var_r30);
                /* 3 straight-line instruction(s) m2c dropped and no
                   postprocessor recovered: psq_l/psq_st pair copies and
                   their ps_* arithmetic.  Blocker #2 in the header. */
                temp_r4 = *((s32 *)((char *)*arg0 + (var_r30 * 4)));
                if (temp_r4 != NULL) {
                    temp_r11 = temp_r28 + 0x10;
                    temp_f12_3 = ((CStruct *)temp_r28)->unk0x10;
                    temp_f0 = temp_r11->unk0x4;
                    var_f13 = temp_f0;
                    if (temp_f12_3 > temp_f0) {
                        var_f13 = temp_f12_3;
                    }
                    temp_f0_2 = temp_r11->unk0x8;
                    var_f1 = temp_f0_2;
                    if (var_f13 > temp_f0_2) {
                        var_f1 = var_f13;
                    }
                    var_f0 = temp_r4->unk0x28 * var_f1;
                    /* 1 straight-line instruction(s) m2c dropped and no
                       postprocessor recovered: psq_l/psq_st pair copies and
                       their ps_* arithmetic.  Blocker #2 in the header. */
                    /* want: fcmpu radius,eps ; cror eq,lt ; bso <skip bone> */
                    if (var_f0 > *(f32 *)&lbl_80292EC8) {
                        if (sp15C > *(f32 *)&lbl_80292EC8) {
                            var_f0 *= sp15C;
                        }
                        /* 5 straight-line instruction(s) m2c dropped and no
                           postprocessor recovered: psq_l/psq_st pair copies and
                           their ps_* arithmetic.  Blocker #2 in the header. */
                        fn_80006FA8(&spD8, &C[8], &C[4], var_f0 + sp160);
                        if ((fn_80007090(&spD8, arg1, 0, &sp140, &sp144) != 0) && ((var_r21 == 0) || (sp144 < sp164))) {
                            var_r21 = ((CStruct *)temp_r28)->unk0x0;
                            sp164 = sp144;
                            var_r20 = sp140;
                        }
                    }
                }
            }
            var_r30 += 1;
            goto loop_20;
        }
        /* want: cmpwi cr4,r18,0 (arg5) / cmpwi cr3,r17,0 (arg6) hoisted to
           0x80050918/0x8005091c, consumed by the beq's at 0x80051198/0x800511a8
           - these are NULL checks on the two out-pointers, not loop tests. */
        if (arg5 != NULL) {
            *arg5 = sqrtf(sp164);
        }
        if (arg6 != NULL) {
            *arg6 = var_r20;
        }
        /* 1 straight-line instruction(s) m2c dropped and no
           postprocessor recovered: psq_l/psq_st pair copies and
           their ps_* arithmetic.  Blocker #2 in the header. */
        return var_r21;
    }
    temp_r3_2 = fn_80036810(arg2, arg4);
    temp_r3_3 = fn_80036854(arg2, temp_r3_2);
    arg3p = (f32 *)((char *)arg3 + 0x30);
    sp314 = &sp104;
    sp308 = &spD8;
    sp310 = &sp100;
    sp2F4 = mptr;
    var_ctr_3 = 4;
    sp218 = temp_r3_3;
    sp304 = &spC8;
    sp30C = &spE8;
    mp3 = &sp158;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    var_ctr_4 = 4;
    sp2FC = temp_r3_2 * 4;
    /* 1 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    do {
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    var_ctr_5 = 4;
    do {
        var_ctr_5 -= 1;
    } while (var_ctr_5 != 0);
    tmpw = fn_80036960(arg2);
    /* WANT 0x80051270-0x800512bc: the 64-byte world-matrix copy
       C <- world[bone]; its first pair is the INDEXED psq_lx form
       (runtime element index), the remaining seven are D-form. */
    for (k = 0; k < 8; k++) {
        ((__ps_t *)C)[k] = ((__ps_t *)tmpw)[temp_r3_2 * 8 + k];
    }
    temp_f1 = A[4];
    /* 1 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    A[4] = A[1];
    /* 1 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    sp240 = temp_f1;
    A[1] = sp240;
    /* 1 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    A[12] = -sp220;
    A[13] = -sp228;
    A[14] = -sp238;
    temp_f0_3 = A[2];
    A[2] = A[8];
    A[8] = temp_f0_3;
    temp_f0_4 = A[9];
    mp0 = A;
    A[9] = A[6];
    A[6] = temp_f0_4;
    mp1 = C;
    sp100 = (A[3] * C[12]) + ((A[2] * C[8]) + ((A[0] * C[0]) + (A[1] * C[4])));
    sp104 = (A[3] * C[13]) + ((A[2] * C[9]) + ((A[0] * C[1]) + (A[1] * C[5])));
    sp108 = (A[3] * C[14]) + ((A[2] * C[10]) + ((A[0] * C[2]) + (A[1] * C[6])));
    sp10C = (A[3] * C[15]) + ((A[2] * C[11]) + ((A[0] * C[3]) + (A[1] * C[7])));
    sp110 = (A[7] * C[12]) + ((A[6] * C[8]) + ((A[4] * C[0]) + (A[5] * C[4])));
    sp114 = (A[7] * C[13]) + ((A[6] * C[9]) + ((A[4] * C[1]) + (A[5] * C[5])));
    sp118 = (A[7] * C[14]) + ((A[6] * C[10]) + ((A[4] * C[2]) + (A[5] * C[6])));
    sp11C = (A[7] * C[15]) + ((A[6] * C[11]) + ((A[4] * C[3]) + (A[5] * C[7])));
    sp120 = (A[11] * C[12]) + ((A[10] * C[8]) + ((A[8] * C[0]) + (A[9] * C[4])));
    sp124 = (A[11] * C[13]) + ((A[10] * C[9]) + ((A[8] * C[1]) + (A[9] * C[5])));
    sp128 = (A[11] * C[14]) + ((A[10] * C[10]) + ((A[8] * C[2]) + (A[9] * C[6])));
    sp12C = (A[11] * C[15]) + ((A[10] * C[11]) + ((A[8] * C[3]) + (A[9] * C[7])));
    sp130 = (A[15] * C[12]) + ((A[14] * C[8]) + ((A[12] * C[0]) + (A[13] * C[4])));
    sp134 = (A[15] * C[13]) + ((A[14] * C[9]) + ((A[12] * C[1]) + (A[13] * C[5])));
    sp138 = (A[15] * C[14]) + ((A[14] * C[10]) + ((A[12] * C[2]) + (A[13] * C[6])));
    /* 1 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    sp13C = (A[15] * C[15]) + ((A[14] * C[11]) + ((A[12] * C[3]) + (A[13] * C[7])));
    /* 5 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    temp_f13_3 = arg3->m00;
    temp_f1_2 = arg3->m10;
    sp244 = temp_f13_3;
    temp_f23_3 = arg3->m20;
    temp_f22_2 = arg3->m30;
    temp_f4 = arg3->m11;
    temp_f25_3 = arg3->m01;
    spC8 = (A[2] * temp_f22_2) + ((A[2] * temp_f23_3) + ((A[0] * temp_f13_3) + (A[1] * temp_f1_2)));
    sp248 = arg3->m21;
    temp_f3_2 = arg3->m31;
    sp24C = temp_f3_2;
    temp_f10 = arg3->m12;
    temp_f24_2 = arg3->m02;
    spCC = (A[2] * temp_f3_2) + ((A[2] * sp248) + ((A[0] * temp_f25_3) + (A[1] * temp_f4)));
    temp_f6_3 = arg3->m22;
    sp250 = temp_f6_3;
    temp_f8_2 = arg3->m32;
    sp254 = temp_f8_2;
    temp_f12_4 = arg3->m13;
    sp25C = temp_f12_4;
    temp_f13_4 = arg3->m03;
    sp258 = temp_f13_4;
    spD0 = (A[2] * temp_f8_2) + ((A[2] * temp_f6_3) + ((A[0] * temp_f24_2) + (A[1] * temp_f10)));
    sp260 = arg3->m23;
    temp_f3_3 = arg3->m33;
    spD4 = (A[2] * temp_f3_3) + ((A[2] * sp260) + ((A[0] * temp_f13_4) + (A[1] * temp_f12_4)));
    sp264 = temp_f3_3;
    spD8 = (A[7] * temp_f22_2) + ((A[6] * temp_f23_3) + ((A[4] * sp244) + (A[5] * temp_f1_2)));
    sp270 = arg3->m22;
    sp274 = arg3->m32;
    temp_f5_2 = (A[12] * arg3->m02) + (A[13] * arg3->m12);
    sp26C = temp_f5_2;
    spF8 = (A[15] * temp_f22_2) + ((A[14] * temp_f23_3) + ((A[12] * sp244) + (A[13] * temp_f1_2)));
    spE8 = (A[11] * temp_f22_2) + ((A[10] * temp_f23_3) + ((A[8] * sp244) + (A[9] * temp_f1_2)));
    spE4 = (A[7] * temp_f3_3) + ((A[6] * sp260) + ((A[4] * temp_f13_4) + (A[5] * temp_f12_4)));
    spF0 = (A[11] * sp254) + ((A[10] * temp_f6_3) + ((A[8] * temp_f24_2) + (A[9] * temp_f10)));
    spF4 = (A[11] * temp_f3_3) + ((A[10] * sp260) + ((A[8] * sp258) + (A[9] * sp25C)));
    spDC = (A[7] * sp24C) + ((A[6] * sp248) + ((A[4] * temp_f25_3) + (A[5] * temp_f4)));
    spEC = (A[11] * sp24C) + ((A[10] * sp248) + ((A[8] * temp_f25_3) + (A[9] * temp_f4)));
    spFC = (A[15] * sp24C) + ((A[14] * sp248) + ((A[12] * temp_f25_3) + (A[13] * temp_f4)));
    spE0 = (A[7] * sp254) + ((A[6] * temp_f6_3) + ((A[4] * temp_f24_2) + (A[5] * temp_f10)));
    *sp310 = (A[15] * sp274) + ((A[14] * sp270) + temp_f5_2);
    sp104 = (A[15] * sp264) + ((A[14] * sp260) + ((sp8.unk0x30 * sp258) + (sp8.unk0x34 * sp25C)));
    /* 9 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    /* want: cmpwi cr4,r26,0 at 0x80051254 - the degenerate-bone case */
    if (temp_r3_2 == 0) {
        temp_f0_5 = *(f32 *)&lbl_80292EC8;
        temp_f13_5 = lbl_80292ECC;
        B[14] = temp_f0_5;
        B[15] = temp_f13_5;
        B[0] = temp_f13_5;
        B[1] = temp_f0_5;
        B[2] = temp_f0_5;
        B[3] = temp_f0_5;
        B[4] = temp_f0_5;
        B[5] = temp_f13_5;
        B[6] = temp_f0_5;
        B[7] = temp_f0_5;
        B[8] = temp_f0_5;
        B[9] = temp_f0_5;
        B[10] = temp_f13_5;
        B[11] = temp_f0_5;
        B[12] = temp_f0_5;
        B[13] = temp_f0_5;
    } else {
        fn_8003A344(temp_r19, temp_r3_2);
        /* 7 straight-line instruction(s) m2c dropped and no
           postprocessor recovered: psq_l/psq_st pair copies and
           their ps_* arithmetic.  Blocker #2 in the header. */
    }
    /* 4 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    sp290 = B[1];
    B[1] = B[4];
    temp_f31 = B[2];
    /* 4 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    mp2 = &B[0];
    temp_f13_6 = -sp278;
    temp_f0_6 = -sp280;
    B[4] = sp290;
    B[2] = B[8];
    B[12] = temp_f13_6;
    temp_f12_5 = -sp288;
    B[13] = temp_f0_6;
    temp_f2_2 = B[6];
    temp_f4_2 = B[9];
    B[8] = temp_f31;
    B[6] = temp_f4_2;
    B[9] = temp_f2_2;
    B[14] = temp_f12_5;
    mp1 = C;
    spC8 = (((Unk_DB0E2BAB *)mp2)->unk0xC * C[12]) + ((((Unk_DB0E2BAB *)mp2)->unk0x8 * C[8]) + ((((Unk_DB0E2BAB *)mp2)->unk0x0 * C[0]) + (((Unk_DB0E2BAB *)mp2)->unk0x4 * C[4])));
    spCC = (((Unk_DB0E2BAB *)mp2)->unk0xC * C[13]) + ((((Unk_DB0E2BAB *)mp2)->unk0x8 * C[9]) + ((((Unk_DB0E2BAB *)mp2)->unk0x0 * C[1]) + (((Unk_DB0E2BAB *)mp2)->unk0x4 * C[5])));
    spD0 = (((Unk_DB0E2BAB *)mp2)->unk0xC * C[14]) + ((((Unk_DB0E2BAB *)mp2)->unk0x8 * C[10]) + ((((Unk_DB0E2BAB *)mp2)->unk0x0 * C[2]) + (((Unk_DB0E2BAB *)mp2)->unk0x4 * C[6])));
    spD4 = (((Unk_DB0E2BAB *)mp2)->unk0xC * C[15]) + ((((Unk_DB0E2BAB *)mp2)->unk0x8 * C[11]) + ((((Unk_DB0E2BAB *)mp2)->unk0x0 * C[3]) + (((Unk_DB0E2BAB *)mp2)->unk0x4 * C[7])));
    spD8 = (((Unk_DB0E2BAB *)mp2)->unk0x1C * C[12]) + ((((Unk_DB0E2BAB *)mp2)->unk0x18 * C[8]) + ((((Unk_DB0E2BAB *)mp2)->unk0x10 * C[0]) + (((Unk_DB0E2BAB *)mp2)->unk0x14 * C[4])));
    spDC = (((Unk_DB0E2BAB *)mp2)->unk0x1C * C[13]) + ((((Unk_DB0E2BAB *)mp2)->unk0x18 * C[9]) + ((((Unk_DB0E2BAB *)mp2)->unk0x10 * C[1]) + (((Unk_DB0E2BAB *)mp2)->unk0x14 * C[5])));
    spE0 = (((Unk_DB0E2BAB *)mp2)->unk0x1C * C[14]) + ((((Unk_DB0E2BAB *)mp2)->unk0x18 * C[10]) + ((((Unk_DB0E2BAB *)mp2)->unk0x10 * C[2]) + (((Unk_DB0E2BAB *)mp2)->unk0x14 * C[6])));
    spE4 = (((Unk_DB0E2BAB *)mp2)->unk0x1C * C[15]) + ((((Unk_DB0E2BAB *)mp2)->unk0x18 * C[11]) + ((((Unk_DB0E2BAB *)mp2)->unk0x10 * C[3]) + (((Unk_DB0E2BAB *)mp2)->unk0x14 * C[7])));
    spE8 = (((Unk_DB0E2BAB *)mp2)->unk0x2C * C[12]) + ((((Unk_DB0E2BAB *)mp2)->unk0x28 * C[8]) + ((((Unk_DB0E2BAB *)mp2)->unk0x20 * C[0]) + (((Unk_DB0E2BAB *)mp2)->unk0x24 * C[4])));
    spEC = (((Unk_DB0E2BAB *)mp2)->unk0x2C * C[13]) + ((((Unk_DB0E2BAB *)mp2)->unk0x28 * C[9]) + ((((Unk_DB0E2BAB *)mp2)->unk0x20 * C[1]) + (((Unk_DB0E2BAB *)mp2)->unk0x24 * C[5])));
    spF0 = (((Unk_DB0E2BAB *)mp2)->unk0x2C * C[14]) + ((((Unk_DB0E2BAB *)mp2)->unk0x28 * C[10]) + ((((Unk_DB0E2BAB *)mp2)->unk0x20 * C[2]) + (((Unk_DB0E2BAB *)mp2)->unk0x24 * C[6])));
    spF4 = (((Unk_DB0E2BAB *)mp2)->unk0x2C * C[15]) + ((((Unk_DB0E2BAB *)mp2)->unk0x28 * C[11]) + ((((Unk_DB0E2BAB *)mp2)->unk0x20 * C[3]) + (((Unk_DB0E2BAB *)mp2)->unk0x24 * C[7])));
    spF8 = (((Unk_DB0E2BAB *)mp2)->unk0x3C * C[12]) + ((((Unk_DB0E2BAB *)mp2)->unk0x38 * C[8]) + ((((Unk_DB0E2BAB *)mp2)->unk0x30 * C[0]) + (((Unk_DB0E2BAB *)mp2)->unk0x34 * C[4])));
    spFC = (((Unk_DB0E2BAB *)mp2)->unk0x3C * C[13]) + ((((Unk_DB0E2BAB *)mp2)->unk0x38 * C[9]) + ((((Unk_DB0E2BAB *)mp2)->unk0x30 * C[1]) + (((Unk_DB0E2BAB *)mp2)->unk0x34 * C[5])));
    sp100 = (((Unk_DB0E2BAB *)mp2)->unk0x3C * C[14]) + ((((Unk_DB0E2BAB *)mp2)->unk0x38 * C[10]) + ((((Unk_DB0E2BAB *)mp2)->unk0x30 * C[2]) + (((Unk_DB0E2BAB *)mp2)->unk0x34 * C[6])));
    *sp314 = (((Unk_DB0E2BAB *)mp2)->unk0x3C * C[15]) + ((((Unk_DB0E2BAB *)mp2)->unk0x38 * C[11]) + ((((Unk_DB0E2BAB *)mp2)->unk0x30 * C[3]) + (((Unk_DB0E2BAB *)mp2)->unk0x34 * C[7])));
    /* 6 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    temp_f9 = arg3->m10;
    sp298 = temp_f9;
    temp_f10_2 = arg3->m11;
    sp2AC = temp_f10_2;
    sp29C = B[1] * temp_f9;
    sp2C4 = arg3->m12;
    sp2D0 = arg3->m13;
    temp_f4_3 = arg3->m00;
    sp294 = temp_f4_3;
    temp_f5_3 = arg3->m01;
    sp2A8 = temp_f5_3;
    temp_f6_4 = arg3->m02;
    sp2C0 = temp_f6_4;
    temp_f23_4 = arg3->m03;
    temp_f22_3 = arg3->m20;
    sp2B0 = (B[0] * temp_f5_3) + (B[1] * temp_f10_2);
    temp_f3_4 = arg3->m21;
    sp2B4 = temp_f3_4;
    sp2C8 = arg3->m22;
    temp_f25_4 = arg3->m23;
    sp2D4 = arg3->m33;
    temp_f5_4 = arg3->m30;
    sp2A4 = temp_f5_4;
    temp_f6_5 = arg3->m31;
    sp2BC = temp_f6_5;
    sp2B8 = (B[2] * sp2B4) + sp2B0;
    sp2CC = arg3->m32;
    spD4 = (B[3] * sp2D4) + ((B[2] * temp_f25_4) + ((B[0] * temp_f23_4) + (B[1] * sp2D0)));
    spE4 = (B[7] * sp2D4) + ((temp_f4_2 * temp_f25_4) + ((B[4] * temp_f23_4) + (B[5] * sp2D0)));
    spC8 = (B[3] * sp2A4) + ((B[2] * temp_f22_3) + ((B[0] * temp_f4_3) + sp29C));
    spD8 = (B[7] * temp_f5_4) + ((temp_f4_2 * temp_f22_3) + ((B[4] * sp294) + (B[5] * temp_f9)));
    spD0 = (B[3] * sp2CC) + ((B[2] * sp2C8) + ((B[0] * temp_f6_4) + (B[1] * sp2C4)));
    spDC = (B[7] * temp_f6_5) + ((temp_f4_2 * temp_f3_4) + ((B[4] * sp2A8) + (B[5] * sp2AC)));
    spE0 = (B[7] * sp2CC) + ((temp_f4_2 * sp2C8) + ((B[4] * sp2C0) + (B[5] * sp2C4)));
    spE8 = (B[11] * temp_f5_4) + ((B[10] * temp_f22_3) + ((B[8] * sp294) + (B[9] * sp298)));
    spCC = (B[3] * sp2BC) + sp2B8;
    sp2E8 = temp_f0_6 * sp2D0;
    temp_f6_6 = (temp_f13_6 * temp_f23_4) + sp2E8;
    temp_f4_4 = temp_f0_6 * sp2AC;
    sp2DC = temp_f4_4;
    temp_f8_3 = (temp_f13_6 * sp2A8) + temp_f4_4;
    sp2EC = temp_f6_6;
    sp2E0 = temp_f8_3;
    temp_f7_2 = (temp_f12_5 * sp2B4) + temp_f8_3;
    sp2D8 = (B[10] * sp2B4) + ((B[8] * sp2A8) + (B[9] * sp2AC));
    sp2E4 = temp_f7_2;
    spEC = (B[11] * sp2BC) + sp2D8;
    sp100 = (B[15] * sp2CC) + ((temp_f12_5 * sp2C8) + ((temp_f13_6 * sp2C0) + (temp_f0_6 * sp2C4)));
    spF0 = (B[11] * sp2CC) + ((B[10] * sp2C8) + ((B[8] * sp2C0) + (B[9] * sp2C4)));
    sp104 = (B[15] * sp2D4) + ((temp_f12_5 * temp_f25_4) + temp_f6_6);
    spF4 = (B[11] * sp2D4) + ((B[10] * temp_f25_4) + ((B[8] * temp_f23_4) + (B[9] * sp2D0)));
    /* 2 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    spF8 = (B[15] * sp2A4) + ((temp_f12_5 * temp_f22_3) + ((temp_f13_6 * sp294) + (temp_f0_6 * sp298)));
    spFC = (B[15] * sp2BC) + temp_f7_2;
    /* 3 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    if ( *(s32 *)(*arg0 + (s32)sp2FC) != NULL) {

    }
    /* 3 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    fn_80006FA8(sp30C, sp308, sp304, 0.0f);
    if (fn_80007090(sp30C, arg1, 0, arg6, mp3) != 0) {
        if (arg5 != NULL) {
            *arg5 = sqrtf(sp158);
        }
        /* 1 straight-line instruction(s) m2c dropped and no
           postprocessor recovered: psq_l/psq_st pair copies and
           their ps_* arithmetic.  Blocker #2 in the header. */
        return arg4;
    }
    /* 1 straight-line instruction(s) m2c dropped and no
       postprocessor recovered: psq_l/psq_st pair copies and
       their ps_* arithmetic.  Blocker #2 in the header. */
    return 0;
}
