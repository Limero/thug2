// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062250-0x8006230C (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80062250(CStruct *arg0, s32 arg1, s32 arg2) {
    struct {
        void * slot208;
        s32 pad20c;
        void * slot210;
    } slots;
    CStruct *temp_r9_2;
    void *var_r0;
    void *temp_r0;
    CStruct *cur_tmp;
    void *head_tmp;
    CStruct *temp_r3;
    s32 var_r7;
    s16 var_r10;
    s32 var_r25;

    var_r7 = 0;
    var_r25 = (arg1 == 0xC4E78E22);
    var_r10 = 0;
    temp_r9_2 = (CStruct *)arg0->unk0x10;
    slots.slot208 = temp_r9_2;
    if (temp_r9_2 != NULL) {
        var_r0 = (void *)temp_r9_2->unk0x4;
    } else {
        var_r0 = NULL;
    }
    slots.slot210 = var_r0;
    if (var_r0 != temp_r9_2) {
        do {
            temp_r3 = (CStruct *)((CStruct *)slots.slot210)->unk0x0;
            if ((arg1 == temp_r3->unk0x8) || (var_r25 != 0)) {
                if (arg2 != 0) {
                    *(s32 *)((char *)arg0 + 0x18) &= ~(1 << var_r10);
                } else {
                    *(s32 *)((char *)arg0 + 0x18) |= 1 << var_r10;
                }
                var_r7 = 1;
            }
            cur_tmp = (CStruct *)slots.slot210;
            head_tmp = (void *)slots.slot208;
            temp_r0 = (void *)cur_tmp->unk0x4;
            slots.slot210 = temp_r0;
            var_r10 += 1;
        } while (temp_r0 != head_tmp);
    }
    return var_r7;
}
