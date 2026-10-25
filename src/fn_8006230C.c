// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006230C-0x80062394 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct Obj_t {
    char pad0x0[0x10];
    void *unk0x10;
    char pad0x14[0x4];
    s32 unk0x18;
} Obj_t;

s32 fn_8006230C(Obj_t *arg0, s32 arg1) {
    struct { void *slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head;
    CStruct *cur;
    CStruct *pay;
    CStruct *step;
    void *node;
    void *next;
    s16 i;
    s32 result;
    s32 one;
    s32 mask;

    head = (CStruct *)arg0->unk0x10;
    result = 1;
    i = 0;
    node = NULL;
    slots.slot208 = head;
    if (head != NULL) node = (void *)head->unk0x4;
    slots.slot210 = node;
    if (node != head) {
        one = 1;
        do {
            cur = (CStruct *)slots.slot210;
            pay = *(CStruct **)cur;
            step = cur;
            __asm__("" : "+r"(step));
            if (arg1 == pay->unk0x8) {
                mask = one << i;
                if ((arg0->unk0x18 & mask) != 0) {
                    result = 0;
                }
            }
            i = (s16)(i + 1);
            next = (void *)step->unk0x4;
            slots.slot210 = next;
        } while (next != (void *)slots.slot208);
    }
    return result;
}
