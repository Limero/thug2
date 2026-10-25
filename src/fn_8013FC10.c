// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013FC10-0x8013FD78 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8029F3E0[];
extern char lbl_8029F3C8[];

typedef struct LS { s32 pad; volatile s32 iter; s32 hc; s32 pad2; } LS;
typedef struct Node {
    s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; s32 f1C; s32 f20;
} Node;

void fn_8013FC10(void *arg0, s32 arg1) {
    LS d1;
    LS d2;
    register s32 a1 __asm__("r9");
    register s32 a2 __asm__("r11");
    register s32 pbs __asm__("r10");
    register LS *q __asm__("r7");
    s32 z;
    void *base;
    register void *n1 __asm__("r9");
    register void *it __asm__("r11");
    register void *c1 __asm__("r9");
    register void *n2 __asm__("r11");
    register LS *pb1 __asm__("r10");
    register s32 z1 __asm__("r8");
    register void *b1 __asm__("r9");
    register void *b2 __asm__("r11");
    register void *b3 __asm__("r9");
    register void *it2 __asm__("r11");
    register void *c2 __asm__("r9");
    register void *n3 __asm__("r11");
    register s32 z2 __asm__("r10");

    __asm__ volatile ("lis %0,%1@ha" : "=r"(a1) : "s"(lbl_8029F3E0));
    pbs = (s32)&d1;
    z = 0;
    __asm__ volatile ("addi %0,%0,%1@l" : "+b"(a1) : "s"(lbl_8029F3E0));
    __asm__ volatile ("lis %0,%1@ha" : "=r"(a2) : "s"(lbl_8029F3C8));
    ((LS *)pbs)->hc = a1;
    ((LS *)pbs)->iter = z;
    __asm__ volatile ("addi %0,%0,%1@l" : "+b"(a2) : "s"(lbl_8029F3C8));
    d2.hc = a2;
    { register s32 d2b __asm__("r9"); d2b = (s32)&d2; ((LS *)d2b)->iter = z; }
    base = (void *)((s32 *)arg0 + 6);
    ((LS *)pbs)->iter = (s32)base;
    __asm__ volatile ("mr %0,%1" : "=r"(q) : "r"(pbs));
    n1 = (void *)((Node *)base)->fC;
    if (((Node *)n1)->f4 == -1) {
        n1 = NULL;
    }
    q->iter = (s32)n1;
    if (n1 == NULL) {
        __asm__ __volatile__("li %0,0" : "=r"(n1));
    } else {
        __asm__ __volatile__("lwz %0,4(%0)" : "+b"(n1));
    }
    arg0 = (void *)((s32 *)arg0 + 0xC);
    it = n1;
    if (it != NULL) {
        z1 = 0;
        __asm__ volatile ("mr %0,%1" : "=r"(pb1) : "r"(q));
        do {
            if (((Node *)it)->f20 == arg1) {
                ((Node *)it)->f18 = z1;
            }
            c1 = (void *)(s32)pb1->iter;
            n2 = (void *)((Node *)c1)->fC;
            if (((Node *)n2)->f4 == -1) {
                n2 = NULL;
            }
            q->iter = (s32)n2;
            if (n2 == NULL) {
                __asm__ __volatile__("li %0,0" : "=r"(n2));
            } else {
                __asm__ __volatile__("lwz %0,4(%0)" : "+b"(n2));
            }
            it = n2;
        } while (it != NULL);
    }
    b1 = (void *)((Node *)arg0)->fC;
    d2.iter = (s32)arg0;
    b2 = b1;
    __asm__ ("" : "+r"(b1) : "r"(b2));
    if (((Node *)b1)->f4 == -1) {
        b2 = NULL;
    }
    d2.iter = (s32)b2;
    if (b2 == NULL) {
        b3 = NULL;
    } else {
        b3 = (void *)((Node *)b2)->f4;
    }
    it2 = b3;
    if (it2 != NULL) {
        z2 = 0;
        do {
            if (((Node *)it2)->f1C == arg1) {
                ((Node *)it2)->f20 = z2;
            }
            c2 = (void *)(s32)d2.iter;
            n3 = (void *)((Node *)c2)->fC;
            if (((Node *)n3)->f4 == -1) {
                n3 = NULL;
            }
            d2.iter = (s32)n3;
            if (n3 == NULL) {
                __asm__ __volatile__("li %0,0" : "=r"(n3));
            } else {
                __asm__ __volatile__("lwz %0,4(%0)" : "+b"(n3));
            }
            it2 = n3;
        } while (it2 != NULL);
    }
    q->hc = (s32)lbl_8029F3E0;
    d2.hc = (s32)lbl_8029F3C8;
}
