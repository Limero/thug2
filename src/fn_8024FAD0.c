// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024FAD0-0x8024FD8C (700B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

register s32 blend_stride __asm__("r8");
register s32 blend_dst0 __asm__("r11");
register s32 blend_src0 __asm__("r12");
register s32 blend_dst1 __asm__("r15");
register s32 blend_src1 __asm__("r16");

register sn_ps blend_scale __asm__("fr8");
register sn_ps q0 __asm__("fr0");
register sn_ps q1 __asm__("fr1");
register sn_ps q2 __asm__("fr2");
register sn_ps q3 __asm__("fr3");
register sn_ps q4 __asm__("fr4");
register sn_ps q5 __asm__("fr5");
register sn_ps q6 __asm__("fr6");
register sn_ps q7 __asm__("fr7");

#define QLOAD_DST_GAPS(D) __asm__ volatile( \
    "psq_l 1,2(%0),0,7\n\t" \
    "psq_l 2,4(%0),0,7\n\t" \
    "psq_l 3,6(%0),0,7" \
    : : "r"((s32)(D)) : "fr1", "fr2", "fr3")

#define QLOAD_SRC_GAPS(S) __asm__ volatile( \
    "psq_l 5,2(%0),0,7\n\t" \
    "psq_l 6,4(%0),0,7\n\t" \
    "psq_l 7,6(%0),0,7" \
    : : "r"((s32)(S)) : "fr5", "fr6", "fr7")

#define QLOAD(D, S) do { \
    q0 = __builtin_psq_l((void *)(D), 0, 7); \
    QLOAD_DST_GAPS(D); \
    q4 = __builtin_psq_l((void *)(S), 0, 7); \
    QLOAD_SRC_GAPS(S); \
} while (0)

#define QBLEND() do { \
    q0 = __builtin_ps_add(q0, q4); \
    q1 = __builtin_ps_add(q1, q5); \
    q2 = __builtin_ps_add(q2, q6); \
    q3 = __builtin_ps_add(q3, q7); \
    q0 = __builtin_ps_madd(q0, blend_scale, blend_scale); \
    q1 = __builtin_ps_madd(q1, blend_scale, blend_scale); \
    q2 = __builtin_ps_madd(q2, blend_scale, blend_scale); \
    q3 = __builtin_ps_madd(q3, blend_scale, blend_scale); \
} while (0)

#define QSTORE(D) do { \
    __builtin_psq_st((void *)((D) + 0), q0, 0, 7); \
    __builtin_psq_st((void *)((D) + 2), q1, 0, 7); \
    __builtin_psq_st((void *)((D) + 4), q2, 0, 7); \
    __builtin_psq_st((void *)((D) + 6), q3, 0, 7); \
} while (0)

void fn_8024FAD0(void) {
    blend_dst1 = blend_dst0 + blend_stride;
    blend_src1 = blend_src0 + blend_stride;

    QLOAD(blend_dst0, blend_src0); blend_src0 += 8; QBLEND(); QSTORE(blend_dst0); blend_dst0 += 8;
    QLOAD(blend_dst0, blend_src0); blend_src0 += 8; QBLEND(); QSTORE(blend_dst0); blend_dst0 += 8;
    QLOAD(blend_dst0, blend_src0); blend_src0 += 8; QBLEND(); QSTORE(blend_dst0); blend_dst0 += 8;
    QLOAD(blend_dst0, blend_src0); QBLEND(); QSTORE(blend_dst0);

    QLOAD(blend_dst1, blend_src1); blend_src1 += 8; QBLEND(); QSTORE(blend_dst1); blend_dst1 += 8;
    QLOAD(blend_dst1, blend_src1); blend_src1 += 8; QBLEND(); QSTORE(blend_dst1); blend_dst1 += 8;
    QLOAD(blend_dst1, blend_src1); blend_src1 += 8; QBLEND(); QSTORE(blend_dst1); blend_dst1 += 8;
    QLOAD(blend_dst1, blend_src1); QBLEND(); QSTORE(blend_dst1);
}
