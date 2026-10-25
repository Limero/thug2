// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C8C04-0x800C8D0C (264B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 lbl_80305FF8;
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_800F0F84(s32, s32);
extern void fn_800C02E8(Unk_D2FDFB5E *, CStruct *);
extern s32 fn_800F0598(s32);
extern s32 fn_800F0610(void *, s32);
extern s32 fn_800A9CC0(s32);
extern s32 fn_80173538(Unk_839CD594 *, s32);
bool fn_800C8C04(Unk_D2FDFB5E *arg0, CStruct *arg1, Unk_FFAD6788 *arg2) {
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r31;
    s32 var_r11;
    s32 var_r30;

    if (GetChecksum_2(arg1, 0, &sp8, 0) != 0) {
        fn_800C02E8(arg0, fn_800F0F84(sp8, 1));
        return true;
    }
    temp_r28 = arg2->unk0xB8;
    var_r30 = 0;
    if (var_r30 < (temp_r29 = fn_800F0598(temp_r28))) {
        do {
            temp_r31 = fn_800F0610(temp_r28, var_r30);
            if (fn_800A9CC0(temp_r31) != 0) {
                fn_800C02E8(arg0, fn_800F0F84(temp_r31, 1));
                return true;
            }
            var_r30 += 1;
        } while (var_r30 < temp_r29);
    }
    var_r11 = (*(s32 *)(*(s32 *)&lbl_80305FF8 + 0x44) != QB_OFF);
    if (var_r11 != 0) {
        fn_800C02E8(arg0, fn_800F0F84(fn_80173538(lbl_80305EAC, 0), 1));
    }
    return true;
}
