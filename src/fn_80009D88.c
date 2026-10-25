// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009D88-0x80009EBC (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8028FF40[];

/* 16-byte stack node: +4 = list-node link, +8 = base-class vtable. */
typedef struct S9D88 {
    s32 unk0x0;
    void *next;
    void *vtable;
    s32 unk0xC;
} S9D88;

/* owner (arg0): +4 re-entrancy counter, +8 list head, +0x20 version, +0x24 dirty */
typedef struct S9D88Owner {
    s32 unk0x0;
    s32 cnt;
    void *head;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 version;
    s32 dirty;
} S9D88Owner;

typedef struct S9D88Vtbl {
    s32 unk0x0;
    u16 unk0x4;
    u16 unk0x6;
    s16 off;
    s16 unk0xA;
    void (*fn)(void *);
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
} S9D88Vtbl;

void fn_80009D88(S9D88Owner *a, s32 arg1, s32 flags) {
    S9D88 s;
    S9D88 *sp;
    S9D88 *ip;
    void *h;
    void *n;
    void *m1;
    register void *m2 __asm__("r11");
    void *p;
    register void *e __asm__("r10");
    register void *t __asm__("r9");
    s32 z;
    S9D88Vtbl *vt;

    if (a->cnt != 0) {
        return;
    }
    a->version = a->version + 1;
    sp = &s;
    z = 0;
    h = (void *)((char *)a + 8);
    for (;;) {
        ip = &s;
        ip->vtable = lbl_8028FF40;
        ip->next = h;
        n = *(void **)((char *)h + 0xC);
        if (*(s32 *)((char *)n + 4) == -1) {
            n = 0;
        }
        sp->next = n;
        if (n == 0) {
            t = 0;
            __asm__ volatile ("" : "+r" (e));
        } else {
            t = *(void **)((char *)n + 4);
        }
        a->dirty = z;
        p = t;
        if (p != 0) {
            do {
                e = p;
                m1 = sp->next;
                m2 = *(void **)((char *)m1 + 0xC);
                if (*(s32 *)((char *)m2 + 4) == -1) {
                    m2 = 0;
                }
                sp->next = m2;
                p = (m2 != 0) ? *(void **)((char *)m2 + 4) : 0;
                if (*(s32 *)((char *)e + 4) == 0) {
                    if (*(s32 *)((char *)e + 0x10) != a->version) {
                        *(s32 *)((char *)e + 0x10) = a->version;
                        if (!(*(s32 *)((char *)e + 0x14) & flags)) {
                            vt = *(S9D88Vtbl **)((char *)e + 0x18);
                            vt->fn(e + vt->off);
                        }
                    }
                }
                if (a->dirty != 0) {
                    break;
                }
            } while (p != 0);
        }
        sp->vtable = lbl_8028FF40;
        if (a->dirty == 0) {
            break;
        }
    }
}
