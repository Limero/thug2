// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196468-0x801964F8 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80190738(Unk_C7387A53 *);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 Game_GetGoalManager(void);
extern s32 fn_8018D7BC(Unk_C7387A53 *);
extern s32 fn_80183D68(Unk_C7387A53 *, s32);
extern s32 fn_80183F08(Unk_C7387A53 *, s32);
extern s32 fn_8018E24C(Unk_C7387A53 *);
void fn_80196468(Unk_C7387A53 *arg0) {
    s32 temp_r30;

    if ((fn_80190738(arg0) != 0) && (ContainsFlag(arg0->unk0x20, QB_COMBO_STARTED) != 0)) {
        temp_r30 = Game_GetGoalManager();
        if (fn_8018D7BC(arg0) != 0) {
            fn_80183D68(temp_r30, fn_8018E24C(arg0));
        } else {
            fn_80183F08(temp_r30, fn_8018E24C(arg0));
        }
    }
}
