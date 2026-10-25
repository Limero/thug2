// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019868C-0x8019878C (256B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_80198F7C(s32 arg0);
extern s32 fn_80128C80(CStruct * arg0, void * arg1, void * arg2, s32 arg3);

s32 fn_8019868C(CStruct *arg0) {
    s32 sp8;
    s32 var_r3;

    if ((fn_80198F7C(arg0) == QB_KING) || (fn_80198F7C(arg0) == QB_NETKING) ||
        (fn_80198F7C(arg0) == QB_SCORECHALLENGE) || (fn_80198F7C(arg0) == QB_NETSCORECHALLENGE) ||
        (fn_80198F7C(arg0) == QB_CREATEGOALS) || (fn_80198F7C(arg0) == QB_FIREFIGHT) ||
        (fn_80198F7C(arg0) == QB_NETFIREFIGHT)) {
        return 0;
    }
    fn_80128C80((char *)arg0 + 4, QB_DEFAULT_TIME_LIMIT, &sp8, 1);
    var_r3 = 1;
    if (sp8 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
