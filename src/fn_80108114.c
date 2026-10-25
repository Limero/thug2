// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80108114-0x80108158 (68B). Byte-identical.
#include "types.h"
extern void fn_8003EF4C(s32, s32, s32, s32);
void fn_80108114(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void * arg4) {
    s32 ptr = arg0 + 0x10;
    s32 t = (arg1 << 0x18) | (arg2 << 0x10) | (arg3 << 8) | 0xFF;
    fn_8003EF4C(arg0, ptr, t, t);
}
