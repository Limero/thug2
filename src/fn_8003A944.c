// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A944-0x8003A99C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8003A46C(s32);
void fn_8003A8D0(void);
void fn_80127370(CStruct *, CStruct *, s32);
bool fn_8003A944(s32 arg0, CStruct *arg1, s32 arg2) {
    fn_8003A8D0();
    fn_80127370(arg1, arg0 + 0x58, 0);
    if (arg2 != 0) {
        fn_8003A46C(arg0);
    }
    return true;
}
