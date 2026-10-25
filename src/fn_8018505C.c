// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018505C-0x801850D4 (120B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern s32 fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018D404(Unk_C8FEE62D * arg0, s32 arg1);

s32 fn_8018505C(s32 arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 var_r30;

    var_r30 = 0;
    sp8 = 0;
    while (sp8 < fn_80184168((void *)arg0)) {
        var_r30 = fn_8018D404((void *)fn_8018B4C0((void *)(arg0 + 4), &sp8, &spC), arg1);
        sp8 += 1;
    }
    return var_r30;
}
