// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124E70-0x80124EC4 (84B). Byte-identical.
#include "types.h"
extern f32 lbl_8029E428;
extern f32 lbl_80303158;
float fn_800144D4(void);
void fn_80124F00(void);
void fn_80124E70(s32 arg0) {
    fn_80124F00();
    if (arg0 != 0) {
        lbl_80303158 = lbl_8029E428;
        return;
    }
    lbl_80303158 = fn_800144D4();
}
