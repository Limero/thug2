// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010284C-0x801028E4 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C928;
void *fn_8010284C(Unk_5B9516A4 *arg0) {
    if (arg0->unk0xAC != 0) {
        f32 base = arg0->unk0xA8;
        f32 tmp[4];
        tmp[0] = -base + arg0->unk0x10;
        tmp[1] = -base + arg0->unk0x14;
        tmp[2] = -base + arg0->unk0x18;
        tmp[3] = lbl_8029C928;
        arg0->unk0xAC = 0;
        arg0->unk0xB0 = *(__ps_t *)&tmp[0];
        arg0->unk0xB8 = *(__ps_t *)&tmp[2];
        tmp[0] = base + arg0->unk0x10;
        tmp[1] = base + arg0->unk0x14;
        tmp[2] = base + arg0->unk0x18;
        tmp[3] = lbl_8029C928;
        arg0->unk0xC0 = *(__ps_t *)&tmp[0];
        arg0->unk0xC8 = *(__ps_t *)&tmp[2];
    }
    return (char *)arg0 + 0xb0;
}
