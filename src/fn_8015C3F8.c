// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C3F8-0x8015C450 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8019849C(void *);
extern char lbl_80305EAC[];
extern char lbl_80305EC0[];
s32 ScriptShouldEndRun(CStruct *pParams, CScript *pScript) {
    s32 var_r31;

    var_r31 = 0;
    if (((s32) *(s32 *)((s32 *)((char *)(*(void * *)&lbl_80305EAC) + (s32)0x54)) != 0) || (fn_8019849C(*(s32 *)&lbl_80305EC0) != 0)) {
        var_r31 = 1;
    }
    return var_r31;
}
