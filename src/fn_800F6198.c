// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F6198-0x800F6250 (184B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
extern char lbl_8029BE74[];
extern void fn_8001075C(s32);
extern s32 Mem_NewZero(s32);
extern void *fn_800AB528(Unk_6849630D *);
extern s32 fn_8005570C(void);
extern void sprintf(s32, ...);
extern s32 fn_800AD890(void *, void *, s32, s32, s32);
extern void fn_80010760(void);
s32 fn_800F6198(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2, s32 arg3, s32 arg4) {
    s32 sp8[63];
    s32 temp_r31;
    s32 temp_r3;
    Unk_07FDFB02 *temp_r9;
    s32 var_r3;

    fn_8001075C(arg1);
    temp_r31 = fn_800AB528(Mem_NewZero(0x34E0));
    sprintf((s32)sp8, (s32)lbl_8029BE74, arg1, fn_8005570C());
    temp_r3 = fn_800AD890(temp_r31, sp8, 1, arg2, arg4);
    if (temp_r3 != 0) {
        temp_r9 = arg0->unk0x50;
        ((s32 (*)(void *, void *))temp_r9->unk0x5C)((char *)arg0 + temp_r9->unk0x58, temp_r31);
        fn_80010760();
        var_r3 = 0;
    } else {
        var_r3 = -1;
    }
    return var_r3;
}
