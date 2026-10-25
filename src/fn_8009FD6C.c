// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FD6C-0x8009FDD8 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009FACC(Unk_6A70655D *);
void fn_8009FD6C(Unk_6A70655D *arg0) {
    Unk_89391A04 *temp_r9;
    void *var_r31;

    var_r31 = arg0->unk0x110;
    if (var_r31 != NULL) {
        do {
            temp_r9 = ((Unk_C8FEE62D *)var_r31)->unk0x18;
            temp_r9->unk0x24(var_r31 + temp_r9->unk0x20);
            var_r31 = ((Unk_C8FEE62D *)var_r31)->unk0x10;
        } while (var_r31 != NULL);
    }
    arg0->unk0x114 = (s32) (arg0->unk0x114 | 0x60);
    fn_8009FACC(arg0);
}
