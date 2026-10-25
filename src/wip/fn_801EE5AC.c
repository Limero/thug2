// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group E)
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 16.2338% -> 16.8831%
//   the `c1` pin was retargeted fr31 -> fr29 (nothing else touched).  New axis:
//   fr-pin REMOVAL had been swept, retargeting had not.  AGENTS-recipes §6hk.
// PARKED: ~40% - full rebuild done (semantics + all PS ops decoded:
// ps_add/ps_sub pair math vs a 4-float const vec; two helper calls
// fn_80107A8C/AA0(&ctx,&v2); guard chain 80107B20/801080D4/80108104; node
// free/refill block with CObject_RemoveRefLink(*node,node) val+ptr idiom and chained
// fn_80108F94(Mem_Alloc2(0xB8), hand); hash-dispatch tail with 4-way float
// ==-chain materialized via mfcr/rlwinm; final cleanup if(fr.spB0)).
// Frame template EXACT at 0x118 ({ctx[0xA8],spB0,pad,v2[2],v4[4],tail[16]}).
// Remaining walls: (a) arg0 homes r29 vs want r31 - saved-reg assignment;
// (b) want r30=&v4 / r29=&v2 created EARLY and used r30-relative for stfs,
// my p4/p2 named-pointer webs get constant-folded back to r1 displacements
// ("+r" barrier had no effect); (c) c1/c2 fr31/fr30 pins hold but store
// forms differ. Retry hints: opaque &fr via asm-wedged struct pointer
// (§6l-76 "=r" wedge), investigate whether v4 was a separate local array
// declared BEFORE ctx in source.
// family=m2c range=0x801EE5AC-0x801EE814 size=616B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 16.2% ([4]rev->14.9% [3]rev->16.2%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_800EB8F8(s32 *, CStruct *, s32 *);
extern void fn_8010794C(Unk_C7387A53 *);
extern void fn_80107A8C(void *, void *);
extern void fn_80107AA0(void *, void *);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern s32 fn_801080D4(Unk_0352A96C *);
extern void *fn_80108104(Unk_C7387A53 *);
extern void *fn_80108F94(Unk_DF3972E8 *, CStruct *);
extern void fn_801D1458(s32);
extern void fn_8009F010(s32, s32, s32);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void Mem_Free(void *);
extern s32 Mem_Alloc2(s32);
extern s32 Tmr_GetTime();
extern f32 lbl_802ADB0C;
extern f32 lbl_802ADB10;
extern f32 lbl_802ADB14;
extern s32 lbl_80303150;

void fn_801EE5AC(Unk_C7387A53 *arg0) {
    struct ctxfr {
        char _c[0xA8];
        s32 spB0;
        char _p[0x14];
        __ps_t v2[2];
        union { __ps_t p; f32 v[4]; } v4;
        char _tail[0x10];
    } fr;
    f32 *p4;
    void *p2;
    register f32 c1 __asm__("fr29");
    register f32 c2 __asm__("fr30");
    Unk_A0AD78F8 *objC;
    Unk_35788951 *obj30;
    s32 *node;
    void *hand;
    s32 eq;

    if (fn_800EB8F8(*((void * *)&arg0->unk0x30), (void *)((char *)*((void * *)&arg0->unk0xC) + 0x58), (void *)((char *)*((void * *)&arg0->unk0x24) + 0xA0)) != 0) {
        fn_8010794C(&fr);
        p4 = &fr.v4.v[0];
        c1 = lbl_802ADB0C;
        p2 = &fr.v2[0];
        c2 = lbl_802ADB10;
        fr.v4.v[0] = c1;
        objC = *((void * *)&arg0->unk0xC);
        fr.v4.v[1] = c2;
        fr.v4.v[2] = c1;
        fr.v4.v[3] = c1;
        fr.v2[0] = __builtin_ps_add(objC->unk0x58, fr.v4.p);
        fr.v2[1] = __builtin_ps_add(objC->unk0x60, *(__ps_t *)((char *)&fr.v4 + 8));
        fn_80107A8C(&fr, &fr.v2[0]);
        fr.v4.v[0] = c1;
        fr.v4.v[3] = c1;
        fr.v4.v[1] = c2;
        fr.v4.v[2] = c1;
        objC = *((void * *)&arg0->unk0xC);
        fr.v2[0] = __builtin_ps_sub(objC->unk0x58, fr.v4.p);
        fr.v2[1] = __builtin_ps_sub(objC->unk0x60, *(__ps_t *)((char *)&fr.v4 + 8));
        fn_80107AA0(&fr, &fr.v2[0]);
        if ((fn_80107B20(&fr, 1, 0) != 0) && (fn_801080D4(&fr) != 0)) {
            node = obj30->unk0x1C;
            obj30 = *((void * *)&arg0->unk0x30);
            hand = fn_80108104(&fr);
            if (node != NULL) {
                obj30->unk0x70 = *node;
                if (*node != 0) {
                    CObject_RemoveRefLink(*node, node);
                    *node = 0;
                }
                Mem_Free(node);
                obj30->unk0x74 = lbl_80303150 + Tmr_GetTime();
                obj30->unk0x1C = node;
                node = NULL;
            }
            obj30->unk0x1C = fn_80108F94(Mem_Alloc2(0xB8), (s32)hand);
        }
        objC = *((void * *)&arg0->unk0x24);
        if (*(s32 *)(objC->unk0x15BC + 0x1C) == 4) {
            fn_801D1458(1);
            fn_8009F010(*((void * *)&arg0->unk0xC), QB_OFFRAIL, 0);
        } else {
            obj30 = *((void * *)&arg0->unk0xC);
            eq = (obj30->unk0x58 == objC->unk0xA0)
              && (obj30->unk0x5C == objC->unk0xA4)
              && (obj30->unk0x60 == objC->unk0xA8)
              && (obj30->unk0x64 == objC->unk0xAC);
            if (eq != 0) {
                obj30->unk0xB8 = c1;
                obj30->unk0xC4 = lbl_802ADB14;
                obj30->unk0xC0 = c1;
                obj30->unk0xBC = c1;
            }
        }
        if (fr.spB0 != 0) {
            CObject_RemoveRefLink(fr.spB0, &fr.spB0);
            fr.spB0 = 0;
        }
    }
}
