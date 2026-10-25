// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D6C8-0x8005D734 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
extern char lbl_80293924[];
s32 fn_8005D60C(s32, s32, s32, s32, s32);
s32 fn_8005529C(s32, void *);
void fn_8005D6C8(s32 arg0, s32 arg1, s32 arg2) {
    char sp8[0x200];
    char sp208[0x200];
    s32 temp_r29;

    temp_r29 = fn_8005529C(arg0, &sp8);
    sprintf(&sp208, lbl_80293924, &sp8);
    fn_8005D60C(&sp208, 0, arg1, temp_r29, arg2);
}
