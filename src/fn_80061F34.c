// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80061F34-0x80061F9C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005F098(s32);
void fn_80061F34(CStruct *arg0) {
    struct {
        void * volatile slot208;
        s32 pad20c;
        void * volatile slot210;
    } slots;
    CStruct *temp_r9_2;
    void *var_r0;
    void *temp_r0;
    CStruct *cur_tmp;
    void *head_tmp;

    temp_r9_2 = (CStruct *)arg0->unk0x10;
    var_r0 = NULL;
    slots.slot208 = temp_r9_2;
    if (temp_r9_2 != NULL) {
        var_r0 = (void *)temp_r9_2->unk0x4;
    }
    slots.slot210 = var_r0;
    if (var_r0 != temp_r9_2) {
        do {
            fn_8005F098(*(s32 *)((CStruct *)slots.slot210)->unk0x0);
            cur_tmp = (CStruct *)slots.slot210;
            head_tmp = (void *)slots.slot208;
            temp_r0 = (void *)cur_tmp->unk0x4;
            slots.slot210 = temp_r0;
        } while (temp_r0 != head_tmp);
    }
}
