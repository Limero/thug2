// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CDBCC-0x801CDC18 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
u32 fn_801CDA44(s32, s32);                          
u32 fn_801CDB68();                                  

s32 fn_801CDBCC(CStruct *arg0, s32 arg1) {
    u32 temp_r28;

    temp_r28 = fn_801CDB68();
    return temp_r28 < fn_801CDA44(arg0, arg1);
}
