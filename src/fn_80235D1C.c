// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80235D1C-0x80235D70 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80235D1C(void *arg0, s32 arg1) {
    if (((s32) (arg0 + 0x10000) != -0x3C94) && ((s32) *(u16 *)((char *)arg0 + (s32)0x13C9A) == 0x4E24)) {
        // m2c dropped the 2nd argument: retail keeps the incoming r4 (= arg1)
        // live for the first call instead of reloading it (see 80235D4C).
        strcpy(arg0 + 0x13CB0, arg1);
        strcpy(arg0 + 0x17730, arg1);
    }
}
