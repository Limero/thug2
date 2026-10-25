// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800205A0-0x800205CC (44B). Byte-identical.
#include "types.h"
void GXInitLightColor(s32, s32);
// GX_InitLightColor @ 0x800205A0
void GX_InitLightColor(s32 arg0, s32 *arg1) {
    s32 sp8;

    sp8 = *arg1;
    GXInitLightColor(arg0, &sp8);
}
