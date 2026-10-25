// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017E398-0x8017E4C8 (304B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80182F98(CStruct * arr, s32 idx);
extern s32 fn_801809F0(s32 arg0, s32 arg1, s32 arg2);
extern s32 fn_80180A28(s32 arg0, s32 arg1);

// EXACT: explicit i/end locals flip the prologue param-save order
s32 fn_8017E398(s32 arg0, s32 arg1, s32 arg2) {
    s32 end = arg2;
    s32 i = arg1;
    s32 var_r25;
    s32 var_r24;
    s32 temp_r30;
    s32 var_r30;

    var_r25 = 0;
    var_r24 = 2;
    if (i < end) {
        s32 temp_r28 = arg0 + 0x54;
        do {
            if (*(s32 *)((char *)fn_80182F98(temp_r28, i) + 0x18) & 2) {
                var_r24 = 2;
            } else if ((i == 0) || (*(s32 *)((char *)fn_80182F98(temp_r28, i - 1) + 0x18) & 2)) {
                var_r24 = fn_801809F0(arg0, *(s32 *)((char *)fn_80182F98(temp_r28, i) + 8), 0);
            }
            temp_r30 = fn_80180A28(arg0, *(s32 *)((char *)fn_80182F98(temp_r28, i) + 4));
            var_r30 = (*(s32 *)((char *)fn_80182F98(temp_r28, i) + 0) * temp_r30 * var_r24) / 200;
            if (*(s32 *)((char *)fn_80182F98(temp_r28, i) + 0x14) != 0) {
                var_r30 = (var_r30 * 0x78) / 100;
            }
            i += 1;
            var_r25 += var_r30;
        } while (i < end);
    }
    return var_r25;
}
