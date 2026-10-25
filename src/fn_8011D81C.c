// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D81C-0x8011D870 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80302CA4;
extern char lbl_80302C34[];
s32 Script_GetInteger(s32, s32);
void fn_8011A8FC(s32);
void fn_8011D81C(void) {
    s32 temp_r3;

    temp_r3 = Script_GetInteger(QB_FORCEAMBIENTSFXTOMUSICVOLUME, 0);
    if ((lbl_80302CA4 == 1) && (temp_r3 == 0)) {
        fn_8011A8FC(*(s32 *)&lbl_80302C34);
        fn_801204CC();
    }
}
