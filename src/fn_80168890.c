// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80168890-0x8016899C (268B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 Script_GetInteger(s32 arg0, s32 arg1);
extern s32 s_round_up_to_platforms_block_size(s32 arg0);
void fn_80168890(s32 arg0) {
    s32 var_r9;

    var_r9 = 0;
    switch ((u32)arg0) {
    case QB_OPTIONSANDPROS:
        var_r9 = Script_GetInteger(QB_SAVESIZE_OPTIONSANDPROS, 1);
        break;
    case QB_CAT:
        var_r9 = Script_GetInteger(QB_SAVESIZE_CAT, 1);
        break;
    case QB_CREATEDGOALS:
        var_r9 = Script_GetInteger(QB_SAVESIZE_CREATEDGOALS, 1);
        break;
    case QB_PARK:
        var_r9 = Script_GetInteger(QB_SAVESIZE_PARK, 1);
        break;
    case QB_NETWORKSETTINGS:
        var_r9 = Script_GetInteger(QB_SAVESIZE_NETWORKSETTINGS, 1);
        break;
    case QB_CREATEDGRAPHIC:
        var_r9 = Script_GetInteger(QB_SAVESIZE_CREATEDGRAPHIC, 1);
        break;
    case QB_UNKNOWN_0xF5D3C2A1:
        break;
    }
    s_round_up_to_platforms_block_size(var_r9 + 0x2C54);
}
