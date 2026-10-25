// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80187934-0x801879D8 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 fn_80198F7C(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);

s32 fn_80187934(Unk_6BF95B44 *arg0, s32 arg1) {
    s32 sp8;
    s32 var_r3;
    s32 var_r4;

    if (arg1 != 0) {
        var_r4 = QB_CAREER;
    } else {
        var_r4 = fn_80198F7C(lbl_80305EC0);
    }
    if (GetInteger(arg0->unk0x3A8, var_r4, &sp8, 0) == 0) {
        sp8 = 1;
    }
    var_r3 = 1;
    switch (sp8) {
    case 0:
        var_r3 = 0;
        break;
    case 1:
        break;
    case 2:
        var_r3 = 2;
        break;
    }
    return var_r3;
}
