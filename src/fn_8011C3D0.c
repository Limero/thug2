// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C3D0-0x8011C418 (72B). Byte-identical.
#include "types.h"
s32 fn_801213FC(void);
f32 fn_801204CC(f32);
bool fn_8011C3D0(f32 farg0) {
    volatile double _dummy;

    if (fn_801213FC() == 0) {
        return false;
    }
    fn_801204CC(farg0);
    return true;
}
