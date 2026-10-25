// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80204748-0x80204774 (44B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305FF8[];
void fn_80204748(Unk_C7387A53 *arg0) {
    s32 var_r11;

    var_r11 = 1;
    if ((s32) *(s32 *)((s32 *)((char *)(*(void * *)&lbl_80305FF8) + (s32)0x44)) == -QB_UNKNOWN_0x2BBC5D44) {
        var_r11 = 0;
    }
    arg0->unk0x2C = var_r11;
}
