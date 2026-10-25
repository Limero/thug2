// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5B18-0x800A5B64 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Node {
    char pad0[0xC];
    struct Node *unk0xC;
    s32 unk0x10;
} Node;
typedef struct Head {
    char pad0[0x14];
    Node *unk0x14;
} Head;
void fn_800A5B18(Head *arg0, Node *arg1) {
    Node *node;
    Node *prev;

    for (node = arg0->unk0x14, prev = 0; node != 0; prev = node, node = node->unk0xC) {
        if (node == arg1) {
            if (prev != 0) {
                prev->unk0xC = arg1->unk0xC;
            } else {
                arg0->unk0x14 = arg1->unk0xC;
            }
            break;
        }
    }
    arg1->unk0x10 = 0;
}
