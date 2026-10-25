// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018748-0x800187BC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
// dequeue @ 0x80018748
void *dequeue(CStruct *arg0, void *arg1) {
    u16 temp_r8;
    s32 v0;
    s32 v4;
    s32 v8;
    temp_r8 = *(u16 *)((char *)arg1 + 0x3E);
    if ((s32) temp_r8 == (s32) *(u16 *)((char *)arg1 + 0x3C)) {
        *(u16 *)((char *)arg1 + 0x3C) = 5;
    } else {
        *(s16 *)((char *)arg1 + 0x3E) = (s16) ((temp_r8 + 1) % 5);
    }
    v0 = *(s32 *)((char *)arg1 + temp_r8 * 0xC);
    v4 = *(s32 *)((char *)arg1 + temp_r8 * 0xC + 4);
    v8 = *(s32 *)((char *)arg1 + temp_r8 * 0xC + 8);
    arg0->unk0x0 = v0;
    arg0->unk0x4 = v4;
    arg0->unk0x8 = v8;
    return arg0;
}