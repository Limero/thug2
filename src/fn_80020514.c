// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80020514-0x80020580 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1
#include "types.h"
extern char lbl_80300284[];
void fn_80020514(s32 arg0, s32 arg1, s32 arg2) {
    void (*p)(s32, s32);
    s32 var_r31;

    var_r31 = (arg0 == 0x19) ? 1 : (arg0 - 9);
    (*(void (**)(s32, s32)) lbl_80300284)((u8) (var_r31 - 0x60), arg1 + 0x80000000);
    p = *(void (**)(s32, s32)) lbl_80300284;
    p((u8) (var_r31 - 0x50), arg2);
}
