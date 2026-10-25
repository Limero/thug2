// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EC330-0x800EC39C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
typedef struct Vtbl_800EC330 {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    void *unk0xC;
} Vtbl_800EC330;
typedef struct Node_800EC330 {
    char pad0x0[0x20];
    Vtbl_800EC330 *unk0x20;
    char pad0x24[0x28];
    struct Node_800EC330 *unk0x4C;
} Node_800EC330;
void fn_800EC330(Node_800EC330 *arg0, s32 arg1) {
    Node_800EC330 *node;
    Vtbl_800EC330 *vt;

    node = arg0->unk0x4C;
    if (node != NULL) {
        vt = node->unk0x20;
        ((void (*)(void *, s32))vt->unk0xC)((char *)node + vt->unk0x8, 3);
        arg0->unk0x4C = NULL;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
