// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EA18-0x8012EABC (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_80125600(void *);
void *fn_8012ED7C(s32);
s32 fn_80130D24(void *, s32);
void fn_8012F544(void *);
void fn_8012EA18(void) {
    s32 temp_r3;
    s32 var_r3;
    CStruct *var_r30;

    var_r30 = (CStruct *) fn_80125600(NULL);
    while (var_r30 != NULL) {
        if ((s32) (var_r30->unk0x0 & 0x80FF00) == 0x800700) {
            var_r3 = 0;
            while (1) {
                temp_r3 = (s32) fn_8012ED7C(var_r3);
                if (temp_r3 == 0) {
                    break;
                }
                if (fn_80130D24((void *) temp_r3, var_r30->unk0x4) != 0) {
                    fn_8012F544((void *) temp_r3);
                }
                var_r3 = temp_r3;
            }
            var_r30->unk0x0 = (s32) (var_r30->unk0x0 & QB_UNKNOWN_0xFF7FFFFF);
        }
        var_r30 = (CStruct *) fn_80125600(var_r30);
    }
}
