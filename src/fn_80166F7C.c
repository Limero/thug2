// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80166F7C-0x80167094 (280B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 Script_GetInteger(s32 arg0, s32 arg1);
s32 s_get_icon_k_required(u32 arg0) {
    switch (arg0) {
    case QB_OPTIONSANDPROS:
        return Script_GetInteger(QB_OPTIONSPROSICONSPACEREQUIRED, 0);
    case QB_NETWORKSETTINGS:
        return Script_GetInteger(QB_NETWORKSETTINGSICONSPACEREQUIRED, 0);
    case QB_CAT:
        return Script_GetInteger(QB_CATICONSPACEREQUIRED, 0);
    case QB_PARK:
        return Script_GetInteger(QB_PARKICONSPACEREQUIRED, 0);
    case QB_CREATEDGOALS:
        return Script_GetInteger(QB_CREATEDGOALSICONSPACEREQUIRED, 0);
    case QB_CREATEDGRAPHIC:
        return Script_GetInteger(QB_CREATEDGRAPHICICONSPACEREQUIRED, 0);
    case QB_UNKNOWN_0xCA41692E ... QB_UNKNOWN_0xCA4169FF:
    default:
        return 0;
    }
}
