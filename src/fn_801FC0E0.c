// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC0E0-0x801FC11C (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void* lbl_80301A38;
s32 fn_800A398C(s32 arg0, s32 arg1);
s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);

void fn_801FC0E0(void) {
    GetChecksum_3(fn_800A398C(lbl_80301A38, QB_RAILEDITOR), QB_RAILEDITOR);
}
