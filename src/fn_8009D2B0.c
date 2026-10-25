// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D2B0-0x8009D2EC (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern bool lbl_80301924[];
s32 fn_8009D2B0(s32 arg0) {
    s32 i = 1;
    s32 n;
    for (n = 0x15; n != 0; n--) {
        if (lbl_80301924[i] == arg0) {
            return i;
        }
        i += 1;
    }
    return 0;
}
