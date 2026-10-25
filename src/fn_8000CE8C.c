// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CE8C-0x8000CF10 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8000E864(CStruct *);
CStruct *fn_8000E878(CStruct *, s32);
s32 fn_8000CE8C(CStruct *arg0, s32 arg1) {
    CStruct *temp_r3;

    fn_8000E864(arg0->unk0xC);
    goto test;
body:
    if (((s32) temp_r3->unk0x4 != 0) && (temp_r3 == arg1)) {
        arg0->unk0x10 = temp_r3;
        if ((s32) temp_r3->unk0x0 != 0) {
            return temp_r3->unk0x8;
        }
        return temp_r3->unk0x4;
    }
test:
    temp_r3 = fn_8000E878(arg0->unk0xC, 0);
    if (temp_r3 != NULL) {
        goto body;
    }
    return 0;
}