// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C81C-0x8016C890 (116B). Byte-identical.
#include "types.h"
extern char lbl_802A8AEC[];
extern char lbl_802A8AFC[];
extern bool lbl_80305E94;
void fn_8016A67C(s32, s32);
bool fn_8016C81C(s32 *arg0) {
    s32 temp_r31;

    temp_r31 = *arg0;
    if ((strcmp(lbl_802A8AEC, (const char *)temp_r31) == 0) || (strcmp(lbl_802A8AFC, (const char *)temp_r31) == 0)) {
        lbl_80305E94 = 1;
    }
    fn_8016A67C(temp_r31, 0);
    return true;
}
