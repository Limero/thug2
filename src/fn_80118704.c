// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118704-0x801187D4 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetText(CStruct *, s32, char **, s32);
s32 fn_80128E34(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_800F2F90(Unk_C7387A53 *);
s32 fn_800F2EDC(Unk_C7387A53 *, const char *, s32, s32, s32, s32);
extern Unk_C7387A53 *lbl_80301B48;
void ScriptLoadAnim(CStruct *arg0) {
    s32 spC;
    char *sp8;
    s32 var_r27;
    s32 var_r31;
    Unk_C7387A53 *temp_r28;
    temp_r28 = lbl_80301B48;
    spC = 0;
    GetText(arg0, QB_NAME, &sp8, 0);
    var_r27 = 0;
    fn_80128E34(arg0, QB_DESCCHECKSUM, &spC, 1);
    if (ContainsFlag(arg0, QB_ASYNC) != 0) {
        var_r27 = 1;
    }
    var_r31 = 0;
    if (ContainsFlag(arg0, QB_USE_PIP) != 0) {
        var_r31 = 1;
    }
    fn_800F2EDC(temp_r28, sp8, spC, fn_800F2F90(temp_r28), var_r27, var_r31);
}
