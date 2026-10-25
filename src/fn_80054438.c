// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054438-0x80054538 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"

Unk_C8FEE62D *fn_800A200C(void *, s32);
void fn_80060E4C(void *, s32);

extern void *lbl_80301A38;

// Count, then collect, the model pointers reachable from the object
// registry at lbl_80301A38 whose 0x18 field is set and whose 0x48 flag bit
// 0x20000000 is clear, into the (array, count) pair at arg0+4 / arg0+8.
void fn_80054438(CStruct *arg0) {
    s32 count;
    s32 val;
    void *p1;
    void *p2;
    Unk_C8FEE62D *node;

    count = 0;
    node = fn_800A200C(lbl_80301A38, QB_MODEL);
    while (node != NULL) {
        p1 = *(void **)((char *)node + 0x210);
        if (*(s32 *)((char *)node->unk0xC + 0x18) != 0
            && !(*(s32 *)((char *)p1 + 0x48) & QB_UNKNOWN_0x20000000)) {
            count++;
        }
        node = (Unk_C8FEE62D *)node->unk0x14;
    }

    if (count != 0) {
        arg0->unk0x4 = (s32)Mem_Alloc(count * 4);
        arg0->unk0x8 = 0;
        node = fn_800A200C(lbl_80301A38, QB_MODEL);
        while (node != NULL) {
            val = *(s32 *)((char *)node->unk0xC + 0x18);
            p2 = *(void **)((char *)node + 0x210);
            if (val != 0 && !(*(s32 *)((char *)p2 + 0x48) & QB_UNKNOWN_0x20000000)) {
                ((s32 *)arg0->unk0x4)[arg0->unk0x8] = val;
                fn_80060E4C(p2, 1);
                arg0->unk0x8 = arg0->unk0x8 + 1;
            }
            node = (Unk_C8FEE62D *)node->unk0x14;
        }
    }
}
