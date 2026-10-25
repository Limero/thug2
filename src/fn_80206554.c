// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206554-0x80206654 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8020686C(Unk_C7387A53 *);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 fn_80206554(Unk_C7387A53 *, u32, CStruct *);
s32 fn_802068B4(Unk_C7387A53 *, s32);
s32 fn_80206938(Unk_C7387A53 *, s32);
s32 fn_802069C4(Unk_C7387A53 *);
s32 fn_80206554(Unk_C7387A53 *arg0, u32 arg1, CStruct *arg2) {
    u32 swv1;
    s32 spC;
    s32 sp8;
    switch (swv1 = arg1) {
    case QB_SETGRAFFITITEXTURE:
        if (GetString(arg2, 0, &sp8, 0) != 0) {
            fn_802068B4(arg0, sp8);
        }
        break;
    case QB_SETSTICKERTEXTURE:
        if (GetString(arg2, 0, &spC, 0) != 0) {
            fn_80206938(arg0, spC);
        }
        break;
    case 0x164645C:
        {
            s32 result = fn_802069C4(arg0);
            if (result != 0) {
                result = 1;
            } else {
                result = 0;
            }
            return result;
        }
    case QB_APPLYCUSTOMTAGTEXTURE:
        fn_8020686C(arg0);
        break;
    default:
        return 2;
    }
    return 1;
}
