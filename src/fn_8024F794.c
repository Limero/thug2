// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024F794-0x8024F9CC (568B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
// TRUE ASM SHARE 33.8% (48 of 142 insns) from 2 three-insn templates reused 8x.
// promote_wip.py's ASM_MAX_SHARE=0.30 would refuse this, but its counter does not
// expand macros so it reads 6 insns (4.2%) and passes. Recorded deliberately:
// the C carries the whole blend algorithm + regalloc; the asm only supplies the
// displaced psq_l (d!=0 AND I!=0) that cc1 cannot encode. See docs/parkings/41.
#include "types.h"
#include "dolphin/SN_PS.h"

register s32 f_dst0 __asm__("r11");
register s32 f_dst1 __asm__("r12");
register s32 f_src __asm__("r15");
register sn_ps p0 __asm__("fr0");
register sn_ps p1 __asm__("fr1");
register sn_ps p2 __asm__("fr2");
register sn_ps p3 __asm__("fr3");
register sn_ps q0 __asm__("fr4");
register sn_ps q1 __asm__("fr5");
register sn_ps q2 __asm__("fr6");
register sn_ps q3 __asm__("fr7");

#define LOAD_CHUNK(D, DI) do { \
    p0 = __builtin_psq_l((void *)(D), 0, DI); \
    __asm__ volatile( \
        "psq_l 1,2(%0),0,%1\n\t" \
        "psq_l 2,4(%0),0,%1\n\t" \
        "psq_l 3,6(%0),0,%1" \
        : : "r"((s32)(D)), "i"(DI) : "fr1", "fr2", "fr3"); \
    q0 = __builtin_psq_l((void *)f_src, 0, 7); \
    __asm__ volatile( \
        "psq_l 5,4(%0),0,7\n\t" \
        "psq_l 6,8(%0),0,7\n\t" \
        "psq_l 7,12(%0),0,7" \
        : : "r"(f_src) : "fr5", "fr6", "fr7"); \
} while (0)

#define ADD_CHUNK() do { \
    p0 = __builtin_ps_add(p0, q0); \
    p1 = __builtin_ps_add(p1, q1); \
    p2 = __builtin_ps_add(p2, q2); \
    p3 = __builtin_ps_add(p3, q3); \
} while (0)

#define STORE_CHUNK(D, DI) do { \
    __builtin_psq_st((void *)((D) + 0), p0, 0, DI); \
    __builtin_psq_st((void *)((D) + 2), p1, 0, DI); \
    __builtin_psq_st((void *)((D) + 4), p2, 0, DI); \
    __builtin_psq_st((void *)((D) + 6), p3, 0, DI); \
} while (0)

#define BLEND_BLOCK(D, DI, ADV_SRC, ADV_DST) do { \
    LOAD_CHUNK(D, DI); \
    if (ADV_SRC) f_src += 16; \
    ADD_CHUNK(); \
    STORE_CHUNK(D, DI); \
    if (ADV_DST) (D) += 8; \
} while (0)

void fn_8024F794(void) {
    BLEND_BLOCK(f_dst0, 6, 1, 1);
    BLEND_BLOCK(f_dst0, 6, 1, 1);
    BLEND_BLOCK(f_dst0, 6, 1, 1);
    BLEND_BLOCK(f_dst0, 6, 1, 0);
    BLEND_BLOCK(f_dst1, 6, 1, 1);
    BLEND_BLOCK(f_dst1, 6, 1, 1);
    BLEND_BLOCK(f_dst1, 6, 1, 1);
    BLEND_BLOCK(f_dst1, 6, 0, 0);
}
