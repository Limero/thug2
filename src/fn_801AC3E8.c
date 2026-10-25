// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AC3E8-0x801AC4E4 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// rail/line node: 0x60-byte element of the container's array. +0x48 chains the
// per-object node list, +0x50 is the flag bitfield (fn_801AEC8C sets bit `arg`,
// fn_801AECA4 clears it), +0x54 is the id searched for.
typedef struct Node_801AC3E8 {
    char pad0x0[0x48];
    struct Node_801AC3E8 *next;
    s32 unk0x4C;
    s32 flags;
    s32 id;
    s32 unk0x58;
    char pad0x5C[0x4];
} Node_801AC3E8;

// container: +0x48 is the node array base, +0x50 its element count.
typedef struct Net_801AC3E8 {
    char pad0x0[0x48];
    Node_801AC3E8 *nodes;
    s32 unk0x4C;
    s32 count;
} Net_801AC3E8;

extern void fn_801AEC8C(Node_801AC3E8 *, s32);
extern void fn_801AECA4(Node_801AC3E8 *, s32);

void fn_801AC3E8(Net_801AC3E8 *net, s32 id, s32 set, s32 walk) {
    s32 i;
    Node_801AC3E8 *node;
    s32 bit;

    for (i = 0; i < net->count; i++) {
        node = &net->nodes[i];
        if (node->id != id) {
            continue;
        }
        if (walk != 0) {
            while (node) {
                bit = 1;
                if (set == 0) {
                    bit = 0;
                }
                if (bit != 0) {
                    fn_801AEC8C(node, 2);
                } else {
                    fn_801AECA4(node, 2);
                }
                node = node->next;
            }
        } else {
            bit = 1;
            if (set == 0) {
                bit = 0;
            }
            if (bit != 0) {
                fn_801AEC8C(node, 2);
            } else {
                fn_801AECA4(node, 2);
            }
        }
        return;
    }
}
