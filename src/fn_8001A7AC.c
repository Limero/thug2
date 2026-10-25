// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001A7AC-0x8001A7F0 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 DVDGetDriveStatus(void);
void fn_8001A788(void);
// DVDCheckAsync @ 0x8001A7AC
s32 DVDCheckAsync(void) {
    s32 st;
    st = DVDGetDriveStatus();
    if (st != 0) {
        if (st != 1) {
            if (st != 0xA) {
                if (st != 8) {
                    fn_8001A788();
                }
            }
        }
    }
}
