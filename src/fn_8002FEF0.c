// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002FEF0-0x8002FFA8 (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_delete(CStruct *, s32);
s32 fn_8009E474(Unk_C7387A53 *, CStruct *);
void fn_80127CD4(CStruct *, s32, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void CStruct_new(s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
void fn_8002FEF0(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r3;

    var_r3 = GetStructure(QB_ANIMTAGTABLE, 1);
    if (var_r3 != 0) {
        var_r3 = GetStructure_2(var_r3, arg1, &sp8, 0);
        if (var_r3 != 0) {
            CStruct_new(8);
            temp_r31 = CStruct_ctor();
            CStruct_new(8);
            temp_r30 = CStruct_ctor();
            fn_80126FF4(temp_r30, sp8);
            fn_80127CD4(temp_r31, QB_ANIMTAGS, temp_r30);
            var_r3 = fn_8009E474(arg0->unk0x78, temp_r31);
            if (temp_r31 != 0) {
                var_r3 = CStruct_delete(temp_r31, 3);
            }
        }
    }
}
