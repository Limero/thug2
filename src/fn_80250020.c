// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80250020-0x80250170 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

register s32 f_src __asm__("r6");
register s32 f_dst __asm__("r11");
register s32 f_pitch __asm__("r8");

#define LOAD_CHUNK(S) do { \
    p0 = ps_l((void *)(S), 0, 7); \
    __asm__ volatile( \
        "psq_l 1,4(%0),0,7\n\t" \
        "psq_l 2,8(%0),0,7\n\t" \
        "psq_l 3,12(%0),0,7" \
        : : "r"((s32)(S)) : "fr1", "fr2", "fr3"); \
} while (0)

#define STORE_CHUNK(D) do { \
    ps_st((void *)((D) + 0), p0, 0, 7); \
    ps_st((void *)((D) + 2), p1, 0, 7); \
    ps_st((void *)((D) + 4), p2, 0, 7); \
    ps_st((void *)((D) + 6), p3, 0, 7); \
} while (0)

void fn_80250020(void) {
    register sn_ps p0 __asm__("fr0");
    register sn_ps p1 __asm__("fr1");
    register sn_ps p2 __asm__("fr2");
    register sn_ps p3 __asm__("fr3");

    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst); f_dst += 16;
    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst);
    __asm__ volatile("dcbst 0,%0" :: "r"(f_dst)); f_dst += f_pitch;

    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst); f_dst += 16;
    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst);
    __asm__ volatile("dcbst 0,%0" :: "r"(f_dst)); f_dst += f_pitch;

    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst); f_dst += 16;
    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst);
    __asm__ volatile("dcbst 0,%0" :: "r"(f_dst)); f_dst += f_pitch;

    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst); f_dst += 16;
    LOAD_CHUNK(f_src); f_src += 16; STORE_CHUNK(f_dst);
    __asm__ volatile("dcbst 0,%0" :: "r"(f_dst));
}
