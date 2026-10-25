// WIP DRAFT (non-matching) — PARKED 2026-08-25
// Reached ~5% (-mps-float). Bounding-box accumulator: min/max init from
// rodata 0x802B1178/117C/1180, loop over *(o+0x30) entries calling
// fn_80241E38(o,i)->node then CHAINED fn_80240C80(*(node+8))->obj, then an
// mtlr/blrl VCALL *(void**)(obj+0xC)(sp8buf, obj+*(s16*)(obj+8)), then PSQ
// pair copy of obj+24/28 into sp+0x18/0x1c and per-axis min/max updates vs
// arg2(min)/arg1(max) using sp8[2]/sp8[1]*k (k=rodata 0x802B1184, reloaded
// EVERY iteration). Remaining walls: (1) want saves ONLY f31; any named-temp
// form for the init constants or updates promotes to f30 (frame 0x58 vs
// 0x50); (2) want's init store order [8],[0],[4],[c] is rotate-right of
// source order but our casted-pointer stores emit un-rotated program order,
// and staging via named regs makes it worse (456B); (3) psq_l/psq_st pair
// shapes need exact slot placement. Needs a dedicated PS/allocator pass.
// Arity truths: fn_80242734(o,min,max) 3-ARG (m2c had it as 2-arg + hidden);
// fn_80241E38 chained into fn_80240C80; vcall target reads s16 offset at
// obj+8 and fn-ptr at obj+0xC.
// family=m2c range=0x80242734-0x802428BC size=392B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// NEEDS: -mps-float (psq_l/psq_st pair copies)
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.9% ([0]rev->2.9%).
#include "types.h"
#include "structs.h"
// FLAG: -mps-float -Os
extern f32 lbl_802B1178;
extern f32 lbl_802B117C;
extern f32 lbl_802B1180;
extern f32 lbl_802B1184;
s32 fn_80241E38(void *, s32);
s32 fn_80240C80(s32);
void fn_80242734(Unk_C7387A53 *arg0, void *arg1, void *arg2) {
    f32 b[3];
    union {
        __ps_t ps;
        f32 f[2];
    } pxy;
    f32 pos_z;
    f32 k;
    f32 v;
    s32 i;
    s32 n;
    Unk_24B3C57B *obj;
    s32 off;

    ((f32 *)arg2)[0] = lbl_802B1178;
    ((f32 *)arg2)[1] = lbl_802B1178;
    ((f32 *)arg2)[2] = lbl_802B1178;
    ((f32 *)arg2)[3] = lbl_802B117C;
    ((f32 *)arg1)[2] = lbl_802B1180;
    ((f32 *)arg1)[3] = lbl_802B117C;
    ((f32 *)arg1)[0] = lbl_802B1180;
    ((f32 *)arg1)[1] = lbl_802B1180;
    for (i = 0; (u32)i < *((u32 *)&arg0->unk0x30); i++) {
        off = obj->unk0x8;
        obj = fn_80240C80(((Unk_1D62F22E_2 *)n)->unk0x8);
        n = fn_80241E38(arg0, i);
        k = lbl_802B1184;
        obj->unk0xC(
            (void *)b, (char *)obj + off);
        pxy.ps = obj->unk0x18;
        v = b[2];
        if (!((pxy.f[0]) - v * k >= ((f32 *)arg2)[0])) {
            ((f32 *)arg2)[0] = (pxy.f[0]) - v * k;
        }
        if (((f32 *)arg1)[0] <= pxy.f[0] + v * k) {
            ((f32 *)arg1)[0] = pxy.f[0] + v * k;
        }
        if (!((pos_z) - v * k >= ((f32 *)arg2)[1])) {
            ((f32 *)arg2)[1] = (pos_z) - v * k;
        }
        if (((f32 *)arg1)[1] <= pxy.f[1] + v * k) {
            ((f32 *)arg1)[1] = pxy.f[1] + v * k;
        }
        if (!(pxy.f[1] >= ((f32 *)arg2)[1])) {
            ((f32 *)arg2)[1] = pxy.f[1];
        }
        if (((f32 *)arg1)[1] <= pxy.f[1] + b[1]) {
            ((f32 *)arg1)[1] = pxy.f[1] + b[1];
        }
    }
}
