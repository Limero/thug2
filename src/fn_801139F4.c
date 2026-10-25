// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801139F4-0x80113A38 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D114[];
void GetFloat(CStruct *, s32, f32 *, s32);
void SetMusicStreamVolume(f32);
bool ScriptSetMusicStreamVolume(CStruct *pParams, CScript *pScript) {
    f32 sp8;

    sp8 = *(f32 *)lbl_8029D114;
    GetFloat(pParams, 0, &sp8, 0);
    SetMusicStreamVolume(sp8);
    return true;
}
