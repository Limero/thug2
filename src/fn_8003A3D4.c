// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A3D4-0x8003A428 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8003A344(CStruct *, s32);
bool fn_8003A3D4(CStruct *arg0, u32 arg1, s32 arg2) {
    s32 res;
    s32 next;

    do {
        if (arg1 <= (u32) arg2) {
            return false;
        }
        res = fn_8003A344(arg0, arg1);
        if (res == arg2) {
            return true;
        }
        next = res;
        arg1 = (u32) next;
    } while (1);
}
