// WIP DRAFT - RETRY of the false AltiVec park (doc06 M5.0q decode discipline;
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 31.7726% -> 58.1169%
//   the `zerof` pin was retargeted fr31 -> fr22 (nothing else touched).  New axis:
//   fr-pin REMOVAL had been swept, retargeting had not.  AGENTS-recipes §6hk.
// PARKED 2026-10-16: still 58.1% NEAR, size-exact 1196B. Re-verified: the
// v3 then-arm pair stays crossjumped away under every web shape; no new
// crossjump-suppressing lever since the 2026-10-07 pin retarget. Body kept.
// doc-29 correction). Old claim "vmhaddshs/vmsumshm @FE79C-FE850" was WRONG:
// all 25 opcode-4 words hand-decoded BOTH ways are standard Gekko PS:
//   ps_sub x6 (C=0) @79C/7A4/7C4/7CC/7F4/810 ; ps_merge10 x4 (C=18)
//   @7E0/7E4/80C/818 ; ps_merge00 x4 (C=16) @7F0/7F8/7FC/844 ;
//   ps_mul xo5=25 B=0 multiplier-in-C-slot @7E8(C=12)/7EC(C=13)/800(C=12)/
//   840(C=0)/880(C=11) - exactly ngccc 3.9.3 __builtin_ps_mul encoding
//   (probe-verified); ps_madd @848(A=f12,B=f0,C=f12), ps_sum0 @84C,
//   ps_rsqrte @85C, ps_muls0 @864, X-form XO10=72 ps_mr @838/850,
//   plus ~30 psq_l/psq_st W0/I0. Fully emittable under -mps-float.
//
// Status: NEAR-best compiling body, PARKED (87/291 = 30% masked index-score;
// ~90% content-similar). What matches byte-exact: prologue/frame 0x10F8
// (frame-template struct incl. the f32-callarg +8 quirk), preheader freeze
// FE480-FE49C, fn_8010391C call chain + guarded-do loop scaffolding, all six
// vertex-load blocks v1/v2 (both paths) incl. per-arm table select + join,
// pv0/pv1/pv2 births, fn_800F6DE0 call/guard, the ENTIRE PS block FE74C-FE884
// frozen verbatim (dead stores sp1048/50/58, r9/r11 recycling, don't-care C
// fields - word map inline below), fn_800F6AD0 tail call (mixed ABI: float
// arg in f1 from &sp1094), latch + epilogue.
// Residual wall (vertex-3 only): want keeps the two IDENTICAL v3 then-arms
// INLINE (A@5A8/B@6C4, word-for-word equal incl. tails) and shares only the
// else-arm pair (@6E8, entered by two beqs); ngccc 3.9.3 crossjumps BOTH
// pairs away to far shared blocks ([bne shared-then][b shared-else]) no
// matter how the webs are shaped. Exhausted: t/vi/vtv/vtj pin sets, per-path
// web splits (vtj3a/vtj3b fixed the cascade - streams now fully index-
// aligned), goto/label form, arm polarity flips, store-order asymmetry,
// pointer-vs-int vt tests, 14 flag combos (-fno-crossjumping/-reorder-blocks
// do not exist in SN cc1). Same intermediate-SN-build behavior family as
// doc06 M5.0j dead-psq_st artifact. Retry when a crossjump-suppressing lever
// or matching build appears; everything else here is done.
// extra_cflags: -mps-float
// family=m2c range=0x800FE42C-0x800FE8D8 size=1196B
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 31.8% ([12]rev->31.8%).
#include "types.h"
#include "structs.h"

extern char lbl_8029C1A8[]; /* 0.0f  */
typedef union { __ps_t p; f32 w[2]; } S;

s32 fn_8010391C(CStruct *, s32, s32 *, void *, s32);
s32 fn_800F6DE0(void *, void *, void *, void *, void *, void *);
s32 fn_800F6AD0(s32, s32, void *, s32, f32);

