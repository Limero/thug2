// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A679C-0x801A6820 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_801A6788(void * arg0);
bool fn_801A679C(CStruct *arg0, s32 *arg1, s32 arg2) {
    CStruct *temp_r11;

    temp_r11 = fn_801A6788(Mem_Alloc2(0xC));
    temp_r11->unk0x4 = arg2;
    temp_r11->unk0x0 = (s32) *arg1;
    if (arg0->unk0x8 == 0) {
        arg0->unk0x8 = temp_r11;
    } else {
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x8) = temp_r11;
    }
    arg0->unk0x10 = 0;
    arg0->unk0xC = temp_r11;
    arg0->unk0x4 = (s32) (arg0->unk0x4 + 1);
    return true;
}
