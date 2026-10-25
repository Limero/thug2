// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80061EC0-0x80061F2C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80061EC0(CStruct *arg0, s32 arg1) {
    struct { void * slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head;
    CStruct *obj;
    CStruct *cur;
    void *node;
    void *next;
    s32 i;

    head = (CStruct *)arg0->unk0x10;
    i = 0;
    node = NULL;
    slots.slot208 = head;
    if (head != NULL) node = (void *)head->unk0x4;
    slots.slot210 = node;
    if (node != head) {
        do {
            if (arg1 == i) {
                obj = *(CStruct **)(CStruct *)slots.slot210;
                return (s32)obj->unk0x4;
            }
            cur = (CStruct *)slots.slot210;
            i++;
            next = (void *)cur->unk0x4;
            slots.slot210 = next;
        } while (next != (void *)slots.slot208);
    }
    return 0;
}
