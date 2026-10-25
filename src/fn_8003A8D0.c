// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A8D0-0x8003A944 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 GetStructure(s32, s32);
void fn_8003EDD8(CStruct *, s32);
void CStruct_dtor(CStruct *);
bool fn_8003A8D0(Unk_31DE137E *arg0) {
    s32 temp_r30;
    s32 ret;

    temp_r30 = (char *)arg0 + 0x58;
    CStruct_dtor(temp_r30);
    if ((s32) arg0->unk0x60 != 0) {
        fn_8003EDD8(arg0->unk0x60, 0);
    }
    ret = GetStructure(QB_APPEARANCE_INIT_STRUCTURE, 0);
    if (ret != 0) {
        fn_80126FF4(temp_r30, ret);
    }
    arg0->unk0x64 = 0;
    return true;
}
