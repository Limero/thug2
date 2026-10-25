// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158594-0x801585D0 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_80174A58(void *, CStruct *);
extern void fn_8003AB40(s32, s32);
bool ScriptPrintCurrentAppearance(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;

    temp_r3 = fn_80174A58(*(s32 *)&lbl_80305EAC, pParams);
    fn_8003AB40(temp_r3 + 4, temp_r3 + 0x5C);
    return true;
}
