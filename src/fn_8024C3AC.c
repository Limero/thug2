// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C3AC-0x8024C474 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA320;
// PARKED 80%: 9 residual scheduler diffs: want interleaves the four sth stores AFTER the zero-store run while every source order/flag/pin combo makes ngccc hoist them before it; wq->r10/hq->r8 pins + (wq&0xFFF0)*(u16)hq asymmetry reproduced
void fn_8024C5A0(s32, s32);
void fn_8024C4D8(void *, s32, s32);
void *fn_8024C3AC(Unk_5B449B03 *arg0, s16 arg1, s16 arg2, s32 arg3) {
    register s32 wqreg __asm__("r10");
    register s32 hqreg __asm__("r8");
    Unk_5B449B03 *p;
    s32 total;
    s32 sz;
    s32 t;
    wqreg = ((arg1 + 0xF) & ~0xF) + 0x40;
    hqreg = ((arg2 + 0xF) & ~0xF) + 0x40;
    total = (wqreg & 0xFFF0) * (u16)hqreg;
    p = arg0;
    p->unk0x14 = (s32)p;
    p->unk0x20 = 0;
    p->unk0x24 = 0;
    t = total >> 1;
    p->unk0x28 = 0;
    t = t + 0x120;
    p->unk0x2C = 0;
    sz = total + t;
    __asm__("" : "+r"(wqreg), "+r"(hqreg), "+r"(arg1), "+r"(arg2) : "r"(sz));
    *((s16 *)&p->unk0x0) = arg1;
    *((s16 *)&p->unk0x2) = arg2;
    *((s16 *)&p->unk0x4) = wqreg;
    *((s16 *)&p->unk0x6) = hqreg;
    if (arg3 != 0) {
        fn_8024C5A0((s32)p, sz);
    } else {
        s32 got = ((s32 (*)(s32)) *(s32 *)&lbl_803CA320)(sz);
        p->unk0x2C = got;
        fn_8024C4D8(p, got, 0);
    }
    p->unk0x18 = 0;
    p->unk0x1C = 0;
    return p;
}
