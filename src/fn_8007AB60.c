// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007AB60-0x8007ABB8 (88B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void fn_8005C8D0(CStruct *, s32, s32);
void fn_8007AC00(s32, s32, s32);
extern char lbl_80295938[];
void *fn_8007AB60(CStruct *arg0, Unk_C8FEE62D *arg1, s32 arg2) {
    fn_8005C8D0(arg0, arg1, 1);
    arg0->unk0x10 = (s32)lbl_80295938;
    fn_8007AC00(arg0, arg1, arg2);
    return arg0;
}
