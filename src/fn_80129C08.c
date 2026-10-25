// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129C08-0x80129E28 (544B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
CStruct *fn_80127358(CStruct *, Unk_C7387A53 *);
s32 fn_8012966C(s32, s32, s8 *, s32);
s32 fn_801297E4(s32, s8 *, s32, f32);
s32 fn_80129890(s32, s32, s8 *, s32);
s32 fn_801298EC(s32, s32, s8 *, s32);
s32 fn_8012998C(s32, s32, s8 *, s32);
s32 fn_80129A2C(s32, s32, s8 *, s32);
s32 fn_80129A90(s32, s32, s8 *, s32);
s32 fn_80129AFC(s32, s32, s8 *, s32, s32);
s32 fn_80129B84(s32, s32, s8 *, s32, s32);

s32 fn_80129C08(CStruct *arg0, s8 *arg1, s32 arg2, s32 arg3, s32 (*arg4)()) {
    s32 var_r3;
    register s8 *var_r29 asm("r29");
    register s32 var_r30 asm("r30");
    register s32 var_r27 asm("r27");
    register s32 var_r28 asm("r28");
    CStruct *var_r31;

    var_r29 = arg1;
    var_r30 = arg2;
    var_r27 = arg3;
    var_r28 = (s32)arg4;
    var_r31 = NULL;
    if (arg0 != 0) {
        var_r31 = fn_80127358(arg0, NULL);
    }
    if (var_r31 != NULL) {
        do {
            if (var_r28 != 0) {
                (*(s32 (*)())var_r28)();
            }
            var_r3 = 0;
            switch (*(u16 *)&var_r31->unk0x0 & 0x7F) {
            case 1:
                var_r3 = fn_8012966C(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30);
                break;
            case 2:
                var_r3 = fn_801297E4(var_r31->unk0x4, var_r29, var_r30, *(f32 *)&var_r31->unk0x8);
                break;
            case 13:
                var_r3 = fn_80129890(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30);
                break;
            case 3:
                var_r3 = fn_801298EC(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30);
                break;
            case 4:
                var_r3 = fn_8012998C(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30);
                break;
            case 5:
                var_r3 = fn_80129A2C(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30);
                break;
            case 6:
                var_r3 = fn_80129A90(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30);
                break;
            case 10:
                var_r3 = fn_80129AFC(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30, var_r27);
                break;
            case 12:
                var_r3 = fn_80129B84(var_r31->unk0x4, var_r31->unk0x8, var_r29, var_r30, var_r27);
                break;
            case 7:
                var_r3 = fn_80129890(var_r31->unk0x4, 0xB9C4F664, var_r29, var_r30);
                break;
            }
            if (var_r3 == 0) {
                goto ret0;
            }
            var_r30 -= var_r3;
            var_r29 += var_r3;
            var_r31 = fn_80127358(arg0, var_r31);
            if (var_r31 != NULL) {
                continue;
            }
            break;
        } while (1);
    }
    if (var_r30 != 0) {
        *var_r29 = 0;
        var_r30 -= 1;
        return arg2 - var_r30;
    }
ret0:
    return 0;
}