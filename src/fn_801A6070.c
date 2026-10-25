// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6070-0x801A63E8 (888B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801A5CF0(void *, s32);
extern s32 fn_801A5D88(Unk_C7387A53 *);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_8003A944(s32, CStruct *, s32);
extern s32 fn_8003AE20(Unk_31DE137E *);
extern void fn_8003ED20(s32, CStruct *);
extern void fn_8003EDD8(CStruct *, s32);
extern s32 fn_801A5210(s32, void *);
extern s32 fn_801A5388(s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
extern s32 CStruct_dtor(CStruct *);
extern void CStruct_delete(CStruct *, s32);
extern s32 fn_801A56BC(s32);
extern s32 fn_801A5240(s32, s32, s32);

void fn_801A6070(void *arg0, s32 arg1, s32 arg2) {
    register s32 a1 __asm__("r29");
    register s32 a0 __asm__("r30");
    register s32 a2 __asm__("r16");
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 obj;
    s32 z;
    s32 g2;
    s32 g3;
    s32 g4;
    s32 g5;
    s32 g6;
    s32 g7;
    s32 g8;
    s32 g9;
    s32 g10;
    s32 g11;

    a1 = arg1;
    a0 = arg0;
    a2 = arg2;
    fn_801A5CF0(arg0, QB_CUSTOM);
    __asm__("li %0,0" : "=r"(z));
    obj = fn_801A5D88(a0);
    sp8 = z;
    GetStructure_2(a1, QB_CUSTOM, &sp8, 0);
    spC = z;
    if ((GetInteger(sp8, QB_VERSION_NUMBER, &spC, 0) != 0) && (spC == 2)) {
        sp10 = z;
        a0 = obj + 4;
        GetStructure_2(sp8, QB_APPEARANCE, &sp10, 0);
        fn_8003A944(a0, sp10, 1);
        a1 = fn_8003AE20(a0);
        if (a1 != 0) {
            a0 = GetStructure_2(sp8, QB_FACETEXTURE, &sp10, 0);
            if (a0 != 0) {
                fn_8003ED20(a1, sp10);
            }
            fn_8003EDD8(a1, a0);
        }
        a0 = obj + 0x6C;
        z = fn_801A5210(obj, QB_AIR);
        g2 = fn_801A5210(obj, QB_RUN);
        g3 = fn_801A5210(obj, QB_OLLIE);
        g4 = fn_801A5210(obj, QB_SPEED);
        g5 = fn_801A5210(obj, QB_SPIN);
        g6 = fn_801A5210(obj, QB_FLIP_SPEED);
        g7 = fn_801A5210(obj, QB_SWITCH);
        g8 = fn_801A5210(obj, QB_RAIL_BALANCE);
        g9 = fn_801A5210(obj, QB_LIP_BALANCE);
        g10 = fn_801A5210(obj, QB_MANUAL_BALANCE);
        g11 = fn_801A5388(obj);
        a1 = CStruct_ctor(CStruct_new(8));
        fn_80126FF4(a1, fn_801A56BC(obj));
        sp10 = 0;
        GetStructure_2(sp8, QB_INFO, &sp10, 0);
        CStruct_dtor(a0);
        fn_80126FF4(a0, sp10);
        if (a2 == 0) {
            fn_801A5240(obj, QB_AIR, z);
            fn_801A5240(obj, QB_RUN, g2);
            fn_801A5240(obj, QB_OLLIE, g3);
            fn_801A5240(obj, QB_SPEED, g4);
            fn_801A5240(obj, QB_SPIN, g5);
            fn_801A5240(obj, QB_FLIP_SPEED, g6);
            fn_801A5240(obj, QB_SWITCH, g7);
            fn_801A5240(obj, QB_RAIL_BALANCE, g8);
            fn_801A5240(obj, QB_LIP_BALANCE, g9);
            fn_801A5240(obj, QB_MANUAL_BALANCE, g10);
            fn_801A5240(obj, QB_MAX_SPECIALS, g11);
            CStruct_dtor(fn_801A56BC(obj));
            fn_80126FF4(fn_801A56BC(obj), a1);
        }
        if (a1 != 0) {
            CStruct_delete(a1, 3);
        }
        sp14 = 1;
        GetInteger(sp8, QB_DECKFLAGS, &sp14, 0);
    }
}
