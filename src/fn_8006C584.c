// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C584-0x8006C610 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern void* lbl_80301428;
void fn_8006F0E4(CStruct *, s32 *);
s32 fn_8006F028(CStruct *, s32 *);
void fn_8006F014(CStruct *);
void fn_8006DEE0(void);
void fn_8006C610(void);
void fn_800856A0(void);
void fn_8006C584(void) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r0;
    s32 var_r31;

    fn_8006F014(lbl_80301428);
    var_r31 = fn_8006F028(lbl_80301428, 0);
    if (var_r31 != 0) {
        do {
            temp_r30 = var_r31;
            var_r31 = fn_8006F028(lbl_80301428, 0);
            temp_r0 = lbl_80301428;
            sp8 = temp_r30;
            fn_8006F0E4(temp_r0, &sp8);
            Mem_Free(temp_r30);
        } while (var_r31 != 0);
    }
    fn_8006DEE0();
    fn_8006C610();
    fn_800856A0();
}
