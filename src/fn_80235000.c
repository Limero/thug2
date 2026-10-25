// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80235000-0x80235088 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 GetInteger(s32, s32, s32 *, s32);
s32 fn_8023C598(s32);
void fn_8023E09C(s32, s32);
bool ScriptEnableParkEdCursor(s32 arg0) {
    s32 sp8;

    sp8 = 0;
    GetInteger(arg0, 0, &sp8, 0);
    if (sp8 != 0) {
        if (fn_8023C598(0) != 0) {
            fn_8023E09C(fn_8023C598(1), 1);
        }
    } else if (fn_8023C598(0) != 0) {
        fn_8023E09C(fn_8023C598(1), 0);
    }
    return true;
}
