// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024000-0x80024050 (80B). Byte-identical.
#include "types.h"
extern s32 lbl_80300368;
extern s32 lbl_8030036C;
extern s32 lbl_80300370;
extern bool lbl_80300374;
void memset(s32, s32, s32);
void fn_80024000(s32 arg0) {
    lbl_8030036C = 0;
    lbl_80300374 = 0;
    if (arg0 != 0) {
        memset(lbl_80300368, 0, lbl_80300370);
    }
}
