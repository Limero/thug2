// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80083460-0x800834E0 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern void* lbl_80301430;
void fn_8006F3F4(CStruct *, s32 *);
s32 fn_8006F338(CStruct *, s32 *);
void fn_8006F324(CStruct *);
void fn_80083460(void) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r0;
    s32 var_r31;

    fn_8006F324(lbl_80301430);
    var_r31 = fn_8006F338(lbl_80301430, 0);
    if (var_r31 != 0) {
        do {
            temp_r30 = var_r31;
            var_r31 = fn_8006F338(lbl_80301430, 0);
            temp_r0 = lbl_80301430;
            sp8 = temp_r30;
            fn_8006F3F4(temp_r0, &sp8);
            Mem_Free(temp_r30);
        } while (var_r31 != 0);
    }
}
