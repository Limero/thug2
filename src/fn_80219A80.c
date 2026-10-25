// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219A80-0x80219B18 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8013FF5C(s32 arg0, s32 arg1);
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

s32 fn_80219A80(s32 arg0) {
    s32 sp8;
    s32 var_r31;

    var_r31 = 4;
    fn_80128E34(fn_8013FF5C(arg0 + 0x110, QB_TEAM_MODE), QB_CHECKSUM, &sp8, 1);
    if (sp8 == QB_TEAMS_NONE) {
        var_r31 = 0;
        goto done;
    }
    if (sp8 == QB_TEAMS_TWO) {
        var_r31 = 2;
        goto done;
    }
    if (sp8 == QB_TEAMS_THREE) {
        var_r31 = 3;
    }
done:
    return var_r31;
}
