// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4628-0x801F467C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
bool fn_801F4628(Unk_13D0EFB0 *arg0, __ps_t *arg1, f32 *arg2, f32 *arg3) {
    __ps_t *src;

    __asm__("" : "=r"(src)
            : "r"((char *)(((arg0->unk0x2BB << 5) + (s32)arg0)) + 0x120));
    arg1[0] = src[0];
    arg1[1] = src[1];
    *arg2 = *(f32 *)((char *)arg0 + (arg0->unk0x2BB << 5) + 0x130);
    *arg3 = *(f32 *)((char *)arg0 + (arg0->unk0x2BB << 5) + 0x134);
    return true;
}
