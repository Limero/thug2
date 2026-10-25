// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D6AC-0x8002D718 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8002D620(s32, s32, u32 *);
void fn_8002D4D8(s32);
bool fn_8002D6AC(Unk_FFAD6788 *arg0, u32 arg1, s32 arg2) {
    register s32 temp_r4 __asm__("r4");
    u32 sp8 = 0x3E7U;
    temp_r4 = fn_8002D620(arg0, arg2, &sp8);
    if (arg1 > sp8 && temp_r4 != 0) {
        fn_8002D4D8(arg0);
        return true;
    }
    return false;
}
