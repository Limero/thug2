// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165790-0x80165838 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
s32 fn_80165790(s32 arg0) {
    s32 temp_r3;

    temp_r3 = arg0 - 0x61;
    switch (temp_r3) {                              
    case 0:
        return QB_OPTIONSANDPROS;
    case 1:
        return QB_CAS;
    case 5:
        return QB_CAT;
    case 2:
        return QB_PARK;
    case 4:
        return QB_NETWORKSETTINGS;
    case 6:
        return QB_CREATEDGOALS;
    case 7:
        return QB_CREATEDGRAPHIC;
    default:
        return 0;
    }
}
