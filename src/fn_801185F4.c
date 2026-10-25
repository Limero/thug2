// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801185F4-0x80118704 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetText(CStruct *, void *, void *, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_800F2ED4(Unk_C7387A53 *);
s32 fn_800F2BA8(Unk_C7387A53 *, s32, s32, s32, s32, s32, s32, s32, s32, CStruct *);
s32 Script_GetInteger(s32, s32);
extern Unk_C7387A53 *lbl_80301B48;
bool ScriptLoadAsset(CStruct *arg0) {
    s32 desc;
    s32 parent;
    s32 name;
    s32 async;
    Unk_C7387A53 *manager;
    manager = lbl_80301B48;
    parent = 0;
    if (GetText(arg0, QB_NAME, &name, 0) == 0) {
        GetText(arg0, 0, &name, 1);
    }
    fn_80128E34(arg0, QB_PARENT, &parent, 0);
    async = ContainsFlag(arg0, QB_ASYNC);
    desc = 0;
    fn_80128E34(arg0, QB_DESC, &desc, 0);
    if (fn_800F2BA8(manager, name, 0, desc, parent, async, 0, fn_800F2ED4(manager), 0, arg0) != 0) {
        goto success;
    }
    switch (Script_GetInteger(QB_ASSERTONMISSINGASSETS, 0)) {
    case 0:
        return true;
    default:
        goto success;
    }
success:
    return true;
}
