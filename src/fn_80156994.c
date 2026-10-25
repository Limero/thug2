// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156994-0x80156A3C (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

struct goals_6994 {
    char pad[0x24];
    s32 mgr;
};
extern struct goals_6994 *lbl_80305EAC;
extern char lbl_802A8094[];
extern char lbl_802A809C[];
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801A6E0C(Unk_93C2DF4D *, s32);
s32 sprintf(s32, ...);
void AddComponent(CStruct *, s32, s32, void *);

bool ScriptGetGoalsCompleted(CStruct *pParams, CScript *pScript) {
    char sp8[100];
    s32 sp70;
    s32 mgr;

    mgr = lbl_80305EAC->mgr;
    sp70 = 0;
    GetInteger(pParams, 0, &sp70, 0);
    sprintf(sp8, (s32)lbl_802A8094, fn_801A6E0C(mgr, sp70));
    AddComponent(pScript->unk0x18, QB_UNKNOWN_0xC661FE79, 3, sp8);
    AddComponent(pScript->unk0x18, QB_UNKNOWN_0xA43DC969, 3, (s32)lbl_802A809C);
    return true;
}
