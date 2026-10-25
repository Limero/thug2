// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CCD34-0x800CD008 (724B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
extern f32 lbl_8029962C;
extern f32 lbl_80299630;
extern f32 lbl_80299634;
extern f32 lbl_80299638;
extern char lbl_80299624[];
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_80128978(s32, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 fn_80119498(s32);
s32 fn_800B0780(s32);
s32 fn_800CD430(Unk_FFAD6788 *, s32, s32, s32, s32, f32, f32, f32);
struct unkC0 {
    char pad[0xC0];
    s32 unkC0;
};
void fn_800CCD34(CScript *arg0, CStruct *arg1) {
    struct sp {
        s32 sp8;
        f32 spC;
        f32 sp10;
        f32 sp14;
        f32 sp18;
        f32 sp1C;
        f32 sp20;
        f32 sp24;
        f32 sp28;
        s32 sp2C;
        s32 sp30;
        s32 sp34;
        char pad[0x10];
    } sp;
    f32 temp_f12;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r28;
    s32 var_r29;
    s32 temp_r0;
    register s32 temp_r11 __asm__("r11");
    s32 *temp_r9;
    s32 var_r3;

    temp_f31 = lbl_8029962C;
    temp_f30 = lbl_80299630;
    sp.sp8 = 0;
    sp.spC = temp_f31;
    sp.sp10 = temp_f31;
    sp.sp28 = temp_f30;
    sp.sp30 = 0;
    var_r29 = 0;
    var_r28 = 0;
    GetChecksum_2(arg1, 0, &sp.sp8, 0);
    GetFloat(arg1, QB_VOL, &sp.spC, 0);
    GetFloat(arg1, QB_PITCH, &sp.sp10, 0);
    if (fn_80128978(arg1, QB_PERCENT) != 0) {
        sp.sp18 = temp_f30;
        sp.sp14 = temp_f31;
        sp.sp20 = temp_f31;
        sp.sp1C = temp_f31;
        GetFloat(arg1, QB_MAXVOL, &sp.sp14, 0);
        GetFloat(arg1, QB_MINVOL, &sp.sp18, 0);
        GetFloat(arg1, QB_MAXPITCH, &sp.sp1C, 0);
        GetFloat(arg1, QB_MINPITCH, &sp.sp20, 0);
        GetFloat(arg1, QB_PERCENT, &sp.sp24, 1);
        temp_f12 = sp.sp24 * lbl_80299634;
        sp.sp24 = temp_f12;
        sp.spC = ((sp.sp14 - sp.sp18) * temp_f12) + sp.sp18;
        sp.sp10 = ((sp.sp1C - sp.sp20) * temp_f12) + sp.sp20;
    }
    if (GetFloat(arg1, QB_DROPOFF, &sp.sp28, 0) != 0) {
        sp.sp28 *= lbl_80299638;
    }
    if (GetChecksum_2(arg1, QB_DROPOFF_FUNCTION, &sp.sp2C, 0) != 0) {
        var_r29 = fn_80119498(sp.sp2C);
    }
    if (ContainsFlag(arg1, QB_NOPOSUPDATE) != 0) {
        var_r28 = 1;
    }
    var_r3 = GetChecksum_2(arg1, QB_EMITTER, &sp.sp30, 0);
    if (var_r3 != 0) {
        var_r3 = fn_800B0780(sp.sp30);
    }
    ((struct unkC0 *)arg0)->unkC0 = var_r3;
    __asm__ volatile("" ::: "memory");
    if (sp.sp8 == 0) {
        sp.sp34 = -1;
        fn_80128294(arg1, (char *)lbl_80299624, &sp.sp34, 0);
        if (sp.sp34 != -1 && sp.sp34 <= 8) {
            temp_r9 = (s32 *)((char *)arg0 + 0x1C);
            temp_r11 = temp_r9[sp.sp34];
            sp.sp8 = temp_r11;
            if (sp.sp8 == 0) {
                return;
            }
        } else {
            return;
        }
    }
    temp_r9 = *((char * *)&arg0->unk0x18);
    ((void (*)(s32, s32, f32, f32))(*((void * *)&((Unk_0E2E8431 *)temp_r9)->unk0x74)))((s32)arg0 + ((Unk_0E2E8431 *)temp_r9)->unk0x70, sp.sp8, sp.spC, sp.sp10);
    fn_800CD430(arg0, sp.sp8, var_r29, var_r28, 0, sp.spC, sp.sp10, sp.sp28);
}
