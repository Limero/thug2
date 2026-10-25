// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E34C-0x8011E39C (80B). Byte-identical.
#include "types.h"
extern char lbl_8038C8C0[];
s32 fn_8011BC38(void);
s32 fn_8011E34C(s32 arg0) {
    s32 mul;
    char *base;

    if (fn_8011BC38() != 0) {
        return 0;
    }
    mul = arg0 * 0xCB0;
    base = lbl_8038C8C0;
    __asm__("" : "+r"(base));
    return *(s32 *)(mul + (base + 0xC80));
}
