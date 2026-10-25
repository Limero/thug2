// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BD7C-0x8011BE24 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8038A820[];
extern s32 fn_80121448(s32);
s32 fn_8011BD7C(s32 arg0, s32 arg1) {
    register char *var_r30 __asm__("r30");
    s32 var_r31;

    register char *tbl __asm__("r9");

    tbl = lbl_8038A820;
    var_r31 = 0;
    var_r30 = tbl + 0x10;
    do {
        if (*(s32 *)(var_r30 - 0xC) == arg0) {
            if (fn_80121448(*(s32 *)var_r30) != 1) {
                return var_r31;
            }
        }
        var_r31 += 1;
        var_r30 += 0x74;
    } while (var_r31 <= 2);

    {
        s32 i;
        char *p;
        p = (char *)lbl_8038A820;
        for (i = 0; i <= 2; i++, p += 0x74) {
            if ((*(s32 *)p == arg0) && (fn_80121448(*(s32 *)(p + 0x10)) != 1)) {
                return i;
            }
        }
    }
    return -1;
}
