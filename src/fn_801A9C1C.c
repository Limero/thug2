// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9C1C-0x801A9CC4 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
struct n12 {
    char pad0[4];
    s32 f4;
    s32 f8;
};
void fn_801A9C1C(CStruct *arg0, void (*cb)(s32, s32), s32 arg2) {
    u32 total;
    u32 i;
    struct n12 *walker;
    struct n12 *node;
    u32 next_i;
    struct n12 *next_w;
    s32 val;
    struct n12 *nxt;
    total = 1U << *(s32 *)arg0;
    i = 0;
    walker = *((struct n12 * *)&arg0->unk0x4);
    while (i < total) {
        node = (struct n12 *)walker->f8;
        next_i = i + 1;
        next_w = walker + 1;
        if (node != NULL) {
            do {
                val = node->f4;
                nxt = (struct n12 *)node->f8;
                if (val != 0) {
                    cb(val, arg2);
                }
                node = nxt;
            } while (node != NULL);
        }
        if (walker->f4 != 0) {
            cb(walker->f4, arg2);
        }
        i = next_i;
        walker = next_w;
    }
}
