// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800558C0-0x80055960 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80127CD4(CStruct *, s32, s32);
void fn_80057470(Unk_FFAD6788 *, CStruct *);
void CStruct_new(s32);
void fn_800558C0(CStruct *);
void fn_800558C0(CStruct *arg0) {
    s32 temp_r30;
    s32 temp_r30_2;

    if (fn_80054E40() != 0) {
        CStruct_new(8);
        temp_r30 = CStruct_ctor();
        fn_80057470(fn_80054E40(), temp_r30);
        fn_80127CD4(arg0, QB_MAINSCENE, temp_r30);
    }
    if (fn_80054E94() != 0) {
        CStruct_new(8);
        temp_r30_2 = CStruct_ctor();
        fn_80057470(fn_80054E94(), temp_r30_2);
        fn_80127CD4(arg0, QB_SKYSCENE, temp_r30_2);
    }
}
