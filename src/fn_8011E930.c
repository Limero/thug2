// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E930-0x8011E96C (60B). Byte-identical.
#include "types.h"
extern char lbl_8038EBB8[];
void fn_8011E930(s32 arg0) {
    char *base = lbl_8038EBB8;
    s32 n = 0x3B;
    s32 z = 0;
    s32 i = 0;
    s32 v;

    do {
        v = *(s32 *)(i + (s32)base);
        if (v != 0) {
            if (v == arg0) {
                *(s32 *)(i + (s32)base) = z;
            }
        }
        i += 8;
    } while (--n != 0);
}
