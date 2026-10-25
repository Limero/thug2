// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A44E8-0x801A4540 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8003A80C(Unk_31DE137E *, Unk_31DE137E *);
s32 fn_80126F40(CStruct *, CStruct *);
s32 fn_801A44E8(s32 arg0, s32 arg1) {
    if (arg1 == arg0) {
        return arg1;
    }
    fn_8003A80C(arg0 + 4, arg1 + 4);
    fn_80126F40(arg0 + 0x6C, arg1 + 0x6C);
    return arg0;
}
