// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126F40-0x80126F88 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void CStruct_dtor(CStruct *);
s32 fn_80126F88(Unk_80577C09 *, CStruct *);
s32 fn_80126F40(CStruct *arg0, CStruct *arg1) {
    if (arg1 != (void *)arg0) {
        CStruct_dtor((void *)arg0);
        fn_80126F88(arg0, arg1);
        return arg0;
    }
    return arg0;
}
