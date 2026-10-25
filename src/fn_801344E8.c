// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801344E8-0x80134524 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801344E8(CScript *arg0, Unk_C8FEE62D *arg1) {
    Unk_C8FEE62D *temp_r9;

    arg1->unk0x14 = 0;
    arg1->unk0x10 = (void *) arg0->unk0x1C;
    arg0->unk0x1C = arg1;
    temp_r9 = arg1->unk0x10;
    if (temp_r9 != NULL) {
        temp_r9->unk0x14 = arg1;
    }
    if ((void *) arg0->unk0x20 == NULL) {
        arg0->unk0x20 = (void *) arg0->unk0x1C;
    }
}
