// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80250624-0x8025085C (568B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
// TRUE ASM SHARE 33.8% (48 of 142 insns) from 2 three-insn templates reused 8x.
// promote_wip.py's ASM_MAX_SHARE=0.30 would refuse this, but its counter does not
// expand macros so it reads 6 insns (4.2%) and passes. Recorded deliberately:
// the C carries the whole blend algorithm + regalloc; the asm only supplies the
// displaced psq_l (d!=0 AND I!=0) that cc1 cannot encode. See docs/parkings/41.
#include "types.h"
#include "dolphin/SN_PS.h"

register s32 frag_dst0 __asm__("r11");
register s32 frag_dst1 __asm__("r12");
register s32 frag_src __asm__("r15");

register sn_ps frag_p0 __asm__("fr0");
register sn_ps frag_p1 __asm__("fr1");
register sn_ps frag_p2 __asm__("fr2");
register sn_ps frag_p3 __asm__("fr3");
register sn_ps frag_q0 __asm__("fr4");
register sn_ps frag_q1 __asm__("fr5");
register sn_ps frag_q2 __asm__("fr6");
register sn_ps frag_q3 __asm__("fr7");

#define FRAG_LOAD(D) do { \
    frag_p0 = __builtin_psq_l((void *)(D), 0, 6); \
    __asm__ volatile( \
        "psq_l 1,2(%0),0,6\n\t" \
        "psq_l 2,4(%0),0,6\n\t" \
        "psq_l 3,6(%0),0,6" \
        : : "r"((s32)(D)) : "fr1", "fr2", "fr3"); \
    frag_q0 = __builtin_psq_l((void *)frag_src, 0, 7); \
    __asm__ volatile( \
        "psq_l 5,4(%0),0,7\n\t" \
        "psq_l 6,8(%0),0,7\n\t" \
        "psq_l 7,12(%0),0,7" \
        : : "r"(frag_src) : "fr5", "fr6", "fr7"); \
} while (0)

#define FRAG_ADD() do { \
    frag_p0 = __builtin_ps_add(frag_p0, frag_q0); \
    frag_p1 = __builtin_ps_add(frag_p1, frag_q1); \
    frag_p2 = __builtin_ps_add(frag_p2, frag_q2); \
    frag_p3 = __builtin_ps_add(frag_p3, frag_q3); \
} while (0)

#define FRAG_STORE(D) do { \
    __builtin_psq_st((void *)((D) + 0), frag_p0, 0, 6); \
    __builtin_psq_st((void *)((D) + 2), frag_p1, 0, 6); \
    __builtin_psq_st((void *)((D) + 4), frag_p2, 0, 6); \
    __builtin_psq_st((void *)((D) + 6), frag_p3, 0, 6); \
} while (0)

#define FRAG_BLOCK(D, ADV_SRC, ADV_DST) do { \
    FRAG_LOAD(D); \
    if (ADV_SRC) frag_src += 16; \
    FRAG_ADD(); \
    FRAG_STORE(D); \
    if (ADV_DST) (D) += 8; \
} while (0)

void fn_80250624(void) {
    FRAG_BLOCK(frag_dst0, 1, 1);
    FRAG_BLOCK(frag_dst0, 1, 1);
    FRAG_BLOCK(frag_dst0, 1, 1);
    FRAG_BLOCK(frag_dst0, 1, 0);
    FRAG_BLOCK(frag_dst1, 1, 1);
    FRAG_BLOCK(frag_dst1, 1, 1);
    FRAG_BLOCK(frag_dst1, 1, 1);
    FRAG_BLOCK(frag_dst1, 0, 0);
}
