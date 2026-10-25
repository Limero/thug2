// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F8AC-0x8009F9AC (256B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern float lbl_80297B5C;
void fn_801309EC(Unk_DB0E2BAB *);
void fn_8009F8AC(Unk_04F8D4E7 *arg0) {
    s32 temp_r0;
    s32 var_r9;
    s32 var_r9_2;
    s32 var_r9_3;
    Unk_07FDFB02 *temp_r9;
    Unk_89391A04 *temp_r9_2;
    void *var_r31;

    var_r9 = 1;
    temp_r0 = arg0->unk0x114;
    if (!(temp_r0 & 1)) {
        var_r9 = 0;
    }
    if (var_r9 == 0) {
        var_r9_2 = 1;
        if (!(temp_r0 & 2)) {
            var_r9_2 = 0;
        }
        if (var_r9_2 == 0) {
            if ((s32) arg0->unk0x14 != 0) {
                fn_801309EC(arg0->unk0x14);
            }
            if (!(arg0->unk0xC & 1)) {
                temp_r9 = arg0->unk0x8;
                ((s32 (*)(void *))temp_r9->unk0x5C)((char *)arg0 + temp_r9->unk0x58);
                goto block_10;
            }
        } else {
block_10:
            var_r31 = arg0->unk0x110;
            if (var_r31 != NULL) {
loop_11:
                var_r9_3 = 1;
                if (!(((Unk_C8FEE62D *)var_r31)->unk0x8 & 1)) {
                    var_r9_3 = 0;
                }
                if ((var_r9_3 != 0) || (temp_r9_2 = ((Unk_C8FEE62D *)var_r31)->unk0x18, ((s32 (*)(void *))temp_r9_2->unk0x14)(var_r31 + temp_r9_2->unk0x10), (((arg0->unk0xC & 1) == 0) != 0))) {
                    var_r31 = ((Unk_C8FEE62D *)var_r31)->unk0x10;
                    if (var_r31 != NULL) {
                        goto loop_11;
                    }
                }
            }
            arg0->unk0x64 = lbl_80297B5C;
            arg0->unk0x114 = (s32) (arg0->unk0x114 & QB_UNKNOWN_0xFFFFFFF7);
        }
    }
}
