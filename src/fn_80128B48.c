// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128B48-0x80128BF0 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

CStruct *fn_80127358(CStruct *head, CStruct *cur);
s32 fn_8012A958(s32, s32);

bool fn_80128B48(CStruct *arg0, CStruct *arg1) {
    CStruct *var_r30;
    CStruct *var_r31;
    CStruct *t;
    s32 var_r28;

    var_r30 = arg0->unk0x4;
    if (var_r30 != 0) {
        do {
            t = fn_80127358(arg1, 0);
            var_r28 = 0;
            goto chk_1;
        nxt_1:
            t = fn_80127358(arg1, var_r31);
        chk_1:
            var_r31 = t;
            if (var_r31 != 0) {
                if (var_r30->unk0x4 != var_r31->unk0x4) {
                    goto nxt_1;
                }
                if (fn_8012A958(var_r30, var_r31) == 0) {
                    goto nxt_1;
                }
                var_r28 = 1;
            }
            if (var_r28 == 0) {
                return false;
            }
            var_r30 = var_r30->unk0xC;
        } while (var_r30 != 0);
    }
    return true;
}
