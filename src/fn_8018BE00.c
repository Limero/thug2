// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BE00-0x8018BED8 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct GoalNode GoalNode;
typedef struct GoalObj GoalObj;
typedef struct GoalVtbl GoalVtbl;

struct GoalNode {
    s32 unk0x0;         /* 0x0: value passed to GoalManager_GetGoal */
    GoalNode *unk0x4;   /* 0x4: next sibling */
};

struct GoalVtbl {
    char pad0x0[0x20];
    s16 off0x20;        /* 0x20: `this` adjustment for fn0x24 */
    char pad0x22[2];
    s32 (*fn0x24)(void *);              /* 0x24 */
    char pad0x28[0x48];
    s16 off0x70;        /* 0x70: `this` adjustment for fn0x74 */
    char pad0x72[2];
    void (*fn0x74)(void *, s32, s32);   /* 0x74 */
};

struct GoalObj {
    char pad0x0[0x14];
    GoalVtbl *vt;       /* 0x14 */
    char pad0x18[0x14];
    GoalNode *head;     /* 0x2C */
    char pad0x30[0x40];
    s32 flags;          /* 0x70 */
};

s32 Game_GetGoalManager(void);
void *GoalManager_GetGoal(s32, s32, s32);
void fn_801907E0(GoalObj *, s32);
void fn_8018BE00(GoalObj *, s32, s32);

void fn_8018BE00(GoalObj *arg0, s32 arg1, s32 arg2) {
    GoalVtbl *vt;
    GoalNode *p;
    s32 mgr;

    vt = arg0->vt;
    if (vt->fn0x24((char *)arg0 + vt->off0x20) != 0) {
        vt = arg0->vt;
        vt->fn0x74((char *)arg0 + vt->off0x70, 1, 1);
    }
    fn_801907E0(arg0, QB_UNINIT);
    arg0->flags &= QB_UNKNOWN_0x7FFFFFFF;
    if (arg1 != 0) {
        mgr = Game_GetGoalManager();
        p = arg0->head;
        while (p != NULL && p->unk0x0 != 0) {
            fn_8018BE00(GoalManager_GetGoal(mgr, p->unk0x0, 1), arg1, arg2 + 1);
            p = p->unk0x4;
        }
    }
}
