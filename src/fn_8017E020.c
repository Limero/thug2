// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017E020-0x8017E170 (336B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801A6F44(s32 arg0, s32 arg1);

s32 fn_8017E020(Unk_C7387A53 *arg0) {
    s32 var_r31;

    var_r31 = 0;
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_ALWAYS_SPECIAL) != 0) {
        var_r31 = QB_CHEAT_ALWAYS_SPECIAL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_PERFECT_MANUAL) != 0) {
        var_r31 |= QB_CHEAT_PERFECT_MANUAL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_PERFECT_RAIL) != 0) {
        var_r31 |= QB_CHEAT_PERFECT_RAIL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_PERFECT_SKITCH) != 0) {
        var_r31 |= QB_CHEAT_PERFECT_SKITCH;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_STATS_13) != 0) {
        var_r31 |= QB_CHEAT_STATS_13;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_FLAG_G_EXPERT_MODE_NO_REVERTS) != 0) {
        var_r31 |= QB_FLAG_G_EXPERT_MODE_NO_REVERTS;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_FLAG_G_EXPERT_MODE_NO_WALKING) != 0) {
        var_r31 |= QB_FLAG_G_EXPERT_MODE_NO_WALKING;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_FLAG_G_EXPERT_MODE_NO_MANUALS) != 0) {
        var_r31 |= QB_FLAG_G_EXPERT_MODE_NO_MANUALS;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_NO_G_DISPLAY_BALANCE) != 0) {
        var_r31 |= QB_NO_G_DISPLAY_BALANCE;
    }
    return var_r31;
}
