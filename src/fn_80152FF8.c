// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152FF8-0x80153054 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80174090(Unk_C5855798 *, void *);
s32 fn_80198BE8(void *);
s32 fn_80219698(CStruct *);
extern char lbl_80305EAC[];
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
bool ScriptResetClock(CStruct *pParams, CScript *pScript) {
    s32 temp_r31;

    temp_r31 = *(s32 *)&lbl_80305EAC;
    if (fn_80219698(*(s32 *)&lbl_80305F9C) != 0) {
        fn_80174090(temp_r31, fn_80198BE8(*(s32 *)&lbl_80305EC0));
    }
    return true;
}
