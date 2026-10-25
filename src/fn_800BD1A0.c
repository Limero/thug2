// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BD1A0-0x800BD354 (436B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure(s32, s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 fn_80128978(s32, s32);
extern s32 CStruct_delete(CStruct *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_80126F88(Unk_80577C09 *, CStruct *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_800BD1A0(Unk_FFAD6788 *arg0, s32 arg1) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    temp_r3 = GetStructure(QB_RIGIDBODYSOUNDS, 1);
    sp8 = 0;
    GetStructure_2(temp_r3, arg1, &sp8, 0);
    if (fn_80128978(sp8, QB_COLLIDESOUND) != 0) {
        GetStructure_2(sp8, QB_COLLIDESOUND, &spC, 1);
        if (arg0->unk0xE0 != 0) {
            CStruct_delete(arg0->unk0xE0, 3);
        }
        temp_r3 = CStruct_ctor(CStruct_new(8));
        arg0->unk0xE0 = temp_r3;
        fn_80126F88(temp_r3, spC);
    }
    if (fn_80128978(sp8, QB_BOUNCESOUND) != 0) {
        GetStructure_2(sp8, QB_BOUNCESOUND, &spC, 1);
        if (arg0->unk0xE4 != 0) {
            CStruct_delete(arg0->unk0xE4, 3);
        }
        temp_r3 = CStruct_ctor(CStruct_new(8));
        arg0->unk0xE4 = temp_r3;
        fn_80126F88(temp_r3, spC);
        if (fn_80128978(sp8, QB_COLLIDEMUTEDELAY) != 0) {
            GetInteger(sp8, QB_COLLIDEMUTEDELAY, &sp10, 0);
            arg0->unk0xE8 = sp10;
        }
        if (fn_80128978(sp8, QB_GLOBALCOLLIDEMUTEDELAY) != 0) {
            GetInteger(sp8, QB_GLOBALCOLLIDEMUTEDELAY, &sp14, 0);
            arg0->unk0xEC = sp14;
        }
        GetFloat(sp8, QB_BOUNCEVELOCITYCALLBACKTHRESHOLD, (char *)arg0 + 0xF0, 0);
        GetFloat(sp8, QB_BOUNCEVELOCITYFULLSPEED, (char *)arg0 + 0xF4, 0);
    }
}
