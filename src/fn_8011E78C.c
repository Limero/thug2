// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E78C-0x8011E7C8 (60B). Byte-identical.
#include "types.h"
extern char lbl_80389818[];
void *fn_8011E78C(s32 arg0) {
    char *p = lbl_80389818;
    char *b = p;
    char *lim = p;
    s32 i = 0;

    do {
        if (*(s32 *)(i + (s32)b) == arg0) {
            return p;
        }
        i += 0x1008;
        p += 0x1008;
    } while ((s32)p <= (s32)lim);
    return NULL;
}
