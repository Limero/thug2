// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80105B90-0x80105BDC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80105BE8(void);
s32 fn_80105BDC(CStruct *);
s32 fn_80105B90(CStruct *arg0) {
    if (fn_80105BE8() != 0) {
        return fn_80105BDC(arg0);
    }
    return fn_80105BDC(arg0) + 8;
}
