// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018064-0x80018098 (52B). Byte-identical.
#include "types.h"
void GX_SetCopyClear(void *, s32);
void fn_80018064(s32 *arg0) {
    s32 sp8;

    sp8 = *arg0;
    GX_SetCopyClear(&sp8, 0xFFFFFF);
}
