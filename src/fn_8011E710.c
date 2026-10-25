// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E710-0x8011E78C (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80389818[];
extern s32 fn_8011E620(CStruct * arg0, s32 arg1);
s32 *fn_8011E710(s32 arg0) {
    char *p = lbl_80389818;
    char *lim = p;
    s32 flag;
    s32 *result;

    do {
        flag = 1;
        if (*(s32 *)p == 0) {
            flag = 0;
        }
        if (flag != 0) {
            p += 0x1008;
            continue;
        }
        if (fn_8011E620(p, arg0) != 0) {
            result = p;
        } else {
            result = NULL;
        }
        return result;
    } while ((s32)p <= (s32)lim);
    return NULL;
}
