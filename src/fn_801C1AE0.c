// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1AE0-0x801C1B40 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AC8F4;
extern char lbl_802AC908[];
void *fn_8009F53C(Unk_DB0E2BAB *arg0);
void *fn_801C1AE0(Unk_DB0E2BAB *arg0) {
    f32 temp_f0;

    fn_8009F53C(arg0);
    temp_f0 = lbl_802AC8F4;
    arg0->unk0x18 = (s32)lbl_802AC908;
    arg0->unk0x4 = QB_SKATERSOUND;
    arg0->unk0x24 = 0;
    *(f32 *)((char *)arg0 + 0x28) = temp_f0;
    *(f32 *)((char *)arg0 + 0x2C) = temp_f0;
    return arg0;
}
