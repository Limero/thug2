// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE524-0x800DE594 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029A288[];
void fn_8009F53C(void);
void *fn_800DE524(Unk_C8FEE62D *arg0) {
    char *var_r9;
    s32 var_r10;

    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_8029A288;
    arg0->unk0x4 = QB_VIBRATION;
    arg0->unk0x1C = 0;
    var_r10 = 1;
    var_r9 = (char *)arg0 + 0x2C;
    do {
        *((s32 *)var_r9) = 0;
        var_r9 -= 0xC;
    } while (--var_r10 != -1);
    return arg0;
}
