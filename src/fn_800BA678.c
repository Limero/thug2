// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BA678-0x800BA704 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80298D94;
extern f32 lbl_80298D98;
extern s32 fn_8009F27C(CStruct * arg0, Unk_15EF4A35 * arg1, s32 arg2, s32 arg3, s32 arg4);
extern void fn_801309EC(Unk_DB0E2BAB * arg0);
void fn_800BA678(Unk_CF292E59 *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    CStruct *temp_r11;
    CStruct *temp_r9;

    if (arg0->unk0xD4 != 0) {
        fn_801309EC((void *)fn_8009F27C(arg0->unk0xC, arg0->unk0xD4, arg0->unk0xDC, 0, 0));
    }
    temp_f0 = lbl_80298D94;
    temp_r9 = (char *)arg0 + (s32)0x128;
    temp_f13 = lbl_80298D98;
    temp_r11 = (char *)arg0 + (s32)0x148;
    arg0->unk0x128 = temp_f0;
    *((f32 *)&temp_r9->unk0x4) = temp_f0;
    *((f32 *)&temp_r9->unk0x8) = temp_f0;
    *((f32 *)&temp_r9->unk0xC) = temp_f13;
    arg0->unk0x148 = temp_f0;
    *((f32 *)&temp_r11->unk0x4) = temp_f0;
    *((f32 *)&temp_r11->unk0x8) = temp_f0;
    *((f32 *)&temp_r11->unk0xC) = temp_f13;
    arg0->unk0x114 = 0;
}
