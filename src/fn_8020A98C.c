// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020A98C-0x8020AA20 (148B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_8020A8FC(Unk_59E38960 * arg0, s32 arg1, s32 arg2);

void fn_8020A98C(Unk_CF8B1206 *arg0, s32 arg1) {
    char *var_r31;
    s32 var_r29;
    s32 temp_r4;

    var_r29 = 0;
    if (var_r29 < arg0->unk0x131C) {
        var_r31 = (char *)arg0 + 0x1348;
        do {
            var_r29 += 1;
            *(s32 *)var_r31 = *(s32 *)var_r31 | fn_8020A8FC(arg0, *(s32 *)(var_r31 - 0x28), arg1);
            var_r31 += 4;
        } while (var_r29 < arg0->unk0x131C);
    }
    temp_r4 = arg0->unk0x1370;
    if (temp_r4 != 0) {
        arg0->unk0x1374 = arg0->unk0x1374 | fn_8020A8FC(arg0, temp_r4, arg1);
    }
}
