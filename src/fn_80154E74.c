// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154E74-0x80154EAC (56B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303448[];
extern s32 fn_80137AD4(Unk_F386DC9F *);
s32 ScriptObserversAllowed(CStruct *pParams, CScript *pScript) {
    s32 var_r3;

    
    var_r3 = ((fn_80137AD4(*(s32 *)&lbl_80303448) != 1));
    return var_r3;
}
