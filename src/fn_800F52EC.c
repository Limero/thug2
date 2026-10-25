// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F52EC-0x800F5414 (296B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800F38B8(Unk_C7387A53 *);
s32 fn_800F39C4(CStruct *);
s32 fn_800553EC(Unk_FFAD6788 *, Unk_78674569 *, s32, Unk_FFAD6788 *, Unk_9994C3F5 *, s32, s32, s32);
void fn_800F3A6C(s32);
s32 fn_80013788(s32);
void Mem_Free_3(s32);
s32 fn_800F3794(void *, s32, s32);

void fn_800F52EC(Unk_A9157FE7 *arg0, Unk_78674569 *arg1, s32 arg2) {
    CStruct *temp_r11;
    Unk_C7387A53 *temp_r3;
    Unk_07FDFB02 *temp_r9;
    s32 temp_r30;
    s32 var_r3;
    s32 var_r55;

    temp_r3 = (void *)fn_800F38B8(arg0);
    temp_r9 = *((void * *)&temp_r3->unk0x50);
    temp_r30 = ((s32 (*)(void *))*((s32 *)&temp_r9->unk0x14))(
        (char *)temp_r3 + temp_r9->unk0x10);
    var_r3 = fn_800F39C4(arg0);
    temp_r11 = *((void * *)&arg0->unk0x58);
    var_r55 = fn_800553EC(var_r3, arg1, arg2,
        temp_r11->unk0x8, temp_r30,
        temp_r11->unk0x4,
        temp_r11->unk0x10,
        *(s32 *)((char *)temp_r11));
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((s32 (*)(void *, void *))temp_r9->unk0x5C)(
        (char *)arg0 + temp_r9->unk0x58, var_r55);
    if ((*(s32 *)(arg0->unk0x58 + (s32)0x14) != 0) &&
        (arg0->unk0x24 != 0)) {
        temp_r9 = *((void * *)&arg0->unk0x50);
        ((s32 (*)(void *))*((s32 *)&temp_r9->unk0x84))(
            (char *)arg0 + temp_r9->unk0x80);
    }
    fn_800F3A6C(arg0->unk0x58);
    arg0->unk0x58 = 0;
    if (arg0->unk0x20 != 0) {
        fn_80013788(arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
    if (arg0->unk0x5C != 0) {
        fn_80013788(arg0->unk0x5C);
        arg0->unk0x5C = 0;
    }
    if (arg0->unk0x60 != 0) {
        Mem_Free_3(arg0->unk0x60);
        arg0->unk0x60 = 0;
    }
    fn_800F3794(arg0, arg1, arg2);
}
