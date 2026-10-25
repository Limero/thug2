// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CAF74-0x801CAFD0 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802ACFF8[];
void *fn_801CAF74(Unk_C8FEE62D *arg0) {
    s32 var_ctr;

    fn_8009F53C();
    var_ctr = 4;
    arg0->unk0x18 = (s32)lbl_802ACFF8;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x64 = 0;
    arg0->unk0x4 = QB_SKATERMATRIXQUERIES;
    return arg0;
}
