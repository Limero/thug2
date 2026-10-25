// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F7270-0x801F72CC (92B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_801F59CC(s32, s32);
extern s32 fn_801F16A0(CStruct *);
extern s32 fn_801F5A0C(s32, s32);

s32 fn_801F7270(s32 arg0, CStruct *arg1) {
    if (fn_801F59CC(arg0, arg1) == 0x32) {
        return 1;
    }
    return fn_801F5A0C(arg0, fn_801F16A0(arg1)) > 9;
}
