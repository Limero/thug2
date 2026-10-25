// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134A44-0x80134B00 (188B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_80134A44(CStruct *arg0, s32 *arg1) {
    Unk_9994C3F5 *temp_r11;
    CStruct *temp_r9;
    s32 temp_r0;
    s32 var_r0;
    s32 var_limit;

    temp_r11 = *((void * *)&arg0->unk0x10);
    var_limit = 1 << arg0->unk0x0;
    if (temp_r11 == NULL) {
        if ((s32)(arg0->unk0xC) >= 0) {
            var_r0 = 0;
            goto block_14;
        }
    } else {
        *((void * *)&arg0->unk0x10) = *((void * *)&temp_r11->unk0x8);
    }
    if (*((void * *)&arg0->unk0x10) != NULL) {
        var_r0 = 1;
    } else {
        do {
            temp_r0 = arg0->unk0xC + 1;
            arg0->unk0xC = temp_r0;
            if (temp_r0 >= var_limit) {
                var_r0 = 0;
                goto block_14;
            }
            temp_r9 = (char *)arg0->unk0x4 + (temp_r0 * 12);
            *((void * *)&arg0->unk0x10) = temp_r9;
            if (temp_r9->unk0x4 != 0) {
                var_r0 = 1;
                goto block_12;
            }
        } while (*((void * *)&temp_r9->unk0x8) == NULL);
        *((void * *)&arg0->unk0x10) = *((void * *)&temp_r9->unk0x8);
block_12:
        var_r0 = 1;
    }
block_14:
    if (var_r0 == 0) {
        return 0;
    }
    temp_r9 = *((void * *)&arg0->unk0x10);
    if (temp_r9 == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *arg1 = *(s32 *)temp_r9;
    }
    return *(s32 *)((char *)*((void * *)&arg0->unk0x10) + (s32)0x4);
}
