// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034850-0x80034994 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80053FB0(void *, void *);
extern f32 lbl_80291C8C;
extern f32 lbl_80291C90;
#include "qb_constants.h"
#include "structs.h"
s32 fn_8002DDE8(s32);
s32 GetFloat(CStruct *, void *, f32 *, void *);
s32 fn_800335E0(CStruct *);
f32 fn_800CBE30(Unk_C7387A53 *, s32);
s32 fn_80054048(void *, void *, void *, s32, f32, f32);
void fn_80033594(void);
void *GetChecksum_3(void *, s32);
s32 fn_8006FB8C(s32, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
typedef struct {
    char pad0x0[0x20];
    s16 unk0x20;
    char pad0x22[0x2];
    s32 unk0x24;
} VT_34850;
void fn_80034850(CScript *arg0, CStruct *arg1) {
    struct {
        s32 sp8;
        f32 spC;
        f32 sp10;
        s32 sp14;
        f32 sp18;
        f32 sp1C;
        char pad[8];
    } fr;
    f32 temp_f31;
    f32 temp_f2;
    register f32 cur2 __asm__("fr1");
    void *temp_r11;
    VT_34850 *temp_r9;

    fn_80033594();
    GetChecksum_2(arg1, QB_ANIMNAME, &fr.sp8, 1);
    temp_f31 = lbl_80291C8C;
    fr.spC = temp_f31;
    fr.sp10 = temp_f31;
    fr.sp1C = temp_f31;
    temp_f2 = fn_800CBE30(GetChecksum_3(fn_800335E0(arg0), QB_ANIMBLENDER), fr.sp8);
    fn_80054048(&fr.spC, &fr.sp10, arg1, 0, fr.sp1C, temp_f2);
    fn_80053FB0(&fr.sp14, arg1);
    fr.sp18 = lbl_80291C90;
    GetFloat(arg1, QB_SPEED, &fr.sp18, 0);
    GetFloat(arg1, QB_CURRENT, &fr.sp1C, 0);
    temp_r11 = arg0->unk0x18;
    temp_r9 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
    ((s32 (*)(void *, f32, s32, f32, f32, void *, f32))temp_r9->unk0x24)(temp_r11 + temp_r9->unk0x20, fr.spC, fr.sp8, fr.sp10, temp_f31, fr.sp14, fr.sp18);
    cur2 = fr.sp1C;
    if (cur2 != temp_f31) {
        fn_8002DDE8(arg0->unk0x18);
    }
    arg0->unk0x20 = fn_8006FB8C(arg0->unk0x1C, arg0->unk0x24 + fr.sp8);
}
