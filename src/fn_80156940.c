// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156940-0x80156994 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_80174A58(void *, CStruct *);
extern s32 fn_801A572C(s32);

s32 ScriptCurrentSkaterIsPro(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;
    s32 var_r31;

    var_r31 = 0;
    temp_r3 = fn_80174A58(*(s32 *)&lbl_80305EAC, pParams);
    if ((temp_r3 != 0) && (fn_801A572C(temp_r3) != 0)) {
        var_r31 = 1;
    }
    return var_r31;
}
