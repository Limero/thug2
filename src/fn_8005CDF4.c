// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CDF4-0x8005CE88 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8005CC88(CStruct *, s32);
s32 fn_8005C070(s32, s32);
s32 fn_8005CA70(CStruct *, s32, s32, s32, s32);
s32 fn_8005CCFC(void);
s32 fn_8005CDF4(CStruct *arg0, s32 arg1, s32 arg2) {
    s32 temp_r29;
    s32 temp_r3;
    s32 temp_r3_3;
    Unk_9994C3F5 *temp_r3_2;
    temp_r3 = fn_8005CCFC();
    if (temp_r3 != 0) {
        temp_r3_2 = *(Unk_9994C3F5 **)&lbl_802FFE98;
        fn_8000F2F8((Unk_9F352E7C *)temp_r3_2, temp_r3_2->unk0x118);
        temp_r3_3 = fn_8005CA70(arg0, arg2, 0, 0, 1);
        temp_r29 = fn_8005C070(temp_r3, temp_r3_3);
        fn_8005CC88(arg0, temp_r3_3);
        fn_8000F320(*(Unk_F12C5E01 **)&lbl_802FFE98);
        return temp_r29;
    }
    return 0;
}
