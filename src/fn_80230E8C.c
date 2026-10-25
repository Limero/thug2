// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230E8C-0x80230F18 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303148;
extern s32 lbl_8030191C;
s32 fn_8000A578(s32, s32);
void fn_80230E8C(s32 arg0) {
    s32 o = arg0;
    s32 temp_r27;
    Unk_C7387A53 *temp_r28;
    CScript *temp_r29;
    s32 temp_r30;
    s32 temp_idx;
    char *temp_b8;
    s32 temp_k;

    temp_r28 = o;
    temp_r27 = lbl_80303148;
    fn_8000A578(temp_r27 + 8, temp_r28->unk0x38);
    temp_r29 = temp_r28->unk0x40;
    temp_r30 = lbl_8030191C;
    fn_8000A578((temp_r29->unk0x24 * 0x94) + temp_r30 + 0xC, temp_r29);
    temp_idx = temp_r29->unk0x24;
    temp_b8 = (char *)temp_r30 + 8;
    temp_k = temp_idx * 0x94;
    temp_r29->unk0x1C = (char *)(temp_k + (s32)temp_r30) + 0x58;
    temp_r29->unk0x20 = *(s32 *)(temp_b8 + temp_k);
    fn_8000A578(temp_r27 + 0x54, temp_r28->unk0x3C);
}
