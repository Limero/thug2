// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F5A28-0x800F5AD0 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800F38B8(Unk_C7387A53 *);
extern void fn_800629D4(Unk_FFAD6788 *, CStruct *);
extern void fn_800F3A6C(s32);
extern void fn_80013788(s32);
extern void fn_800F3794(void *, s32, s32);
void fn_800F5A28(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    s32 var_r27;
    Unk_FFAD6788 *temp_r30;
    void *temp_r3;
    Unk_89391A04 *temp_r9;
    Unk_07FDFB02 *temp_r9_2;
    void *temp_r3_2;

    temp_r3 = fn_800F38B8(arg0);
    var_r27 = 0;
    temp_r9 = ((Unk_C7387A53 *)temp_r3)->unk0x50;
    fn_800629D4(
        temp_r30 = ((s32 (*)(void *))temp_r9->unk0x14)(temp_r3 + temp_r9->unk0x10),
        arg1);
    temp_r9_2 = arg0->unk0x50;
    ((s32 (*)(void *, void *))temp_r9_2->unk0x5C)((char *)arg0 + temp_r9_2->unk0x58, temp_r30->unk0x8C);
    fn_800F3A6C(arg0->unk0x54);
    arg0->unk0x54 = var_r27;
    temp_r3_2 = arg0->unk0x20;
    if (temp_r3_2 != 0) {
        fn_80013788(temp_r3_2);
        arg0->unk0x20 = var_r27;
    }
    fn_800F3794(arg0, arg1, arg2);
}
