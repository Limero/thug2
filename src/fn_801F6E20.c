// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6E20-0x801F6E90 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AE328[];
extern char lbl_802AE388[];
extern s32 fn_80128170(CStruct * arg0, void * arg1, void * arg2, s32 arg3);
extern s32 fn_801F5898(void * arg0, CStruct * arg1);
extern void fn_801F4AE4(s32 arg0, s32 arg1);
bool fn_801F6E20(void *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r3;

    sp8 = (s32)lbl_802AE328;
    fn_80128170(arg1, (s32)lbl_802AE388, &sp8, 0);
    temp_r3 = fn_801F5898(arg0, arg1);
    if (temp_r3 != 0) {
        fn_801F4AE4(temp_r3, sp8);
    }
    return true;
}
