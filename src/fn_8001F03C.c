// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F03C-0x8001F068 (44B). Byte-identical.
#include "types.h"
void GXSetFog(s32, s32);
void fn_8001F03C(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 sp8;

    sp8 = *arg1;
    GXSetFog(arg0, &sp8);
}
