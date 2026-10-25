// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013442C-0x801344E0 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029EFF8[];
void fn_80134A30(CStruct *);
s32 fn_80134A44(CStruct *, s32 *);
void fn_80134B00(CStruct *, s32 *);
void fn_80134368(Unk_9994C3F5 *, s32);
void fn_80134C54(CStruct *, s32);
void fn_8009C8A8(Unk_C8FEE62D *, s32);
void fn_8013442C(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_C8FEE62D *var_r31;

    arg0->unk0x14 = (s32)lbl_8029EFF8;
    fn_80134A30((void *)arg0->unk0x18);
    var_r31 = (void *)fn_80134A44(arg0->unk0x18, 0);
    if (var_r31 != NULL) {
        do {
            fn_80134B00((void *)arg0->unk0x18, (char *)var_r31 + 4);
            var_r31->unk0x10 = 0;
            var_r31->unk0x14 = 0;
            if (var_r31 != NULL) {
                fn_80134368(var_r31, 3);
            }
            var_r31 = (void *)fn_80134A44(arg0->unk0x18, 0);
        } while (var_r31 != NULL);
    }
    if (arg0->unk0x18 != 0) {
        fn_80134C54((void *)arg0->unk0x18, 3);
    }
    fn_8009C8A8(arg0, arg1);
}
