// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174A58-0x80174AB8 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(s32, s32, s32, s32);
extern char lbl_80305EFC[];
s32 fn_801A5D9C(s32, s32);
s32 fn_801A5D88(s32);
void fn_80174A58(void *arg0, CStruct *arg1) {
    s32 sp8;

    if ((arg1 != 0) && (GetInteger(arg1, QB_SKATER, &sp8, 0) != 0)) {
        fn_801A5D9C(*(s32 *)&lbl_80305EFC, sp8);
        return;
    }
    fn_801A5D88(*(s32 *)&lbl_80305EFC);
}