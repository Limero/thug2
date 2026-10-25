// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013A93C-0x8013A9C0 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8013B6F4(void *, void *);
extern char lbl_8029F3F8[];
#include "structs.h"
s32 fn_8013F74C(s32);
bool fn_8013A93C(CStruct *arg0) {
    s32 *temp_r29;
    s32 temp_r11;
    u32 temp_r9;
    u32 var_r4;
    void *temp_r30;
    s32 temp_ra;

    temp_r30 = arg0->unk0x10;
    temp_r29 = arg0->unk0x0;
    if (fn_8013F74C(temp_r30) == 0) {
        temp_ra = **((s32 * *)&arg0->unk0xC);
        temp_r11 = *((s32 *)temp_r29);
        if (temp_r11 == (s32) *((s32 *)&((Unk_2DBBFAC5 *)temp_r30)->unk0x20E4)) {
            *((s32 *)&((Unk_2DBBFAC5 *)temp_r30)->unk0x20E8) = temp_r11;
            temp_r9 = *(volatile u32 *)lbl_8029F3F8;
            var_r4 = (u32)temp_ra - *(volatile s32 *)temp_r29;
            if (var_r4 > temp_r9) {
                var_r4 = temp_r9;
            }
            fn_8013B6F4(temp_r30 + 0x20B4, var_r4);
        }
    }
    return true;
}
