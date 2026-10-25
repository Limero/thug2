// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183A94-0x80183B28 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80183A94(Unk_C7387A53 *);
s32 fn_801840F0(Unk_C7387A53 *, void *);
s32 fn_8018EC90(void);
s32 fn_80183A94(Unk_C7387A53 *arg0) {
    s32 temp_r31;
    s32 var_r29;
    s32 var_r30;
    CStruct *var_r9;

    var_r29 = 0;
    var_r9 = arg0->unk0x2C;
    while (1) {
        if ((s32) var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
        if (var_r9 == NULL) {
            break;
        }
        var_r9 = var_r9->unk0xC;
        var_r29 += 1;
    }
    var_r30 = 0;
    while (var_r30 < var_r29) {
        temp_r31 = fn_801840F0(arg0, var_r30);
        if (fn_8018EC90() != 0) {
            return temp_r31;
        }
        var_r30 += 1;
    }
    return 0;
}
