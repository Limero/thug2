// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6CCC-0x801F6D0C (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F443C(Unk_AF33B3CC *);                               
s32 fn_801F5898();                                  

bool fn_801F6CCC(void) {
    s32 temp_r3;

    temp_r3 = fn_801F5898();
    if ((temp_r3 == 0) || (fn_801F443C(temp_r3) == 0)) {
        return false;
    }
    return true;
}
