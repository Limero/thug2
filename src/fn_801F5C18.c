// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5C18-0x801F5CC0 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80183B28(Unk_C7387A53 *arg0, s32 arg1);
s32 fn_80186CE0(s32 arg0, s32 arg1);
s32 Game_GetGoalManager(void);
s32 fn_801F2184(s32);
void fn_801F203C(void *);
void fn_801F59CC(void *);
void fn_801F5C18(Unk_F0C166E4 *arg0, Unk_127FDB99 *arg1) {
    s32 temp_r30;
    s32 var_r9;

    var_r9 = 1;
    if ((s32) arg1->unk0x2BE == 0) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        temp_r30 = Game_GetGoalManager();
        if (fn_80186CE0(temp_r30, fn_801F2184(arg1)) != 0) {
            fn_80183B28((Unk_C7387A53 *)temp_r30, fn_801F2184(arg1));
        }
    }
    fn_801F203C(arg1);
    if ((s32) arg0->unk0xAC00 == (s32) arg1) {
        arg0->unk0xAC00 = 0;
    }
    fn_801F59CC(arg0);
}
