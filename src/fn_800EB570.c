// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EB570-0x800EB5D0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029ACF8[];
void *fn_800EB570(Unk_C8FEE62D *arg0) {
    s32 var_ctr;

    fn_8009F53C();
    var_ctr = 4;
    arg0->unk0x18 = (s32)lbl_8029ACF8;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x1C = 0;
    arg0->unk0x4 = QB_MOVABLECONTACT;
    arg0->unk0x74 = 0;
    return arg0;
}
