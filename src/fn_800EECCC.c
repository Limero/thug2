// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EECCC-0x800EED20 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029B030[];
void *fn_800EECCC(Unk_C8FEE62D *arg0) {
    s32 var_ctr;

    fn_8009F53C();
    var_ctr = 4;
    arg0->unk0x18 = (s32)lbl_8029B030;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x4 = QB_UNKNOWN_0x9649D4F9;
    return arg0;
}
