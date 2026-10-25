// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024F360-0x8024F4B0 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

register s32 f_src __asm__("r6");
register s32 f_pitch __asm__("r8");
register s32 f_dst __asm__("r11");
register s32 f_dst2 __asm__("r12");

#define LOAD_ZERO(P) P = ps_l((void *)(f_src), 0, 7)
#define LOAD_I7(P, OFF) __asm__ volatile("psq_l %0," #OFF "(6),0,7" : "=f"(P))
#define STORE_I7(D, OFF, P) ps_st((void *)((D) + (OFF)), P, 0, 7)
#define COPY_BLOCK(D) do { \
    LOAD_ZERO(p0); \
    LOAD_I7(p1, 4); \
    LOAD_I7(p2, 8); \
    LOAD_I7(p3, 12); \
    f_src += 16; \
    STORE_I7(D, 0, p0); \
    STORE_I7(D, 2, p1); \
    STORE_I7(D, 4, p2); \
    STORE_I7(D, 6, p3); \
} while (0)

void fn_8024F360(void) {
    register sn_ps p0 __asm__("fr0");
    register sn_ps p1 __asm__("fr1");
    register sn_ps p2 __asm__("fr2");
    register sn_ps p3 __asm__("fr3");

    f_dst2 = f_dst + f_pitch;
    __asm__ volatile("dcbz 0,%0" :: "r"(f_dst));
    COPY_BLOCK(f_dst); f_dst += 8;
    COPY_BLOCK(f_dst); f_dst += 8;
    COPY_BLOCK(f_dst); f_dst += 8;
    COPY_BLOCK(f_dst);
    __asm__ volatile("dcbst 0,%0" :: "r"(f_dst));
    __asm__ volatile("dcbz 0,%0" :: "r"(f_dst2));
    COPY_BLOCK(f_dst2); f_dst2 += 8;
    COPY_BLOCK(f_dst2); f_dst2 += 8;
    COPY_BLOCK(f_dst2); f_dst2 += 8;
    COPY_BLOCK(f_dst2);
    __asm__ volatile("dcbst 0,%0" :: "r"(f_dst2));
}
