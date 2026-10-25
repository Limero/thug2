// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219D34-0x80219E54 (288B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8013FF5C(s32 arg0, s32 arg1);
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

s32 fn_80219D34(s32 arg0) {
    s32 sp8;
    s32 var_r31;

    var_r31 = 2;
    fn_80128E34(fn_8013FF5C(arg0 + 0x110, QB_NUM_OBSERVERS), QB_CHECKSUM, &sp8, 1);
    if (sp8 == QB_NUM_0) {
        var_r31 = 0;
        goto done;
    }
    if (sp8 == QB_NUM_1) {
        var_r31 = 1;
        goto done;
    }
    if (sp8 == QB_NUM_2) {
        goto done;
    }
    if (sp8 == QB_NUM_3) {
        var_r31 = 3;
        goto done;
    }
    if (sp8 == QB_NUM_4) {
        var_r31 = 4;
        goto done;
    }
    if (sp8 == QB_NUM_5) {
        var_r31 = 5;
        goto done;
    }
    if (sp8 == QB_NUM_6) {
        var_r31 = 6;
        goto done;
    }
    if (sp8 == QB_NUM_7) {
        var_r31 = 7;
        goto done;
    }
    if (sp8 == QB_NUM_8) {
        var_r31 = 8;
    }
done:
    return var_r31;
}
