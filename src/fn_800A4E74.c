// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4E74-0x800A4EE0 (108B). Byte-identical.
#include "types.h"
extern char lbl_80301A78[];
extern char lbl_80301A7C[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_800A4E74(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80301A78 == 0) && (arg0 != 0)) {
        fn_800099AC(0xB220, 0, 1);
        *(s32 *)&lbl_80301A78 = fn_800A51DC();
    }
    *(s32 *)&lbl_80301A7C += 1;
    return *(s32 *)&lbl_80301A78;
}
