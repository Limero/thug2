// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80166B94-0x80166C18 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
s32 fn_801A5CE8(Unk_C7387A53 *);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_80145240(s32, CStruct *);
void fn_801453E4(Unk_7258DEBD *, CStruct *);
void fn_80145514(s32, CStruct *);
void fn_801A6070(void *, s32, s32);
register s32 r31_guard __asm__("r31");
void s_read_story_skater_info(s32 arg0, s32 arg1) {
    register s32 temp_r28 __asm__("r28");
    register s32 temp_r29 __asm__("r29");
    register s32 temp_r30 __asm__("r30");
    register s32 temp_r27 __asm__("r27");

    temp_r28 = lbl_80305EFC;
    temp_r29 = arg0;
    temp_r30 = lbl_80305EAC;
    temp_r27 = arg1;
    temp_r30 = fn_801746A4(temp_r30, fn_801A5CE8(temp_r28));
    fn_80145240(temp_r30, temp_r29);
    fn_801453E4(temp_r30, temp_r29);
    fn_80145514(temp_r30, temp_r29);
    fn_801A6070(temp_r28, temp_r27, 1);
}
