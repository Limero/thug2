// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80096588-0x8009666C (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Ilibs/dolphin/include
#include "types.h"
#include "dolphin/gx/GXEnum.h"
void SetBlendMode(GXBlendMode, GXBlendFactor, GXBlendFactor, GXLogicOp, GXBool, GXBool, GXBool);
// set_blend_mode @ 0x80096588
void set_blend_mode(s32 arg0, u32 arg1, s32 arg2) {
    switch (arg1) {
    case 0: goto dflt;
    case 1 ... 2:
        SetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_ONE, GX_LO_CLEAR, GX_ENABLE,
                    arg2 & 0xFF, GX_TRUE);
        break;
    case 3 ... 4:
        SetBlendMode(GX_BM_SUBTRACT, GX_BL_ZERO, GX_BL_ZERO, GX_LO_CLEAR, GX_ENABLE,
                    arg2 & 0xFF, GX_TRUE);
        break;
    case 5 ... 6:
        SetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR, GX_ENABLE,
                    arg2 & 0xFF, GX_TRUE);
        break;
    case 9 ... 10:
        SetBlendMode(GX_BM_BLEND, GX_BL_SRC_COLOR, GX_BL_ONE, GX_LO_CLEAR, GX_ENABLE,
                    arg2 & 0xFF, GX_TRUE);
        break;
    case 7 ... 8:
        SetBlendMode(GX_BM_BLEND, GX_BL_SRC_COLOR, GX_BL_ZERO, GX_LO_CLEAR, GX_ENABLE,
                    arg2 & 0xFF, GX_TRUE);
        break;
    default: dflt:
        SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR, GX_ENABLE, arg2 & 0xFF,
                    GX_TRUE);
        break;
    }
}
