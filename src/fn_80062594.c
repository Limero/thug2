// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062594-0x80062618 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005F51C(s32, s32);
struct BF48 { u32 f0 : 4; u32 f4 : 1; u32 f5 : 27; };
void fn_80062594(CStruct *arg0, s32 arg1) {
    struct { void * volatile slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head;
    CStruct *cur;
    CStruct *curA;
    CStruct *curB;
    CStruct *hd;
    void *node;
    void *next;

    head = (CStruct *)arg0->unk0x10;
    node = NULL;
    slots.slot208 = head;
    ((struct BF48 *)&arg0->unk0x48)->f4 = arg1;
    if (head != NULL) node = (void *)head->unk0x4;
    slots.slot210 = node;
    if (node != head) {
        do {
            curA = (CStruct *)slots.slot210;
            fn_8005F51C(*(s32 *)curA->unk0x0, arg1);
            curB = (CStruct *)slots.slot210;
            hd = (CStruct *)slots.slot208;
            next = (void *)curB->unk0x4;
            slots.slot210 = next;
        } while (next != (void *)hd);
    }
}
