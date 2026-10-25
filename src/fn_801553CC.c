// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801553CC-0x80155430 (100B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_8016D1A8(void);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8016CFDC(Unk_C7387A53 *);
void fn_8019EFD4(Unk_6A70655D *, Unk_C7387A53 *);

bool ScriptSetViewerAnim(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r30;
    s32 temp_r3;

    var_r30 = fn_8016D1A8();
    if (var_r30 != 0) {
        fn_80128E34(pParams, 0, &sp8, 1);
        temp_r3 = fn_8016CFDC(var_r30);
        if (temp_r3 != 0) {
            fn_8019EFD4(temp_r3, sp8);
        }
    }
    return true;
}
