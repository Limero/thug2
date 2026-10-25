// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198854-0x801988AC (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_80128C80(CStruct * arg0, void * arg1, void * arg2, s32 arg3);

s32 fn_80198854(CStruct *arg0) {
    s32 sp8;
    s32 var_r3;

    if (fn_80128C80((char *)arg0 + 4, QB_TRACK_BEST_COMBO, &sp8, 0) == 0) {
        return 0;
    }
    var_r3 = 1;
    if (sp8 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
