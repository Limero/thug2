// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CE00-0x8022CE48 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022C750(void *, s32);
void fn_8022CFF8(s32);
void fn_8022D074(void);
void fn_8022CE00(CStruct *arg0, void *arg1) {
    fn_8022CFF8(arg0->unk0x10);
    if (arg1 != 0) {
        fn_8022C750(arg1, 3);
    }
    fn_8022D074();
}
