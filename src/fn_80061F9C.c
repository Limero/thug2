// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80061F9C-0x800620EC (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Pay61F9C {
    void *unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    struct Sub61F9C *unk0xC;
} Pay61F9C;
typedef struct Sub61F9C {
    char pad0x0[4];
    void *unk0x4;
} Sub61F9C;
typedef struct Node61F9C {
    Pay61F9C *pay;
    struct Node61F9C *unk0x4;
    struct Node61F9C *unk0x8;
} Node61F9C;
typedef struct List61F9C {
    char pad0x0[0x10];
    Node61F9C *head;
    s32 unk0x14;
    char pad0x18[0x4A - 0x18];
    u16 unk0x4A;
    u16 unk0x4C;
    u16 unk0x4E;
} List61F9C;

void fn_80055228(void *);
void fn_8005546C(void *, s32);
void fn_8005D734(void *);
void Mem_Free(void *);

void fn_80061F9C(List61F9C *arg0, s32 arg1) {
    Node61F9C *sp[12];
    Node61F9C *head;
    Node61F9C *cur;
    Node61F9C *n;
    Node61F9C *nxt;
    Pay61F9C *pay;
    s32 *cnt;

    head = arg0->head;
    sp[0] = head;
    cur = NULL;
    if (head != NULL) {
        cur = head->unk0x4;
    }
    sp[2] = cur;
    if (cur != head) {
        do {
            pay = sp[2]->pay;
            if (pay->unk0x8 == arg1) {
                fn_80055228(pay->unk0x0);
                if (sp[2]->pay->unk0xC != NULL) {
                    Sub61F9C *sub = sp[2]->pay->unk0xC;
                    void *t = sub->unk0x4;
                    __asm__("" : "+r"(sub) : "r"(t));
                    fn_8005546C(sub, 1);
                    fn_8005D734(t);
                }
                if (sp[2]->pay->unk0xC != NULL) {
                    arg0->unk0x4C -= 1;
                } else {
                    arg0->unk0x4E -= 1;
                }
                arg0->unk0x4A -= 1;
                cnt = (s32 *)((char *)arg0 + 0x10);
                Mem_Free(sp[2]->pay);
                n = sp[2];
                sp[6] = n;
                sp[10] = n;
                nxt = n->unk0x4;
                sp[8] = n;
                sp[6] = nxt;
                if (n != arg0->head) {
                    n->unk0x8->unk0x4 = n->unk0x4;
                    n->unk0x4->unk0x8 = n->unk0x8;
                    Mem_Free(n);
                    cnt[1] -= 1;
                }
                sp[4] = sp[6];
                return;
            }
            sp[2] = sp[2]->unk0x4;
        } while (sp[2] != sp[0]);
    }
}
