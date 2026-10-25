// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FEC98-0x801FECF4 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AE96C[];
extern s32 fn_80128A90(CStruct * arg0, void * arg1);
s32 fn_801FEC98(Unk_31DE137E *arg0, s32 arg1, CStruct *arg2) {
    register s32 var_r3 __asm__("r3");

    var_r3 = 2;
    if (arg1 == QB_OBJ_ALLOWSKITCHING) {
        arg0->unk0x1C = fn_80128A90(arg2, (s32)lbl_802AE96C) == 0;
        var_r3 = 1;
    }
    return var_r3;
}
