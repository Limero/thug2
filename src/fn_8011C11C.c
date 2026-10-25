// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C11C-0x8011C164 (72B). Byte-identical.
#include "types.h"
s32 fn_8011BC38(void);
f32 fn_801204CC(f32);
bool fn_8011C11C(f32 farg0) {
    volatile double _dummy;

    if (fn_8011BC38() != 0) {
        return false;
    }
    fn_801204CC(farg0);
    return true;
}
