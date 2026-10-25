// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9988-0x801F99D8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F9988(Unk_C7387A53 *arg0, f32 minX, f32 minY, f32 maxX, f32 maxY) {
    s32 var_r3;
    Unk_DB0E2BAB *node;
    f32 temp_f0;
    f32 *p;

    node = *((void * *)&arg0->unk0xC);
    var_r3 = 0;
    if (node == NULL) {
        return var_r3;
    }
    do {
        temp_f0 = *((f32 *)&node->unk0x8);
        p = (f32 *)((char *)node + 8);
        if ((temp_f0 > minX) && (temp_f0 < maxX)) {
            f32 temp_f1 = p[2];
            if ((temp_f1 > minY) && (temp_f1 < maxY)) {
                var_r3 += 1;
            }
        }
        node = *((void * *)&node->unk0x24);
    } while (node != NULL);
    return var_r3;
}
