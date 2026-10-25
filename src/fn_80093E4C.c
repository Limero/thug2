// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80093E4C-0x80093F48 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern void *lbl_80301820;

/* out-node: flags at +0, an 8-pair PS blob at +8, the 3 int links at +0x48/+4C/+54,
 * the u16 "is valid" flag at +0x50, the 0xFF sentinel at +0x58 and the list link
 * at +0x6C (this node is pushed on the head at lbl_80301820). */
typedef struct {
    s32 unk0x00;
    s32 unk0x04;
    __ps_t unk08[8];
    s32 unk0x48;
    s32 unk0x4C;
    u16 unk0x50;
    u16 unk0x52;
    void *unk0x54;
    s32 unk0x58;
    u16 unk0x5C;
    u16 unk0x5E;
    s32 unk0x60;
    s32 unk0x64;
    s32 unk0x68;
    void *unk0x6C;
} Unk_93E4C_A;

/* the peer node the caller passes in: +0x6C is a s32 count here (not the link),
 * +0x5E the u16 element count, +0x58 the element-pointer array, +0x08 a node. */
typedef struct {
    s32 unk0x00;
    s32 unk0x04;
    void *unk0x08;
    char pad0x0C[0x48];
    void *unk0x54;
    void **unk0x58;
    u16 unk0x5C;
    u16 unk0x5E;
    s32 unk0x60;
    s32 unk0x64;
    s32 unk0x68;
    s32 unk0x6C;
} Unk_93E4C_B;

typedef struct {
    s32 unk0x0;
    u16 unk0x4;
    u16 unk0x6;
} Unk_93E4C_C;

typedef struct {
    s32 unk0x0;
    void *pad0x4[4];
    void *unk0x14;
} Unk_93E4C_D;

typedef struct {
    s32 unk0x0;
    void *unk0x4;
} Unk_93E4C_E;

typedef struct {
    s32 unk0x0;
    char pad0x4[2];
    u8 unk0x6;
} Unk_93E4C_F;

void fn_80093E4C(Unk_93E4C_A *arg0, Unk_93E4C_B *arg1, __ps_t *arg2, s32 arg3, s32 arg4) {
    s32 i;
    Unk_93E4C_D *elem;
    Unk_93E4C_C *node;

    /* retail opens with the empty self-targeting doloop li r0,4 / mtctr / bdnz .
     * (recipes §6ew / doc 30) — plain C reproduces it with no flag and no pin. */
    for (i = 4; i != 0; i--) {
    }
    arg0->unk08[0] = arg2[0];
    arg0->unk08[1] = arg2[1];
    arg0->unk08[2] = arg2[2];
    arg0->unk08[3] = arg2[3];
    arg0->unk08[4] = arg2[4];
    arg0->unk08[5] = arg2[5];
    arg0->unk08[6] = arg2[6];
    arg0->unk08[7] = arg2[7];
    arg0->unk0x4C = arg3;
    arg0->unk0x50 = 1;
    arg0->unk0x6C = lbl_80301820;
    arg0->unk0x48 = arg4;
    arg0->unk0x54 = arg1;
    arg0->unk0x00 = 0;
    arg0->unk0x60 = 0;
    lbl_80301820 = arg0;
    arg0->unk0x64 = 0;
    arg0->unk0x58 = 0xFF;
    if (arg4 != 0 && arg1->unk0x6C <= 0) {
        return;
    }
    for (i = 0; i < (s32)arg1->unk0x5E; i++) {
        /* BOTH loop-invariant loads have to be written INSIDE the body: that puts
         * them in the rotated loop's entry block (after the `bge` guard) and lets
         * r4 die at the +0x58 load, which is what coalesces the walk pointer into
         * r4 and the counter into r10. See AGENTS-recipes.md §6gb. */
        node = (Unk_93E4C_C *)arg1->unk0x08;
        elem = arg1->unk0x58[i];
        if (node->unk0x6 == 0) {
            return;
        }
        if (((Unk_93E4C_F *)((Unk_93E4C_E *)elem->unk0x14)->unk0x4)->unk0x6 & 0x80) {
            return;
        }
    }
    arg0->unk0x00 |= 4;
}
