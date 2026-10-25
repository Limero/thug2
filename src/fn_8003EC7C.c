// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003EC7C-0x8003ED20 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void SetFacePointsStruct(Unk_DB0E2BAB *, CStruct *);
void AddString(CStruct *, s32, void *);
void AddArrayPointer(CStruct *, s32, s32);
void fn_801292A8(CStruct *, s32, s32);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
void fn_8003E7CC(s32);
void fn_8003EC7C(s32 arg0, CStruct *arg1) {
    s32 *var_r30;
    s32 temp_r29;
    s32 temp_r4;
    s32 var_r31;

    var_r30 = arg0 + 0x40;
    fn_8003E7CC(0xC);
    var_r31 = 0;
    temp_r29 = fn_80128F94();
    fn_80129068(temp_r29, 0x1108, 0xD);
    do {
        temp_r4 = var_r31;
        var_r31 += 1;
        fn_801292A8(temp_r29, temp_r4, *((s32 *)var_r30));
        var_r30 = (s32 *)((char *)var_r30 + 4);
    } while (var_r31 <= 0x1107);
    AddArrayPointer(arg1, QB_RAWTEXTUREDATA, temp_r29);
    AddString(arg1, QB_OVERLAYTEXTURENAME, arg0 + 0x4460);
    SetFacePointsStruct(arg0 + 8, arg1);
}
