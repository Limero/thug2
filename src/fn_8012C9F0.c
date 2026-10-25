// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012C9F0-0x8012CA80 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803032A8[];
void *fn_8012C9F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r11;
    Unk_2C0676B9 *var_r3;

    temp_r11 = fn_8012ED70();
    var_r3 = *(void * *)&lbl_803032A8;
    if (var_r3 != NULL) {
loop_1:
        if (((s32) var_r3->unk0x8 != arg0) || ((s32) var_r3->unk0x10 != arg1) || ((s32) var_r3->unk0xC != arg2) || ((temp_r0 = var_r3->unk0x4, ((temp_r0 == temp_r11) == 0)) && (temp_r0 != 0))) {
            var_r3 = var_r3->unk0x5C;
            if (var_r3 == NULL) {
                goto block_7;
            }
            goto loop_1;
        }
    } else {
block_7:
        var_r3 = NULL;
    }
    return var_r3;
}
