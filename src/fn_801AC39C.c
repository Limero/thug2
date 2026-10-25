// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AC39C-0x801AC3E8 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *lbl_80305FF8;
extern void fn_801ABDB0(void);
void fn_801AC39C(void) {
    s32 temp_r0;
    s32 var_r11;

    var_r11 = 1;
    temp_r0 = ((Unk_C7387A53 *)lbl_80305FF8)->unk0x44;
    if (temp_r0 == -QB_UNKNOWN_0x2BBC5D44) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        fn_801ABDB0();
    }
}
