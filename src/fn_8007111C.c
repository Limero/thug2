// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007111C-0x8007138C (624B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct Vtbl7111C {
    char pad0x0[0x38];
    s16 unk0x38;
    char pad0x3A[0x2];
    s32 (*unk0x3C)(void *, s32);
    s16 unk0x40;
    char pad0x42[0x2];
    s32 (*unk0x44)(void *, void *);
    s16 unk0x48;
    char pad0x4A[0x2];
    s32 (*unk0x4C)(void *, void *);
    s16 unk0x50;
    char pad0x52[0x2];
    s32 (*unk0x54)(void *, f32);
    s16 unk0x58;
    char pad0x5A[0x2];
    s32 (*unk0x5C)(void *, f32);
    s16 unk0x60;
    char pad0x62[0x2];
    s32 (*unk0x64)(void *, f32);
    s16 unk0x68;
    char pad0x6A[0x2];
    s32 (*unk0x6C)(void *, f32);
} Vtbl7111C;

s32 fn_801293FC(CStruct *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
bool fn_8007111C(CStruct *arg0, CStruct *arg1) {
    struct {
        s32 sp8;
        s32 spC;
        f32 sp10;
        f32 sp14;
        f32 sp18;
        f32 sp1C;
        s32 sp20;
        s32 sp24;
        s32 sp28;
    } fr;

    if (GetInteger(arg1, QB_ON, &fr.spC, 0) != 0) {
        ((Vtbl7111C *)arg0->unk0x4)->unk0x3C((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x38, fr.spC);
    }
    if (GetFloat(arg1, QB_BACKDIST, &fr.sp10, 0) != 0) {
        ((Vtbl7111C *)arg0->unk0x4)->unk0x5C((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x58, fr.sp10);
    }
    if (GetFloat(arg1, QB_FRONTDIST, &fr.sp14, 0) != 0) {
        ((Vtbl7111C *)arg0->unk0x4)->unk0x54((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x50, fr.sp10);
    }
    if (GetFloat(arg1, QB_STRENGTH, &fr.sp18, 0) != 0) {
        ((Vtbl7111C *)arg0->unk0x4)->unk0x64((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x60, fr.sp18);
    }
    if (GetFloat(arg1, QB_CROSSFADE, &fr.sp1C, 0) != 0) {
        ((Vtbl7111C *)arg0->unk0x4)->unk0x6C((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x68, fr.sp1C);
    }
    if (GetArray(arg1, QB_BACKCOLOR, &fr.sp20, 0) != 0) {
        s32 r, g, b;
        r = fn_801293FC(fr.sp20, 0);
        g = fn_801293FC(fr.sp20, 1);
        b = fn_801293FC(fr.sp20, 2);
        *(u8 *)&fr.sp24 = (u8)r;
        {
            u8 *col = (u8 *)&fr.sp24;
            col[1] = (u8)g;
            col[2] = (u8)b;
            col[3] = 0;
        }
        fr.sp8 = fr.sp24;
        ((Vtbl7111C *)arg0->unk0x4)->unk0x4C((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x48, &fr.sp8);
    }
    if (GetArray(arg1, QB_FRONTCOLOR, &fr.sp20, 0) != 0) {
        s32 r2, g2, b2;
        r2 = fn_801293FC(fr.sp20, 0);
        g2 = fn_801293FC(fr.sp20, 1);
        b2 = fn_801293FC(fr.sp20, 2);
        *(u8 *)&fr.sp28 = (u8)r2;
        {
            u8 *col = (u8 *)&fr.sp28;
            col[1] = (u8)g2;
            col[2] = (u8)b2;
            col[3] = 0;
        }
        fr.sp8 = fr.sp28;
        ((Vtbl7111C *)arg0->unk0x4)->unk0x44((char *)arg0 + ((Vtbl7111C *)arg0->unk0x4)->unk0x40, &fr.sp8);
    }
    return true;
}
