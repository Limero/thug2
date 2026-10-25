// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FAFD4-0x801FB004 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void fn_801FAFD4(Unk_C7387A53 *arg0, __ps_t *arg1, f32 *arg2, f32 *arg3) {
    __ps_t *src;

    src = *((__ps_t * *)&arg0->unk0x20);
    arg1[0] = src[8];
    arg1[1] = src[9];
    *(f32 *)arg2 = *(f32 *)((char *)arg0->unk0x20 + 0x8C);
    *(f32 *)arg3 = *(f32 *)((char *)arg0->unk0x20 + 0x7C);
}
