// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206E7C-0x80206EA4 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80206E7C(Unk_76553646 *arg0) {
    char *var_r9;
    s32 var_ctr;

    var_ctr = 0xA;
    arg0->unk0x12AC = 0;
    arg0->unk0x127C = 0;
    var_r9 = (char *)arg0 + 0x12A4;
    do {
        *(s32 *)var_r9 = 0;
        var_r9 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
