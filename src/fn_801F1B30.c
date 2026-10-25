// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1B30-0x801F1CE8 (440B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure(s32, s32);
extern void fn_801311A0(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, Unk_80577C09 *);
s32 fn_801F1B30(s32 arg0) {
    s32 var_r31 = 0;

    switch ((u32)arg0) {
    case QB_SKATE:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_SKATE, 0);
        break;
    case QB_COMBO:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_COMBO, 0);
        break;
    case QB_HIGHSCORE:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_HIGHSCORE, 0);
        break;
    case QB_HIGHCOMBO:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_HIGHCOMBO, 0);
        break;
    case QB_SKATETRIS:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_SKATETRIS, 0);
        break;
    case QB_COMBOSKATETRIS:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_COMBOSKATETRIS, 0);
        break;
    case QB_TRICKTRIS:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_TRICKTRIS, 0);
        break;
    case QB_GAP:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_GAP, 0);
        break;
    case QB_RACE:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_RACE, 0);
        break;
    case QB_TRICKBEAT:
        var_r31 = GetStructure(QB_EDITEDGOAL_EXTRAPARAMS_TRICKBEAT, 0);
        fn_801311A0(QB_GOAL_EDITOR_GET_BEAT_PATTERN, 0, 0, var_r31);
        break;
    }
    return var_r31;
}
