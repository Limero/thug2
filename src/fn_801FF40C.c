// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FF40C-0x801FF4FC (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AEA50;
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
void fn_801FF500(Unk_C7387A53 * arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);

s32 fn_801FF40C(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2) {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;

    switch (arg1) {
    case QB_SC_SETSKATERCAMOVERRIDE:
        GetFloat(arg2, QB_HEADING, &sp8, (sp14 = lbl_802AEA50, 1));
        GetFloat(arg2, QB_TILT, &spC, 1);
        GetFloat(arg2, QB_TIME, &sp10, 1);
        GetFloat(arg2, QB_ZOOM, &sp14, 0);
        fn_801FF500(arg0, sp8, spC, sp10, sp14);
        goto ret1;
    case QB_SC_CLEARSKATERCAMOVERRIDE:
        arg0->unk0x20 = 0;
        goto ret1;
    default:
        return 2;
    }
ret1:
    return 1;
}
