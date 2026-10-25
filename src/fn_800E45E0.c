// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E45E0-0x800E465C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80068954(s32, s32);
s32 fn_80068998(s32, s32);
extern char lbl_8030044C[];
s32 GetInteger(CStruct *, void *, s32 *, void *);
bool fn_800E45E0(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2) {
    s32 sp8;

    sp8 = 0;
    GetInteger(arg2, QB_IFEMPTY, &sp8, 0);
    if (sp8 != 0) {
        fn_80068998(*(s32 *)lbl_8030044C, arg0->unk0x28);
    } else {
        fn_80068954(*(s32 *)lbl_8030044C, arg0->unk0x28);
    }
    return true;
}
