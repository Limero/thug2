// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006150C-0x800615D0 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_8005F844(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);

typedef struct Node6150C {
    s32 *unk0x0;
    struct Node6150C *unk0x4;
} Node6150C;

typedef struct {
    char pad0[0x10];
    Node6150C *unk0x10;
} O6150C;

s32 fn_8006150C(O6150C *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    /* Frame template: the two walk pointers are kept in stack slots so the
       allocator leaves r29/r30/r31 to arg1/arg2/acc, exactly as want does. */
    struct {
        void *volatile slot0; /* -> r1+0x8  (head) */
        s32 pad4;              /* -> r1+0xc  (keeps slot8 at +8) */
        void *volatile slot8;  /* -> r1+0x10 (cur)  */
    } slots;
    volatile double _d1; /* FPR frame quirk: 2 saved FPRs -> +0x10 */
    volatile double _d2;
    Node6150C *head;
    void *node;
    void *next;
    s32 acc;
    s32 r;
    Node6150C *curA;
    Node6150C *curB;
    Node6150C *hd;

    acc = 0;
    head = arg0->unk0x10;
    slots.slot0 = head;
    if (head != NULL) { node = (void *)head->unk0x4; } else { node = NULL; }
    slots.slot8 = node;
    if (node != head) {
        do {
            curA = (Node6150C *)slots.slot8;
            r = fn_8005F844(*curA->unk0x0, arg1, arg2, farg0, farg1);
            acc = (acc ? 1 : 0) | (r ? 1 : 0);
            curB = (Node6150C *)slots.slot8;
            hd = (Node6150C *)slots.slot0;
            next = (void *)curB->unk0x4;
            slots.slot8 = next;
        } while (next != (void *)hd);
    }
    return acc;
}
