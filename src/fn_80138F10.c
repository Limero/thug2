// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80138F10-0x80138F84 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
void memset(s32, s32, s32);
bool fn_80138F10(Unk_C1D369D9 *arg0, s32 arg1) {
    memset((char *)arg0 + 0x2308, 0, 8);
    arg0->unk0x2309 = 2;
    arg0->unk0x230A = 0;
    arg0->unk0x2308 = 8;
    arg0->unk0x230C = arg1;
    asm volatile ("" ::: "memory");
    if (arg1 == 0) {
        arg0->unk0x182C = arg1;
    } else {
        arg0->unk0x182C = 1;
    }
    return true;
}
