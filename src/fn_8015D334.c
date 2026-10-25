// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D334-0x8015D388 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern bool lbl_802FFE58;
extern char lbl_80305F1C[];
extern s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern s32 fn_801A920C(s32 obj, s32 val);
bool ScriptTrickOffAllObjects(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r0;

    temp_r0 = lbl_802FFE58;
    if (temp_r0 == 0) {
        sp8 = temp_r0;
        GetInteger(pParams, 0, &sp8, 0);
        fn_801A920C(*(s32 *)&lbl_80305F1C, sp8);
    }
    return true;
}
