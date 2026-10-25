// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2140-0x801F2184 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_803A3000[];
extern char lbl_802AE2A4[];
s32 sprintf();

void *fn_801F2140(void *arg0) {
    sprintf(lbl_803A3000, (s32)lbl_802AE2A4, *(s32 *)((char *)arg0 + 0x2C0));
    return lbl_803A3000;
}
