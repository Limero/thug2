// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801630A0-0x801630F8 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80366478;
void GetText(CStruct *, void *, void *, s32);
s32 fn_8005CFC0(Unk_9994C3F5 *, s32);
void fn_8005CC88(CStruct *, CStruct *);
bool ScriptUnloadSFPTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp;

    GetText(pParams, 0, &sp8, 0);
    temp = fn_8005CFC0(lbl_80366478, sp8);
    if (temp != 0) {
        fn_8005CC88(lbl_80366478, temp);
    }
    return true;
}
