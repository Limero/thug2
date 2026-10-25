// WIP DRAFT (non-matching) — hand-rebuilt from disasm (PS normalize + dual hash path)
// family=m2c range=0x801CC75C-0x801CCB68 size=1036B
// PARKED (hand-rebuild, DIFF ~16% under -mps-float): fully decoded; compiles.
// Two-way type switch (0x84 big / 0x85 small / else return 4); both paths:
// sp8/spC = *(lbl_802AD188)[0..1], memset(&sp10,0,0x18) via UNPROTOTYPED
// fn_8026AFB8 (want keeps crclr), entry=fn_8021D358(mgr,(u16)(s8)*(u8*)p),
// strncpy(&sp8, fn_8014510C(*(entry+0x18)), 0x20) [prototyped - no crclr],
// script-cmd block &sp28 via CStruct_ctor/AddString(QB_STRING0)/AddChecksum
// (flag ? D039432C : C304BD92)/fn_8009F010(obj,hash)/CStruct_delete(2).
// Big path adds: page-anchor r30=0x80300000 across the memset (mgr loaded
// AFTER via 0x5f9c(r30)); PS normalize block (sub/mul/merge00/madd/sum0/
// rsqrte/res over obj/t +88/+96 pairs vs lbl_802AD128) with STAGED scalar
// compare (union spill to sp60 + two lfs reads - expressible!); dist<lim arm
// stores consts AC/B0 to sp30..3F via named dp pointer; dist>=lim arm res-
// scales D1/D2; common tail muls0 x4 by splat(-cB4) writing sp40..58 +
// obj+184/192 + cBC@obj+BC; subfic/adde (field==0) guard; chained r3 into
// fn_801D17AC/fn_8020D1D4; fn_80219698(mgr) gate; lvl-delta branch with
// fn_80131154((s32)lbl_802AD190,0,0,0) [lis+addi symbol form].
// Remaining gap: FPR/saved-reg coloring cascade vs want (r28/r30/v31 webs),
// doc06-class PS spill idioms. Sweep needs -mps-float (see 6p-107).
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 20.5% ([3]rev->19.7% [5]rev->20.1% [13]rev->20.5%).
// UPDATED 2026-09-15 (e): 20.5% -> 20.8%. m2c invented a *symbol* call argument: it read the lis/addi pair that materialises a label address as an extra arg. tools/label_arg_scan.py automated the A/B; keep the best body.
#include "types.h"
extern s32 lbl_80305F9C;
extern s32 lbl_802AD188[2];
extern char lbl_802AD190[];
extern f32 lbl_802AD1A8;
extern f32 lbl_802AD1AC;
extern f32 lbl_802AD1B0;
extern f32 lbl_802AD1B4;
extern f32 lbl_802AD1B8;
extern f32 lbl_802AD1BC;
extern __ps_t lbl_802AD128;
#include "qb_constants.h"
#include "structs.h"

#define SP8   (*(s32 *)((char *)&fr))
#define W30   (((Unk_C9718640 *)&fr)->unk0x28)
#define W38   (((Unk_C9718640 *)&fr)->unk0x30)
#define W40   (*((__ps_t *)&((Unk_BAA0DADA *)&fr)->unk0x38))
#define W48   (((Unk_BAA0DADA *)&fr)->unk0x40)
#define W50   (((Unk_BAA0DADA *)&fr)->unk0x48)
#define W58   (((Unk_C9718640 *)&fr)->unk0x50)

