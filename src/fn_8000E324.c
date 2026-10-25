// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E324-0x8000E370 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE8C[];
s32 GetText(s32, s32, s32 *, s32);
void fn_8000DDB0(s32, s32);
bool ScriptWaitLoadPre(s32 arg0) {
    s32 sp8;
    s32 saved;
    saved = *(s32 *)&lbl_802FFE8C;
    GetText(arg0, 0, &sp8, 1);
    fn_8000DDB0(saved, sp8);
    return true;
}
