// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219724-0x80219840 (284B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8013FF5C(s32 arg0, s32 arg1);
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
s32 fn_80219724(s32 arg0) {
    s32 sp8;
    s32 var_r3;

    fn_80128E34(fn_8013FF5C(arg0 + 0x110, QB_RANK_LIMIT), QB_CHECKSUM, &sp8, 1);
    if (sp8 == QB_NUM_1) {
        var_r3 = 0;
        goto done;
    }
    if (sp8 == QB_NUM_2) {
        var_r3 = 1;
        goto done;
    }
    if (sp8 == QB_NUM_3) {
        var_r3 = 2;
        goto done;
    }
    if (sp8 == QB_NUM_4) {
        var_r3 = 3;
        goto done;
    }
    if (sp8 == QB_NUM_5) {
        var_r3 = 4;
        goto done;
    }
    if (sp8 == QB_NUM_6) {
        var_r3 = 5;
        goto done;
    }
    if (sp8 == QB_NUM_7) {
        var_r3 = 6;
        goto done;
    }
    if (sp8 != QB_NUM_8) {
        var_r3 = 8;
        if (sp8 != QB_NUM_9) {
            var_r3 = 9;
        }
        goto done;
    }
    var_r3 = 7;
done:
    return var_r3;
}
