// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F70E4-0x801F7114 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F5898(void);
s32 fn_801F4D6C(Unk_5FCDF30E *);
bool fn_801F70E4(void) {
    s32 temp_r3;

    temp_r3 = fn_801F5898();
    if (temp_r3 != 0) {
        fn_801F4D6C(temp_r3);
    }
    return true;
}
