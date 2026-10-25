// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0214-0x800B029C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800ADCD4(void *);
s32 fn_800AE234(void *);
s32 fn_800B0214(CScript *arg0) {
    s32 var_r30;
    s32 var_r3;

    if ((s32) arg0->unk0x24 != 0) {
        var_r3 = 1;
        goto block_5;
    }
    if ((s32) arg0->unk0x1C != 0) {
        var_r3 = 0;
        goto block_5;
    }
    if ((s32) arg0->unk0x3C == 0) {
        goto block_6;
    }
    var_r30 = 0;
    if ((fn_800ADCD4(arg0->unk0x3C) != 0) && (fn_800AE234(arg0->unk0x3C) != 0)) {
        var_r30 = 1;
    }
    var_r3 = var_r30;
block_5:
    return var_r3;
block_6:
    return 0;
}
