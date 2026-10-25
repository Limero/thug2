// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CCF64-0x801CCF80 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801CCF64(s32 arg0, Unk_C7387A53 *arg1) {
    register __ps_t *src __asm__("r11");
    register __ps_t *dst __asm__("r9");

    src = *((__ps_t * *)&arg1->unk0xC);
    __asm__("mr %0,%1" : "=r"(dst) : "r"(arg0));
    dst[0] = src[11];
    dst[1] = src[12];
}
