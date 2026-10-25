// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019E24-0x80019E50 (44B). Byte-identical.
#include "types.h"
s32 DVDReadAsyncPrio(s32, s32, s32, s32, s32, s32);
// dvd_read_safe @ 0x80019E24
void dvd_read_safe(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    DVDReadAsyncPrio(arg0, arg1, arg2, arg3, 0, 2);
    fn_8001A788();
}
