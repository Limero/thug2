// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801831A8-0x8018322C (132B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_80183194(void);
bool fn_801831A8(CStruct *arg0, s32 *arg1, s32 arg2) {
    CStruct *temp_r3;

    Mem_Alloc2(0xC);
    temp_r3 = fn_80183194();
    temp_r3->unk0x4 = arg2;
    temp_r3->unk0x0 = *(s32 *)arg1;
    if (arg0->unk0x8 == NULL) {
        arg0->unk0x8 = temp_r3;
    } else {
        *(s32 *)(arg0->unk0xC + (s32)0x8) = temp_r3;
    }
    arg0->unk0x10 = 0;
    arg0->unk0xC = temp_r3;
    arg0->unk0x4 = arg0->unk0x4 + 1;
    return true;
}
