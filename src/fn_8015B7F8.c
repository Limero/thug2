// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B7F8-0x8015B8A4 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_802A8198[];
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_80174AB8(void *, s32);
extern s32 fn_8003AE20(Unk_31DE137E *);
extern s32 GetStructure_3(CStruct *, void *, void *, s32);
extern s32 GetFacePointsStruct(Unk_DB0E2BAB *, CStruct *);
extern void fn_80129570(s32, s32);
extern void fn_8003EE50(s32, void *);
bool ScriptSetPlayerFacePoints(CStruct *pParams, CScript *pScript) {
    s32 sp8[14];
    s32 sp40;
    s32 sp44;
    s32 temp_r30;

    GetInteger(pParams, QB_PLAYER, &sp40, 1);
    temp_r30 = fn_8003AE20(fn_80174AB8(*(s32 *)&lbl_80305EAC, sp40) + 4);
    if (GetStructure_3(pParams, (s32)lbl_802A8198, &sp44, 0) == 0) {
        sp44 = pParams;
    }
    if (GetFacePointsStruct(sp8, sp44) == 0) {
        fn_80129570(pParams, 0);
    }
    fn_8003EE50(temp_r30, sp8);
    return true;
}
