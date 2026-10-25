// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801746A4-0x8017471C (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W746A4_Node {
    u8 _p0[4];
    s32 id;
    u8 _p8[4];
    struct W746A4_Node *next;
} W746A4_Node;

typedef struct W746A4_Root {
    u8 _p[0x38];
    W746A4_Node *head;
} W746A4_Root;

s32 fn_801746A4(W746A4_Root *arg0, u32 arg1) {
    W746A4_Node *p;
    W746A4_Node *res;
    u32 count = 0;

    p = arg0->head;
    for (;;) {
        if (p->id == -1) {
            p = NULL;
        }
        if (p == NULL) {
            break;
        }
        p = p->next;
        count++;
    }
    if (count <= arg1) {
        return 0;
    }
    p = arg0->head;
    for (;;) {
        if (p->id == -1) {
            p = NULL;
        }
        if (p == NULL) {
            break;
        }
        if (arg1-- == 0) {
            res = p;
            goto done;
        }
        p = p->next;
    }
    res = NULL;
done:
    return res->id;
}
