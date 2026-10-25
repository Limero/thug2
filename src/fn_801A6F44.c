// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6F44-0x801A6F8C (72B). Byte-identical.
// Thin setter wrapper: stores fn_801A6FDC(arg0, Script_GetInteger(arg1, 0))
// into global lbl_80305F04.
// Suggested rename: fn_SetSomethingFromTwoArgs (see fn_801A6FDC / Script_GetInteger).
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305F04;
extern s32 Script_GetInteger(s32, s32);
extern s32 fn_801A6FDC(s32, s32);
void fn_801A6F44(s32 arg0, s32 arg1) {
    lbl_80305F04 = fn_801A6FDC(arg0, Script_GetInteger(arg1, 0));
}