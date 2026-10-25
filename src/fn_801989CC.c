// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801989CC-0x80198A38 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;

extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_80198F7C(s32 arg0);
extern void fn_802199E4(s32 arg0, s32 arg1);

void fn_801989CC(CStruct *arg0, s32 arg1) {
    s32 temp_r29;

    temp_r29 = lbl_80305F9C;
    AddInteger((char *)arg0 + 4, QB_NUM_TEAMS, arg1);
    if (fn_80198F7C(arg0) == QB_NETLOBBY) {
        fn_802199E4(temp_r29, arg1);
    }
}
