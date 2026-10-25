// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80252C3C-0x80252C90 (84B). Byte-identical.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"
void fn_80252E74(void *);
void fn_8025302C(s32, s32);
extern s32 lbl_803CA348;
void fn_80252C3C(s32 arg0, s32 arg1) {
    fn_80252E74(arg0);
    fn_8025302C(arg0 + 4, 2);
    if (arg1 & 1) {
        ((s32 (*)(s32))*(s32 *)&lbl_803CA348)(arg0);
    }
}
