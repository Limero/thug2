// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119A08-0x80119A54 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_801198C8(void *, s32);

s32 fn_80119A08(void *arg0, s32 arg1) {
    while (fn_801198C8(arg0, arg1) == 0) {
        arg1 += 1;
    }
    return arg1;
}
