// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802415C4-0x80241638 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
s32 fn_802415C4(s32 arg0, Unk_C8FEE62D *arg1) {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    register s32 ret __asm__("r3");
    Unk_42076946 *p3;
    if (arg1->unk0x28 & 1) {
        char *p = *((char * *)&arg1->unk0x14);
        sp8 = ((Unk_0737AFB8 *)p)->unk0x18;
        ((Unk_E266FB50 *)&sp8)->unk0x8 = *((f32 *)&((Unk_42076946 *)p)->unk0x10);
    } else {
        char *p = *((char * *)&arg1->unk0x14);
        sp8 = *((f32 *)&((Unk_42076946 *)p)->unk0x10);
        ((Unk_E266FB50 *)&sp8)->unk0x8 = ((Unk_0737AFB8 *)p)->unk0x18;
    }
    p3 = *((char * *)&arg1->unk0x14);
    __asm__("mr %0,%1" : "=r"(ret) : "r"(arg0));
    spC = p3->unk0x14;
    __asm__("" : : "m"(spC), "m"(sp14));
    *(__ps_t *)((char *)arg0) = *(__ps_t *)((char *)&sp8);
    ((__ps_t *)((char *)arg0))[1] = ((__ps_t *)((char *)&sp8))[1];
    return ret;
}
