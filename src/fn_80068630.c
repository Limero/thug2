// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068630-0x80068760 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"

/* The list is a chain of objects that each embed a 2-word link header at
   +0x0C.  The header's second word is -1 on the terminating (sentinel) entry,
   so advancing the chain is

       link = node->link;
       if (link->unk0x4 == -1) link = 0;
       node = link ? (Entry *)((char *)link - 0xC) : 0;

   i.e. the object pointer is recovered by subtracting the header size.  Both
   the +0x0C slot (used once, to enter the list) and the +0x18 slot (used on
   every step) hold such a header, and the list head itself is the object hung
   off the caller's +0x10 field. */
typedef struct Link {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0x4];
} Link;

typedef struct Entry {
    char pad0x0[0xC];
    Link *link0xC;
    struct Entry *next;
    char pad0x14[0x4];
    Link *link0x18;
    char pad0x1C[0x128];
    s32 flag;
} Entry;

void fn_8006374C(void *, s32);
void fn_8026A07C(void *, u32, u32, s32 (*)(void **, void **));
s32 fn_8006821C(void **, void **);
extern s32 lbl_80300460;

void fn_80068630(Entry *arg0, s32 arg1) {
    void *sp8[0x100];
    void **sp_base;
    s32 count;
    s32 flag;
    void **cur;
    void **cur2;
    s32 i;
    s32 elem;
    Entry *head;
    Entry *node;
    Link *link;
    Link *link2;
    Entry *next_node;

    memset(sp8, 0, 0x400);
    sp_base = (void **)sp8;
    count = 0;
    head = arg0->next;
    if (head != NULL) {
        link = head->link0xC;
        if (link->unk0x4 == -1) {
            link = NULL;
        }
        if (link != NULL) {
            node = (Entry *)((char *)link - 0xC);
        } else {
            node = NULL;
        }
        if (node != NULL) {
            cur = sp_base;
            do {
                if (node->flag != 0) {
                    *cur = node;
                    count += 1;
                    cur += 1;
                }
                link2 = node->link0x18;
                if (link2->unk0x4 == -1) {
                    link2 = NULL;
                }
                if (link2 != NULL) {
                    next_node = (Entry *)((char *)link2 - 0xC);
                } else {
                    next_node = NULL;
                }
                node = next_node;
            } while (node != NULL);
        }
    }
    if (count == 0) {
        return;
    }
    flag = 0;
    fn_8026A07C(sp8, count, 4, fn_8006821C);
    if ((arg1 != 0) || (lbl_80300460 != 0)) {
        flag = 1;
    }
    if (count > 0) {
        cur2 = sp_base;
        i = count;
        do {
            elem = *(s32 *)cur2;
            cur2 += 1;
            fn_8006374C((void *)elem, flag);
            i -= 1;
        } while (i != 0);
    }
}
