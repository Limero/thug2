// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E24C-0x8000E2B4 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetText(CStruct *, void *, void *, void *);
s32 fn_80128A90(CStruct *, void *);
s32 fn_8000DC80(Unk_C8FEE62D *, void *, void *);
extern char lbl_802FFE8C[];
extern char lbl_80290358[];
bool ScriptUnloadPreFile(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 *temp_r29;

    temp_r29 = *(s32 *)&lbl_802FFE8C;
    GetText(pParams, 0, &sp8, 1);
    fn_8000DC80(temp_r29, sp8, fn_80128A90(pParams, (s32)lbl_80290358));
    return true;
}