// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801349B4-0x80134A30 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern s32 fn_80134984(s32);

void *fn_801349B4(Unk_C8FEE62D *arg0, s32 arg1) {
    u32 count;
    s32 size;
    s32 *temp_r3;
    s32 walk;

    size = 1 << arg1;
    *(s32 *)arg0 = arg1;
    count = size - 1;
    temp_r3 = (s32 *)Mem_Alloc(size * 0xC);
    walk = (s32)temp_r3;
    if (size != 0) {
        do {
            fn_80134984(walk);
            walk += 0xC;
        } while (count-- != 0u);
    }
    arg0->unk0x4 = (s32)temp_r3;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
