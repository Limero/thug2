// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FE094-0x800FE130 (156B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern void fn_800073AC(void *, void *, s32, s32);

void fn_800FE094(void *arg0) {
    volatile __ps_t dst[8];
    register char *a0 __asm__("r10");
    register __ps_t *src __asm__("r11");
    register void *dst4 __asm__("r4");
    register __ps_t *p __asm__("r9");

    __asm__ volatile("li 0, 4\n\tmr %0, %4\n\tmtctr 0\n\taddi %1, 1, 8\n\taddi %2, %0, 0x20\n\tmr %3, %1\n\t.long 0x42000000"
                     : "=r"(a0), "=r"(p), "=r"(src), "=r"(dst4)
                     : "r"(arg0));

    p[0] = src[0];
    p[1] = src[1];
    p[2] = src[2];
    p[3] = src[3];
    p[4] = src[4];
    p[5] = src[5];
    p[6] = src[6];
    p[7] = src[7];
    dst[6] = ((Unk_BE223D5D *)a0)->unk0x10;
    dst[7] = ((Unk_BE223D5D *)a0)->unk0x18;
    fn_800073AC(a0 + 0xA8, dst4, 0x80808080u, 1);
}
