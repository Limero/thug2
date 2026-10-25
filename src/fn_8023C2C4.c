// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C2C4-0x8023C3AC (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void fn_8023FC44(void *);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_8012772C(CStruct *, u32, f32);
extern void AddChecksum(CStruct *, s32, u32);
extern s32 Script_RunScript(u32, void *, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);

extern f32 lbl_802B0E54;
extern f32 lbl_802B0E58;
extern f32 lbl_80306044;

void fn_8023C2C4(void) {
    struct { char _[0x2c]; f32 v; char _2[0x48]; } sp8;
    f32 var_f31;
    s32 obj;
    s32 cond;

    fn_8023FC44(&sp8);
    var_f31 = sp8.v;
    if (var_f31 < lbl_802B0E54) {
        var_f31 = lbl_802B0E54;
    } else if (var_f31 > lbl_802B0E58) {
        var_f31 = lbl_802B0E58;
    }
    obj = CStruct_ctor(CStruct_new(8));
    fn_8012772C(obj, QB_PARK_PERCENT, var_f31);
    cond = lbl_80306044 >= lbl_802B0E58;
    if (cond != 0) {
        AddChecksum(obj, 0, QB_PARK_FULL);
    }
    Script_RunScript(QB_PARKED_UPDATE_PERCENT_BAR, obj, 0, 0, 0);
    if (obj != 0) {
        CStruct_delete(obj, 3);
    }
}
