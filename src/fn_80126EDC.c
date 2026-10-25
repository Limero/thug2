// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126EDC-0x80126F40 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303278;
extern s32 lbl_8030327C;
void fn_80126E9C(void);
void fn_80126F40(CStruct *, CStruct *);
s32 fn_80126EDC(CStruct *arg0, CStruct *arg1) {
    s32 temp_r9;

    fn_80126E9C();
    fn_80126F40(arg0, arg1);
    temp_r9 = lbl_80303278 + 1;
    lbl_80303278 = temp_r9;
    if (temp_r9 > lbl_8030327C) {
        lbl_8030327C = temp_r9;
    }
    return arg0;
}
