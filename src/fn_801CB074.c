// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CB074-0x801CB0C4 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801CB074(Unk_31DE137E *arg0) {
    __ps_t *d = (__ps_t *)arg0;
    __ps_t *src;
    __ps_t *dst2;
    __ps_t *s2;

    __asm__("" : "=r"(src) : "r"(*((__ps_t * *)&arg0->unk0x64)));
    __asm__("" : "=r"(dst2) : "r"((__ps_t *)((char *)arg0 + 0x20)));
    d[4] = src[4];
    __asm__("" : "=r"(s2) : "r"((__ps_t *)((char *)src + 0x20)));
    d[5] = src[5];
    d[6] = src[6];
    d[7] = src[7];
    dst2[4] = s2[4];
    dst2[5] = s2[5];
    d[10] = src[10];
    d[11] = src[11];
}
