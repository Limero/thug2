// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F467C-0x801F46B0 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801F467C(s32 arg0, __ps_t *arg1, s32 arg2) {
    __ps_t *src;

    arg2 <<= 5;
    __asm__("" : "=r"(src) : "r"((char *)(arg2 + (s32)arg0) + 0x120));
    arg1[0] = src[0];
    arg1[1] = src[1];
    __asm__("" : "+r"(arg2));
    arg0 = (s32)((char *)arg0 + arg2);
    *((f32 *)&((CStruct *)arg1)->unk0x4) += *((f32 *)&((Unk_FFAD6788 *)arg0)->unk0x130);
}
