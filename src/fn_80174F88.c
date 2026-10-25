// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174F88-0x8017503C (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *fn_801746A4(void *, s32);
void fn_801738A4(void *, void *, s32, s32);
void fn_80145008(void *);
typedef struct Node { s32 f_00; s32 f_04; s32 f_08; void *f_0C; } Node;
typedef struct Ent { char _pad[0xC8]; s32 f_C8; } Ent;
void fn_80174F88(void *arg0, s32 arg1, s32 arg2) {
    unsigned int i;
    unsigned int n;
    s32 z;
    Node *p;
    Ent *e;
    char *base;
    register s32 a0 __asm__("r29");
    a0 = (s32)arg0;
    base = (char *)a0 + 0x2C;
    z = 0;
    i = 0;
loop1:
    p = *(Node **)((char *)base + 0xC);
    n = 0;
    goto chk;
bdy:
    p = p->f_0C;
    n++;
chk:
    if (p->f_04 == -1) {
        p = 0;
    }
    if (p != 0) {
        goto bdy;
    }
    if (i < n) {
        e = (Ent *)fn_801746A4((void *)a0, (s32)i);
        if (e->f_C8 != 0) {
            fn_801738A4((void *)a0, e, arg1, arg2);
        }
        fn_80145008(e);
        i++;
        goto loop1;
    }
    *(s32 *)((char *)a0 + 0x54) = z;
}
