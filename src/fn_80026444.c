// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026444-0x800264A0 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80014898(s32);
s32 fn_8002632C(s32, void *);
s32 fn_800147E8(Unk_C8FEE62D *, void *);
extern char lbl_802915C8[];
extern char lbl_80362CD8[];
s32 fn_80026444(Unk_C8FEE62D *arg0) {
    s32 temp_r3;
    s32 var_r30;

    var_r30 = 0;
    temp_r3 = fn_800147E8(arg0, (s32)lbl_802915C8);
    if (temp_r3 != 0) {
        var_r30 = fn_8002632C(temp_r3, (s32)lbl_80362CD8);
    }
    fn_80014898(temp_r3);
    return var_r30;
}
