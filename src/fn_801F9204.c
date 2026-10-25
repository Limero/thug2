// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9204-0x801F9314 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Unk_9204_node Unk_9204_node;
struct Unk_9204_node {
    char pad0x0[0x24];
    s32 unk0x24;
    s32 unk0x28;
    void *unk0x2C;
    void *unk0x30;
};

typedef struct Unk_9204_self {
    char pad0x0[0x1C];
    s32 unk0x1C;
    char pad0x20[0x4];
    Unk_9204_node *unk0x24;
    Unk_9204_node *unk0x28;
    void *unk0x2C;
    void *unk0x30;
} Unk_9204_self;

extern void fn_80057CB0(void *arg0);
extern void fn_80057D30(void *arg0, s32 arg1);

void fn_801F9204(Unk_9204_self *arg0) {
    Unk_9204_node *node;

    if (arg0->unk0x1C != 0) {
        if (arg0->unk0x30 != 0) {
            fn_80057CB0(arg0->unk0x30);
            fn_80057D30(arg0->unk0x30, -1);
        }
        if (arg0->unk0x2C != 0) {
            fn_80057CB0(arg0->unk0x2C);
            fn_80057D30(arg0->unk0x2C, -1);
        }
        node = arg0->unk0x28;
        if ((node != NULL) && (node->unk0x2C != NULL)) {
            fn_80057CB0(node->unk0x2C);
            fn_80057D30(arg0->unk0x28->unk0x2C, -1);
        }
        node = arg0->unk0x24;
        if ((node != NULL) && (node->unk0x24 == 0) && (node->unk0x30 != NULL)) {
            fn_80057CB0(node->unk0x30);
            fn_80057D30(arg0->unk0x24->unk0x30, -1);
        }
        node = arg0->unk0x28;
        if ((node != NULL) && (node->unk0x28 == 0) && (node->unk0x30 != NULL)) {
            fn_80057CB0(node->unk0x30);
            fn_80057D30(arg0->unk0x28->unk0x30, -1);
        }
        arg0->unk0x1C = 0;
    }
}
