// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800612A8-0x80061360 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_8005F0CC(s32);

s32 fn_800612A8(CStruct *arg0, s32 arg1) {
    struct {
        void *volatile slot8;
        s32 padc;
        void *volatile slot10;
    } slots;
    CStruct *temp_r9;
    CStruct *temp_r3;
    CStruct *cur_tmp;
    void *head_tmp;
    void *temp_r0;
    void *var_r0;
    s32 var_r25;
    s32 var_r10;

    temp_r9 = (CStruct *)arg0->unk0x10;
    var_r25 = (arg1 == 0xC4E78E22);
    var_r10 = 0;
    slots.slot8 = temp_r9;
    var_r0 = temp_r9 ? (void *)temp_r9->unk0x4 : NULL;
    slots.slot10 = var_r0;
    if (var_r0 != temp_r9) {
        do {
            temp_r3 = (CStruct *)((CStruct *)slots.slot10)->unk0x0;
            if (((arg1 == temp_r3->unk0x8) || (var_r25 != 0))) {
                fn_8005F0CC(temp_r3->unk0x0);
                var_r10 = 1;
            }
            cur_tmp = (CStruct *)slots.slot10;
            head_tmp = (void *)slots.slot8;
            temp_r0 = (void *)cur_tmp->unk0x4;
            slots.slot10 = temp_r0;
        } while (temp_r0 != head_tmp);
    }
    return var_r10;
}
