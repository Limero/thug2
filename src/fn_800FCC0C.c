// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCC0C-0x800FCCD8 (204B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800FCC0C(Unk_C8FEE62D *arg0, Unk_DB0E2BAB *arg1) {
    s32 var_r0;
    s32 var_r3;

    if ((s32) arg0->unk0x38 != 0) {
        fn_800FCAA4();
        arg0->unk0x38 = 0;
    }
    var_r3 = 0;
    if ((s32) arg0->unk0x3C != 0) {
        if ((*((f32 *)&arg1->unk0x0) > *((f32 *)&arg0->unk0x28)) || (*((f32 *)&arg0->unk0x18) > *((f32 *)&arg1->unk0x10)) || (*((f32 *)&arg1->unk0x8) > *((f32 *)&arg0->unk0x30)) || (*((f32 *)&arg0->unk0x20) > *((f32 *)&arg1->unk0x18)) || (*((f32 *)&arg1->unk0x4) > *((f32 *)&arg0->unk0x2C)) || (*((f32 *)&arg0->unk0x1C) > *((f32 *)&arg1->unk0x14))) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            goto block_12;
        }
    } else {
block_12:
        var_r3 = 1;
    }
    return var_r3;
}
