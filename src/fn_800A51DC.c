// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A51DC-0x800A529C (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc2(s32);
void fn_800A4BB4(void *);
void *fn_800A6B7C(void *, s32);
void *fn_800A6C3C(void *, s32);
extern char lbl_802980B0[];
void *fn_800A51DC(Unk_AD65BA9A *arg0) {
    s32 *hi;
    s32 *hi2;
    s32 *p;
    s32 ctr;

    hi = (s32 *)((char *)arg0 + 0x10000);
    *(s32 *)((char *)hi - 0x4de4) = (s32)lbl_802980B0;
    fn_800A4BB4((char *)arg0 + 0x20);
    arg0->unk0x8 = (s32)fn_800A6B7C(Mem_Alloc2(0x18), 8);
    arg0->unk0xC = (s32)fn_800A6B7C(Mem_Alloc2(0x18), 4);
    arg0->unk0x10 = (s32)fn_800A6C3C(Mem_Alloc2(0x18), 8);
    ctr = 0x28;
    arg0->unk0x4 = 0;
    arg0->unk0x14 = 0;
    __asm__("mr %0,%1" : "=r"(hi2) : "r"(hi));
    arg0->unk0x18 = 0;
    arg0->unk0x1C = 0;
    *(s32 *)((char *)hi - 0x4fcc) = 0;
    p = (s32 *)((char *)hi2 - 0x4df0);
    do {
        *p = 0;
        p = (s32 *)((char *)p - 0xC);
        ctr -= 1;
    } while (ctr != 0);
    *(s32 *)((char *)hi2 - 0x4de8) = 0;
    return arg0;
}
