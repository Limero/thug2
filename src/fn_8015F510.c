// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015F510-0x8015F5F4 (228B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80127358(CStruct *, Unk_C7387A53 *);
s32 GetStructure(s32, s32);
s32 fn_8015F510(s32 arg0, s32 arg1, s32 arg2) {
    register s32 obj __asm__("r25");
    register s32 var_r29 __asm__("r29");
    s32 *var_r31;
    s32 temp_r30;
    s32 temp_r28;
    s32 var_r3_2;

    obj = arg0;
    __asm__("" : "+r"(obj));
    if (arg2 > 0xA) {
        return 0;
    }
    var_r31 = fn_80127358(obj, NULL);
    var_r29 = 0;
    if (var_r31 != NULL) {
        do {
            temp_r30 = GetStructure(var_r31[2], 0);
            temp_r28 = (s32)fn_80127358(obj, var_r31);
            if (var_r29 == 0) {
                if ((*var_r31 & 0x7F0000) == 0xA0000) {
                    var_r3_2 = var_r31[2];
                } else if (temp_r30 != 0) {
                    var_r3_2 = temp_r30;
                } else {
                    goto skip;
                }
                var_r29 = fn_8015F510(var_r3_2, arg1, arg2 + 1);
            }
skip:
            if ((*var_r31 & 0x7F0000) == 0xD0000 && var_r31[2] == arg1) {
                var_r29 = var_r31[1];
            }
            var_r31 = (s32 *)temp_r28;
        } while (var_r31 != NULL);
    }
    return var_r29;
}
