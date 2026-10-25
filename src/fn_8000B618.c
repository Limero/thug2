// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B618-0x8000B680 (104B). Byte-identical.
#include "types.h"
extern char lbl_802FFE7C[];
extern char lbl_802FFE80[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_8000B618(s32 arg0) {
    if (((s32) *(s32 *)&lbl_802FFE7C == 0) && (arg0 != 0)) {
        fn_800099AC(0x24, 0, 1);
        *(s32 *)&lbl_802FFE7C = fn_8000B838();
    }
    *(s32 *)&lbl_802FFE80 += 1;
    return *(s32 *)&lbl_802FFE7C;
}
