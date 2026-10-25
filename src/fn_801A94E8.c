// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A94E8-0x801A9528 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A94E8(s32 arg0) {
    Unk_F5317C5D *temp_r9;

    if (arg0 != NULL) {
        temp_r9 = *((s32 * *)&((Unk_C8FEE62D *)arg0)->unk0x14);
        ((s32 (*)(s32, s32)) * (s32 *)((char *)temp_r9 + (s32)0xC))(arg0 + temp_r9->unk0x8, 3);
    }
}
