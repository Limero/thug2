// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B9BC-0x8015BA18 (92B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_80174AB8(void *, s32);
extern s32 fn_8003AE20(Unk_31DE137E *);
extern s32 fn_8003EDD0(CStruct *);
s32 ScriptPlayerFaceIsValid(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    temp_r3 = fn_8003AE20(fn_80174AB8(*(s32 *)&lbl_80305EAC, sp8) + 4);
    if (temp_r3 == 0) {
        return 0;
    }
    return fn_8003EDD0(temp_r3);
}
