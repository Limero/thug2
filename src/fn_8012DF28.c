// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012DF28-0x8012DF78 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node {
    s32 unk0;
    s32 unk4;
    struct Node *unk8;
} Node;

extern Node *lbl_803032B8;

s32 fn_8012DF28(s32 arg0) {
    Node *p = lbl_803032B8;

    if (p == NULL) {
        return 0;
    }
    for (p = p + (arg0 & 0xFFF); p != NULL; p = p->unk8) {
        if (p->unk0 == arg0) {
            return p->unk4;
        }
    }
    return 0;
}
