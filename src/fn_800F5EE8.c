// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F5EE8-0x800F5F8C (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800F39C4(CStruct *);
extern s32 fn_8005D560(s32, s32, s32, s32, s32, s32, s32);
extern s32 fn_800F3A6C(s32);
extern s32 fn_80013788(s32);
extern void fn_800F3794(void *, s32, s32);
void fn_800F5EE8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    CStruct *temp_r11;
    Unk_07FDFB02 *temp_r9;
    s32 var_r28;
    s32 temp_r3;

    temp_r3 = fn_800F39C4(arg0);
    var_r28 = 0;
    temp_r11 = *((void * *)&arg0->unk0x54);
    temp_r3 = fn_8005D560(temp_r3, arg1, arg2,
                          temp_r11->unk0x0,
                          temp_r11->unk0x4,
                          temp_r11->unk0x8,
                          temp_r11->unk0xC);
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((s32 (*)(void *, s32))(*((void * *)&temp_r9->unk0x5C)))((char *)arg0 + temp_r9->unk0x58, temp_r3);
    fn_800F3A6C(arg0->unk0x54);
    temp_r3 = arg0->unk0x20;
    arg0->unk0x54 = var_r28;
    if (temp_r3 != 0) {
        fn_80013788(temp_r3);
        arg0->unk0x20 = var_r28;
    }
    fn_800F3794(arg0, arg1, arg2);
}
