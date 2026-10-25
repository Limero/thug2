// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011CA08-0x8011CA60 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 fn_8011BC38(void);
extern void fn_80120924(s32 arg0);
extern s32 fn_8011C390(s32 arg0);
extern s32 lbl_80302CD0;
s32 fn_8011CA08(s32 arg0) {
    s32 var_r3;

    if (fn_8011BC38() != 0) {
        return 0;
    }
    fn_80120924(0);
    var_r3 = fn_8011C390(arg0);
    if (var_r3 != 0) {
        lbl_80302CD0 = 2;
    }
    return var_r3;
}
