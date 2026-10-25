// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FB184-0x800FB19C (24B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800FB184(CStruct *arg0, s32 arg1) {
    s32 *temp_r9;

    temp_r9 = arg0->unk0x8;
    arg0->unk0x0 = arg1;
    if (temp_r9 != NULL) {
        *temp_r9 = arg1;
    }
}
