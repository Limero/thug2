// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1BB4-0x800A1C18 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800A1BB4(Unk_C7387A53 *arg0, s32 arg1) {
    u32 var_r11;
    void *var_r9;

    for (var_r11 = 0; var_r11 < (u32) *((u32 *)&arg0->unk0x50); var_r11++) {
        var_r9 = (char *)arg0 + 0x58 + var_r11 * 8;
        if ((s32) *(s32 *)((char *)var_r9 - 0x4) == arg1) {
            return ((s32 (*)())*(s32 *)((char *)var_r9))();
        }
    }
    return 0;
}
