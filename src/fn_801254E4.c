// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801254E4-0x80125548 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80303248;
typedef struct Node {
    char _pad0[4];
    s32 unk4;
    char _pad8[8];
    s32 unk10;
} Node;
void fn_801254E4(Node *arg0) {
    s32 *table;
    Node *node;
    Node *prev;
    s32 off;
    s32 zero;

    off = (arg0->unk4 & 0xFFF) << 2;
    table = (s32 *)lbl_80303248;
    prev = 0;
    node = *(Node **)((char *)(off + (s32)table));
    if (node == 0) {
        return;
    }
    zero = 0;
    while (1) {
        if (node == arg0) {
            if (prev != 0) {
                prev->unk10 = node->unk10;
            } else {
                *(s32 *)((char *)(off + (s32)table)) = node->unk10;
            }
            node->unk10 = zero;
            return;
        }
        prev = node;
        node = node->unk10;
        if (node == 0) {
            return;
        }
    }
}
