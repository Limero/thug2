// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D0E4-0x8022D110 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80305FF0[];
extern char lbl_80305FE0[];
extern char lbl_80305FE8[];
void fn_8022D0E4(s32 arg0) {
    s32 idx = *(s32 *)lbl_80305FF0;
    *(s32 *)((char *)lbl_80305FE0 + (idx << 2)) = arg0;
    *(s32 *)((char *)lbl_80305FE8 + (idx << 2)) = 0;
}
