// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6CCC-0x800B6D30 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802989C4;
extern char lbl_802989E8[];
void *fn_800B6CCC(Unk_DB0E2BAB *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802989E8;
    arg0->unk0x4 = QB_MODELLIGHTUPDATE;
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x24 = 0;
    *((f32 *)&arg0->unk0x28) = lbl_802989C4;
    return arg0;
}
