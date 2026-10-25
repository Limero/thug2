// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F5D8-0x8021F658 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 fn_8009CF2C(CStruct *);
s32 fn_80198B10(s32);
s32 fn_8021E024(void *);
s32 fn_8013FF5C(s32, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8021F5D8(CStruct *arg0) {
    s32 sp8;

    sp8 = QB_GRAFFITI_INDIVIDUAL_SCORING;
    if ((fn_8009CF2C(arg0) != 0) && (fn_80198B10(lbl_80305EC0) != 0)) {
        fn_80128E34(fn_8013FF5C(fn_8021E024(arg0), QB_TEAM_GRAFFITI_MODE), QB_CHECKSUM, &sp8, 1);
    }
    return sp8;
}
