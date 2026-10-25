// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F84C-0x8009F8AC (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F094(Unk_C8FEE62D *);
void fn_8009F84C(Unk_6A70655D *arg0) {
    Unk_B1B57F13 *temp_r9;
    void *var_r31;

    var_r31 = arg0->unk0x110;
    if (var_r31 != NULL) {
        do {
            temp_r9 = ((Unk_C8FEE62D *)var_r31)->unk0x18;
            ((s32 (*)(void *))temp_r9->unk0x2C)(var_r31 + temp_r9->unk0x28);
            var_r31 = ((Unk_C8FEE62D *)var_r31)->unk0x10;
        } while (var_r31 != NULL);
    }
    fn_8009F094(arg0);
}
