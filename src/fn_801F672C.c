// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F672C-0x801F6768 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void* lbl_80301A38;
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);

void fn_801F672C(void) {
    GetChecksum_3(fn_800A398C(lbl_80301A38, QB_GOALEDITOR), QB_GOALEDITOR);
}
