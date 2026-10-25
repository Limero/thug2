// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E2B4-0x8000E2FC (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE8C[];
s32 GetText(s32, s32, s32 *, s32);
void fn_8000DD2C(s32, s32);
void ScriptIsLoadPreFinished(s32 arg0) {
    s32 sp8;
    s32 saved;
    saved = *(s32 *)&lbl_802FFE8C;
    GetText(arg0, 0, &sp8, 1);
    fn_8000DD2C(saved, sp8);
}
