// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010A68-0x80010AC0 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802906B8[];
void fn_80010A68(s32 arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    temp_r9 = arg0 + 4;
    temp_r9->unk0x14 = (s32)lbl_802906B8;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  temp_r9->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  temp_r9->unk0x10;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
