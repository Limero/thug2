// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C594-0x8015C5F0 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 lbl_80305F9C;
extern s32 fn_80219698(CStruct * arg0);
extern s32 fn_8021FE28(Unk_C7387A53 * arg0);
extern void fn_80177F38(Unk_C7387A53 * arg0, s32 arg1);

s32 ScriptCalculateFinalScores(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;

    temp_r31 = lbl_80305F9C;
    if (fn_80219698(temp_r31) != 0) {
        fn_80177F38(lbl_80305EAC, 1);
        return 1;
    }
    return fn_8021FE28(temp_r31);
}
