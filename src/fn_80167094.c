// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80167094-0x80167108 (116B). Byte-identical.
#include "types.h"
extern s32 lbl_802FFE50;
extern s32 s_round_up_to_platforms_block_size(s32 arg0);
extern s32 s_get_platforms_block_size(void);
extern s32 s_get_icon_k_required(u32 arg0);
s32 s_calculate_total_space_used_on_card(s32 arg0, s32 arg1) {
    register s32 var_r30 __asm__("r30");

    var_r30 = s_round_up_to_platforms_block_size(arg1);
    var_r30 = var_r30 / s_get_platforms_block_size();
    switch (lbl_802FFE50) {
    case 1 ... 3:
        var_r30 += s_get_icon_k_required(arg0);
        var_r30 += 4;
        break;
    case 4:
        var_r30 += 3;
        break;
    case 5 ... 8:
    default:
        break;
    }
    return var_r30;
}
