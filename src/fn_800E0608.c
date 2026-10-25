// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E0608-0x800E067C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern u8 lbl_8029A5CC;
extern f32 lbl_8029A5D0;
extern char lbl_8029A5F8[];
void *fn_800E0608(Unk_C5F4A878 *arg0) {
    s32 p;
    s32 h;
    f32 fv;
    u8 bv;
    s32 z;
    fn_8009F53C();
    p = (s32)lbl_8029A5F8;
    h = QB_FLOATINGLABEL;
    arg0->unk0x18 = p;
    arg0->unk0x4 = h;
    bv = lbl_8029A5CC;
    fv = lbl_8029A5D0;
    z = 0;
    arg0->unk0x5C = 2;
    arg0->unk0x1C = bv;
    arg0->unk0x60 = fv;
    arg0->unk0x64 = z;
    arg0->unk0x68 = z;
    return arg0;
}
