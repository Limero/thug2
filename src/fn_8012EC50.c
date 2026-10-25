// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EC50-0x8012ED70 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Node_t {
    char _pad0[8];
    s32 unk8;
} Node_t;

typedef struct Mgr_t {
    char _pad0[0x118];
    s32 unk118;
} Mgr_t;

extern s32 lbl_802FFE98;
#define MGR ((Mgr_t *) *(void **) &lbl_802FFE98)

void *fn_80125600(void *);
void fn_8000F2F8(void *, s32);
void *Mem_Alloc_3(s32);
void fn_8000F320(void *);
void fn_8012DE30(void *);
void Mem_Free_3(void *);
void *fn_8012ED7C(void *);
s32 fn_80130D74(void *);
void fn_8012F360(void *);
void fn_8012F4DC(void *);
void fn_80012948(void *);

void fn_8012EC50(void *arg0) {
    register void *a0 __asm__("r27") = arg0;
    Node_t *node;
    Node_t *node2;
    s32 count;
    register Node_t **buf __asm__("r28");
    Node_t **pf;
    Node_t **pp;
    s32 i;
    void *walk;

    if (a0 != 0) {
        node = NULL;
        count = 0;
        while ((node = (Node_t *) fn_80125600(node)) != NULL) {
            if (node->unk8 == (s32) a0) {
                count += 1;
            }
        }

        if (count != 0) {
            __asm__("" : "+r"(count));
            fn_8000F2F8(MGR, MGR->unk118);
            buf = (Node_t **) Mem_Alloc_3(count * 4);
            fn_8000F320(MGR);

            node2 = (Node_t *) fn_80125600(NULL);
            if (node2 != NULL) {
                pf = buf;
                do {
                    if (node2->unk8 == (s32) a0) {
                        *pf = node2;
                        pf += 1;
                    }
                    node2 = (Node_t *) fn_80125600(node2);
                } while (node2 != NULL);
            }

            if (count > 0) {
                __asm__("mr %0,%1" : "=r"(i) : "r"(count));
                pp = buf;
                do {
                    void *t;
                    t = *pp;
                    pp += 1;
                    fn_8012DE30(t);
                } while (--i != 0);
            }
            Mem_Free_3(buf);
        }

        walk = fn_8012ED7C(NULL);
        while (walk != 0) {
            if (fn_80130D74(walk) == 0) {
                fn_8012F360(walk);
                fn_8012F4DC(walk);
            }
            walk = fn_8012ED7C(walk);
        }
        fn_80012948(a0);
    }
}
