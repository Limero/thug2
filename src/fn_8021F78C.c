// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F78C-0x8021F840 (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8013FF5C(s32, s32);

s32 fn_8021F78C(s32 arg0) {
    s32 sp8;
    s32 var_r3;

    fn_80128E34((void *)fn_8013FF5C(arg0 + 0x110, QB_FIREBALL_DIFFICULTY), QB_CHECKSUM, &sp8, 1);
    if (sp8 == QB_NUM_1) {
        var_r3 = 1;
    } else if (sp8 == QB_NUM_2) {
        var_r3 = 2;
    } else {
        if (sp8 == QB_NUM_3) {
            goto arm3;
        }
        if (sp8 == QB_NUM_4) {
            goto arm4;
        }
        var_r3 = 5;
        if (sp8 == QB_NUM_5) {
            goto end;
        }
    arm3:
        var_r3 = 3;
        goto end;
    arm4:
        var_r3 = 4;
    }
end:
    return var_r3;
}
