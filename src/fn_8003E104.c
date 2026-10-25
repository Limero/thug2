// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E104-0x8003E148 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: CAS appearance gate (Create-A-Skater family, alongside
// ScriptMassageFaceTexture 0x8003E5F8 / ScriptCombineFaceTextureWithOverlay
// 0x8003E77C which call it after resolving the skater's face texture via
// fn_8005CF80). lbl_8030042C is the active-appearance handle set by
// fn_8003DB00; when non-zero, spawns/refreshes the appearance object via
// fn_8005C6E8(handle, 0). Suggested rename: ScriptCASAppearanceActive
#include "types.h"
extern s32 lbl_8030042C;
void fn_8005C6E8(s32, s32, s32);
bool fn_8003E104(s32 arg0) {
    if (lbl_8030042C != 0) {
        fn_8005C6E8(arg0, lbl_8030042C, 0);
        return true;
    }
    return false;
}
