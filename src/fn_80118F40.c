// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118F40-0x80118FCC (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D394;
extern f32 lbl_8029D3A0;
extern s32 lbl_80302C30;

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_800145AC(void);

s32 ScriptTimeGreaterThan(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    s32 spC;
    s32 temp_r30;

    sp8 = lbl_8029D394;
    GetFloat(pParams, 0, &sp8, 0);
    temp_r30 = lbl_80302C30;
    spC = fn_800145AC() - temp_r30;
    return (f32)(u32)spC > sp8 * lbl_8029D3A0;
}