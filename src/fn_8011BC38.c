// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BC38-0x8011BC60 (40B). Byte-identical.
#include "types.h"
extern char lbl_802FFE50[];
extern s32 lbl_80302C94;
s32 fn_8011BC38(void) {
    if ((s32) *(s32 *)&lbl_802FFE50 == 2) {
        return 1;
    }
    return lbl_80302C94 ^ 1;
}
