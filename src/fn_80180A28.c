// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80180A28-0x80180A50 (40B). Byte-identical.
#include "types.h"
extern bool lbl_802A9448;
extern bool lbl_802A9438[];
s32 fn_80180A28(s32 arg0, s32 arg1) {
    if (arg1 > 4) {
        return lbl_802A9448;
    }
    return lbl_802A9438[arg1];
}
