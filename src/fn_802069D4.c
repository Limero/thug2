// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802069D4-0x80206A78 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
bool fn_802069D4(s32 arg0) {
    if (arg0 != QB_UPRIGHT) {
        if ((u32)arg0 <= QB_UPRIGHT) {
            if (arg0 != QB_DOWNRIGHT) {
                if ((u32)arg0 <= QB_DOWNRIGHT) {
                    if (arg0 == QB_RIGHT) goto yes;
                } else {
                    if (arg0 == QB_LEFT) goto yes;
                }
                goto no;
            }
            goto yes;
        }
        if (arg0 != QB_UP) {
            if ((u32)arg0 <= QB_UP) {
                if (arg0 == QB_UPLEFT) goto yes;
                goto no;
            }
            if (arg0 == QB_DOWNLEFT) goto yes;
            if (arg0 == QB_DOWN) goto yes;
            goto no;
        }
        goto yes;
    }
yes:
    return true;
no:
    return false;
}
