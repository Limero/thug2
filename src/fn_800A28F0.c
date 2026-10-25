// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A28F0-0x800A2954 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node {
    char _0[4];
    s32 f4;
    struct Node *f8;
} Node;

extern Node *lbl_8037BB58;

void fn_800A2EE0(s32 *, s32 *, s8 *);

typedef struct S {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s8 f20;
} S;

void fn_800A28F0(void) {
    S s;
    Node *p;
    s32 var;
    Node *t8;

    var = 0;
    p = lbl_8037BB58;
    if (p != NULL) {
        var = p->f4;
    }
    s.f08 = (s32)p;
    s.f00 = var;
    t8 = p->f8;
    s.f10 = var;
    s.f08 = (s32)t8;
    s.f18 = (s32)t8;
    s.f20 = 0;
    fn_800A2EE0(&s.f10, &s.f18, &s.f20);
}
