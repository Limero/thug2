// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80175450-0x801754AC (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(s32, s32);
s32 fn_801754AC(s32);
s32 fn_80175450(s32 arg0, CStruct *arg1) {
    s32 var_r30;

    
    return (ContainsFlag(arg1, QB_ABSENTINNETGAMES) != 0) && (fn_801754AC(arg0) != 0);
}