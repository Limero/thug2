// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3968-0x800A398C (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800A3968(s32 arg0, s32 arg1) {
    Unk_C7387A53 *temp_r3;
    CStruct *temp_r4;

    temp_r3 = arg0 + 0x30;
    temp_r4 = arg1 + 0x2C;
    temp_r4->unk0x10 = temp_r3;
    temp_r4->unk0xC = (void *) temp_r3->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r3) + 0xC) + 0x10) = temp_r4;
    temp_r3->unk0xC = temp_r4;
}
