// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801961B8-0x80196354 (412B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8018D924(Unk_C7387A53 *);
extern s32 fn_8018D7BC(Unk_C7387A53 *);
extern s32 fn_80190738(Unk_C7387A53 *);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 Game_GetGoalManager(void);
extern s32 fn_80183BC0(Unk_C7387A53 *, s32, s32);
extern s32 fn_8018E24C(Unk_C7387A53 *);
extern s32 fn_8018D120(Unk_C8FEE62D *, s32, s32, s32);
extern s32 fn_80183D68(Unk_C7387A53 *, s32);
void fn_80196354(Unk_C8FEE62D *);
#define VCALL_AC(argo) ((s32 (*)(void *))*(s32 *)((char *)*(s32 *)((char *)(argo) + (s32)0x14) + (s32)0xAC))((char *)(argo) + *(s16 *)((char *)*(s32 *)((char *)(argo) + (s32)0x14) + (s32)0xA8))
#define VCALL24(argo) ((s32 (*)(void *))*(s32 *)((char *)*(s32 *)((char *)(argo) + (s32)0x14) + (s32)0x24))((char *)(argo) + *(s16 *)((char *)*(s32 *)((char *)(argo) + (s32)0x14) + (s32)0x20))
s32 fn_801961B8(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 var_r29;

    if ((VCALL_AC(arg0) != 0) || (fn_8018D924(arg0) != 0) ||
        ((fn_8018D7BC(arg0) != 0) && (fn_80190738(arg0) != 0))) {
        return 0;
    }
    var_r29 = 0;
    sp8 = 0;
    GetArray(arg0->unk0x20, QB_GOAL_OBJECTS, &sp8, 1);
    GetChecksum_2(fn_80129528(sp8, arg0->unk0x60), QB_FLAG, &spC, 1);
    if (spC == arg1) {
        if (VCALL24(arg0) == 0) {
            temp_r30 = Game_GetGoalManager();
            fn_80183BC0(temp_r30, fn_8018E24C(arg0), 0);
        }
        var_r29 = fn_8018D120(arg0, arg1, arg2, arg3);
        if (VCALL24(arg0) != 0) {
            if (fn_8018D7BC(arg0) != 0) {
                if (fn_80190738(arg0) == 0) {
                    temp_r30_2 = Game_GetGoalManager();
                    fn_80183D68(temp_r30_2, fn_8018E24C(arg0));
                }
            } else {
                fn_80196354(arg0);
            }
        }
    }
    return var_r29;
}
