// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0C3C-0x800B0CF8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800B0C3C(CStruct *arg0, s32 *arg1) {
    s32 var_r10;
    s32 temp_r0;
    Unk_9994C3F5 *temp_r11;
    Unk_4C649A8C *temp_r9;
    s32 var_r0;

    temp_r11 = *((void * *)&arg0->unk0x10);
    var_r10 = 1 << arg0->unk0x0;
    if (temp_r11 == NULL) {
        if (arg0->unk0xC >= 0) {
            var_r0 = 0;
            goto tail;
        }
    } else {
        *((void * *)&arg0->unk0x10) = *((void * *)&temp_r11->unk0x8);
    }
    if (*((void * *)&arg0->unk0x10) != NULL) {
        var_r0 = 1;
        goto tail;
    }
    do {
        temp_r0 = arg0->unk0xC + 1;
        arg0->unk0xC = temp_r0;
        if (temp_r0 >= var_r10) {
            var_r0 = 0;
            goto tail;
        }
        temp_r9 = (char *)*((void * *)&arg0->unk0x4) + (temp_r0 * 12);
        *((void * *)&arg0->unk0x10) = temp_r9;
        if (temp_r9->unk0x4 != 0) {
            var_r0 = 1;
            goto tail;
        }
    } while (((Unk_42076946_3 *)temp_r9)->unk0x8 == NULL);
    *((void * *)&arg0->unk0x10) = ((Unk_42076946_3 *)temp_r9)->unk0x8;
    var_r0 = 1;
tail:
    if (var_r0 == 0) {
        return 0;
    }
    if (*((void * *)&arg0->unk0x10) == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *arg1 = *(s32 *)*((void * *)&arg0->unk0x10);
    }
    return *(s32 *)(*((void * *)&arg0->unk0x10) + 4);
}
