// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E2B8-0x8011E34C (148B). Byte-identical.
#include "types.h"
extern char lbl_8038C8C0[];
extern char lbl_8038E220[];
s32 fn_8011BC38(void);
s32 fn_801209CC(void);
s32 Script_GenerateCRC(s32);
s32 fn_8011E2B8(s32 arg0, s32 arg1) {
    s32 mul;
    char *base;
    s32 h1;
    s32 t;

    if ((fn_8011BC38() == 0) && (fn_801209CC() != 1)) {
        mul = arg0 * 0xCB0;
        base = lbl_8038C8C0;
        if (arg1 < *(s32 *)(mul + (base + 0xC80))) {
            h1 = Script_GenerateCRC(lbl_8038E220);
            t = h1 ^ Script_GenerateCRC(mul + ((s32)base + arg1 * 0x28));
            return t == 0;
        }
    }
    return 0;
}
