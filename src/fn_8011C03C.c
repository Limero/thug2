// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011C03C-0x8011C0A8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8011BC60(void);
s32 fn_8011BD7C(s32, s32);
void fn_801210B4(s32, f32);
bool fn_8011C03C(s32 arg0, f32 farg0) {
    volatile double _dummy;
    register s32 r __asm__("r3");
    if (fn_8011BC60() != 0) {
        return true;
    }
    r = fn_8011BD7C(arg0, 1);
    if (r >= 0) {
        fn_801210B4(r, farg0);
        return true;
    }
    return false;
}
