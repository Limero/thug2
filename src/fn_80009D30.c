// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009D30-0x80009D88 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8028FF28[];
void fn_80009D30(void *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    temp_r9 = (Unk_C8FEE62D *)(arg0 + 8);
    temp_r9->unk0x14 = (int)lbl_8028FF28;
    *(s32 *)(*(s32 *)((char *)temp_r9 + 0x10) + 0xC) = temp_r9->unk0xC;
    *(s32 *)(*(s32 *)((char *)temp_r9 + 0xC) + 0x10) = temp_r9->unk0x10;
    temp_r9->unk0xC = (int)temp_r9;
    temp_r9->unk0x10 = (int)temp_r9;
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
