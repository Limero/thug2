// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FEF4-0x8001FF14 (32B). Byte-identical.
// The DOL passes r3/r4 through untouched to GXSetPixelFmt - no args here
// keeps the call a bare bl (8 instructions, 0x20).
#include "types.h"
extern void GXSetPixelFmt(void);
// GX_SetPixelFmt @ 0x8001FEF4
void GX_SetPixelFmt(s32 arg0, s32 arg1) { GXSetPixelFmt(); }
