// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A470-0x8022A510 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80198F7C(s32);
void *GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_801813F0(CStruct *);
extern s32 lbl_80305EC0;
s32 fn_8022A470(CScript *arg0) {
    s32 var_r9;
    Unk_31DE137E *temp_r3;
    s32 temp_r0;
    s32 var_r3;

    var_r9 = 1;
    if (!(arg0->unk0x1D8 & 0x20000)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        return 1;
    }
    if ((fn_80198F7C(lbl_80305EC0) == QB_NETFIREFIGHT) && (arg0->unk0x18 != 0) && (temp_r3 = GetChecksum_3(arg0->unk0x18, QB_SKATERSCORE), temp_r3 != NULL)) {
        temp_r0 = fn_801813F0(temp_r3->unk0x1C);
        var_r3 = 1;
        if (temp_r0 != 0) {
            goto block_4;
        }
        return var_r3;
    }
block_4:
    var_r3 = 0;
    return var_r3;
}
