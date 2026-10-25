// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017200C-0x80172054 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012772C(CStruct *, s32, f32);
extern s32 lbl_80305EA4;
s32 ScriptTODManager_GetTimeMultiplier(s32 arg0, CScript *arg1) {
    s32 var_r3;
    Unk_E9D95610 *mgr;

    mgr = lbl_80305EA4;
    if (mgr == 0) {
        var_r3 = 0;
    } else {
        fn_8012772C(arg1->unk0x18, QB_TOD_TIME_MULTIPLIER, mgr->unk0x344);
        var_r3 = 1;
    }
    return var_r3;
}