s32 fn_800FE42C(Unk_9994C3F5 *arg0, void *arg1, void *arg2, void *arg3, s32 arg4) {
    struct {
        char buf[0x1000]; /* sp8 .. sp1007 query workspace */
        S p0xy;  /* 1008 */
        S p0zw;  /* 1010 */
        S p1xy;  /* 1018 */
        S p1zw;  /* 1020 */
        S p2xy;  /* 1028 */
        S p2zw;  /* 1030 */
        S w38;   /* 1038 */
        S w40;   /* 1040 */
        S w48;   /* 1048 */
        S w50;   /* 1050 */
        s32 node;/* 1058 */
        S dxy;   /* 1060 */
        S dzw;   /* 1068 */
        S exy;   /* 1070 */
        S ezw;   /* 1078 */
        S s80;   /* 1080 */
        S s88;   /* 1088 */
        s32 cnt; /* 1090 */
        f32 dst; /* 1094 */
        S s98;   /* 1098 */
        f32 n9C; /* 109C */
        S sA0;   /* 10A0 */
    } fr;
    register s32 a0 __asm__("r28");
    register s32 a1 __asm__("r20");
    register s32 a2 __asm__("r17");
    register s32 a3 __asm__("r16");
    register s32 res __asm__("r18");
    register s32 iv __asm__("r19");
    register char *cur __asm__("r27");
    register char *q1010 __asm__("r26");
    register char *q1060 __asm__("r21");
    register char *q1068 __asm__("r22");
    register char *q1070 __asm__("r23");
    register char *q1080 __asm__("r24");
    register char *q1088 __asm__("r25");
    register char *pv0 __asm__("r31");
    register char *pv1 __asm__("r30");
    register char *pv2 __asm__("r29");
    register f32 zerof __asm__("fr22");
    register char *pair38 __asm__("r5");
    register void *t __asm__("r10");
    register s32 vi0 __asm__("r11");
    register void *t3 __asm__("r8");
    register s32 vtv3 __asm__("r10");
    void *vtj3a;
    void *vtj3b;
    s32 sc3;
    register s32 vi03 __asm__("r9");
    f32 px3;
    f32 py3;
    f32 pz3;
    s32 vtv;
    s32 vtv1;
    s32 vtj;
    Unk_010E853D *ent;
    s32 sc;
    u16 nd;
    f32 px;
    f32 py;
    f32 pz;
    s32 ret;

    a0 = (s32)arg0;
    a1 = (s32)arg1;
    a2 = (s32)arg2;
    a3 = (s32)arg3;
    res = 0;
    cur = (char *)fn_8010391C(arg0->unk0x8, arg4, &fr.cnt,
                              fr.buf, 0x800);
    iv = 0;
    if ((u32)res < (u32)fr.cnt) {
        /* preheader FE480-FE49C: page lis + pair-slot addis + f31=0.0f */
        __asm__ __volatile__(
            ".long 0x3D20802A\n\t"   /* lis r9, 0x802A (page of lbl_8029C1A8) */
            "addi %0, 1, 0x1010\n\t"
            "lfs 31, -0x3e58(9)\n\t" /* zerof = *(f32*)0x8029C1A8 */
            "addi %1, 1, 0x1060\n\t"
            "addi %2, 1, 0x1068\n\t"
            "addi %3, 1, 0x1070\n\t"
            "addi %4, 1, 0x1080\n\t"
            "addi %5, 1, 0x1088"
            : "=r"(q1010), "=r"(q1060), "=r"(q1068), "=r"(q1070),
              "=r"(q1080), "=r"(q1088)
            :
            : "r9", "memory");
        do {
            t = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            if (((Unk_A6515021 *)t)->unk0xA != 0) {
                nd = *(u16 *)cur;
                ent = (char *)((Unk_A6515021 *)t)->unk0xC + ((s32)nd << 3);
            t = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            vtv = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
            vi0 = ent->unk0x4;

            if (vtv != 0) {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + vtv));
                fr.p0xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x3C) + 4);
                fr.p0xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
            } else {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + (s32)((Unk_A6515021 *)t)->unk0x30));
                fr.p0xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x30) + 4);
                fr.p0xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x30);
            }
            sc = sc + vtj;
            pz = *((f32 *)&((Unk_9994C3F5 *)sc)->unk0x8);
            fr.p0zw.w[1] = zerof;
            fr.p0zw.w[0] = pz;
            t = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            vi0 = ((Unk_912FC5E0 *)ent)->unk0x5;
            vtv1 = ((Unk_A6515021 *)t)->unk0x3C;

            if (vtv1 != 0) {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + vtv1));
                fr.p1xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x3C) + 4);
                fr.p1xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
            } else {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + (s32)((Unk_A6515021 *)t)->unk0x30));
                fr.p1xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x30) + 4);
                fr.p1xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x30);
            }
            sc = sc + vtj;
            pz = *((f32 *)&((Unk_9994C3F5 *)sc)->unk0x8);
            fr.p1zw.w[1] = zerof;
            fr.p1zw.w[0] = pz;
            t3 = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            vi03 = ent->unk0x6;
            vtv3 = *((void * *)&((Unk_C7387A53 *)t3)->unk0x3C);

                        if (vtv3 == 0)
                goto alt_A;

                sc3 = vi03 * 12;
                px3 = *(f32 *)((char *)(sc3 + vtv3));
                fr.p2xy.w[0] = px3;
                py3 = *(f32 *)((char *)(sc3 + ((Unk_A6515021 *)t)->unk0x3C) + 4);
                fr.p2xy.w[1] = py3;
                vtj3a = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
                        goto join_A;
        alt_A:

                sc3 = vi03 * 12;
                px3 = *(f32 *)((char *)(sc3 + (s32)((Unk_A6515021 *)t)->unk0x30));
                fr.p2xy.w[0] = px3;
                py3 = *(f32 *)((char *)(sc3 + ((Unk_A6515021 *)t)->unk0x30) + 4);
                fr.p2xy.w[1] = py3;
                vtj3a = *((void * *)&((Unk_A6515021 *)t)->unk0x30);
                    join_A:

            sc3 = sc3 + vtj3a;
            pz3 = *((f32 *)&((Unk_9994C3F5 *)sc3)->unk0x8);
            fr.p2zw.w[1] = zerof;
            fr.p2zw.w[0] = pz3;
            } else {
                ent = (char *)((Unk_A6515021 *)t)->unk0xC + ((s32)nd * 10);
                nd = *(u16 *)cur;
            t = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            vtv = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
            vi0 = *((u16 *)&ent->unk0x4);

            if (vtv != 0) {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + vtv));
                fr.p0xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x3C) + 4);
                fr.p0xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
            } else {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + (s32)((Unk_A6515021 *)t)->unk0x30));
                fr.p0xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x30) + 4);
                fr.p0xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x30);
            }
            sc = sc + vtj;
            pz = *((f32 *)&((Unk_9994C3F5 *)sc)->unk0x8);
            fr.p0zw.w[1] = zerof;
            fr.p0zw.w[0] = pz;
            t = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            vi0 = *((u16 *)&ent->unk0x6);
            vtv1 = ((Unk_A6515021 *)t)->unk0x3C;

            if (vtv1 != 0) {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + vtv1));
                fr.p1xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x3C) + 4);
                fr.p1xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
            } else {
                sc = vi0 * 12;
                px = *(f32 *)((char *)(sc + (s32)((Unk_A6515021 *)t)->unk0x30));
                fr.p1xy.w[0] = px;
                py = *(f32 *)((char *)(sc + ((Unk_A6515021 *)t)->unk0x30) + 4);
                fr.p1xy.w[1] = py;
                vtj = *((void * *)&((Unk_A6515021 *)t)->unk0x30);
            }
            sc = sc + vtj;
            pz = *((f32 *)&((Unk_9994C3F5 *)sc)->unk0x8);
            fr.p1zw.w[1] = zerof;
            fr.p1zw.w[0] = pz;
            t3 = *((void * *)&((Unk_9994C3F5 *)a0)->unk0x8);
            vi03 = ((Unk_912FC5E0 *)ent)->unk0x8;
            vtv3 = *((void * *)&((Unk_C7387A53 *)t3)->unk0x3C);

                        if (vtv3 == 0)
                goto alt_B;

                sc3 = vi03 * 12;
                px3 = *(f32 *)((char *)(sc3 + vtv3));
                fr.p2xy.w[0] = px3;
                py3 = *(f32 *)((char *)(sc3 + ((Unk_A6515021 *)t)->unk0x3C) + 4);
                fr.p2xy.w[1] = py3;
                vtj3b = *((void * *)&((Unk_A6515021 *)t)->unk0x3C);
                        goto join_B;
        alt_B:

                sc3 = vi03 * 12;
                px3 = *(f32 *)((char *)(sc3 + (s32)((Unk_A6515021 *)t)->unk0x30));
                fr.p2xy.w[0] = px3;
                py3 = *(f32 *)((char *)(sc3 + ((Unk_A6515021 *)t)->unk0x30) + 4);
                fr.p2xy.w[1] = py3;
                vtj3b = *((void * *)&((Unk_A6515021 *)t)->unk0x30);
                    join_B:

            sc3 = sc3 + vtj3b;
            pz3 = *((f32 *)&((Unk_9994C3F5 *)sc3)->unk0x8);
            fr.p2zw.w[0] = pz3;
            fr.p2zw.w[1] = zerof;
            }

            pv0 = &fr.p0xy;
            pv1 = &fr.p1xy;
            pv2 = &fr.p2xy;
            ret = fn_800F6DE0(a1, a2, pv0, pv1, pv2, &fr.dst);
            if (ret != 0) {
                __asm__ __volatile__(
                    "psq_l 0, 0(31), 0, 0\n\t"                 /* 74C P0.xy */
                    "addi 9, 1, 0x1048\n\t"                    /* 750  */
                    "addi 11, 1, 0x1050\n\t"                   /* 754  */
                    "addi 10, 1, 0x1020\n\t"                   /* 758  */
                    "psq_st 0, 0(9), 0, 0\n\t"                 /* 75C dead copy P0.xy */
                    "addi 8, 1, 0x1030\n\t"                    /* 760  */
                    ".long 0x3D20802A\n\t"                     /* 764 lis r9,0x802A */
                    ".long 0x3CC0802A\n\t"                     /* 768 lis r6,0x802A */
                    "psq_l 11, 0(26), 0, 0\n\t"                /* 76C P0.zw */
                    "addi 9, 9, -0x3fa0\n\t"                   /* 770 -> lbl_8029C060 */
                    "addi %0, 1, 0x1038\n\t"                   /* 774 pair38 birth */
                    "addi 7, 1, 0x1040\n\t"                    /* 778  */
                    "psq_st 11, 0(11), 0, 0\n\t"               /* 77C dead copy P0.zw */
                    "addi 11, 1, 0x1078\n\t"                   /* 780  */
                    "lhz 0, 0(27)\n\t"                         /* 784 node */
                    "stw 0, 0x1058(1)\n\t"                     /* 788 dead node store */
                    "psq_l 12, 0(31), 0, 0\n\t"                /* 78C  */
                    "psq_l 0, 0(30), 0, 0\n\t"                 /* 790  */
                    "psq_l 11, 0(26), 0, 0\n\t"                /* 794  */
                    "psq_l 13, 0(10), 0, 0\n\t"                /* 798  */
                    ".long 0x10006028\n\t"                     /* 79C ps_sub dxy */
                    "psq_st 0, 0(21), 0, 0\n\t"                /* 7A0 -> sp1060 */
                    ".long 0x11AD5828\n\t"                     /* 7A4 ps_sub dzw */
                    "psq_l 8, 0(9), 0, 0\n\t"                  /* 7A8 f8={0,0} pair */
                    "psq_st 13, 0(22), 0, 0\n\t"               /* 7AC -> sp1068 */
                    "addi 9, 1, 0x1098\n\t"                    /* 7B0  */
                    "psq_l 13, 0(31), 0, 0\n\t"                /* 7B4  */
                    "psq_l 0, 0(29), 0, 0\n\t"                 /* 7B8  */
                    "psq_l 12, 0(26), 0, 0\n\t"                /* 7BC  */
                    "psq_l 9, 0(8), 0, 0\n\t"                  /* 7C0  */
                    ".long 0x10006828\n\t"                     /* 7C4 ps_sub exy */
                    "psq_st 0, 0(23), 0, 0\n\t"                /* 7C8 -> sp1070 */
                    ".long 0x11296028\n\t"                     /* 7CC ps_sub ezw */
                    "psq_st 9, 0(11), 0, 0\n\t"                /* 7D0 -> sp1078 */
                    "psq_l 10, 0(21), 0, 0\n\t"                /* 7D4 dxy */
                    "psq_l 12, 0(23), 0, 0\n\t"                /* 7D8 exy */
                    "psq_l 0, 0(22), 0, 0\n\t"                 /* 7DC dzw */
                    ".long 0x11AC4CA0\n\t"                     /* 7E0 merge10 {ey,ez} */
                    ".long 0x116A04A0\n\t"                     /* 7E4 merge10 {dy,dz} */
                    ".long 0x116B0332\n\t"                     /* 7E8 mul f11*f12 */
                    ".long 0x11AA0372\n\t"                     /* 7EC mul f10*f13 */
                    ".long 0x118C4C20\n\t"                     /* 7F0 merge00 {ex,ez} */
                    ".long 0x11AD5828\n\t"                     /* 7F4 sub {cz,cx} */
                    ".long 0x10005420\n\t"                     /* 7F8 merge00 {dz,dx} */
                    ".long 0x116D6C20\n\t"                     /* 7FC merge00 splat cz */
                    ".long 0x10000332\n\t"                     /* 800 mul {dz2,dx2} */
                    "psq_st 11, 0(9), 0, 0\n\t"                /* 804 -> sp1098 */
                    "lfs 11, -0x3e54(6)\n\t"                   /* 808 1.0f */
                    ".long 0x118004A0\n\t"                     /* 80C merge10 swap */
                    ".long 0x10006028\n\t"                     /* 810 sub diff */
                    "stfs 11, 0x109C(1)\n\t"                   /* 814 dead store */
                    ".long 0x11AD04A0\n\t"                     /* 818 merge10 */
                    "psq_st 13, 0(24), 0, 0\n\t"               /* 81C -> sp1080 */
                    "psq_l 0, 0(9), 0, 0\n\t"                  /* 820  */
                    "psq_st 0, 0(25), 0, 0\n\t"                /* 824 -> sp1088 */
                    "psq_l 12, 0(24), 0, 0\n\t"                /* 828  */
                    "psq_st 12, 0(5), 0, 0\n\t"                /* 82C -> sp1038 */
                    "psq_l 13, 0(25), 0, 0\n\t"                /* 830  */
                    "psq_st 13, 0(7), 0, 0\n\t"                /* 834 -> sp1040 */
                    ".long 0x10006890\n\t"                     /* 838 ps_mr f0<-f13 */
                    "psq_l 12, 0(5), 0, 0\n\t"                 /* 83C  */
                    ".long 0x10000032\n\t"                     /* 840 mul dd*dd */
                    ".long 0x10004420\n\t"                     /* 844 merge00 w/zero-pair */
                    ".long 0x100C033A\n\t"                     /* 848 ps_madd */
                    ".long 0x10000014\n\t"                     /* 84C ps_sum0 */
                    ".long 0x11600090\n\t"                     /* 850 ps_mr f11<-f0 */
                    "fcmpu 0, 11, 31\n\t"                      /* 854 mag vs 0.0f */
                    "ble 1f\n\t"                               /* 858 skip clamp */
                    ".long 0x11A00034\n\t"                     /* 85C ps_rsqrte f13,f0 */
                    "addi 9, 1, 0x10a0\n\t"                    /* 860  */
                    ".long 0x100C0358\n\t"                     /* 864 ps_muls0 f0,f12,f13 */
                    "psq_st 0, 0(5), 0, 0\n\t"                 /* 868 -> sp1038 */
                    "psq_st 13, 0(9), 0, 0\n\t"                /* 86C -> sp10A0 */
                    "lfs 0, -0x3e54(6)\n\t"                    /* 870 1.0f */
                    "stfs 0, 0x10A4(1)\n\t"                    /* 874 dead store */
                    "psq_l 0, 0(7), 0, 0\n\t"                  /* 878  */
                    "psq_l 11, 0(9), 0, 0\n\t"                 /* 87C  */
                    ".long 0x100002F2\n\t"                     /* 880 mul scale */
                    "psq_st 0, 0(7), 0, 0"                 /* 884 -> sp1040 */
                    "
	1:"
                    : "=r"(pair38)
                    :
                    : "r0", "r6", "r7", "r8", "r9", "r10", "r11",
                      "fr0", "fr8", "fr9", "fr10", "fr11", "fr12", "fr13",
                      "memory");
                /* liveness pins: keep asm-read registers live across block */
                __asm__ volatile(""
                                 :
                                 : "r"(pv0), "r"(pv1), "r"(pv2), "r"(q1010),
                                   "r"(q1060), "r"(q1068), "r"(q1070),
                                   "r"(q1080), "r"(q1088), "f"(zerof));
                if (fn_800F6AD0(a1, a0, pair38, a3,
                                *(volatile f32 *)&fr.dst) != 0) {
                    res = 1;
                }
            }
            iv++;
            cur += 2;
        } while ((u32)iv < (u32)fr.cnt);
    }
    return res;
}
