// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126698-0x801266EC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80126620(void);
int sprintf(char *, const char *, ...);
extern char lbl_8039C2C0[];
extern char lbl_8029E5B8[];
s32 fn_80126698(s32 arg0) {
    s32 var_r3;

    var_r3 = fn_80126620();
    if (var_r3 == 0) {
        sprintf(lbl_8039C2C0, lbl_8029E5B8, arg0);
        var_r3 = (s32)lbl_8039C2C0;
    }
    return var_r3;
}
