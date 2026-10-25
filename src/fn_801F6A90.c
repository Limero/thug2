// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6A90-0x801F6AD0 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F5898(s32);
s32 fn_801F4374(Unk_5FCDF30E *, CStruct *);
bool fn_801F6A90(void *arg0, CStruct *arg1) {
    s32 temp_r3;

    temp_r3 = fn_801F5898(arg0);
    if (temp_r3 != 0) {
        fn_801F4374(temp_r3, arg1);
    }
    return true;
}
