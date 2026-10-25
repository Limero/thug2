// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E21C-0x8013E27C (96B). Byte-identical.
#include "types.h"
#include "structs.h"
u32 fn_8013F800(Unk_FFAD6788 *);                            
s32 fn_8013F810(Unk_A99C4F7E *);                            

bool fn_8013E21C(s32 *arg0,Unk_A99C4F7E * arg1) {
    u32 temp_r30;

    temp_r30 = *arg0 - arg1->unk0x78;
    if ((temp_r30 >= fn_8013F800(arg1)) || (fn_8013F810(arg1) != 0)) {
        return true;
    }
    return false;
}
