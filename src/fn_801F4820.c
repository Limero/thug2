// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4820-0x801F4858 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801F4820(Unk_13D0EFB0 *arg0) {
    s32 temp_r11;
    s32 var_r9;

    temp_r11 = arg0->unk0x114;
    var_r9 = 0;
    if ((temp_r11 == QB_COMBO) || (temp_r11 == QB_SKATE)) {
        var_r9 = arg0->unk0x2BB - 2;
    }
    return var_r9;
}
