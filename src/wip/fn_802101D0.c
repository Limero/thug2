// WIP DRAFT — hand-rebuilt from disasm (groupB PS zone, 2026-08-25)
// PARKED (-mps-float): full structural rebuild done; scheduler/allocator
// residue remains. Decode summary (154 insns):
//   prologue: r30=&sp8 desc, r31=arg0; fn_8010794C(desc)
//   a01=pair(arg0+0x28); hash call GetStructure(0x6775E538,0);
//   a02=pair(arg0+0x30); GetFloat(chained_ret,0x9EA1974A,&spD8,1)
//   spC += spD8; b02/b01 = volatile copies of a01 (psq pair copies,
//     stored rotated: b02 first); b01.y += out(spDC via 2nd chained call)
//   fn_80107B20(desc,0,0)==0 -> shared tail node cleanup (CObject_RemoveRefLink +
//     li 0 store). Nonzero: 3rd hash call -> &spE0 (f29).
//   PS block: spE8/spF0 = TWO volatile copies of f29 (prevents CSE ->
//     want recomputes each product twice!): psq_l pairs + ps_mr moves,
//     xC8/xD0 = ps_muls0(pair(arg0+0x50/+0x58), scB); then
//     a01/a02 = ps_sub(a01/a02, ps_muls0(same inputs, scA)).
//   diff = *(f32*)(r1+0x94) - spC  [0x94 written by fn_80107B20 desc]
//   2nd 80107B20 != 0 -> tail. Else scalar ballistic block:
//   ret=f1(fn_802156FC(arg0)) f32-ret; rad=*(arg0+0x48);
//   disc = rad*rad - 2*ret*diff (fmuls/fmsubs); if disc > lbl_802AF5A0:
//   bl fn_8026FD2C() [chained r3]; k=(rad-disc)/ret [fdiv+frsp];
//   -spE0/k broadcast via stfs+psq_l+ps_mr; ps_muls0 pairs -> arg0->1980/
//   1988 (+ copies to 0xC8/0xD0); arg0->1990 = spE0+diff;
//   arg0->1978 = 2*rad/ret - k.
// Remaining walls (all documented classes): got frame 0x168 vs want 0x148
// (function-scope __ps_t/P locals reserve +8 slots each, §6ae-173 —
// narrowing scopes did not remove them); got saves f27-f31 vs want
// f28-f31 (one extra live FP web — suspected double-promotion in the
// /ret chain; untried: explicit (double) dance per §6j-1); remaining
// cascade shifts everything by +8..0x20 so pct metric reads low (front
// stream matches 1:1 modulo displacement).
// family=hand range=0x802101D0-0x80210438 size=616B
// INERT: not registered in splits.txt/configure.py — never compiled.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.5% ([0]rev->4.5%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_8010794C(Unk_C7387A53 *);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern f32 fn_802156FC(s32);
extern s32 fn_8026FD2C();
extern f32 lbl_802AF5A0;

typedef union { __ps_t ps; f32 f[2]; } P;

void fn_802101D0(Unk_E8E8E93C *arg0) {
    struct fr_s {
        volatile P a01;
        volatile P a02;
        volatile P b01;
        volatile P b02;
        char pad1[0x6C];
        f32 x94;
        char padX[0x18];
        s32 node;
        char pad2[0x14];
        P xC8;
        P xD0;
        volatile f32 d8;
        volatile f32 dc;
        volatile f32 e0;
        volatile f32 e8;
        volatile f32 f0;
        f32 f8;
        char padT[0x1C];
    } fr;
    char *dp;
    f32 diff;
    f32 lim;
    P t;
    __ps_t scA;
    __ps_t scB;

    dp = (char *)&fr.a01;
    fn_8010794C(dp);
    fr.a01.ps = arg0->unk0x28;
    fr.a02.ps = arg0->unk0x30;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALKER_HEIGHT, (void *)&fr.d8, 1);
    fr.a01.f[1] = fr.a01.f[1] + fr.d8;
    fr.b02.ps = *(__ps_t volatile *)&fr.a01;
    fr.b01.ps = *(__ps_t volatile *)&fr.a01;
    fr.b01.f[1] = fr.b01.f[1] + fr.dc;
    if ((s32)fn_80107B20(dp, 0, 0) == 0) {
        goto tail;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_JUMP_OBSTRUCTION_CHECK_BACK, (void *)&fr.e0, 1);
    fr.e8 = fr.e0;
    fr.f0 = fr.e0;
    t.ps = arg0->unk0x58;
    scB = *(__ps_t volatile *)&fr.f0;
    fr.xC8.ps = __builtin_ps_muls0(t.ps, scB);
    t.ps = arg0->unk0x50;
    fr.xD0.ps = __builtin_ps_muls0(t.ps, scB);
    scA = *(__ps_t volatile *)&fr.e8;
    fr.a01.ps = __builtin_ps_sub(fr.a01.ps, __builtin_ps_muls0(arg0->unk0x50, scA));
    fr.a02.ps = __builtin_ps_sub(fr.a02.ps, __builtin_ps_muls0(arg0->unk0x58, scA));
    diff = fr.x94 - fr.a01.f[1];
    if ((s32)fn_80107B20(dp, 0, 0) != 0) {
        goto tail;
    }
    {
        f32 ret = fn_802156FC(arg0);
        f32 rad = arg0->unk0x48;
        f32 disc;
        lim = lbl_802AF5A0;
        disc = rad * rad - (ret + ret) * diff;
        fn_8026FD2C();
        if (!(disc <= lim)) {
            f32 k;
            P pr;
            k = rad - disc;
            k = k / ret;
            *(f32 volatile *)&fr.f8 = -(fr.e0) / k;
            pr.ps = *(__ps_t volatile *)&fr.f8;
            arg0->unk0x1978 = (rad + rad) / ret - k;
            arg0->unk0x1990 = fr.e0 + diff;
            arg0->unk0x1988 = __builtin_ps_muls0(arg0->unk0x58, pr.ps);
            arg0->unk0x1980 = __builtin_ps_muls0(arg0->unk0x50, pr.ps);
        }
    }
tail:
    if (fr.node != 0) {
        CObject_RemoveRefLink((void *)fr.node, (void *)&fr.node);
    }
    fr.node = 0;
}
