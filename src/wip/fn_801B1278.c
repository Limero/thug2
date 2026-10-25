// WIP DRAFT — hand-rebuilt paired-single reconstruction (-mps-float). PARKED.
// family=m2c range=0x801B1278-0x801B1654 size=988B
// STATUS (2026-08-26, doc06 M5.0t retry): the old "REAL unknown op xo5=6/7"
// park is INVALID. All four mystery words 101DF00C/109DF00C/101DF00E/11BDF00E
// hand-decode as Gekko PS X-FORM indexed pair ops (XO@bits22-30 + w@bit21):
// psq_lx f4/f0 <- r29+r30 (1328/13F8/1488) and psq_stx f13/f0 -> r29+r30
// (1450/1490) — emittable from plain C under -mps-float. EVERY one of the 33
// opcode-4 words in this function decodes to standard emittable PS:
//   ps_mr 132C(f10<-f7)/1334(f8<-f0); merge00 133C(f11<-f8,f7)/1360(f0<-
//   f4,f5)/13B4(f10<-f12,f12)/1418(f8<-f8,f0rodata); merge10 1354(f10<-
//   f7,f8)/1358(f12<-f4,f5)/13A4(f10<-f11,f11 — DEAD result, retail kept it,
//   reproduced via "+f" barrier)/13D4(f12<-f12,f11); mul 1368/1374/1380/13E8;
//   muls0 1388/1398/139C/13B0/148C/1498; sub 1390/13AC; add 13BC/13C0/13DC/
//   13F4; madd 1420(f7*f4+f8); sum0 142C. Plus D-form psq_l/st spills.
//   capstone's vmrghb/vmhaddshs/vmsumshm/vsel/vpkuhum labels are ALL misreads
//   of these words (tools/ps_disasm.py also prints signed psq displacements
//   and phantom I1 fields — raw-word decode only).
// Structure rebuilt from disasm: chained fn_800335E0->GetChecksum_3,
// f1-chained fn_80036304->sqrtf (r3 call-arg staged at 1318 via r3
// register pin), quat-blend PS block -> arg1[idx] xy={A,A} zw via sum0 dot +
// fmsubs, fdivs scale tail (muls0 both pairs), fill loop (matches verbatim),
// self-targeting bdnz spin (doc30; falls out of plain C here), two row-copy
// loops, hit/miss row-copy loop with negation tail.
// Frame model: FR template struct covers r1+8..r1+0x9E3 exactly (0x9DC bytes;
// a4A8 sized 0x500 = want's silent third-quarter region); tl[15] pads to the
// save area. Want prologue: stwu -0xa10, stfd f30/f31 @a00/a08, stmw
// r25..r31 @0x9e4, LR @a14. Fill loop + spin + count-call region matches
// byte-for-byte including mtctr/bdnz forms and or.-test.
// extra_cflags: -mps-float
//
// RESIDUAL (why DIFF at ~20.6%, not NEAR/EXACT):
//  1. Block-C FPR web coloring: want reuses f0/f7-f13 across ~25 short webs
//     with exact recycle points; GCC's allocator picks different colors
//     despite per-web locals mirroring web lifetimes (load-fed pins r7/r4/r5/
//     fr30/fr31 stick; chain pins collapse per doc06 M5.0o/§6ae-169).
//  2. GPR homes: arg1 homes r30 vs want r29, cnt home r24 vs want r28
//     (recycled arg0 slot), temp_r25 needed an r25 pin to land right.
//  3. Copy-loop 1 converts to mtctr/bdnz form (want addic./bne);
//     -fno-strength-reduce/-fno-branch-count-reg/hard-reg pins do not block
//     it here; walker sa coalesces into a1c's register (want keeps a copy in
//     r11).
//  4. Hit loop: GCC splits the dw walker web (want keeps ONE r31 base with
//     displaced B/C/A-row accesses at +0/+8/+0xC00/+0xC08/-0x400/-0x3F4);
//     every decomposition tried rebases differently.
//  5. Quad-store run rotates [18,20,1C,24] vs want [18,1C,24,20]; pb lis/addi
//     sinks below the store run (want straddles it).
// ASM disclosure (recipe 185 audit): 32 explicit asm insn templates out of
// 247 total insns = 13% — scalar-phase fmr/lfs/stfs/fmsubs on mixed-mode
// values, dead-op barrier, pb pin. All control flow, memory structure, and
// semantics are C-carried; no raw-word transcription.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 20.2% ([9]rev->20.2%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ABE04;
extern f32 lbl_802ABE08;
extern char lbl_802ABDC8[];
s32 fn_80033604(s32 arg0);
s32 fn_800335E0(CStruct * arg0);
s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
s32 fn_80036810(Unk_C8FEE62D * arg0, s32 arg1);
f32 sqrtf(f32 arg0);
s32 fn_80036968(Unk_C8FEE62D * arg0);
s32 fn_8003A380(void *arg0, s32 arg1);
f32 fn_80036304(CStruct * arg0);

