// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183F08-0x80183FDC (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 GoalManager_GetGoal(void *, s32, s32);
s32 fn_80183BC0(void *, s32, s32);
s32 fn_80198F7C(s32);
s32 fn_80198FBC(s32);
typedef struct {
    char _00[0x88];
    s16 unk88;
    char _8A[2];
    s32 unk8C;
} GoalVT;
s32 fn_80183F08(Unk_C7387A53 *arg0, s32 arg1) {
    s32 goal;
    GoalVT *vt;
    s32 (*fp)(void *);

    goal = GoalManager_GetGoal(arg0, arg1, 1);
    if (goal != 0) {
        vt = *(GoalVT **)((char *)goal + 0x14);
        fp = (s32 (*)(void *))vt->unk8C;
        fp((char *)goal + vt->unk88);
        if (fn_80198F7C(lbl_80305EC0) == QB_CLASSIC) {
            fn_80183BC0(arg0, arg1, 0);
        } else if ((fn_80198F7C(lbl_80305EC0) == QB_NETGOALATTACK) && (fn_80198FBC(lbl_80305EC0) == QB_GOALS_CLASSIC)) {
            fn_80183BC0(arg0, arg1, 0);
        }
    }
    return goal != 0;
}
