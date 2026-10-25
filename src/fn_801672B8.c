// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801672B8-0x80167408 (336B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern char lbl_803A0114[];
extern char lbl_802A8528[];
extern char lbl_802A853C[];
extern char lbl_802A854C[];
extern char lbl_802A8558[];
extern char lbl_802A8560[];
extern char lbl_802A856C[];
s32 s_generate_xbox_directory_name(u32 arg0, s32 arg1) {
    switch (arg0) {
    case QB_NETWORKSETTINGS:
        sprintf(lbl_803A0114, lbl_802A8528, arg1);
        break;
    case QB_OPTIONSANDPROS:
        sprintf(lbl_803A0114, lbl_802A853C, arg1);
        break;
    case QB_CAT:
        sprintf(lbl_803A0114, lbl_802A854C, arg1);
        break;
    case QB_PARK:
        sprintf(lbl_803A0114, lbl_802A8558, arg1);
        break;
    case QB_CREATEDGOALS:
        sprintf(lbl_803A0114, lbl_802A8560, arg1);
        break;
    case QB_CREATEDGRAPHIC:
        sprintf(lbl_803A0114, lbl_802A856C, arg1);
        break;
    case QB_UNKNOWN_0xCA41692E ... QB_UNKNOWN_0xCA4169FF:
    default:
        break;
    }
    return (s32)lbl_803A0114;
}
