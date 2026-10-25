// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A27BC-0x800A28A4 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node {
    s32 f0;
    struct Node *next;
    struct Node *prev;
} Node;

typedef union Slot {
    Node *p;
    u64 q;
} Slot;

typedef struct Fr {
    Slot f8;
    Slot f10;
    Slot f18;
    Slot f20;
    Slot f28;
    Slot f30;
    Slot f38;
    Slot f40;
} Fr;

extern Node *lbl_8037BB58;
void Mem_Free(void *);

void fn_800A27BC(s32 arg0) {
    Fr fr;
    Node **hp = &lbl_8037BB58;
    s32 *pid = &fr.f40;
    Node *cur;
    s32 var_r0;
    s32 n1;
    s32 g;

    fr.f40.p = (Node *)arg0;
    fr.f8.p = lbl_8037BB58;
    var_r0 = 0;
    if (fr.f8.p != NULL) {
        var_r0 = (s32)fr.f8.p->next;
    }
    fr.f10.p = (Node *)var_r0;
    if (fr.f10.p != fr.f8.p) {
        do {
            cur = fr.f10.p;
            if (cur->f0 == *pid) {
                g = (s32)*hp;
                fr.f28.p = cur;
                n1 = (s32)cur->next;
                fr.f20.p = cur;
                fr.f10.p = (Node *)n1;
                if ((fr.f38.p = cur, fr.f20.p = cur->next, fr.f30.p = cur, cur != (Node *)g)) {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                    Mem_Free(cur);
                    ((s32 *)hp)[1] = ((s32 *)hp)[1] - 1;
                }
                fr.f18.p = fr.f20.p;
            } else {
                fr.f10.p = cur->next;
            }
        } while (fr.f10.p != fr.f8.p);
    }
}
