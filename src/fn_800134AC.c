// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800134AC-0x800135A0 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFF10;
extern char lbl_80290884[];
s32 fn_8000DE40(void);
s32 fn_8000DEBC(Unk_C8FEE62D *, u8 *, s32);
s32 fn_800134AC(Unk_DB0E2BAB *arg0, Unk_C8FEE62D *arg1, s32 arg2, s32 arg3) {
    s32 temp_r9;
    register s32 fpv __asm__("r0");
    s32 var_r3;
    CStruct *temp_r3;
    Unk_C8FEE62D *temp_r8;
    Unk_C7387A53 *temp_r9_2;

    arg0->unk0x14 = 1;
    arg0->unk0x28 = arg3;
    arg0->unk0x20 = arg2;
    if (fn_8000DE40() != 0) {
        temp_r3 = fn_8000DEBC(arg1, (u8 *)lbl_80290884, 1);
        arg0->unk0x34 = temp_r3;
        if (temp_r3 != NULL) {
            arg0->unk0x20 = 1;
            arg0->unk0x0 = 1;
            temp_r8 = arg0->unk0x3C;
            arg0->unk0x2C = (s32) temp_r3->unk0x10;
            temp_r9 = *(volatile s32 *)&lbl_802FFF10;
            temp_r9 = temp_r9 + 1;
            lbl_802FFF10 = temp_r9;
            (*(volatile s32 *)&arg0->unk0x38)++;
            *(volatile s32 *)&arg0->unk0x38;
            fpv = *(volatile s32 *)&temp_r8->unk0x14;
            ((s32 (*)(void *, void *, s32, void *, s32, void *, void *))fpv)((char *)arg0 + *(s16 *)((char *)temp_r8 + 0x10), arg0->unk0x14, 0, *(volatile s32 *)&arg0->unk0x0, 0, temp_r8, temp_r9);
            var_r3 = 1;
            if ((s32) arg0->unk0x0 == 0) {
                var_r3 = 0;
            }
            return var_r3;
        }
    }
    temp_r9_2 = arg0->unk0x3C;
    var_r3 = ((s32 (*)(void *, void *))temp_r9_2->unk0x24)((char *)arg0 + *(s16 *)((char *)temp_r9_2 + 0x20), arg1);
    return var_r3;
}
