// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010CB44-0x8010CC40 (252B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern u32 lbl_803830E8[];
s32 fn_80119470(void);
s32 GetStructure(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void CStruct_delete(CStruct *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_8010BA84(s32);
s32 fn_8010BBC4(s32, void *, s32);
void fn_8010C8BC(CStruct *, s32);

bool fn_8010CB44(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 var;

    temp_r29 = fn_80119470();
    if (temp_r29 != 0) {
        return false;
    }
    temp_r30 = fn_8010BA84(arg0);
    GetStructure_2(GetStructure(QB_TERRAIN_DEFAULT, 1), QB_SOUNDACTIONS, &sp8, 1);
    spC = temp_r29;
    if (fn_8010BBC4(temp_r30, &spC, QB_SOUNDACTIONS) != 0) {
        var = 0;
        temp_r31 = CStruct_ctor(CStruct_new(8));
        fn_80126FF4((void *)temp_r31, (void *)sp8);
        fn_80126FF4((void *)temp_r31, (void *)spC);
        if ((u32)var < lbl_803830E8[2]) {
            do {
                fn_8010C8BC(temp_r31, (u8)var);
                var += 1;
            } while ((u32)var < lbl_803830E8[2]);
        }
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    return true;
}
