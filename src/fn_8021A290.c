// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A290-0x8021A31C (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80305EC0;
s32 fn_80198F7C(s32 arg0);
s32 fn_80198B10(s32 arg0);
s32 fn_80140068(s32 arg0, void * arg1, void * arg2);
s32 fn_8021A290(s32 arg0) {
    s32 var_r3;

    if (fn_80198F7C(lbl_80305EC0) == QB_NETLOBBY) {
        return 0;
    }
    if (fn_80198B10(lbl_80305EC0) != 0) {
        var_r3 = (fn_80140068(arg0 + 0x110, QB_SCORE_DISPLAY, QB_CHECKSUM) ^ QB_SCORE_TEAMS) == 0;
    } else {
        var_r3 = 0;
    }
    return var_r3;
}
