// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800246B4-0x80024724 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009EE2C(Unk_FFAD6788 *, s32, CStruct *);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_800244BC(Unk_FFAD6788 *, f32);
extern f32 lbl_80291344;
s32 fn_800246B4(Unk_FFAD6788 *arg0, s32 arg1, CStruct *arg2) {
    f32 sp8;

    if (arg1 == QB_CHANGECAMERAFOV) {
        GetFloat(arg2, 0, &sp8, 1);
        fn_800244BC(arg0, sp8 * lbl_80291344);
        return 1;
    } else {
        return fn_8009EE2C(arg0, arg1, arg2);
    }
}
