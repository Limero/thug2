// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBEC0-0x800CBF00 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct ListNode {
    s32 unk0x0;
    s32 unk0x4;        /* -1 == end-of-list sentinel */
    s32 unk0x8;
    struct ListNode *unk0xC;   /* ->next */
    char _pad[0x20];
    s32 unk0x30;       /* the searched-for id */
    s32 unk0x34;
    s32 unk0x38;       /* head, reached via the +0x38 shortcut */
} ListNode;

/* Returns 1 if some node in arg0->unk0x38's list has unk0x30 == arg1. */
bool fn_800CBEC0(ListNode *arg0, s32 arg1) {
    ListNode *a, *b, *c;

    a = *(ListNode **)((char *)arg0 + 0x38);
    if (a->unk0x4 == -1) {
        a = 0;
    }
    b = a;
    if (b != 0) {
        do {
            if (b->unk0x30 == arg1) {
                return true;
            }
            c = b->unk0xC;
            if (c->unk0x4 == -1) {
                c = 0;
            }
            b = c;
        } while (b != 0);
    }
    return false;
}
