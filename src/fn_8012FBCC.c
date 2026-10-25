// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012FBCC-0x8012FC30 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8009CF2C(CStruct *);
s32 fn_8012FAFC(CStruct *, s32, Unk_6A70655D *, void *);
extern char lbl_80305F9C[];
s32 fn_8012FBCC(Unk_15EF4A35 *arg0, CStruct *arg1, s32 arg2) {
    s32 var_r31;
    s32 var_r5;

    var_r5 = arg2;
    if (var_r5 == 0) {
        var_r5 = arg0->unk0xBC;
    }
    var_r31 = 0;
    if (var_r5 != 0) {
        var_r31 = fn_8012FAFC(arg1, arg0->unk0x14, var_r5, arg0);
    } else {
        fn_8009CF2C(*(s32 *)&lbl_80305F9C);
    }
    return var_r31;
}
