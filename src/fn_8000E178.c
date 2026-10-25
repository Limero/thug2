// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E178-0x8000E1B4 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802FFE8C[];
s32 GetText(s32, s32, s32, s32);
s32 fn_8000DBC4(s32, s32);
void ScriptInPreFile(s32 arg0) {
    s32 sp8;

    GetText(arg0, 0, &sp8, 1);
    fn_8000DBC4(*(s32 *)&lbl_802FFE8C, sp8);
}
