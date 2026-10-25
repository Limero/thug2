// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3438-0x800F34F0 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80012224(s32, void *);
typedef struct { s32 unk0x0; s32 unk0x4; s32 unk0x8; } Rec3;
void fn_800F3438(CStruct *arg0, s32 *arg1) {
    Rec3 *head;
    Rec3 *prev;
    Rec3 *node;
    Rec3 *next;

    head = (Rec3 *)arg0->unk0x4;
    if (head == 0) {
        return;
    }
    prev = 0;
    node = (Rec3 *)((char *)head + ((*arg1) & ((1 << arg0->unk0x0) - 1)) * 0xC);
    if (node == 0) {
        return;
    }
    while (node != 0) {
        next = (Rec3 *)node->unk0x8;
        if (node->unk0x0 == *arg1 && node->unk0x4 != 0) {
            if (prev != 0) {
                prev->unk0x8 = (s32)next;
                fn_80012224(0, node);
            } else {
                node->unk0x0 = (s32)prev;
                node->unk0x4 = (s32)prev;
            }
            arg0->unk0x8--;
            return;
        }
        prev = node;
        node = next;
    }
}
