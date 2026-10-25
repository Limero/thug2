// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8998-0x801A8A38 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];
void CStruct_dtor(CStruct *);
s32 fn_80219698(CStruct *);
void fn_801A9C1C(void *, void *, void *);
void fn_80177F38(Unk_C7387A53 *, s32);
void fn_801A9324(void *, s32);
s32 fn_801A893C(CScript *, CStruct *);

struct fn998_frame { s32 sp8; s32 spC; char pad[512]; };

bool fn_801A8998(Unk_C7387A53 *arg0, s32 arg1) {
    struct fn998_frame fr;
    s32 mgr = *(s32 *)&lbl_80305F9C;

    CStruct_dtor(arg0->unk0x38);
    if (fn_80219698(mgr) != 0) {
        fr.spC = 0;
        fr.sp8 = arg1;
        fn_801A9C1C((char *)arg0 + 8, (void *)fn_801A893C, &fr.sp8);
        if (fr.spC == 0) {
            return false;
        }
        fn_80177F38(*(s32 *)&lbl_80305EAC, 0);
    }
    fn_801A9324(arg0, arg1 + 1);
    return true;
}
