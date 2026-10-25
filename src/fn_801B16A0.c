// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B16A0-0x801B175C (188B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802ABEBC;
extern char lbl_802ABE8C[];
extern char lbl_802ABE98[];
extern char lbl_802ABEA4[];
extern char lbl_802ABEB0[];
s32 fn_801B1654(f32 farg0);
s32 fn_8012834C(CStruct * arg0, void *arg1, void *arg2, s32 arg3);

f32 fn_801B16A0(CStruct *arg0, f32 arg1) {
    f32 sp8;
    s32 temp_r3;

    temp_r3 = fn_801B1654(arg1);
    sp8 = lbl_802ABEBC;
    switch (temp_r3) {
    case 1:
        fn_8012834C(arg0, (void *)lbl_802ABE8C, &sp8, 1);
        break;
    case 2:
        fn_8012834C(arg0, (void *)lbl_802ABE98, &sp8, 1);
        break;
    case 3:
        fn_8012834C(arg0, (void *)lbl_802ABEA4, &sp8, 1);
        break;
    case 0:
    case 4:
    default:
        fn_8012834C(arg0, (void *)lbl_802ABEB0, &sp8, 1);
        break;
    }
    return sp8;
}
