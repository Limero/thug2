// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F68AC-0x801F6968 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801F5898(void * arg0, CStruct * arg1);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern void fn_801F3534(Unk_9A728979 * arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

bool fn_801F68AC(void *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 mgr;

    mgr = fn_801F5898(arg0, arg1);
    if (mgr != 0) {
        sp8 = 0;
        GetInteger(arg1, QB_SET_INDEX, &sp8, 0);
        spC = 0;
        GetInteger(arg1, QB_SPIN, &spC, 0);
        sp10 = 0;
        GetInteger(arg1, QB_NUM_TAPS, &sp10, 0);
        fn_801F3534(mgr, sp8, ContainsFlag(arg1, QB_REQUIRE_PERFECT), spC, sp10);
    }
    return true;
}
