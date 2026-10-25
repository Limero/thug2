// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241580-0x802415C4 (68B). Byte-identical.
#include "types.h"
s32 fn_800546A0(s32);
void fn_80057D30(s32, s32);
void fn_80241580(s32 *arg0, s32 arg1) {
    s32 r = fn_800546A0(*arg0);
    fn_80057D30(r, arg1 != 0 ? 0xFF : 0);
}
