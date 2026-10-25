// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014898-0x80014904 (108B). Byte-identical.
#include "types.h"
s32 fn_8000DFA0(s32, s32);
s32 fn_80014898(s32);
void fn_8001B754(void *);
void fn_800146A4(void *);
s32 fn_80014898(s32 arg0) {
    s32 temp_r30;

    if (fn_8000DE40() != 0) {
        temp_r30 = fn_8000DFA0(arg0, 0);
        if (fn_8000DE5C() != 0) {
            return temp_r30;
        }
    }
    fn_8001B754(arg0 + 0x84);
    fn_800146A4(arg0);
    return 0;
}
