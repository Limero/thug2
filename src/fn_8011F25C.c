// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011F25C-0x8011F298 (60B). Byte-identical.
#include "types.h"
void fn_8011F210(s32);
// StopAllSoundFX @ 0x8011F25C
void StopAllSoundFX(void) {
    s32 var_r31;

    var_r31 = 0;
    do {
        fn_8011F210(var_r31);
        var_r31 += 1;
    } while (var_r31 <= 0x3A);
}
