// WIP DRAFT — hand-rebuilt from disasm (groupB PS zone, 2026-08-25)
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 26.7123% -> 34.9315% `volatile` keyword(s) removed from the body
// PARKED 25.3% (-mps-float): near-complete rebuild (script chains, probes,
// PS math, fn_80005A90 2nd-probe half); residue is PS-zone allocator/
// scheduler class — see docs/parkings/06 + doc-15/32. Best body kept.
// family=hand range=0x80210D10-0x80210F58 size=584B
// INERT: not registered in splits.txt/configure.py — never compiled.
// FLAG: -mps-float -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_8010794C(Unk_C7387A53 *);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void fn_80005854(void *, void *);
extern void fn_80005A90(Unk_C1F9F519 *, Unk_C1F9F519 *);
extern void fn_8009F010(s32, s32, s32);
extern f32 lbl_802AF5C4;
extern f32 lbl_802AF5C8;
extern f32 lbl_802AF5CC;
extern char lbl_802AF450[];
typedef union { __ps_t ps; f32 f[2]; } P;
void fn_80210D10(Unk_B68EC6D0 *arg0) {
    struct fr_s {
        P a01;
        P a02;
        P b01;
        P b02;
        char pad1[0x68];
        P x90;
        P x98;
        P buf[2];
        s32 node;
        char pad2[0x14];
        P oC8;
        P oD0;
        P oD8;
        char padZ[8];
        f32 e8;
        char padW[4];
        P lenv;
        char tail[0x14];
    } fr;
    char *dp;
    char *bp;
    P t;
    f32 lim;
    f32 adj;
    f32 chk;
    void *res;
    if (arg0->unk0x1998 != 0) {
        return;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALKER_HEIGHT, (void *)&fr.e8, 1);
    lim = lbl_802AF5C4;
    chk = arg0->unk0x48;
    adj = fr.e8;
    if (chk < lim) {
        adj = adj - lbl_802AF5C8;
    }
    dp = (char *)&fr.a01;
    fn_8010794C(dp);
    fr.a01.ps = arg0->unk0x28;
    fr.b01.ps = arg0->unk0x28;
    fr.a01.f[1] = fr.a01.f[1] + lbl_802AF5CC;
    fr.a02.ps = arg0->unk0x30;
    fr.b01.f[1] = fr.b01.f[1] + adj;
    fr.b02.ps = arg0->unk0x30;
    res = (void *)fn_80107B20(dp, 1, 0);
    if ((s32)res == 0) {
        if (fr.node != 0) {
            CObject_RemoveRefLink((void *)fr.node, (void *)&fr.node);
        }
        fr.node = (s32)res;
        return;
    }
    ((Unk_F6393DBC *)arg0)->unk0x3C = arg0->unk0x48;
    {
        P u;
        t.ps = arg0->unk0x40;
        t.ps = __builtin_ps_mul(t.ps, *(__ps_t *)((char *)&fr.buf[1]));
        u.ps = arg0->unk0x38;
        t.ps = __builtin_ps_merge00(t.ps, *(__ps_t *)&lbl_802AF450);
        t.ps = __builtin_ps_madd(u.ps, u.ps, *(__ps_t *)((char *)&fr.buf[0]));
        t.ps = __builtin_ps_sum0(t.ps, t.ps, t.ps);
        fr.lenv.ps = t.ps;
    }
    if (!(fr.lenv.f[0] >= lim)) {
        bp = (char *)&fr.buf[0];
        fn_80005854((char *)arg0 + 0x38, bp);
    }
    bp = (char *)&fr.buf[0];
    t.ps = *(__ps_t *)&fr.b01;
    arg0->unk0x48 = ((Unk_F6393DBC *)arg0)->unk0x3C;
    ((Unk_F6393DBC *)arg0)->unk0x3C = lim;
    fr.oC8.ps = __builtin_ps_sub(*(__ps_t *)((char *)&fr.x90), t.ps);
    fr.oD0.ps = __builtin_ps_sub(*(__ps_t *)((char *)&fr.x98), *(__ps_t *)&fr.b02);
    fn_80005A90((char *)&fr.oC8, bp);
    t.ps = *(__ps_t *)&fr.b01;
    t.ps = __builtin_ps_add(arg0->unk0x28, *(__ps_t *)&fr.oC8);
    *(__ps_t *)&fr.b01 = t.ps;
    fr.oD8.ps = t.ps;
    *(__ps_t *)&fr.b02 = __builtin_ps_add(arg0->unk0x30, *(__ps_t *)&fr.oD0);
    fr.oD8.ps = __builtin_ps_add(arg0->unk0x30, *(__ps_t *)&fr.oD0);
    res = (void *)fn_80107B20(dp, 1, 0);
    if ((s32)res != 0) {
        t.ps = __builtin_ps_add(*(__ps_t *)((char *)&fr.x90), *(__ps_t *)((char *)&fr.buf[0]));
        arg0->unk0x28 = t.ps;
        t.ps = __builtin_ps_add(*(__ps_t *)((char *)&fr.x98), *(__ps_t *)((char *)&fr.buf[1]));
        fr.oD8.ps = t.ps;
        arg0->unk0x30 = t.ps;
    } else {
        arg0->unk0x28 = *(__ps_t *)&fr.b01;
        arg0->unk0x30 = *(__ps_t *)&fr.b02;
    }
    fn_8009F010(arg0->unk0xC, QB_HITCEILING, 0);
    if (fr.node != 0) {
        CObject_RemoveRefLink((void *)fr.node, (void *)&fr.node);
    }
    fr.node = 0;
}
