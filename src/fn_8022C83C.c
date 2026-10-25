// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C83C-0x8022C898 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x10];
    Unk_C7387A53 *unk0x10;
    s32 unk0x14;
    s16 unk0x18;
    char pad0x1A[0x6];
    CStruct *unk0x20;
} Rec_8022C83C;
void fn_8022CE00(CStruct *, void *);
void fn_8022C83C(Rec_8022C83C *arg0) {
    Unk_C7387A53 *node;
    Unk_C7387A53 *next;
    node = arg0->unk0x10;
    while (node != 0) {
        next = node->unk0x34;
        fn_8022CE00(arg0->unk0x20, node);
        node = next;
    }
    arg0->unk0x10 = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x18 = 0;
}
