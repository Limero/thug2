// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022AE98-0x8022AF44 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Linked-list traversal: iterates the list rooted at lbl_802B03E0
// (via the local stack-head idiom shared with fn_8022AF44) and writes a
// running index z into offset +0xA0 of each node, stopping at the list tail.
// Suggested rename: ListWriteOrderIndices / AssignNodeIndices.
#include "types.h"
#include "structs.h"
extern char lbl_802B03E0[];

struct LS { s32 pad; volatile s32 iter; void *hc; };

void fn_8022AE98(void *arg0) {
    struct LS ls;
    register char *ha __asm__("r11");
    register struct LS *p __asm__("r9");
    register struct LS *q __asm__("r8");
    register struct LS *r2 __asm__("r10");
    char *itv;
    register char *itv1 __asm__("r9");
    register void *n __asm__("r11");
    Unk_C7387A53 *cur;
    register s32 z __asm__("r7");

    __asm__ __volatile__("lis %0,%1@ha" : "=r"(ha) : "s"(lbl_802B03E0));
    p = &ls;
    __asm__ __volatile__("");
    itv = (char *)arg0 + 0x178;
    __asm__ __volatile__("addi %0,%0,%1@l" : "+b"(ha) : "s"(lbl_802B03E0));
    p->hc = (void *)ha;
    __asm__ __volatile__("mr %0,%1" : "=r"(q) : "r"(p));
    p->iter = (s32)itv;
    n = ((Unk_E266FB50_2 *)itv)->unk0xC;
    if (((CStruct *)n)->unk0x4 == -1) {
        n = NULL;
    }
    q->iter = (s32)n;
    if (n == NULL) {
        __asm__ __volatile__("li %0,0" : "=r"(n));
    } else {
        __asm__ __volatile__("lwz %0,4(%0)" : "+b"(n));
    }
    cur = n;
    if (cur == NULL) {
        goto done;
    }
    z = 0;
    __asm__ __volatile__("mr %0,%1" : "=r"(r2) : "r"(q));
    for (;;) {
        cur->unk0xA0 = z;
        itv1 = (char *)(r2->iter);
        n = ((Unk_E266FB50_2 *)itv1)->unk0xC;
        if (((CStruct *)n)->unk0x4 == -1) {
            n = NULL;
        }
        q->iter = (s32)n;
        if (n == NULL) {
            __asm__ __volatile__("li %0,0" : "=r"(n));
        } else {
            __asm__ __volatile__("lwz %0,4(%0)" : "+b"(n));
        }
        if (n == NULL) {
            break;
        }
        cur = n;
    }
done:
    q->hc = &lbl_802B03E0;
}
