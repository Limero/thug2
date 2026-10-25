// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007AB20-0x8007AB60 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005C868(CStruct *, s32, s32);
extern char lbl_80295938[];
void *fn_8007AB20(CStruct *arg0, s32 arg1) {
    fn_8005C868((s32)arg0, arg1, 1);
    arg0->unk0x10 = (s32)lbl_80295938;
    return arg0;
}
