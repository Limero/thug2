// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E3E4-0x8007E45C (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005F2D0(s32, s32);
void fn_8007E3E4(CStruct *arg0, s32 arg1) {
    struct { void * volatile slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head;
    void *node;
    void *temp_r0;
    CStruct *cur;
    CStruct *curA;
    CStruct *curB;
    CStruct *hd;
    void *next;

    head = (CStruct *)arg0->unk0x10;
    node = NULL;
    slots.slot208 = head;
    if (head != NULL) node = (void *)head->unk0x4;
    slots.slot210 = node;
    if (node != head) {
        do {
            curA = (CStruct *)slots.slot210;
            fn_8005F2D0(*(s32 *)curA->unk0x0, arg1);
            curB = (CStruct *)slots.slot210;
            hd = (CStruct *)slots.slot208;
            next = (void *)curB->unk0x4;
            slots.slot210 = next;
        } while (next != (void *)hd);
    }
}
