// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B5D0-0x8022B75C (396B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802B03E0[];
extern s32 strcasecmp(s32 arg0, s32 arg1);

struct LS { s32 pad; volatile s32 iter; void *hc; };

bool fn_8022B5D0(s32 arg0, s32 arg1, s32 arg2) {
    struct LS ls;
    struct LS *p;
    register struct LS *q __asm__("r31");
    register s32 a0 __asm__("r28");
    register s32 a1 __asm__("r29");
    register s32 a2 __asm__("r30");
    register char *itv __asm__("r10");
    register char *itv2 __asm__("r9");
    Unk_C7387A53 *cur;
    register void *k __asm__("r3");
    CStruct *h;
    register void *h2 __asm__("r11");
    register void *h3 __asm__("r11");
    Unk_C7387A53 *hh;

    __asm__ __volatile__("mr %0,%1" : "=r"(a0) : "r"(arg0));
    p = &ls;
    p->hc = &lbl_802B03E0;
    itv = (char *)a0 + 0x178;
    p->iter = (s32)itv;
    __asm__ __volatile__("mr %0,%1" : "=r"(q) : "r"(p));
    __asm__ __volatile__("mr %0,%1" : "=r"(a1) : "r"(arg1));
    __asm__ __volatile__("mr %0,%1" : "=r"(a2) : "r"(arg2));
    h = *((void * *)&((Unk_C7387A53 *)itv)->unk0xC);
    if (h->unk0x4 == -1) {
        h = NULL;
    }
    q->iter = (s32)h;
    if (h == NULL) {
        __asm__ __volatile__("li %0,0" : "=r"(h));
    } else {
        __asm__ __volatile__("lwz %0,4(%0)" : "+b"(h));
    }
    cur = h;
    if (cur == NULL) {
        goto list2;
    }
    for (;;) {
        if (cur->unk0x28 == a2) {
            if (strcasecmp((s32)((char *)cur + 0x18), a1) == 0) {
                goto found1;
            }
        }
        hh = *((void * *)&((CStruct *)q)->unk0x4);
        h2 = *((void * *)&hh->unk0xC);
        if (((CStruct *)h2)->unk0x4 == -1) {
            h2 = NULL;
        }
        q->iter = (s32)h2;
        cur = (h2 != NULL) ? *((void * *)&((CStruct *)h2)->unk0x4) : NULL;
        if (cur != NULL) {
            continue;
        }
        break;
    }
list2:
    itv2 = (char *)a0 + 0x190;
    q->iter = (s32)itv2;
    h3 = *((void * *)&((Unk_C7387A53 *)itv2)->unk0xC);
    if (((CStruct *)h3)->unk0x4 == -1) {
        __asm__ __volatile__("li %0,0" : "=r"(h3));
    }
    q->iter = (s32)h3;
    if (h3 != NULL) {
        goto h3load;
    }
    __asm__ __volatile__("li %0,0" : "=r"(k));
    goto checknext;
found1:
    q->hc = &lbl_802B03E0;
    return true;
found2:
    q->hc = &lbl_802B03E0;
    return true;
h3load:
    __asm__ __volatile__("lwz %0,4(%1)" : "=r"(k) : "b"(h3));
checknext:
    cur = k;
    if (cur == NULL) {
        goto notfound;
    }
    for (;;) {
        if (cur->unk0x28 == a2) {
            if (strcasecmp((s32)((char *)cur + 0x18), a1) == 0) {
                goto found2;
            }
        }
        hh = *((void * *)&((CStruct *)q)->unk0x4);
        h2 = *((void * *)&hh->unk0xC);
        if (((CStruct *)h2)->unk0x4 == -1) {
            h2 = NULL;
        }
        q->iter = (s32)h2;
        cur = (h2 != NULL) ? *((void * *)&((CStruct *)h2)->unk0x4) : NULL;
        if (cur != NULL) {
            continue;
        }
        break;
    }
notfound:
    q->hc = &lbl_802B03E0;
    return false;
}
