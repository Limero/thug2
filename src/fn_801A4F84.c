// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A4F84-0x801A4FF0 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 fn_80129EA0(CStruct *, u8 *);
s32 CStruct_ctor(s32);

s32 fn_801A4F84(s32 arg0, s32 arg1) {
    register s32 r30 asm("r30") = arg0;
    register s32 r29 asm("r29") = arg1;
    s32 temp_r31;
    s32 temp_r29;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    temp_r29 = fn_80129EA0(temp_r31, r29);
    fn_80126FF4(r30 + 0x6C, temp_r31);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return temp_r29;
}
