// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001AE04-0x8001AE8C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 dvd_file_getcharacter(Unk_C7387A53 *);
// dvd_file_gets @ 0x8001AE04
s8 *dvd_file_gets(Unk_C7387A53 *arg0, s8 *arg1, s32 arg2) {
    s32 var_r30;
    s8 *var_r31;
    s32 var_r3;

    var_r30 = arg2;
    var_r3 = -1;
    var_r31 = arg1;
loop_1:
    var_r30 -= 1;
    if (var_r30 > 0) {
        var_r3 = dvd_file_getcharacter(arg0);
        if (var_r3 != -1) {
            *(s8 *)var_r31 = (s8)var_r3;
            var_r31 += 1;
            if ((s8)var_r3 != 0xA) {
                goto loop_1;
            }
        }
    }
    *var_r31 = 0;
    if ((var_r3 != -1) || (var_r31 != arg1)) {
        return arg1;
    }
    return NULL;
}