extern s32 fn_8021D358(s32, s32);
extern s32 fn_8014510C(Unk_EE36B018 *);
extern s32 CStruct_ctor(s32);
extern void AddString(CStruct *, s32, void *);
extern void AddChecksum(CStruct *, s32, s32);
extern void fn_8009F010(s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern void *strncpy(void *, void *, s32);
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_801D17AC(s32, s32);
extern s32 fn_8020D1D4(s32, s32);
extern s32 fn_80219698(CStruct *);
extern s32 fn_801813F0(CStruct *);
extern void fn_80181300(Unk_F515CE8D *, s32);
extern void fn_80131154(CStruct *, Unk_9994C3F5 *, s32);

s32 fn_801CC75C(Unk_43D5C83F *arg0) {
    char fr[0x78];
    register s32 v27 __asm__("r27");
    register char *v28 __asm__("r28");
    register s32 v29 __asm__("r29");
    Unk_5ECFB536 *v30;
    CScript *v31;
    __ps_t A2;
    __ps_t B2;
    __ps_t RW;
    __ps_t D2;
    __ps_t A1;
    __ps_t B1;
    __ps_t SQ;
    __ps_t D1;
    __ps_t MG;
    __ps_t AC;
    __ps_t DT;
    __ps_t DP;
    __ps_t RF;
    __ps_t S30;
    __ps_t S70;
    __ps_t S38;
    __ps_t NN;
    __ps_t R1;
    __ps_t R2;
    f32 lim;
    f32 dv;
    f32 dv2;
    f32 dd;
    f32 *dp;
    f32 cAC;
    f32 cB0;
    f32 cB4;
    f32 cBC;
        s32 sp8v;
    s32 spCv;
    s32 mgr;
    Unk_386C684C *t;
    Unk_E06AC104 *r9v;
    s32 var_r11;
    s32 ret;

    v28 = (char *)arg0->unk0x0;
    v27 = 1;
    v29 = arg0->unk0x18;
    if (((Unk_10B7F399_2 *)v28)->unk0x1 == 0) {
        v27 = 0;
    }
    if ((s32)arg0->unk0x4 == 0x84) {
        goto big;
    }
    if ((s32)arg0->unk0x4 != 0x85) {
        return 4;
    }
    /* ---- small path (0x85) ---- */
    v31 = (void *)&fr;
    sp8v = lbl_802AD188[0];
    spCv = lbl_802AD188[1];
    *(s32 *)&fr = sp8v;
    ((Unk_C9718640 *)&fr)->unk0x4 = spCv;
    memset((char *)&fr + 8, 0, 0x18);
    mgr = lbl_80305F9C;
    t = fn_8021D358(mgr, (u16)(s8)*(u8 *)v28);
    if (t != NULL) {
        strncpy(&fr, fn_8014510C(t->unk0x18), 0x20);
    }
    v28 = v30;
    v30 = (char *)&fr + 0x20;
    CStruct_ctor((s32)v30);
    AddString((s32)v30, QB_STRING0, v31);
    if (v27 != 0) {
        AddChecksum((s32)v28, 0, QB_FIREBALL);
    } else {
        AddChecksum((s32)v28, 0, QB_PROJECTILE);
    }
    fn_8009F010(v29, QB_MADEOTHERSKATERBAIL, v28);
    CStruct_delete((s32)v28, 2);
    return 4;
    /* ---- big path (0x84) ---- */
big:
    v31 = (void *)&fr;
    sp8v = lbl_802AD188[0];
    spCv = lbl_802AD188[1];
    *(s32 *)&fr = sp8v;
    ((Unk_C9718640 *)&fr)->unk0x4 = spCv;
    v30 = (char *)0x80300000;
    memset((char *)&fr + 8, 0, 0x18);
    t = fn_8021D358(mgr, (u16)(s8)*(u8 *)v28);
    mgr = v30->unk0x5F9C;
    if ((v31 = (void *)t) == NULL) {
        goto tail;
    }
    t = v31->unk0x18;
    A2 = ((Unk_F67115E1 *)v29)->unk0x60;
    B2 = t->unk0x60;
    RW = lbl_802AD128;
    D2 = __builtin_ps_sub(A2, B2);
    A1 = ((Unk_F67115E1 *)v29)->unk0x58;
    B1 = t->unk0x58;
    SQ = __builtin_ps_mul(D2, D2);
    lim = lbl_802AD1A8;
    D1 = __builtin_ps_sub(A1, B1);
    MG = __builtin_ps_merge00(SQ, RW);
    W30 = D1;
    AC = __builtin_ps_madd(D1, MG, D1);
    W38 = D2;
    DT = __builtin_ps_sum0(AC, AC, AC);
    DT = __builtin_ps_rsqrte(DT);
    DT = __builtin_ps_res(DT);
    { SN_PS_type tmp60; tmp60.ps = DT; W38 = *( __ps_t *)&tmp60; }
    dv = *((f32 *)&((Unk_BAA0DADA *)&fr)->unk0x38);
    dv2 = ((Unk_BAA0DADA *)&fr)->unk0x38;
    if (dv2 < lim) {
        cAC = lbl_802AD1AC;
        cB0 = lbl_802AD1B0;
        dp = (f32 *)&W30;
        dp[0] = cAC;
        dp[3] = cAC;
        dp[1] = cB0;
        dp[2] = cAC;
    } else {
        dd = dv2;
        ((Unk_C9718640 *)&fr)->unk0x44 = dv2;
        *((f32 *)&((Unk_BAA0DADA *)&fr)->unk0x40) = dd;
        DP = ((Unk_BAA0DADA *)&fr)->unk0x40;
        RF = __builtin_ps_res(DP);
        W38 = __builtin_ps_muls0(D2, RF);
        W30 = __builtin_ps_muls0(D1, RF);
    }
    cB4 = lbl_802AD1B4;
    S30 = W30;
    *((f32 *)&((Unk_BAA0DADA *)&fr)->unk0x48) = cB4;
    S70 = ((Unk_BAA0DADA *)&fr)->unk0x48;
    S38 = W38;
    NN = __builtin_ps_neg(S70);
    R1 = __builtin_ps_muls0(S30, NN);
    cBC = lbl_802AD1BC;
    R2 = __builtin_ps_muls0(S38, NN);
    W50 = R1;
    W58 = R2;
    NN = __builtin_ps_neg(S70);
    R1 = __builtin_ps_muls0(R1, NN);
    R2 = __builtin_ps_muls0(R2, NN);
    W40 = R1;
    W48 = R2;
    ((Unk_F67115E1 *)v29)->unk0xB8 = R1;
    R2 = W48;
    ((Unk_F67115E1 *)v29)->unk0xC0 = R2;
    ((Unk_5F85C510 *)v29)->unk0xBC = cBC;
    r9v = *(s32 *)((char *)GetChecksum_3(v29, QB_SKATERPHYSICSCONTROL) + 0x38);
    var_r11 = 0;
    if (r9v->unk0x188 == 0) {
        var_r11 = r9v->unk0x20 == 0;
    }
    if (var_r11 != 0) {
        fn_801D17AC(GetChecksum_3(v29, QB_SKATERCOREPHYSICS), t);
    } else {
        fn_8020D1D4(GetChecksum_3(v29, QB_WALK), t);
    }
    strncpy(&fr, fn_8014510C(t), 0x20);
    if (fn_80219698(mgr) == 0) {
        v30 = (char *)((Unk_F67115E1 *)v29)->unk0x2A4 + 0x1C;
        if ((fn_801813F0((s32)v30) - ((Unk_10B7F399_2 *)v28)->unk0x4) < 0) {
            fn_80181300((s32)v30, 0);
            fn_80131154(0, 0, 0);
        } else {
            fn_80181300((s32)v30, fn_801813F0((s32)v30) - ((Unk_10B7F399_2 *)v28)->unk0x4);
        }
    }
tail:
    v28 = v30;
    v30 = (char *)&fr + 0x20;
    CStruct_ctor((s32)v30);
    AddString((s32)v30, QB_STRING0, (char *)&fr);
    if (v27 != 0) {
        AddChecksum((s32)v28, 0, QB_FIREBALL);
    } else {
        AddChecksum((s32)v28, 0, QB_PROJECTILE);
    }
    fn_8009F010(v29, QB_SKATERCOLLIDEBAIL, v28);
    CStruct_delete((s32)v28, 2);
    return 4;
}
