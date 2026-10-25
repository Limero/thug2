// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183FDC-0x8018403C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* 0x801839F0 was renamed GoalManager_GetGoal (scope:global) — the masked
 * sweep cannot see a stale callee name; the LINK does. Always resolve callee
 * addresses through symbols.txt before promoting. */
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_8018CD3C(s32, s32);

s32 fn_80183FDC(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = GoalManager_GetGoal(arg0, arg1, 1);

    if (r != 0) {
        fn_8018CD3C(r, arg2);
    }
    return r != 0;
}
