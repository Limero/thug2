// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007FE50-0x8007FF34 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    char _p0[0x30];
    s32 unk0x30;
} A_t;

void fn_8007FE50(A_t *arg0, __ps_t *arg1) {
    volatile __ps_t sp8[8];
    __ps_t *sp;
    __ps_t *src;
    __ps_t *dst;
    register volatile __ps_t *sp1 __asm__("r8");
    s32 ctr;

    if (arg0->unk0x30 != 0) {
        sp = (__ps_t *)sp8;
        src = (__ps_t *)((char *)arg0->unk0x30 + 8);
        sp1 = sp;
        ctr = 4;
        do {
        } while (--ctr != 0);
        sp[0] = src[0];
        /* Second read of unk0x30. Statement position is load-bearing: it must
           follow the first volatile store, or CSE folds it into the guard's
           load (one lwz instead of two) and src/unk0x30 then share one
           register. Landing it here keeps the reload at +0x34 and splits
           unk0x30->r9 from src->r10. Do not hoist it next to the guard. */
        dst = (__ps_t *)arg0->unk0x30;
        sp[1] = src[1];
        sp[2] = src[2];
        sp[3] = src[3];
        sp[4] = src[4];
        sp[5] = src[5];
        sp[6] = src[6];
        sp[7] = src[7];
        sp8[5] = arg1[5];
        sp8[0] = arg1[0];
        sp1[1] = arg1[1];
        sp8[2] = arg1[2];
        sp8[3] = arg1[3];
        sp8[4] = arg1[4];
        dst[1] = sp8[0];
        dst[2] = sp1[1];
        dst[3] = sp8[2];
        dst[4] = sp8[3];
        dst[5] = sp8[4];
        dst[6] = sp8[5];
        dst[7] = sp8[6];
        dst[8] = sp8[7];
    }
}
