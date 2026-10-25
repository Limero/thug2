// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E844-0x8011E8A4 (96B). Byte-identical.
#include "types.h"
extern char lbl_80389818[];
extern s32 fn_8011E5E0(char *arg0);
void fn_8011E844(s32 arg0, s32 arg1) {
    char *p;
    u32 n;

    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            p = lbl_80389818;
            n = 0;
            do {
                fn_8011E5E0(p);
                p += 0x1008;
            } while (n-- != 0);
        }
    }
}
