// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102230-0x801022D4 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_80105B40(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
typedef struct {
    volatile __ps_t p[8];
} Buf40;
void fn_80102230(Unk_9994C3F5 *arg0, s32 arg1, s32 arg2) {
    Buf40 local;
    volatile __ps_t *dst;
    __ps_t *src;
    register void *buf __asm__("r8");
    s32 i;

    dst = (volatile __ps_t *)&local;
    src = (__ps_t *)((char *)arg0 + 0x20);
    buf = (void *)dst;
    for (i = 4; i != 0; i--) {
        __asm__ volatile("");
    }
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    ((volatile __ps_t *)&local)[6] = *(__ps_t *)((char *)arg0 + 0x10);
    ((volatile __ps_t *)&local)[7] = *(__ps_t *)((char *)arg0 + 0x18);
    i = 1;
    fn_80105B40(arg0->unk0x8, (void *)buf, arg1, arg2, i);
}
