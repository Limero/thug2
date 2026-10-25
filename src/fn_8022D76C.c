// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D76C-0x8022D7C0 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80240C80(void *);
void fn_8024144C(s32 *, s32, s32);
void fn_8022D76C(Unk_9994C3F5 *arg0, s32 arg1) {
    void *temp_r30;
    Unk_9994C3F5 *var_r30;
    void *ret;

    var_r30 = arg0->unk0x8;
    if (var_r30 != NULL) {
        do {
            temp_r30 = var_r30->unk0x8;
            ret = fn_80240C80(var_r30);
            fn_8024144C(ret, arg1, 0);
            var_r30 = temp_r30;
        } while (var_r30 != NULL);
    }
}
