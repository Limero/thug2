// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E3C4-0x8018E400 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, void *);
s32 fn_8018E3C4(Unk_C7387A53 *);
s32 fn_8018E3C4(Unk_C7387A53 *arg0) {
    s32 var_r3;

    
    return ( !(ContainsFlag(arg0->unk0x20, QB_EDITED_GOAL) == 0) );
}
