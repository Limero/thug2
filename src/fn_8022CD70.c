// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CD70-0x8022CDB4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022CFF8(s32);
void *fn_8022D024(s32);
void *fn_8022C724(void *);
void fn_8022D074(void);
void *fn_8022CD70(CStruct *arg0) {
    void *temp_r30;

    fn_8022CFF8(arg0->unk0x10);
    temp_r30 = fn_8022C724(fn_8022D024(0x38));
    fn_8022D074();
    return temp_r30;
}
