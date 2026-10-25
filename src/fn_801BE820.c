// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BE820-0x801BEC5C (1084B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802AC44C[];
extern char lbl_802AC468[];
extern char lbl_802AC488[];
extern char lbl_802AC49C[];
extern f32 lbl_802AC4B4;
extern f32 lbl_802AC4B8;
extern f32 lbl_802AC4BC;
extern f32 lbl_802AC4C0;
extern f32 lbl_802AC4C4;
extern f32 lbl_802AC4C8;
extern f32 lbl_802AC4CC;
extern f32 lbl_802AC4D0;
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x1C];
    Unk_FFAD6788 *unk0x1C;
} CAMOBJ1BE820;
extern CAMOBJ1BE820 *GetChecksum_3(Unk_6A70655D *, u32);
extern s32 fn_8005DE84(void);
extern s32 fn_80125A08(s32, s32);
extern s32 GetChecksum(CStruct *, s32);
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, u32, f32 *, s32);
extern s32 GetText(CStruct *, void *, void *, s32);
extern f32 fn_80125784(s32, s32);
extern void fn_800244BC(Unk_FFAD6788 *, f32);
// CSkaterCameraComponent_SetMode @ 0x801BE820
void CSkaterCameraComponent_SetMode(Unk_2C96AD5A *arg0, s32 arg1, f32 farg0) {
    struct {
        f32 s[7]; /* &sp8..&sp20 out-params */
        char pad[0x10];
    } fr;
    register f32 temp_f30 __asm__("fr30");
    f32 temp_f0;
    f32 temp_f9;
    CAMOBJ1BE820 *temp_r27;
    s32 temp_r28;
    s32 temp_r30;
    s32 t;

    temp_r27 = GetChecksum_3(arg0->unk0xC, QB_CAMERA);
    switch (temp_r28 = fn_8005DE84()) {
    case 1:
        t = fn_80125A08((s32)lbl_802AC44C, 0);
        break;
    case 2:
        t = fn_80125A08((s32)lbl_802AC468, 0);
        break;
    default:
        t = fn_80125A08((s32)lbl_802AC488, 0);
        break;
    }
    temp_r30 = GetStructure(GetChecksum(t, arg1), 0);
    temp_f30 = lbl_802AC4B4;
    arg0->unk0x2C = arg1;
    arg0->unk0x140 = temp_f30;
    GetFloat(temp_r30, QB_HORIZ_FOV, &fr.s[0], 0);
    GetFloat(temp_r30, QB_BEHIND, &fr.s[1], 0);
    GetFloat(temp_r30, QB_ABOVE, &fr.s[2], 0);
    GetFloat(temp_r30, QB_TILT, &fr.s[3], 0);
    GetFloat(temp_r30, QB_ORIGIN_OFFSET, &fr.s[4], 0);
    GetFloat(temp_r30, QB_LIP_TRICK_TILT, (char *)arg0 + (s32)0x140, 0);
    GetFloat(temp_r30, QB_LIP_TRICK_ABOVE, (char *)arg0 + (s32)0x144, 0);
    GetFloat(temp_r30, QB_SLERP, (char *)arg0 + (s32)0x14C, 0);
    GetFloat(temp_r30, QB_VERT_AIR_SLERP, (char *)arg0 + (s32)0x150, 0);
    GetFloat(temp_r30, QB_VERT_AIR_LANDED_SLERP, (char *)arg0 + (s32)0x154, 0);
    GetFloat(temp_r30, QB_LERP_XZ, (char *)arg0 + (s32)0xF0, 0);
    GetFloat(temp_r30, QB_LERP_Y, (char *)arg0 + (s32)0xF4, 0);
    GetFloat(temp_r30, QB_VERT_AIR_LERP_XZ, (char *)arg0 + (s32)0xF8, 0);
    GetFloat(temp_r30, QB_VERT_AIR_LERP_Y, (char *)arg0 + (s32)0xFC, 0);
    GetFloat(temp_r30, QB_GRIND_LERP, (char *)arg0 + (s32)0x100, 0);
    GetFloat(temp_r30, QB_WALLRIDE_OFFSET_ANGLE, (char *)arg0 + (s32)0x130, 0);
    temp_f0 = lbl_802AC4B8;
    arg0->unk0x124 = temp_f0;
    arg0->unk0x128 = temp_f0;
    arg0->unk0x120 = temp_f0;
    GetFloat(temp_r30, QB_ZOOM_LERP, &fr.s[5], 0);
    GetFloat(temp_r30, QB_GRIND_ZOOM, (char *)arg0 + (s32)0x124, 0);
    GetFloat(temp_r30, QB_BIG_AIR_TRICK_ZOOM, (char *)arg0 + (s32)0x120, 0);
    GetFloat(temp_r30, QB_LIP_TRICK_ZOOM, (char *)arg0 + (s32)0x128, 0);
    arg0->unk0x11C = fr.s[5];
    GetText(temp_r30, QB_NAME, &fr.s[6], 0);
    temp_f9 = lbl_802AC4BC;
    arg0->unk0xEC = fr.s[0];
    arg0->unk0x138 = fr.s[3];
    arg0->unk0x158 = fr.s[4] * temp_f9;
    if (farg0 > temp_f30) {
        register f32 a __asm__("fr13");
        register f32 b __asm__("fr12");
        f32 c;
        f32 e4v;
        f32 d8v;
        f32 d0 = arg0->unk0xD0;
        f32 dc = arg0->unk0xDC;
        a = fr.s[1] * temp_f9;
        b = lbl_802AC4C0 / farg0;
        fr.s[1] = a;
        arg0->unk0xD4 = farg0;
        arg0->unk0xE0 = farg0;
        c = fr.s[2] * temp_f9;
        fr.s[2] = c;
        d8v = (a - d0) * b;
        e4v = (c - dc) * b;
        arg0->unk0xE4 = e4v;
        arg0->unk0xD8 = d8v;
    } else {
        arg0->unk0xD4 = temp_f30;
        arg0->unk0xD0 = fr.s[1] * temp_f9;
        arg0->unk0xDC = fr.s[2] * temp_f9;
        arg0->unk0xE0 = temp_f30;
    }
    switch (temp_r28) {
    case 1: {
        f32 v = fn_80125784((s32)lbl_802AC49C, 0);
        fn_800244BC(temp_r27->unk0x1C, v * lbl_802AC4C4);
        break;
    }
    case 2:
        fn_800244BC(temp_r27->unk0x1C, arg0->unk0xEC);
        break;
    default:
        fn_800244BC(temp_r27->unk0x1C, arg0->unk0xEC);
        break;
    }
    switch (arg1) {
case 5 ... 6:
        *(f32 *)(arg0->unk0x174 + 0x30) = lbl_802AC4C8;
        break;
case 7 ... 8:
        *(f32 *)(arg0->unk0x174 + 0x30) = lbl_802AC4CC;
        break;
case 0xB ... 0xC:
        *(f32 *)(arg0->unk0x174 + 0x30) = lbl_802AC4D0;
        break;
case 9:
case 10:
default:
        *(f32 *)(arg0->unk0x174 + 0x30) = lbl_802AC4B4;
        break;
    }
}
