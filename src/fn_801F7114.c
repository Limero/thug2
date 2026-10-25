// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F7114-0x801F7168 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "types.h"
#include "structs.h"
s32 fn_801F5898(void);
s32 fn_801F4BB8(void *, s32);
s32 ContainsFlag(CStruct *, s32);
bool fn_801F7114(void *arg0, CStruct *arg1) {
    s32 temp_r3;

    temp_r3 = fn_801F5898();
    if (temp_r3 != 0) {
        fn_801F4BB8(temp_r3, ContainsFlag(arg1, QB_MARKUNBEATEN));
    }
    return true;
}
