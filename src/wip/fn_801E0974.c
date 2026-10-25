// WIP DRAFT (hand-rebuilt from disasm)
// family=m2c range=0x801E0974-0x801E1224 size=2224B
// PARKED 13.7%: big-function allocator-order wall (want saves more
// callee-saved webs than C reconstruction reaches). Structure fully
// reconstructed (matrix pair-mul via fn_80003EB0, two doc-30 bdnz$ spin
// windows via split volatile asm, psq copies via __ps_t, duplicated-call
// tail, cror/bns float guard). Register homes stay inverted vs want:
// want anchor=r31/arg0=r29/m78=r30 + two &slot bases r27/r28 (stmw r27,
// frame 0x110, 7 FPRs); got arg0 pin lands but anchor emits lis+copy via
// scratch instead of bare lis r31; stmw span short one web; frame 0xd8;
// 6 FPRs. Tried: raw chases (GCSE shares anchor in wrong reg), named mgrP,
// pin-a-copy arg0->r29 (+13.7%), anchor pin r31 + m2p same-reg recycle
// (6ad-166), m78 pin r30, inline-asm @ha/"s" anchor birth (regressed to
// 2.7%), sa/sb slot-pair arrays for base webs (regressed).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AD750;
extern f32 lbl_802AD754;
extern f32 lbl_802AD758;
extern f32 lbl_802AD75C;
extern f32 lbl_802AD760;
extern f32 lbl_802AD764;
extern char lbl_80305EAC[];
extern s32 lbl_80305F04;
extern char lbl_80303150[];

typedef struct { char _0[0x24]; s32 unk24; } MgrA_t;
typedef struct { char _0[0x13C]; f32 unk13C; f32 unk140; } MgrB_t;
typedef struct { char _0[0x13F0]; f32 unk13F0; } MgrC_t;
typedef struct { char _0[0x1C]; s32 unk1C; } MgrD_t;
typedef struct { char _0[0x40]; s32 unk40; char _44[0x6C]; s32 unkAC; } MgrE_t;

s32 fn_801A6F44(s32 arg0, s32 arg1);
void fn_801A6F8C(s32 arg0, s32 arg1);
s32 Script_GetInteger(s32 arg0, s32 arg1);
f32 fn_8012570C(s32 arg0, s32 arg1);
void fn_801A3E4C(Unk_C8FEE62D * arg0);
f32 fn_801F0958(Unk_31DE137E * arg0);
void *fn_80003EB0(Unk_DB0E2BAB * arg0, f32 farg1);
f32 fn_8014030C(s32 arg0, s32 arg1, Unk_FFAD6788 * arg2);
void fn_8017F5B0(Unk_FFAD6788 * arg0, s32 arg1);
s32 Tmr_GetTime(void);

