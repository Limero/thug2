// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022AF44-0x8022B000 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Linked-list traversal: iterates the list rooted at lbl_802B03E0
// (local stack-head idiom, sibling of fn_8022AE98) and counts nodes whose
// +0x9C flag is nonzero, returning the total.
// Suggested rename: ListCountActiveNodes / CountActiveEntries.
#include "types.h"
#include "structs.h"
extern char lbl_802B03E0[];

struct LS { s32 pad; volatile s32 iter; void *hc; };

s32 fn_8022AF44(void *arg0) {
    struct LS ls;
    register char *ha __asm__("r11");
    register struct LS *p __asm__("r9");
    register struct LS *q __asm__("r7");
    register struct LS *r2 __asm__("r8");
    char *itv;
    register char *itv1 __asm__("r9");
    register s32 count __asm__("r10");
    register void *cur __asm__("r11");
    register void *h2 __asm__("r11");
    register void *h __asm__("r9");
    s32 ret;

    __asm__ __volatile__("lis %0,%1@ha" : "=r"(ha) : "s"(lbl_802B03E0));
    p = &ls;
    __asm__ __volatile__("");
    itv = (char *)arg0 + 0x178;
    __asm__ __volatile__("addi %0,%0,%1@l" : "+b"(ha) : "s"(lbl_802B03E0));
    p->hc = (void *)ha;
    __asm__ __volatile__("mr %0,%1" : "=r"(q) : "r"(p));
    p->iter = (s32)itv;
    count = 0;
    h = ((Unk_E266FB50_2 *)itv)->unk0xC;
    if (((CStruct *)h)->unk0x4 == -1) {
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
        goto done;
    }
    __asm__ __volatile__("mr %0,%1" : "=r"(r2) : "r"(q));
    for (;;) {
        if (((Unk_FFAD6788 *)cur)->unk0x9C != 0) {
            count += 1;
        }
        itv1 = (char *)(r2->iter);
        h2 = ((Unk_E266FB50_2 *)itv1)->unk0xC;
        if (((CStruct *)h2)->unk0x4 == -1) {
            h2 = NULL;
        }
        q->iter = (s32)h2;
        if (h2 == NULL) {
            __asm__ __volatile__("li %0,0" : "=r"(h2));
        } else {
            __asm__ __volatile__("lwz %0,4(%0)" : "+b"(h2));
        }
        if (h2 == NULL) {
            break;
        }
        cur = h2;
    }
done:
    q->hc = (ret = count, (void *)&lbl_802B03E0);
    return ret;
}
