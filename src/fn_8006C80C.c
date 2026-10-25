// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C80C-0x8006C8A0 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    void *unk0x0;   /* 0x00 */
    s32   unk0x4;   /* 0x04 */
    s32   unk0x8;   /* 0x08 */
    s32   unk0xC;   /* 0x0C */
    s32   unk0x10;  /* 0x10 */
    f32   unk0x14;  /* 0x14 */
    f32   unk0x18;  /* 0x18 */
    f32   unk0x1C;  /* 0x1C */
    s32   unk0x20;  /* 0x20 */
} Node6C80C;

s32  Mem_Alloc2(s32 arg0);
void fn_8006F4AC(s32 arg0, Node6C80C **arg1, Node6C80C *arg2);
extern s32 lbl_80301428;

void fn_8006C80C(s32 arg0, s32 *arg1, s32 *arg2, f32 farg0, f32 farg1, s32 arg3) {
    Node6C80C *n;
    struct { Node6C80C *p; s32 pad[5]; } sp8;
    s32 a;
    s32 b;
    s32 zero;
    register f32 t0 __asm__("fr31");

    a = *arg1;
    b = *arg2;
    zero = 0;
    t0 = farg0;
    n = (Node6C80C *)Mem_Alloc2(0x24);
    n->unk0x4 = a;
    n->unk0x8 = b;
    n->unk0x14 = t0;
    n->unk0x18 = t0;
    n->unk0x1C = farg1;
    n->unk0x10 = arg3;
    n->unk0x20 = zero;
    n->unk0x0 = (void *)arg0;
    sp8.p = n;
    fn_8006F4AC(lbl_80301428, &sp8.p, n);
}