void fn_801E0974(void *arg0) {
    f32 sp8[16];
    f32 sp48[16];
    void *sp88;
    void *sp8C;
    void *sp90;
    void *sp94;
    f32 temp_f1;
    f32 var_f25;
    f32 var_f31;
    f32 f750;
    MgrA_t *temp_r9;
    MgrB_t *temp_r11;
    MgrB_t *temp_r9_2;
    MgrB_t *mgrb;
    MgrD_t *objd;
    MgrE_t *flg;
    MgrC_t *mgrc;
    f32 *R;
    f32 *M;
    f32 *M2;
    f32 t94;
    register void *a0 __asm__("r29");
    register MgrA_t **anchor __asm__("r31");

    a0 = arg0;
    anchor = (MgrA_t **)&lbl_80305EAC;
    temp_r9 = *anchor;
    if (fn_801A6F44(temp_r9->unk24, (s32)QB_CHEAT_PERFECT_RAIL) != 0) {
        temp_r9 = *anchor;
        fn_801A6F8C(temp_r9->unk24, Script_GetInteger(QB_CHEAT_PERFECT_RAIL, 0));
        temp_r11 = *((MgrB_t * *)&((Unk_1E29BE92 *)a0)->unk0x15B8);
        f750 = lbl_802AD750;
        temp_r11->unk13C = f750;
        lbl_80305F04 = 1;
        temp_r9_2 = *((MgrB_t * *)&((Unk_1E29BE92 *)a0)->unk0x15B8);
        temp_r9_2->unk140 = f750;
    }
    mgrb = *((MgrB_t * *)&((Unk_1E29BE92 *)a0)->unk0x15B8);
    fn_801A3E4C((char *)mgrb + 0x108);
    var_f31 = fn_8012570C(QB_NATAS_SPIN_FACTOR, 1);
    temp_f1 = fabs(fn_801F0958(*((MgrB_t * *)&((Unk_1E29BE92 *)a0)->unk0x15B8)));
    var_f25 = var_f31 - (temp_f1 / (lbl_802AD754 / var_f31)) + lbl_802AD758;
    if (((Unk_1E29BE92 *)a0)->unk0x1590 != 0) {
        var_f25 = -var_f25;
    }
    t94 = ((Unk_1E29BE92 *)a0)->unk0x94;
    {
        register char *m2p __asm__("r31");
        m2p = (char *)a0 + 0x20;
        M2 = (f32 *)m2p;
    }
    ((Unk_1E29BE92 *)a0)->unk0x424 = (var_f25 < lbl_802AD750);
    {
        register f32 *m78r __asm__("r30");
        m78r = *((f32 * *)&((Unk_1E29BE92 *)a0)->unk0xC) + 0x78;
        M = m78r;
    }
    var_f25 *= t94;
    __asm__ volatile("li 0, 4\n\tmtctr 0\n\tbdnz $" ::: "r0", "ctr");
    sp88 = fn_80003EB0(sp8, var_f25);
    R = (f32 *)sp88;
    __asm__ volatile("li 0, 4\n\tmtctr 0" ::: "r0", "ctr");
    sp8C = M;
    sp48[0] = R[0] * M[0] + R[1] * M[4] + R[2] * M[8] + R[3] * M[12];
    sp48[1] = R[0] * M[1] + R[1] * M[5] + R[2] * M[9] + R[3] * M[13];
    sp48[2] = R[0] * M[2] + R[1] * M[6] + R[2] * M[10] + R[3] * M[14];
    sp48[3] = R[0] * M[3] + R[1] * M[7] + R[2] * M[11] + R[3] * M[15];
    sp48[4] = R[4] * M[0] + R[5] * M[4] + R[6] * M[8] + R[7] * M[12];
    sp48[5] = R[4] * M[1] + R[5] * M[5] + R[6] * M[9] + R[7] * M[13];
    sp48[6] = R[4] * M[2] + R[5] * M[6] + R[6] * M[10] + R[7] * M[14];
    sp48[7] = R[4] * M[3] + R[5] * M[7] + R[6] * M[11] + R[7] * M[15];
    sp48[8] = R[8] * M[0] + R[9] * M[4] + R[10] * M[8] + R[11] * M[12];
    sp48[9] = R[8] * M[1] + R[9] * M[5] + R[10] * M[9] + R[11] * M[13];
    sp48[10] = R[8] * M[2] + R[9] * M[6] + R[10] * M[10] + R[11] * M[14];
    sp48[11] = R[8] * M[3] + R[9] * M[7] + R[10] * M[11] + R[11] * M[15];
    sp48[12] = R[12] * M[0] + R[13] * M[4] + R[14] * M[8] + R[15] * M[12];
    sp48[13] = R[12] * M[1] + R[13] * M[5] + R[14] * M[9] + R[15] * M[13];
    sp48[14] = R[12] * M[2] + R[13] * M[6] + R[14] * M[10] + R[15] * M[14];
    sp48[15] = R[12] * M[3] + R[13] * M[7] + R[14] * M[11] + R[15] * M[15];
    ((Unk_18AF37A6 *)M)->unk0x0 = *(__ps_t *)&sp48[0];
    ((Unk_18AF37A6 *)M)->unk0x8 = *(__ps_t *)&sp48[2];
    ((Unk_18AF37A6 *)M)->unk0x10 = *(__ps_t *)&sp48[4];
    ((Unk_18AF37A6 *)M)->unk0x18 = *(__ps_t *)&sp48[6];
    ((Unk_18AF37A6 *)M)->unk0x20 = *(__ps_t *)&sp48[8];
    ((Unk_18AF37A6 *)M)->unk0x28 = *(__ps_t *)&sp48[10];
    ((Unk_18AF37A6 *)M)->unk0x30 = *(__ps_t *)&sp48[12];
    ((Unk_18AF37A6 *)M)->unk0x38 = *(__ps_t *)&sp48[14];
    __asm__ volatile("bdnz $" ::: "ctr");
    sp90 = fn_80003EB0(sp8, var_f25);
    R = (f32 *)sp90;
    sp94 = M2;
    sp48[0] = R[0] * M2[0] + R[1] * M2[4] + R[2] * M2[8] + R[3] * M2[12];
    sp48[1] = R[0] * M2[1] + R[1] * M2[5] + R[2] * M2[9] + R[3] * M2[13];
    sp48[2] = R[0] * M2[2] + R[1] * M2[6] + R[2] * M2[10] + R[3] * M2[14];
    sp48[3] = R[0] * M2[3] + R[1] * M2[7] + R[2] * M2[11] + R[3] * M2[15];
    sp48[4] = R[4] * M2[0] + R[5] * M2[4] + R[6] * M2[8] + R[7] * M2[12];
    sp48[5] = R[4] * M2[1] + R[5] * M2[5] + R[6] * M2[9] + R[7] * M2[13];
    sp48[6] = R[4] * M2[2] + R[5] * M2[6] + R[6] * M2[10] + R[7] * M2[14];
    sp48[7] = R[4] * M2[3] + R[5] * M2[7] + R[6] * M2[11] + R[7] * M2[15];
    sp48[8] = R[8] * M2[0] + R[9] * M2[4] + R[10] * M2[8] + R[11] * M2[12];
    sp48[9] = R[8] * M2[1] + R[9] * M2[5] + R[10] * M2[9] + R[11] * M2[13];
    sp48[10] = R[8] * M2[2] + R[9] * M2[6] + R[10] * M2[10] + R[11] * M2[14];
    sp48[11] = R[8] * M2[3] + R[9] * M2[7] + R[10] * M2[11] + R[11] * M2[15];
    sp48[12] = R[12] * M2[0] + R[13] * M2[4] + R[14] * M2[8] + R[15] * M2[12];
    sp48[13] = R[12] * M2[1] + R[13] * M2[5] + R[14] * M2[9] + R[15] * M2[13];
    sp48[14] = R[12] * M2[2] + R[13] * M2[6] + R[14] * M2[10] + R[15] * M2[14];
    sp48[15] = R[12] * M2[3] + R[13] * M2[7] + R[14] * M2[11] + R[15] * M2[15];
    ((Unk_18AF37A6 *)M2)->unk0x0 = *(__ps_t *)&sp48[0];
    ((Unk_18AF37A6 *)M2)->unk0x8 = *(__ps_t *)&sp48[2];
    ((Unk_18AF37A6 *)M2)->unk0x10 = *(__ps_t *)&sp48[4];
    ((Unk_18AF37A6 *)M2)->unk0x18 = *(__ps_t *)&sp48[6];
    ((Unk_18AF37A6 *)M2)->unk0x20 = *(__ps_t *)&sp48[8];
    ((Unk_18AF37A6 *)M2)->unk0x38 = *(__ps_t *)&sp48[14];
    ((Unk_18AF37A6 *)M2)->unk0x28 = *(__ps_t *)&sp48[10];
    ((Unk_18AF37A6 *)M2)->unk0x30 = *(__ps_t *)&sp48[12];
    flg = *((MgrE_t * *)&((Unk_1E29BE92 *)a0)->unk0x15BC);
    mgrc = *((MgrC_t * *)&((Unk_1E29BE92 *)a0)->unk0x15AC);
    objd = *((MgrD_t * *)&((Unk_1E29BE92 *)a0)->unk0x15B4);
    if ((flg->unk40 != 0) && (flg->unkAC == 0)) {
        f32 th;
        th = lbl_802AD760 - fn_8014030C((s32)QB_SPIN_COUNT_SLOP, 1, ((Unk_1E29BE92 *)a0)->unk0xC) + lbl_802AD764;
        if (!((fabs(mgrc->unk13F0)) < th)) {
            fn_8017F5B0(objd->unk1C, (s32)mgrc->unk13F0);
        }
    } else {
        fn_8017F5B0(objd->unk1C, (s32)mgrc->unk13F0);
    }
    ((Unk_1E29BE92 *)a0)->unk0x1594 = *(s32 *)&lbl_80303150 + Tmr_GetTime();
}
