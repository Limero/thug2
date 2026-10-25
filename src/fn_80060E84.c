// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060E84-0x80060F44 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* self+0x10: circular list head; self+0x48: four-bit flag group. */
typedef struct N60E84 {
    void **slot;
    struct N60E84 *next;
} N60E84;

typedef struct {
    char pad0[0x10];
    N60E84 *unk0x10;
    char pad0x14[0x34];
    u32 b31 : 1;
    u32 f30 : 1;
    u32 f29 : 1;
    u32 rest : 29;
} T60E84;

/* head at +0, cursor at +8: retail's 8(r1) / 0x10(r1) slots. */
typedef struct {
    N60E84 *head;
    char pad0[4];
    N60E84 *cur;
} W60E84;

extern void fn_8005F1F0(void *, s32);

bool fn_80060E84(T60E84 *arg0, s32 arg1) {
    W60E84 volatile w;
    N60E84 *cur;
    N60E84 *head;
    N60E84 *next;
    N60E84 *h;

    if (arg0->f29 && (arg1 != 0)) {
        return false;
    }
    if (arg0->f30 == arg1) {
        return true;
    }
    head = arg0->unk0x10;
    w.head = head;
    cur = (head != NULL) ? head->next : NULL;
    w.cur = cur;
    if (cur != head) {
        do {
            fn_8005F1F0((void *)*w.cur->slot, arg1);
            next = w.cur->next;
            h = w.head;
            w.cur = next;
        } while (next != h);
    }
    arg0->f30 = arg1;
    return true;
}
