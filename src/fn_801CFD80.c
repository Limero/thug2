// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CFD80-0x801CFE30 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_80131960(CStruct *, s32, s32);
extern s32 fn_8009F27C(CStruct *, Unk_15EF4A35 *, void *, s32, s32);
extern void CStruct_delete(CStruct *, s32);
bool fn_801CFD80(Unk_7C733D0A *arg0, CStruct *arg1) {
    s32 var_r30;
    void *var_r31;

    var_r30 = arg0->unk0x34C;
    GetInteger(arg1, 0, (char *)arg0 + 0x34C, 0);
    var_r30 = arg0->unk0x34C - var_r30;
    var_r31 = (void *)CStruct_ctor(CStruct_new(8));
    AddInteger(var_r31, QB_COUNT, var_r30);
    fn_80131960(arg0->unk0xC, QB_AMMO_METER_CHANGE, 0);
    fn_8009F27C(arg0->unk0xC, QB_AMMO_METER_CHANGE, var_r31, 0, 0);
    if (var_r31 != 0) {
        CStruct_delete(var_r31, 3);
    }
    return true;
}
