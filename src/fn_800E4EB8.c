// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E4EB8-0x800E4F28 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029A9DC;
extern char lbl_8029A9F0[];
void *fn_800E4EB8(Unk_528843D8 *arg0) {
    s32 var_ctr;

    fn_8009F53C();
    var_ctr = 5;
    arg0->unk0x18 = (s32)lbl_8029A9F0;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x70 = 0;
    arg0->unk0x4 = QB_BLINK;
    *((f32 *)&arg0->unk0x7C) = lbl_8029A9DC;
    arg0->unk0x74 = 0;
    arg0->unk0x80 = 0;
    return arg0;
}