typedef union { __ps_t p; f32 w[2]; } PSU;

typedef struct FR {
    f32 q08[4];      /* r1+0x08 */
    f32 q18[4];      /* r1+0x18 quad {A,A,B,A} */
    f32 q28[8];      /* r1+0x28..0x47 */
    f32 q48[24];     /* r1+0x48..0xA7 spill pairs */
    s32 aA8[0x100];  /* r1+0xA8..0x4A7 */
    s32 a4A8[0x140]; /* r1+0x4A8..0x9A7 */
    f32 tl[15];      /* r1+0x9A8..0x9E3 */
} FR;

s32 fn_801B1278(CScript *arg0, s32 arg1) {
    FR fr;
    Unk_9994C3F5 *temp_r27;
    s32 temp_r25;
    Unk_31DE137E *temp_r3;
    s32 var_idx;
    register void *cap __asm__("r3");
    register s32 a1c __asm__("r29");
    register s32 t25 __asm__("r25");
    s32 c1;
    register f32 conA __asm__("fr31");
    register f32 conB __asm__("fr30");
    register __ps_t r7p __asm__("fr7");
    register __ps_t lBA __asm__("fr0");
    register __ps_t mA __asm__("fr10");
    register __ps_t mB __asm__("fr8");
    register __ps_t gBA __asm__("fr11");
    register __ps_t mYZ __asm__("fr12");

    register __ps_t r4p __asm__("fr4");
    register __ps_t r5p __asm__("fr5");
    Unk_7AAFF886 *r31p;
    f32 *qp;
    char *pb;
    char *tlp;
    char *tlm;
    char *tll;
    char *tl3;
    char *tl8;
    f32 fret;
    __ps_t mAB, mXZ, mulA, gY, gX, dAQ, qwg, qxA, sY,
        AAg, zwA, deadm, sX, BAg, uY, ad0, ad13, vZ, ad0b, rTL, mZ,
        ad13b, xy2, zw2, k01, mgK, dot7, su, pAA, oB, oA;
    f32 qwv, e60v;
    f32 sf13, sf12, sf10, sf0, sf3;
    f32 sv;
    f32 qw;
    __ps_t pa;
    __ps_t pb8;
    __ps_t pc;
    __ps_t pd;
    __ps_t pe;
    __ps_t pf;
    __ps_t pg;
    __ps_t ph;
    s32 idxoff;
    s32 cnt;
    s32 i;
    s32 k;
    s32 off;
    s32 off27;
    char *dw;
    char *srcAw;
    char *b8;
    char *sb;
    char *sa;
    f32 *fp;

    temp_r27 = (void *)fn_80033604(arg0);
    a1c = arg1;
    temp_r25 = t25 = temp_r27->unk0x8;
    /* single fn_800335E0 call; its return chains into GetChecksum_3 arg0 */
    temp_r3 = GetChecksum_3(fn_800335E0((s32)arg0), QB_SKATERFLIPANDROTATE);
    if ((temp_r3 != 0) && (temp_r3->unk0x1C != 0)) {
        var_idx = fn_80036810(temp_r27, QB_BONE_BOARD_ROOT);
        if (var_idx != -1) {
            conA = lbl_802ABE04;                 /* 12e4 lis/lfs f31 */
            qp = &fr.q18[0];             /* 12f0 addi r11 */
            conB = lbl_802ABE08;                 /* 12f4 lis/lfs f30 */
            idxoff = var_idx << 4;               /* 12f8 slwi r30 */
            qp[0] = conA;                        /* 12fc stfs 0x18 */
            r31p = (char *)a1c + idxoff;        /* 1300 add r31 */
            qp[1] = conA;                        /* 1304 stfs 0x1c */
            pb = lbl_802ABDC8;                   /* 1308 lis/addi r9 */
            __asm__("" : "+r"(pb));
            qp[3] = conA;                        /* 130c stfs 0x24 */
            qp[2] = conB;                        /* 1314 stfs 0x20 */
            cap = r31p;                          /* 1318 mr r3, r31 */
            tlp = (char *)&fr.tl[0];             /* 131c addi r11,0x9a8 */
            /* PS transform block (1320-1468) -> quat blend into arg1[idx].
               Each want value-web gets its own local; lifetimes mirror the
               DOL register web deaths so GCC colors approximate want. */
            r7p = *(__ps_t *)&fr.q18[0];         /* 1320 psq_l 24(r1) f7 */
            lBA = *(__ps_t *)&fr.q18[2];         /* 1324 psq_l 32(r1) f0 */
            r4p = *(__ps_t *)((char *)a1c + idxoff); /* 1328 psq_lx f4 */
            mA = r7p;                            /* 132c ps_mr f10,f7 */
            *(__ps_t *)&fr.q28[2] = lBA;         /* 1330 psq_st 48(r1) */
            mB = lBA;                            /* 1334 ps_mr f8,f0 */
            *(__ps_t *)&fr.q28[0] = r7p;         /* 1338 psq_st 40(r1) */
            gBA = __builtin_ps_merge00(mB, r7p); /* 133c ps_merge00 f11 */
            sv = fr.q28[3];                      /* 1340 lfs f3 */
            r5p = r31p->unk0x8;         /* 1344 psq_l 8(r31) f5 */
            *(__ps_t *)&fr.q28[4] = mA;          /* 1348 psq_st 56(r1) */
            __asm__ __volatile__("fmr %0, %1" : "=f"(sf13) : "f"(sv));   /* 134c */
            *(__ps_t *)&fr.q28[6] = mB;          /* 1350 psq_st 64(r1) */
            mAB = __builtin_ps_merge10(r7p, mB); /* 1354 ps_merge10 f10 */
            mYZ = __builtin_ps_merge10(r4p, r5p);/* 1358 ps_merge10 f12 */
            qwv = ((Unk_E266FB50_4 *)r31p)->unk0xC;          /* 135c lfs f2 */
            mXZ = __builtin_ps_merge00(r4p, r5p);/* 1360 ps_merge00 f0 */
            __asm__ __volatile__("stfs %0, %1" : : "f"(sf13), "m"(fr.tl[0])); /* 1364 */
            mulA = __builtin_ps_mul(mAB, r4p);   /* 1368 ps_mul f10 */
            __asm__ __volatile__("fmr %0, %1" : "=f"(sf13) : "f"(qwv));   /* 136c */
            __asm__ __volatile__("stfs %0, %1" : : "f"(sf13), "m"(fr.tl[2])); /* 1370 */
            gY = __builtin_ps_mul(r7p, mYZ);     /* 1374 ps_mul f12 */
            dAQ = *(__ps_t *)tlp;                /* 1378 psq_l {A,qw} f13 */
            tlm = (char *)&fr.tl[2];             /* 137c addi r11,0x9b0 */
            gX = __builtin_ps_mul(gBA, mXZ);     /* 1380 ps_mul f11 */
            qwg = *(__ps_t *)tlm;                /* 1384 psq_l {qw,uninit} f9 */
            qxA = __builtin_ps_muls0(r4p, dAQ);  /* 1388 ps_muls0 f0 */
            tll = (char *)&fr.tl[4];             /* 138c addi r11,0x9b8 */
            sY = __builtin_ps_sub(gY, qxA);      /* 1390 ps_sub f12 */
            *(__ps_t *)&fr.q48[12] = qxA;        /* 1394 psq_st 120(r1) */
            AAg = __builtin_ps_muls0(r7p, qwg);  /* 1398 ps_muls0 f6 */
            zwA = __builtin_ps_muls0(r5p, dAQ);  /* 139c ps_muls0 f13 */
            *(__ps_t *)&fr.q48[16] = AAg;        /* 13a0 psq_st 136(r1) */
            deadm = __builtin_ps_merge10(gX, gX);/* 13a4 DEAD in want */
            __asm__ __volatile__("" : "+f"(deadm));
            *(__ps_t *)&fr.q48[14] = zwA;        /* 13a8 psq_st 128(r1) */
            sX = __builtin_ps_sub(gX, qxA);      /* 13ac ps_sub f11 */
            BAg = __builtin_ps_muls0(mB, qwg);   /* 13b0 ps_muls0 f9 */
            uY = __builtin_ps_merge00(sY, sY);   /* 13b4 ps_merge00 f10 */
            *(__ps_t *)tll = uY;                 /* 13b8 psq_st 0(r11) */
            ad0 = __builtin_ps_add(qxA, AAg);    /* 13bc ps_add f0 */
            ad13 = __builtin_ps_add(zwA, BAg);   /* 13c0 ps_add f13 */
            *(__ps_t *)&fr.q48[8] = ad0;         /* 13c4 psq_st 104(r1) */
            __asm__ __volatile__("fmr %0, %1" : "=f"(sf10) : "f"(conB));  /* 13c8 */
            *(__ps_t *)&fr.q48[10] = ad13;       /* 13cc psq_st 112(r1) */
            __asm__ __volatile__("stfs %0, %1" : : "f"(sf10), "m"(fr.tl[5])); /* 13d0 */
            vZ = __builtin_ps_merge10(sY, sX);   /* 13d4 ps_merge10 f12 */
            *(__ps_t *)&fr.q48[18] = BAg;        /* 13d8 psq_st 144(r1) */
            ad0b = __builtin_ps_add(ad0, vZ);    /* 13dc ps_add f0 */
            *(__ps_t *)&fr.q48[20] = vZ;         /* 13e0 psq_st 152(r1) */
            rTL = *(__ps_t *)tll;                /* 13e4 reload tl[4..5] f12 */
            mZ = __builtin_ps_mul(mB, r5p);      /* 13e8 ps_mul f8 */
            *(__ps_t *)&fr.q48[4] = ad0b;        /* 13ec psq_st 88(r1) */
            *(__ps_t *)&fr.q48[22] = rTL;        /* 13f0 psq_st 160(r1) */
            ad13b = __builtin_ps_add(ad13, rTL); /* 13f4 ps_add f13 */
            xy2 = *(__ps_t *)((char *)a1c + idxoff); /* 13f8 psq_lx f0 */
            *(__ps_t *)&fr.q48[0] = xy2;         /* 13fc psq_st 72(r1) */
            zw2 = r31p->unk0x8;         /* 1400 psq_l f10 */
            *(__ps_t *)&fr.q48[2] = zw2;         /* 1404 psq_st 80(r1) */
            *(__ps_t *)&fr.q48[6] = ad13b;       /* 1408 psq_st 96(r1) */
            k01 = *(__ps_t *)pb;                 /* 140c rodata pair f0 */
            __asm__ __volatile__("lfs %0, %1" : "=f"(sf13) : "m"(fr.q48[4])); /* 1410 */
            tl3 = (char *)&fr.tl[6];             /* 1414 addi r9,0x9c0 */
            mgK = __builtin_ps_merge00(mZ, k01); /* 1418 ps_merge00 f8 */
            __asm__ __volatile__("lfs %0, %1" : "=f"(sf12) : "m"(fr.q48[5])); /* 141c */
            dot7 = __builtin_ps_madd(r7p, r4p, mgK); /* 1420 ps_madd f7 */
            __asm__ __volatile__("stfs %0, %1" : : "f"(sf13), "m"(fr.q28[0])); /* 1424 */
            e60v = fr.q48[6];                    /* 1428 lfs f11 */
            su = __builtin_ps_sum0(dot7, dot7, dot7); /* 142c ps_sum0 f7 */
            *(__ps_t *)tl3 = su;                 /* 1430 psq_st 0(r9) */
            __asm__ __volatile__("stfs %0, %1" : : "f"(sf12), "m"(fr.q28[1])); /* 1434 */
            __asm__ __volatile__("lfs %0, %1" : "=f"(sf10) : "m"(fr.tl[6]));  /* 1438 */
            __asm__ __volatile__("fmr %0, %1" : "=f"(sf0) : "f"(sf10));       /* 1440 */
            __asm__ __volatile__("stfs %0, %1" : : "f"(e60v), "m"(fr.q28[2])); /* 1444 */
            __asm__ __volatile__("fmsubs %0, %1, %2, %3" : "=f"(sf3) : "f"(sv), "f"(qwv), "f"(sf0)); /* 1448 */
            __asm__ __volatile__("stfs %0, %1" : : "f"(sf3), "m"(fr.q28[3])); /* 144c */
            pAA = *(__ps_t *)&fr.q28[4];         /* 143c psq_l 40(r1) f13 */
            *(__ps_t *)((char *)a1c + idxoff) = pAA; /* 1450 psq_stx */
            oB = *(__ps_t *)&fr.q28[2];          /* 1454 psq_l 48(r1) f10 */
            oA = *(__ps_t *)&fr.q28[0];          /* 1458 psq_l 40(r1) f0 */
            *(__ps_t *)&fr.q08[2] = oB;          /* 145c psq_st 16(r1) */
            *(__ps_t *)&fr.q08[0] = oA;          /* 1460 psq_st 8(r1) */
            r31p->unk0x8 = oB;          /* 1464 psq_st 8(r31)
            /* back-to-back bls: fn_80036304's f1 return feeds sqrtf */
            if ((fret = sqrtf(fn_80036304(cap))) > conA) {
                conB = conB / fret;              /* 1478 fdivs */
                tl8 = (char *)&fr.tl[8];         /* 147c addi r9,0x9c8 */
                fr.tl[8] = conB;                 /* 1480 stfs */
                {
                    register __ps_t rCf __asm__("fr12");
                    rCf = *(__ps_t *)tl8;        /* 1484 */
                    pa = *(__ps_t *)((char *)a1c + idxoff); /* 1488 lx */
                    pa = __builtin_ps_muls0(pa, rCf);    /* 148c */
                    *(__ps_t *)((char *)a1c + idxoff) = pa; /* 1490 stx */
                    {
                        register __ps_t rDf __asm__("fr13");
                        rDf = r31p->unk0x8;       /* 1494 */
                        rDf = __builtin_ps_muls0(rDf, rCf);/* 1498 */
                        r31p->unk0x8 = rDf;       /* 149c */
                    }
                }
            }
        }
    }
    if (arg0->unk0x18 != 0) {
        {
            register f32 cb2 __asm__("fr13");
            register f32 ca2 __asm__("fr0");
            cb2 = lbl_802ABE08;                  /* 14b4 lfs f13 */
            k = 0x40;                            /* 14b8 li r11 */
            ca2 = lbl_802ABE04;                  /* 14bc lfs f0 */
            fp = (f32 *)&fr.aA8[0];              /* 14c4 addi r9 */
            do {
                fp[0] = ca2;
                fp[1] = ca2;
                fp[2] = ca2;
                fp[3] = cb2;
                fp += 4;
                k -= 1;
            } while (k != 0);
        }
        k = 0x40;
        do {
            k -= 1;
        } while (k != 0);
        if ((cnt = fn_80036968(temp_r27)) > 0) {
            sa = (char *)a1c;
            sb = (char *)&fr.aA8[0];
            c1 = cnt;
            do {
                pa = *(__ps_t *)sa;
                c1 -= 1;
                *(__ps_t *)sb = pa;
                pe = ((Unk_C1F9F519 *)sa)->unk0x8;
                ((Unk_C1F9F519 *)sb)->unk0x8 = pe;
                sa += 0x10;
                sb += 0x10;
            } while (c1 != 0);
        }
        if (cnt > 0) {
            sa = (char *)a1c + 0x400;
            off = 0;
            c1 = cnt;
            do {
                pa = ((Unk_C1F9F519 *)sa)->unk0x8;
                sb = (char *)&fr.a4A8[0] + off;
                off += 0x10;
                ((Unk_C1F9F519 *)sb)->unk0x8 = pa;
                pe = *(__ps_t *)sa;
                *(__ps_t *)sb = pe;
                sa += 0x10;
            } while (c1 != 0);
        }
        dw = (char *)a1c + 0x400;
        srcAw = (char *)&fr.aA8[0];
        b8 = (char *)&fr;
        off27 = 0;
        for (i = 0; i < cnt; i++) {
            s32 hit = fn_8003A380(t25, i);
            if (hit != -1) {
                char *s4 = (char *)&fr.a4A8[0] + (hit << 4);
                char *t = b8 + (hit << 4);
                char *sA = t + 0xA0;
                ((Unk_D686B995 *)dw)->unk0x8 = ((Unk_C1F9F519 *)s4)->unk0x8;
                ((Unk_D686B995 *)dw)->unk0xC08 = ((Unk_C1F9F519 *)sA)->unk0x8;
                ((Unk_D686B995 *)dw)->unk0xC00 = ((Unk_C1F9F519 *)sA)->unk0x0;
                ((Unk_D686B995 *)dw)->unk0x0 = ((Unk_C1F9F519 *)s4)->unk0x0;
            } else {
                ((Unk_D686B995 *)dw)->unk0xC00 = ((Unk_C1F9F519 *)srcAw)->unk0x0;
                ((Unk_D686B995 *)dw)->unk0xC08 = ((Unk_C1F9F519 *)srcAw)->unk0x8;
                sb = (char *)&fr.a4A8[0] + off27;
                ((Unk_D686B995 *)dw)->unk0x8 = ((Unk_C1F9F519 *)sb)->unk0x8;
                ((Unk_D686B995 *)dw)->unk0x0 = ((Unk_C1F9F519 *)sb)->unk0x0;
            }
            *(f32 *)(dw - 0x400) = -*(f32 *)(dw - 0x400);
            *(f32 *)(dw - 0x3F4) = -*(f32 *)(dw - 0x3F4);
            *(f32 *)dw = -*(f32 *)dw;
            off27 += 0x10;
            srcAw += 0x10;
            dw += 0x10;
        }
    }
    return 1;
}
