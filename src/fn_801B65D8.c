// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B65D8-0x801B668C (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F0F84(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_801B65D8(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 tmp;

    tmp = fn_800F0F84(arg1, 1);
    if ((GetChecksum_2(tmp, QB_SKATEACTION, &sp8, 0) != 0) && ((sp8 == QB_VERT_GRAB) || (sp8 == QB_VERT_LIP) || (sp8 == -QB_UNKNOWN_0x19205139) || (sp8 == -QB_UNKNOWN_0x25F8DC26) || (sp8 == -QB_UNKNOWN_0x1706EDA9) || (sp8 == -QB_UNKNOWN_0x2A4B0FEC))) {
        return true;
    }
    return false;
}