// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A724-0x8020A7A8 (132B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_8020A604(Unk_D386C1E6 * arg0, s32 arg1, s32 arg2);

void fn_8020A724(Unk_90685748 *arg0) {
    char *var_r31;
    s32 var_r29;
    s32 temp_r4;

    temp_r4 = arg0->unk0x12F0;
    if ((temp_r4 != 0) && (*(s32 *)(arg0->unk0x20 + (s32)0x80) != 0)) {
        fn_8020A604(arg0, temp_r4, 1);
    }
    var_r29 = 0;
    if (var_r29 < arg0->unk0x12C4) {
        var_r31 = (char *)arg0 + 0x12C8;
        do {
            var_r29 += 1;
            fn_8020A604(arg0, *(s32 *)var_r31, 0);
            var_r31 += 4;
        } while (var_r29 < arg0->unk0x12C4);
    }
}
