// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137E30-0x80137EE4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_80137CF8(void *, void *, s32, s32);
void *Mem_Alloc(u16);
void *memcpy(void *, void *, s32);
void Mem_Free2(s32);

typedef struct S137E30 {
    u8 unk0x0;
    u16 unk0x2;
    s32 unk0x4;
    char pad0x8[4];
    s32 unk0xC;
} S137E30;

S137E30 *fn_80137E30(S137E30 *arg0, u8 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s16 spA;
    u8 sp8;
    s32 r29;
    s32 r30;
    register s32 a4 __asm__("r6");

    r30 = arg3;
    sp8 = arg1;
    spA = arg2;
    a4 = arg4;
    arg0->unk0xC = 0;
    arg0->unk0x4 = 0;
    if (arg2 == 0) {
        goto end;
    }
    r29 = 0;
    if (a4 != 0) {
        r29 = fn_80137CF8(&sp8, &spA, r30, a4);
        if (r29 != 0) {
            r30 = r29;
        }
    }
    {
        void *buf = Mem_Alloc((u16) spA);
        arg0->unk0x4 = (s32) buf;
        memcpy(buf, (void *) r30, (u16) spA);
    }
    if (r29 != 0) {
        Mem_Free2(r29);
    }
end:
    arg0->unk0x0 = sp8;
    arg0->unk0x2 = (u16) spA;
    return arg0;
}
