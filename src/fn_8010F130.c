// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010F130-0x8010F1B0 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetString(CStruct *, s32 *, s32 *, s32);
s32 fn_8000A778(s32);
void fn_8016A6E4(void);
extern s32 lbl_80383100[];
// ScriptUnloadQB @ 0x8010F130
bool ScriptUnloadQB(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;
    s32 i;

    sp8 = 0;
    GetString((void *)pParams, 0, &sp8, 0);
    temp_r31 = fn_8000A778(sp8);
    fn_8016A6E4();
    for (i = 0; i < 15; i++) {
        if (temp_r31 == lbl_80383100[i]) {
            lbl_80383100[i] = 0;
        }
    }
    return true;
}
