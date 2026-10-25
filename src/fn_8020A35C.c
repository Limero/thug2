// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A35C-0x8020A384 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8020A35C(Unk_13928190 *arg0) {
    char *var_r9;
    s32 var_ctr;

    var_ctr = 0xA;
    arg0->unk0x12F4 = 0;
    arg0->unk0x12C4 = 0;
    var_r9 = (char *)arg0 + 0x12EC;
    do {
        *(s32 *)var_r9 = 0;
        var_r9 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
