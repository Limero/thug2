// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004B270-0x8004B314 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct B4270 {
    char pad0[0x44];
    s32 unk0x44;
    char pad48[0x4];
    s32 unk0x4C;
    char pad50[0x14];
    s32 unk0x64;
    char pad68[0x4];
    char pad6C[0x4];
    s32 unk0x70;
} B4270;

void fn_8004B270(B4270 *arg0, s32 arg1) {
    s32 stack[32];
    s32 *p;
    s32 count;
    B4270 *node;
    s32 var_r0;
    s32 n;

    if (arg0->unk0x4C == 0) {
        return;
    }
    stack[0] = arg0->unk0x4C;
    count = 1;
    p = stack + 1;
    while (count != 0) {
        count -= 1;
        node = *(B4270 **)--p;
        if (arg1 == 1) {
            node->unk0x44 += 1;
        } else {
            n = node->unk0x44;
            var_r0 = (n > 0);
            if ((var_r0 != 0) && (n > 0)) {
                node->unk0x44 = n - 1;
            }
        }
        if (node->unk0x70 != 0) {
            *p = node->unk0x70;
            p += 1;
            count += 1;
        }
        if (node->unk0x64 != 0) {
            *p = node->unk0x64;
            p += 1;
            count += 1;
        }
    }
}
