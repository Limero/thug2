// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F71EC-0x801F7270 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AE328[];
extern char lbl_802AE2B8[];
s32 fn_80128170(CStruct *, void *, void *, s32);
s32 fn_801F5898(void *, CStruct *);
s32 fn_801F4B2C(s32, s32);
bool fn_801F71EC(Unk_F0C166E4 *arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = (s32)lbl_802AE328;
    if (((s32) arg0->unk0xAC00 != 0) && (fn_80128170(arg1, (s32)lbl_802AE2B8, &sp8, 0) != 0)) {
        s32 r = fn_801F5898(arg0, arg1);
        arg0->unk0xAC00 = r;
        fn_801F4B2C(r, sp8);
    }
    return true;
}
