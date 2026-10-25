// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B07B4-0x800B0844 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern CStruct * lbl_80301B08;
void fn_800B0C28(CStruct *);
s32 fn_800B0C3C(CStruct *, s32 *);
void fn_800B07B4(s32 arg0, s32 arg1) {
    CStruct *var_r3;
    s32 v;

    fn_800B0C28(lbl_80301B08);
    var_r3 = fn_800B0C3C(lbl_80301B08, 0);
    while (var_r3 != NULL) {
        if (var_r3->unk0x4 == arg0) {
            v = 1;
            if (arg1 == 0) {
                v = 0;
            }
            var_r3->unk0x28 = v;
            return;
        }
        var_r3 = fn_800B0C3C(lbl_80301B08, 0);
    }
}
