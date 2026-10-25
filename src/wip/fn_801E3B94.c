// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group E)
// PARKED: prologue EXACT after frame-template fix (ctx struct sized
// 0xD0 with spA4@+0x9C/spB0@+0xA8 members + r28 pin for &ct); remaining: Structure (verified vs want):
//   s32 fn(void *obj /*r29*/, void *arg1 /*r30*/):  r28 = &ctx(sp8)
//   if (*((*obj)->0x15BC + 0xA0) != 0) return 0;      // li r3,0 hoisted pre-load
//   fn_8010794C(&ctx);
//   delta = fn_8014030C(0x786B3272, 1, obj->0xC);     // f32-returning callee
//   val = *(f32*)(arg1+4);
//   // pair copies: ctx.a <- objC[0x58] pair, overwritten by objC[0x60] pair;
//   // tmp = old.f5C + delta stored back; ctx.c/d re-copy same objC pairs;
//   // max-clamp: if (val < objC->f5C) ctx.c.hi = val;
//   // min-clamp: if (val + delta > tmp) ctx.a.hi = val + delta;
//   if ((r31 = fn_80107B20(&ctx,1,0)) == 0) {         // or. r31,r3,r3
//       if (ctx.spB0) { CObject_RemoveRefLink(spB0,&spB0); spB0 = r31; }
//       return 0;
//   }
//   if (!(spA4 > *(f32*)&lbl_802AD7F0)) goto cleanup0;  // ble -> Ld1c
//   // body: ps_add sums of arg1 pairs + ctx fields into ctx.e/f (+delta on
//   // lanes 0xC/0x1C), copy sums to ctx.spC8/spD0, second fn_80107B20;
//   // if ret2 != 0 goto cleanup0 (stores literal 0);
//   // else: obj->0x58/0x60 pairs = sums; obj->f5C += *(f32*)&lbl_802AD7F4;
//   //       if (spB0) { dfc0(spB0,&spB0); spB0 = ret2; } return 1;
//   // cleanup0 shared tail: if (spB0) { dfc0(spB0,&spB0); spB0 = 0; } ret 0.
//   // NOTE the two cleanup blocks differ: Ld1c stores li r0,0, Ld3c/success
//   // reuse r31 (known zero) - single-variable 'res' source shape.
// Remaining walls: (a) the ps_add/ps_sub clamp web in the prologue block -
//   exact C staging not recovered (want interleaves reloads from ctx.a with
//   reg-resident sums); (b) vsel-class misdecodes resolved as ps_add but
//   scheduling order still off. Retry hints: treat ctx as ONE frame-template
//   struct incl. spA4/spB0 members; stage sums through named __ps_t temps
//   per §7b recipes; check fn_80005A90-style helper for the clamp idiom.
// family=m2c range=0x801E3B94-0x801E3D70 size=476B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 5.1% ([0]rev->4.4% [1]rev->5.1%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern void fn_8010794C(Unk_C7387A53 *);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern f32 lbl_802AD7F0;
extern f32 lbl_802AD7F4;

s32 fn_801E3B94(Unk_71062261 *arg0, CStruct *arg1) {
s32 fs_t;
    struct wctx {
        union { __ps_t p; f32 v[2]; } a;
        union { __ps_t p; f32 v[2]; } b;
        union { __ps_t p; f32 v[2]; } c;
        union { __ps_t p; f32 v[2]; } d;
        union { __ps_t p; f32 v[2]; } e;
        union { __ps_t p; f32 v[2]; } f;
        union { __ps_t p; f32 v[2]; } g;
        union { __ps_t p; f32 v[2]; } h;
        union { __ps_t p; f32 v[2]; } i;
        union { __ps_t p; f32 v[2]; } j;
        char _p[0x14];
        f32 spA4;
        char _p2[8];
        s32 spB0;
        char _tail[0x5C];
    } ct;
    register s32 res __asm__("r31");
    register struct wctx *cp __asm__("r28");
    Unk_B358EECF *objC;
    f32 val;
    f32 delta;

    if (*(s32 *)(arg0->unk0x15BC + 0xA0) != 0) {
        return 0;
    }
    cp = &ct;
    fn_8010794C(cp);
    ct.d.p = objC->unk0x60;
    ct.c.p = objC->unk0x58;
    ct.a.v[1] = val + delta;
    ct.a.p = objC->unk0x60;
    val = ct.a.v[1];
    ct.a.p = objC->unk0x58;
    objC = *((void * *)&arg0->unk0xC);
    delta = fs_t;
    val = *((f32 *)&arg1->unk0x4);
    fs_t = fn_8014030C(QB_PHYSICS_AIR_SNAP_UP, 1, (s32)*((void * *)&arg0->unk0xC));
    if (val < ((Unk_82779A3F *)objC)->unk0x5C) {
        ct.c.v[1] = val;
    }
    if (val + delta > ct.a.v[1]) {
        ct.a.v[1] = val + delta;
    }
    res = fn_80107B20(cp, 1, 0);
    if (res != 0) {
        if (ct.spA4 > lbl_802AD7F0) {
            res = fn_80107B20(cp, 1, 0);
            ct.h.p = ct.f.p;
            ct.g.p = ct.e.p;
            ct.f.v[0] = ct.f.v[0] + delta;
            ct.e.v[1] = ct.e.v[1] + delta;
            ct.f.v[1] = *((f32 *)&arg1->unk0xC) + ct.h.v[1];
            ct.f.v[0] = *((f32 *)&arg1->unk0x8) + ct.h.v[0];
            ct.e.v[1] = *((f32 *)&arg1->unk0x4) + ct.g.v[1];
            ct.e.v[0] = *((f32 *)&arg1->unk0x0) + ct.g.v[0];
            if (res == 0) {
                objC = *((void * *)&arg0->unk0xC);
                objC->unk0x58 = ct.g.p;
                objC->unk0x60 = ct.h.p;
                ((Unk_82779A3F *)objC)->unk0x5C = ((Unk_82779A3F *)objC)->unk0x5C + lbl_802AD7F4;
                if (ct.spB0 != 0) {
                    CObject_RemoveRefLink(ct.spB0, &ct.spB0);
                    ct.spB0 = res;
                }
                return 1;
            }
        }
        if (ct.spB0 != 0) {
            CObject_RemoveRefLink(ct.spB0, &ct.spB0);
            ct.spB0 = 0;
        }
        return 0;
    }
    if (ct.spB0 != 0) {
        CObject_RemoveRefLink(ct.spB0, &ct.spB0);
        ct.spB0 = res;
    }
    return 0;
}
