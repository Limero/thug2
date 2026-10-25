// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018C374-0x8018C570 (508B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

/* One vtable layout serves all three vcall sites: every one is
   `lha off ; lwz fn ; add ; mtlr ; blrl` — an s16 this-adjustment followed
   by the fn pointer.  Sites use +0x20/+0x24, +0x78/+0x7C and +0xA8/+0xAC.
   (Unk_89391A04 only covers the first pair; the other two needed their own.) */
typedef struct Vt_C374 {
    char pad00[0x20];
    s16 off0x20;
    char pad22[2];
    s32 (*fn0x24)(void *);
    char pad28[0x50];
    s16 off0x78;
    char pad7A[2];
    s32 (*fn0x7C)(void *);
    char pad80[0x28];
    s16 off0xA8;
    char padAA[2];
    s32 (*fn0xAC)(void *);
} Vt_C374;

/* The goal the traversal walks: vtable at +0x14, next-link at +0x30. */
typedef struct Goal_C374 {
    char pad00[0x14];
    Vt_C374 *vt;
    char pad18[0x18];
    s32 *unk0x30;
} Goal_C374;

/* `this`: doubly-linked node (+0x0C/+0x10), vtable +0x14, owning script
   +0x20 (every ContainsFlag/Script_RunScript arg), goal chain head +0x30.
   +0x20 must be s32-wide (lwz), so Unk_007756DA's s16 there is unusable. */
typedef struct Self_C374 {
    char pad00[0x0C];
    struct Self_C374 *unk0x0C;
    struct Self_C374 *unk0x10;
    Vt_C374 *vt;
    void *unk0x18;
    char pad1C[4];
    void *script;
    char pad24[0xC];
    s32 *unk0x30;
} Self_C374;

s32 fn_8018DE04(void *);
void fn_801270B4(void *, s32);
void fn_8012720C(void *, s32);
s32 ContainsFlag(void *, s32);
void fn_8018D684(void *);
void fn_8018BD34(void *);
void fn_801907E0(void *, s32);
void Script_RunScript(s32, void *, void *, s32, s32);
void fn_8018BE00(void *, s32, s32);
s32 Game_GetGoalManager(void);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_8018B90C(void *);

bool fn_8018C374(Self_C374 *arg0, s32 arg1, s32 arg2) {
    Vt_C374 *vt;
    Goal_C374 *goal;
    s32 *p;
    s32 mgr;

    vt = arg0->vt;
    if (((s32 (*)(void *))vt->fn0x24)((char *)arg0 + vt->off0x20) != 0) {
        if (fn_8018DE04(arg0) != 0) {
            fn_801270B4(arg0->script, QB_KEY_COMBOS);
        }
        vt = arg0->vt;
        ((s32 (*)(void *))vt->fn0x7C)((char *)arg0 + vt->off0x78);
        if (ContainsFlag(arg0->script, QB_PRESERVE_FLAGS) == 0) {
            fn_8018D684(arg0);
        }
        fn_8018BD34(arg0);
        fn_801907E0(arg0, QB_DEACTIVATE);
        if (ContainsFlag(arg0->script, QB_QUICK_START) == 0) {
            fn_8012720C(arg0->script, QB_TESTING_GOAL);
        }
        if ((ContainsFlag(arg0->script, QB_JUST_WON_GOAL) == 0) &&
            (ContainsFlag(arg0->script, QB_QUICK_START) == 0)) {
            Script_RunScript(QB_READY_SKATER_FOR_EARLY_END_CURRENT_GOAL, arg0->script, 0, 0, 0);
            if (arg2 != 0) {
                /* NB: +0x30 is re-read here rather than kept across the two
                   calls below — the want reloads it after Game_GetGoalManager. */
                if ((arg0->unk0x30 != NULL) && (*arg0->unk0x30 != 0)) {
                    goal = 0;      /* hoisted above the call in the want */
                    fn_8018BE00(arg0, 0, 0);
                    mgr = Game_GetGoalManager();
                    p = arg0->unk0x30;
                    while ((p != NULL) && (*p != 0)) {
                        goal = (Goal_C374 *)GoalManager_GetGoal(mgr, *p, 1);
                        p = goal->unk0x30;
                    }
                    if (goal != NULL) {
                        vt = goal->vt;
                        if (((s32 (*)(void *))vt->fn0xAC)((char *)goal + vt->off0xA8) == 0) {
                            fn_8018B90C(goal);
                        }
                    }
                }
            }
        }
        arg0->unk0x10->unk0x0C = arg0->unk0x0C;
        arg0->unk0x0C->unk0x10 = arg0->unk0x10;
        arg0->unk0x0C = arg0;
        arg0->unk0x10 = arg0;
        return true;
    }
    return false;
}
