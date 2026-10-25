// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A8410-0x800A84B4 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ScriptAllocatePathManMemory — allocates path-man memory: writes fixed
// sizes (0xC8/0x14/0xC8) through GetInteger under three hash keys, then
// fn_800A8328(handle, a, b, c). fn_800A8328 declared f32-returning so ngccc
// drops the crclr cr1eq before its bl (§4p item-27).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
extern s32 fn_800A7F38(void);
extern f32 fn_800A8328(CStruct *, s32, s32, CStruct *);
bool ScriptAllocatePathManMemory(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r28;

    temp_r28 = fn_800A7F38();
    sp8 = 0xC8;
    GetInteger(pParams, QB_MAXLINKS, &sp8, 0);
    spC = 0x14;
    GetInteger(pParams, QB_MAXOBJECTSPERPATH, &spC, 0);
    sp10 = 0xC8;
    GetInteger(pParams, QB_MAXPEDSPERPATH, &sp10, 0);
    fn_800A8328(temp_r28, sp8, spC, sp10);
    return true;
}
