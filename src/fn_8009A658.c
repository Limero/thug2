// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A658-0x8009A6C0 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct A658_N {
    struct A658_N *next;
    u8 _p[4];
    f32 key;
} A658_N;

extern A658_N *lbl_803018F0;

void fn_8009A658(A658_N *node) {
    A658_N *p = lbl_803018F0;
    A658_N *q;

    if (p == NULL || node->key <= p->key) {
        node->next = p;
        lbl_803018F0 = node;
        return;
    }
    for (q = p; q->next != NULL; q = q->next) {
        if (node->key <= q->next->key) break;
    }
    node->next = q->next;
    q->next = node;
}
