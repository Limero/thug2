// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3A1C-0x800F3A6C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Set {
    char pad0[0x60];
} Set;
extern Set lbl_803CA080[];
extern s32 lbl_80301BB8[];
Set *fn_800F3A1C(s32 arg0) {
    Set *p = lbl_803CA080;
    s32 i;
    s32 cur;
    s32 bit;

    for (i = 0; i < 4; i++) {
        cur = lbl_80301BB8[0];
        bit = 1 << i;
        if (!(cur & bit)) {
            lbl_80301BB8[0] = cur | bit;
            return p;
        }
        p++;
    }
    return 0;
}
