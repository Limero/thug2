// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F2D8-0x8012F360 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CStruct_new(s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 CStruct_ctor(s32);
s32 fn_80128ACC(CStruct *, s32);
s32 fn_8012F2D8(Unk_C8FEE62D *arg0, CStruct *arg1) {
    s32 var_r29;
    var_r29 = 0;
    if ((arg1 != 0) && ((((s32) arg0->unk0x14 != 0) && (fn_80128ACC(arg0->unk0x14, arg1) != 0)) || (((s32) arg0->unk0x18 != 0) && (fn_80128ACC(arg0->unk0x18, arg1) != 0)))) {
        var_r29 = CStruct_ctor(CStruct_new(8));
        fn_80126FF4(var_r29, arg1);
    }
    return var_r29;
}
