// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F19C8-0x801F1B30 (360B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 GetStructure(s32, s32);
s32 fn_801F19C8(s32 arg0) {
    s32 var_r9 = 0;

    switch ((u32)arg0) {
    case QB_SKATE:
        var_r9 = GetStructure(QB_GOAL_SKATELETTERS_GENERICPARAMS, 0);
        break;
    case QB_COMBO:
        var_r9 = GetStructure(QB_GOAL_AMATEURCOMBOLINE_GENERICPARAMS, 0);
        break;
    case QB_HIGHSCORE:
        var_r9 = GetStructure(QB_GOAL_HIGHSCORE_GENERICPARAMS, 0);
        break;
    case QB_HIGHCOMBO:
        var_r9 = GetStructure(QB_GOAL_HIGHCOMBO_GENERICPARAMS, 0);
        break;
    case QB_COMBOSKATETRIS:
    case QB_SKATETRIS:
    case QB_TRICKTRIS:
        var_r9 = GetStructure(QB_GOAL_TETRIS_GENERICPARAMS, 0);
        break;
    case QB_GAP:
        var_r9 = GetStructure(QB_GOAL_GAPS_GENERICPARAMS, 0);
        break;
    case QB_RACE:
        var_r9 = GetStructure(QB_GOAL_RACE_GENERICPARAMS, 0);
        break;
    case QB_TRICKBEAT:
        var_r9 = GetStructure(QB_GOAL_TRICKBEAT_GENERICPARAMS, 0);
        break;
    }
    return var_r9;
}
