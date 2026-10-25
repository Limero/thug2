// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801745B4-0x801746A4 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct N {
    u8 _p0[4];
    s32 id;
    u8 _p8[4];
    struct N *next;
} N;

typedef struct L {
    u8 _p[0xC];
    N * volatile head;
} L;

typedef struct Res {
    u8 _p[0xC8];
    s32 flag;
} Res;

void *fn_801745B4(void *arg0) {
    L *list = (L *)((char *)arg0 + 0x2C);
    N *head;
    s32 hb;
    N *p;
    N *res;
    register Res *e __asm__("r3");
    u32 i;
    u32 j;

    head = list->head;
    hb = (head->id == -1);
    for (i = 0;; i++) {
        j = 0;
        p = head;
        if (hb) {
            p = NULL;
        }
        while (p != NULL) {
            p = p->next;
            j++;
            if (p->id == -1) {
                p = NULL;
            }
        }
        if (i >= j) {
            break;
        }
        p = list->head;
        j = i;
        for (;;) {
            if (p->id == -1) {
                p = NULL;
            }
            if (p == NULL) {
                break;
            }
            if (j-- == 0) {
                res = p;
                goto got1;
            }
            p = p->next;
        }
        res = NULL;
    got1:
        if (res == NULL) {
            continue;
        }
        p = list->head;
        j = i;
        for (;;) {
            if (p->id == -1) {
                p = NULL;
            }
            if (p == NULL) {
                break;
            }
            if (j-- == 0) {
                res = p;
                goto got2;
            }
            p = p->next;
        }
        res = NULL;
    got2:
        e = (Res *)res->id;
        if (e->flag != 0) {
            return e;
        }
    }
    return NULL;
}
