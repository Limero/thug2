// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230B18-0x80230BA4 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802309C8(s32, s32, s32 *, s32 *);
bool fn_80230B18(s32 arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 var_r9;
    char *var_r3;
    s32 var_r11;

    sp8 = 0;
    spC = 0;
    fn_802309C8(arg0, arg1, &sp8, &spC);
    var_r9 = sp8;
    var_r11 = spC;
    if (var_r9 <= var_r11) {
        var_r3 = (char *)((var_r9 * 0x28) + arg0);
        do {
            if (((Unk_74BF3C95 *)var_r3)->unk0xBC == 0) {
                return true;
            }
            if (((Unk_74BF3C95 *)var_r3)->unk0xC0 == 0) {
                goto next_iter;
            }
            return true;
        next_iter:
            var_r9 += 1;
            var_r3 += 0x28;
        } while (var_r9 <= var_r11);
    }
    return false;
}
