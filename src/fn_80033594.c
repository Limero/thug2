// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033594-0x800335C8 (52B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80033594(s32 arg0, CStruct *arg1) {
    GetChecksum_2(arg1, QB_ID, arg0 + 0x10, 0);
}
