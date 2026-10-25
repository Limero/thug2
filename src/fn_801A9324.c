// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9324-0x801A9388 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_801A9D18(CStruct * arg0);
extern s32 fn_801A9D2C(s32 arg0, s32 * arg1);
extern s32 fn_801A8848(Unk_C8FEE62D * arg0, s32 arg1);
bool fn_801A9324(s32 arg0, s32 arg1) {
    s32 temp_r3;

    fn_801A9D18(arg0 + 8);
    while ((temp_r3 = fn_801A9D2C(arg0 + 8, 0)) != 0) {
        if (fn_801A8848(temp_r3, arg1) == 0) {
            return false;
        }
    }
    return true;
}
