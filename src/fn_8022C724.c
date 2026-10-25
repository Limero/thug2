// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C724-0x8022C750 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802B04B4;

void fn_8022C724(void *arg0) {
    register void *o __asm__("r11");
    CStruct *temp_r9;
    f32 temp_f0;

    o = arg0;
    temp_f0 = lbl_802B04B4;
    temp_r9 = (char *)o + 0x10;
    *((f32 *)&((CStruct *)o)->unk0x10) = temp_f0;
    *((f32 *)&temp_r9->unk0x4) = temp_f0;
    *((f32 *)&temp_r9->unk0x8) = temp_f0;
    *((f32 *)&temp_r9->unk0xC) = temp_f0;
    ((CStruct *)o)->unk0x34 = 0;
}
