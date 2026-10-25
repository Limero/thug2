// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058F00-0x80058F48 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void * lbl_80300474;
void fn_80058B48(s32, s32);
void fn_80058C38(CStruct *);
void fn_80058F00(CStruct * arg0) {
    fn_80058B48(arg0, 1);
    fn_80058C38(arg0);
    arg0->unk0x4C = lbl_80300474;
    lbl_80300474 = arg0;
}
