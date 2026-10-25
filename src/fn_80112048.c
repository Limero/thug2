// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112048-0x80112178 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8002D1C4(s32, s32, s32);
void fn_80031AF0(s32, s32);
bool ScriptInitAnimSystem(CStruct *arg0) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 var_r5;

    sp8 = 0;
    GetInteger(arg0, QB_ANIMHEAPSIZE, &sp8, 1);
    spC = 0;
    GetInteger(arg0, QB_CACHEBLOCKALIGN, &spC, 1);
    sp10 = 0;
    GetChecksum_2(arg0, QB_DEFCACHETYPE, &sp10, 1);
    switch ((u32)sp10) {
    case QB_STANDARD:
        var_r5 = 2;
        break;
    case 0x50428FBDu:
        var_r5 = 3;
        break;
    case 0x7ADB1481u:
        var_r5 = 4;
        break;
    default:
        var_r5 = 0;
        break;
    }
    fn_8002D1C4(sp8, spC, var_r5);
    sp14 = 0;
    sp18 = 0;
    GetInteger(arg0, QB_MAXDEGENERATEANIMS, &sp14, 1);
    GetInteger(arg0, QB_MAXANIMSUBSETS, &sp18, 1);
    fn_80031AF0(sp14, sp18);
    return true;
}
