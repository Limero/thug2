// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B74B4-0x800B7508 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80298B78[];
extern void fn_8009F558(void *);
void fn_800B74B4(Unk_C8FEE62D *arg0) {
    Unk_C7387A53 *temp_r10;

    temp_r10 = arg0->unk0x1C;
    arg0->unk0x18 = (s32)lbl_80298B78;
    if (temp_r10 != NULL) {
        temp_r10->unk0x2C = 0;
        arg0->unk0x1C = NULL;
    }
    arg0->unk0x4C = 0;
    fn_8009F558(arg0);
}
