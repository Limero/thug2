// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001CA24-0x8001CA68 (68B). Byte-identical.
#include "types.h"
extern bool lbl_80300188;
s32 GX_SetDrawSync(s32);
void fn_8001CA24(void) {
    if (lbl_80300188 != 0) {
        GX_SetDrawSync(0xFEEB);
        GX_ClearGPMetric();
    }
    GX_InvalidateVtxCache();
    GX_InvalidateTexAll();
}
