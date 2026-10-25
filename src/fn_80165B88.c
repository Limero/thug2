// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165B88-0x80165BE4 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
void fn_80145168(void * arg0, CStruct * arg1);
void fn_8014535C(Unk_7258DEBD * arg0, CStruct * arg1);
void fn_80145480(s32 arg0, CStruct * arg1);
void s_insert_story_skater_info(CStruct *arg0) {
    s32 temp_r29;

    temp_r29 = fn_801746A4(lbl_80305EAC, 0);
    fn_80145168(temp_r29, arg0);
    fn_8014535C(temp_r29, arg0);
    fn_80145480(temp_r29, arg0);
}
