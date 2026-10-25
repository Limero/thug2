// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CD1C-0x8009CD44 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009CD1C(s32 unused, CStruct *arg1) {
    CStruct *temp_r9;

    temp_r9 = arg1->unk0x10;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  temp_r9->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  temp_r9->unk0x10;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
}
