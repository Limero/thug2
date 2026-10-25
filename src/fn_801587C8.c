// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801587C8-0x80158848 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
extern s32 fn_801A5D9C(s32, s32);
extern s32 fn_801A5240(s32, s32, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);

void ScriptSetSkaterProfileProperty(CStruct *arg0) {
    s32 sp10;
    s32 spC;
    s32 sp8;

    GetInteger(arg0, QB_PLAYER, &sp8, 1);
    GetChecksum_2(arg0, 0, &spC, 0);
    { register s32 z6 __asm__("r6"); register s32 z4 __asm__("r4");
      __asm__("li %0,0\n\tli %1,0" : "=r"(z6), "=r"(z4));
      GetInteger(arg0, z4, &sp10, z6); }
    fn_801A5240(fn_801A5D9C(lbl_80305EFC, sp8), spC, sp10);
}
