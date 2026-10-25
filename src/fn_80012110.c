// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012110-0x80012154 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 *fn_80012110(Unk_C8FEE62D *arg0) {
    s32 *temp_r3;
    s32 temp_r9;

    if ((s32 *) arg0->unk0x14 != NULL) {
        temp_r9 = arg0->unk0x10 + 1;
        arg0->unk0x10 = temp_r9;
        if (temp_r9 > (s32) arg0->unk0x58) {
            arg0->unk0x58 = temp_r9;
        }
        temp_r3 = arg0->unk0x14;
        arg0->unk0x14 = (s32 *) *temp_r3;
        return temp_r3;
    }
    return NULL;
}
