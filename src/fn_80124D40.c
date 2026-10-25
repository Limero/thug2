// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124D40-0x80124DA0 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
void fn_8000A288(s32, s32);
void fn_80124D40(s32 arg0, s32 arg1) {
    fn_8000A288(arg0 + 0xA0, 2);
    fn_8000A288(arg0 + 0x54, 2);
    fn_8000A288(arg0 + 8, 2);
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
