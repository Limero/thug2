// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A548-0x8018A62C (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 Game_GetGoalManager(void);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_8018EC90(void);
s32 fn_8021B55C(s32, s32);
void fn_80137CB4(Unk_9F066EC1 *);
s32 NextItem(s32);
u8 fn_8021F6CC(Unk_2EC243AC *);
s32 fn_8018E24C(Unk_C7387A53 *);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

// ScriptGoalManager_AnnounceGoalStarted @ 0x8018A548
bool ScriptGoalManager_AnnounceGoalStarted(CStruct *pParams, CScript *pScript) {
    struct { u8 b; char p0; u16 h; void *p; char p1[0x20]; s32 w30; char p2[4]; u8 b38; char p3[3]; s32 w3c; } sp;
    register s32 ctx __asm__("r29");
    register s32 darg __asm__("r3");
    s32 temp_r30;
    s32 nm;

    nm = lbl_80305F9C;
    ctx = Game_GetGoalManager();
    GetChecksum_2(pParams, QB_NAME, &sp.w30, 1);
    ctx = GoalManager_GetGoal(ctx, sp.w30, 1);
    if (fn_8018EC90() == 0) {
        if (*(s32 *)*((s32 * *)&((Unk_C7387A53 *)ctx)->unk0x30) != 0) {
            return true;
        }
        temp_r30 = fn_8021B55C(nm, 0);
        fn_80137CB4(&sp.b);
        NextItem(nm);
        sp.b38 = fn_8021F6CC((void *)nm);
        sp.w3c = fn_8018E24C(ctx);
        darg = temp_r30;
        sp.p = &sp.b38;
        sp.h = 8;
        sp.b = 0x6F;
        fn_8013DE78(darg, &sp.b);
    }
    return true;
}
