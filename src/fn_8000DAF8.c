// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DAF8-0x8000DB60 (104B). Byte-identical.
#include "types.h"
extern char lbl_802FFE8C[];
extern char lbl_802FFE90[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_8000DAF8(s32 arg0) {
    if (((s32) *(s32 *)&lbl_802FFE8C == 0) && (arg0 != 0)) {
        fn_800099AC(0x240, 0, 1);
        *(s32 *)&lbl_802FFE8C = fn_8000D0A4();
    }
    *(s32 *)&lbl_802FFE90 += 1;
    return *(s32 *)&lbl_802FFE8C;
}
