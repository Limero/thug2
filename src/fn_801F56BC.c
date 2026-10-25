// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F56BC-0x801F56F0 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801F56BC(Unk_E7466DF4 *arg0, __ps_t *arg1, f32 *arg2, f32 *arg3) {
    Unk_3190581D *p = arg0->unk0xAC08;
    arg1[0] = p->unk0x40;
    arg1[1] = p->unk0x48;
    *arg2 = *(f32 *)((char *)arg0->unk0xAC08 + 0x8C);
    *arg3 = *(f32 *)((char *)arg0->unk0xAC08 + 0x7C);
}
