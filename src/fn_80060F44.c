// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060F44-0x80060FA8 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80060F44(CStruct *arg0, s32 arg1) {
    struct { void * slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head;
    CStruct *obj;
    CStruct *cur;
    void *node;
    void *next;

    head = (CStruct *)arg0->unk0x10;
    node = NULL;
    slots.slot208 = head;
    if (head != NULL) node = (void *)head->unk0x4;
    slots.slot210 = node;
    if (node != head) {
        do {
            cur = (CStruct *)slots.slot210;
            obj = *(CStruct **)cur;
            if (arg1 == (s32)obj->unk0x8) return (s32)obj->unk0x0;
            next = (void *)cur->unk0x4;
            slots.slot210 = next;
        } while (next != (void *)slots.slot208);
    }
    return 0;
}
