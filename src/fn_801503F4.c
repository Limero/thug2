// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801503F4-0x80150590 (412B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80300E00;
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];

s32 fn_8009CF2C(CStruct *);
s32 fn_8009CFA0(CStruct *);
s32 fn_800F0F84(s32, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_80175450(s32, CStruct *);
s32 fn_8015010C(s32);
s32 fn_80150164(s32, Unk_FFAD6788 *);
s32 fn_80151DF8(s32, s32, s32);
s32 fn_80152220(s32, CStruct *);
s32 fn_801523E4(s32);
s32 fn_80152034(s32);
s32 fn_80152510(s32, CStruct *);

s32 fn_801503F4(s32 arg0, s32 arg1, Unk_FFAD6788 *arg2, CStruct *arg3) {
    s32 temp_r26;
    s32 temp_r27;
    s32 temp_r28;
    s32 var_r28;

    temp_r27 = *(s32 *)&lbl_80305F9C;
    temp_r26 = *(s32 *)&lbl_80305EAC;
    if ((fn_8009CFA0(temp_r27) == 0) || (fn_80175450(temp_r26, fn_800F0F84(arg0, 1)) == 0)) {
        var_r28 = 0;
        if (((arg2 != NULL) && ((s32)arg2->unk0xBC != 0)) && ((fn_8009CF2C(temp_r27) == 0) && (lbl_80300E00 == 2))) {
            var_r28 = (arg2->unk0xBC == fn_801746A4(temp_r26, 1));
        }
        switch (arg1) {
        case 0:
            return fn_8015010C(arg0);
        case 1:
            return fn_80150164(arg0, arg2);
        case 2:
            return fn_80151DF8(arg0, 0, var_r28);
        case 3:
            return fn_80151DF8(arg0, 1, var_r28);
        case 6:
            return fn_80152220(arg0, arg3);
        case 4:
            fn_80151DF8(arg0, 0, var_r28);
            return fn_801523E4(arg0);
        case 5:
            return fn_80152034(arg0);
        case 7:
            return fn_80152510(arg0, arg3);
        }
    } else {
        return 0;
    }
    return 0;
}
