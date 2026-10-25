// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801376A4-0x80137724 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029F1A8[];
void fn_801376A4(s32 arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r11;
    Unk_C8FEE62D *temp_r9;

    temp_r9 = arg0 + 0x1C;
    temp_r9->unk0x14 = (s32)lbl_8029F1A8;
    temp_r11 = arg0 + 4;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  temp_r9->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  temp_r9->unk0x10;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r11->unk0x14 = (s32)lbl_8029F1A8;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0x10) + 0xC) =  temp_r11->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0xC) + 0x10) =  temp_r11->unk0x10;
    temp_r11->unk0xC = temp_r11;
    temp_r11->unk0x10 = temp_r11;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
