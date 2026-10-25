// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E7C8-0x8011E824 (92B). Byte-identical.
#include "types.h"
extern char lbl_80389818[];
extern s32 fn_8011E6C4(s32 * arg0);
void *fn_8011E7C8(s32 arg0) {
    char *p = lbl_80389818;
    char *b = p;
    char *lim = p;
    s32 i = 0;

    do {
        if (*(s32 *)(i + (s32)b) != arg0) {
            i += 0x1008;
            p += 0x1008;
            continue;
        }
        return (void *)fn_8011E6C4(p);
    } while ((s32)p <= (s32)lim);
    return NULL;
}
