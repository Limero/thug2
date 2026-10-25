// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801809F0-0x80180A28 (56B). Byte-identical.
#include "types.h"
extern bool lbl_802A9434;
extern bool lbl_802A9420[];
s32 fn_801809F0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        return arg1 + 1;
    }
    if (arg1 > 5) {
        return lbl_802A9434;
    }
    return lbl_802A9420[arg1];
}
