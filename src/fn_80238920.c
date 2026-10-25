// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80238920-0x80238964 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80306004[];
void fn_802353D0(CStruct *, s32);
void fn_80238920(void) {
    void *ptr = *(void **)lbl_80306004;
    if (ptr != NULL) {
        fn_802353D0(ptr, 3);
    }
    *(s32 *)lbl_80306004 = 0;
}
