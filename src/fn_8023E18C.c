// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023E18C-0x8023E290 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
extern void *fn_8023897C(void * arg0, s32 arg1, s32 * arg2);
extern void fn_8023DE20(Unk_31DE137E * arg0, s32 arg1);
extern void fn_8023C7A4(CStruct * arg0);
extern void fn_8023EDE4(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_8023EC64(Unk_C7387A53 * arg0, s32 arg1);

void fn_8023E18C(CStruct *arg0, s32 arg1) {
    s32 var_r28;
    s32 var_r30;
    Unk_32A45DC6 *temp_r3;
    char *p;

    var_r30 = *(s32 *)(arg0->unk0x0 + 0x13C90);
    if (var_r30 > 0) {
        var_r28 = 0;
        do {
            arg0->unk0x6C += arg1;
            if (arg0->unk0x6C < 0) {
                arg0->unk0x6C = *(s32 *)(arg0->unk0x0 + 0x13C90) - 1;
            }
            if (arg0->unk0x6C >= *(s32 *)(arg0->unk0x0 + 0x13C90)) {
                arg0->unk0x6C = var_r28;
            }
            temp_r3 = fn_8023897C(arg0->unk0x0, arg0->unk0x6C, (char *)arg0 + 0x70);
            if ((s32)temp_r3->unk0x150 != 0) {
                break;
            }
        } while (--var_r30 > 0);
    }
    temp_r3 = fn_8023897C(arg0->unk0x0, arg0->unk0x6C, (char *)arg0 + 0x70);
    if ((s32)temp_r3->unk0x151 != 0) {
        fn_8023DE20(arg0, temp_r3->unk0x14C);
        fn_8023C7A4(arg0);
        fn_8023EDE4(arg0, 5);
        return;
    }
    p = (char *)temp_r3 + 8;
    fn_8023EC64(arg0, *(s32 *)(p + (temp_r3->unk0x14C) * 8));
}
