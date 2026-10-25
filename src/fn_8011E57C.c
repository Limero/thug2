// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E57C-0x8011E5C8 (76B). Byte-identical.
#include "types.h"
extern s32 fn_8011BC60(void);
extern s32 fn_8011BD7C(s32 arg0, s32 arg1);
u32 fn_8011E57C(s32 arg0) {
    if (fn_8011BC60() == 0) {
        return (~(u32)fn_8011BD7C(arg0, 0)) >> 0x1F;
    }
    return 0;
}
