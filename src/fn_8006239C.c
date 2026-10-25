// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006239C-0x80062438 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Vt_239C {
    char pad0x00[0x38];
    s16 off;
    char pad0x3A[2];
    void (*fn)(void *, void *);
} Vt_239C;

typedef struct Obj_239C {
    char pad0x00[0x14];
    Vt_239C *vt;
} Obj_239C;

typedef struct Self_239C {
    char pad0x00[0x10];
    void *unk0x10;
} Self_239C;

typedef struct Args_239C {
    s8 a;
    s8 b;
    s8 c;
    s8 d;
} Args_239C;

typedef struct Frame_239C {
    void *volatile head;  /* +0x00 -> r1+0x08 */
    s32 pad04;            /* +0x04 -> r1+0x0C */
    void *volatile cur;   /* +0x08 -> r1+0x10 */
    s32 pad0c;            /* +0x0C -> r1+0x14 */
    Args_239C tmp;        /* +0x10 -> r1+0x18 (2nd arg of the vcall) */
    s32 pad14;            /* +0x14 -> r1+0x1C */
    volatile Args_239C args; /* +0x18 -> r1+0x20 (the four s8 params) */
    s32 pad1c;            /* +0x1C -> r1+0x24 */
} Frame_239C;

bool fn_8006239C(Self_239C *arg0, s8 arg1, s8 arg2, s8 arg3, s8 arg4) {
    Frame_239C fr;
    void *head;
    void *node;
    void *curh;
    void *cur;
    void *next;
    void *h;
    Obj_239C *obj;
    Vt_239C *vt;

    fr.args.a = arg1;
    fr.args.b = arg2;
    fr.args.c = arg3;
    fr.args.d = arg4;
    head = arg0->unk0x10;
    node = NULL;
    fr.head = head;
    if (head != NULL) node = *(void **)((char *)head + 4);
    fr.cur = node;
    if (node != head) {
        do {
            curh = fr.cur;
            obj = *(Obj_239C **)*(void **)((char *)curh + 0);
            fr.tmp = fr.args;
            vt = obj->vt;
            vt->fn((char *)obj + vt->off, &fr.tmp);
            cur = fr.cur;
            h = fr.head;
            next = *(void **)((char *)cur + 4);
            fr.cur = next;
        } while (next != h);
    }
    return true;
}
