// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062438-0x800624AC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005F1BC(s32);
s32 fn_80062438(CStruct *arg0) {
    struct { void * volatile slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head, *curA;
    void *next;
    register s32 curB __asm__("r11");
    s32 acc;
    acc = 0;
    head = (CStruct *)arg0->unk0x10;
    next = NULL;
    slots.slot208 = head;
    if (head != NULL) next = (void *)head->unk0x4;
    goto test;
loop:
    curA = (CStruct *)slots.slot210;
    acc |= fn_8005F1BC(*(s32 *)curA->unk0x0);
    curB = (s32)slots.slot210;
    head = (CStruct *)slots.slot208;
    next = (void *)(*(s32 *)((char *)curB + 4));
test:
    slots.slot210 = next;
    if (next != (void *)head) goto loop;
    return acc;
}
