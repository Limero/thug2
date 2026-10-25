// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A20B8-0x800A2164 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct A20B8_node {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0xC];
    struct A20B8_node *unk0x14;
} A20B8_node;

typedef struct A20B8_ctx {
    char pad0x0[0x50];
    s32 unk0x50;
} A20B8_ctx;

extern s32 lbl_803C9E80[];

void fn_800A20B8(A20B8_ctx *arg0, A20B8_node *arg1) {
    A20B8_node *e;
    A20B8_node *w;
    s32 target;
    u32 i;

    i = 0;
    target = arg1->unk0x4;
    if (i < (u32)arg0->unk0x50) {
        do {
            s32 id = ((s32 *)arg0)[0x15 + i * 2];
            if (id == target) {
                e = (A20B8_node *)lbl_803C9E80[i];
                if (e == arg1) {
                    lbl_803C9E80[i] = (s32)arg1->unk0x14;
                    arg1->unk0x14 = NULL;
                    return;
                }
                w = e;
                if (w != NULL) {
                    do {
                        A20B8_node *nx = w->unk0x14;
                        if (nx == arg1) {
                            w->unk0x14 = nx->unk0x14;
                            nx->unk0x14 = NULL;
                            return;
                        }
                        w = nx;
                    } while (w != NULL);
                }
            }
            i += 1;
        } while (i < (u32)arg0->unk0x50);
    }
}
