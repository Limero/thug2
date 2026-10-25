// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191E30-0x80191E8C (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(s32, void *, s32, s32, s32);
void fn_80191C50(void *);
void fn_80191E30(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = arg1;
    if (arg1 != 0) {
        Script_RunScript(QB_GOAL_PRO_STOP_ANIM_SCRIPTS, fn_80191FD4(), 0, 0, 0);
        fn_80191C50(arg0);
    }
}
