// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801671A0-0x801672B8 (280B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 fn_80125A6C(void *arg0, s32 arg1);
extern char lbl_802A84AC[];
extern char lbl_802A84C4[];
extern char lbl_802A84D0[];
extern char lbl_802A84E0[];
extern char lbl_802A84F8[];
extern char lbl_802A8510[];
s32 s_get_version_number(u32 arg0) {
    switch (arg0) {
    case QB_OPTIONSANDPROS:
        return fn_80125A6C(lbl_802A84AC, 1);
    case QB_CAT:
        return fn_80125A6C(lbl_802A84C4, 1);
    case QB_PARK:
        return fn_80125A6C(lbl_802A84D0, 1);
    case QB_NETWORKSETTINGS:
        return fn_80125A6C(lbl_802A84E0, 1);
    case QB_CREATEDGOALS:
        return fn_80125A6C(lbl_802A84F8, 1);
    case QB_CREATEDGRAPHIC:
        return fn_80125A6C(lbl_802A8510, 1);
    case QB_UNKNOWN_0xCA41692E ... QB_UNKNOWN_0xCA4169FF:
    default:
        return -1;
    }
}
