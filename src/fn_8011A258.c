// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A258-0x8011A2AC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8011A238(s32);
s32 fn_8011A150(s32, s32);
void fn_8011A258(s32 arg0) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < fn_8011A238(arg0); var_r31++) {
        fn_8011A150(arg0, var_r31);
    }
    fn_8011EF10();
}
