// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115A28-0x80115BC8 (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void *fn_8012543C(s32);
bool ScriptGlobalExists(CStruct *arg0) {
    u32 swv1;
    s32 spC;
    s32 sp8;
    s32 var_r31;
    Unk_6A78CE27 *temp_r3;
    sp8 = 0;
    GetChecksum_2(arg0, QB_NAME, &sp8, 0);
    spC = 0;
    var_r31 = 0;
    GetChecksum_2(arg0, QB_TYPE, &spC, 0);
    switch (swv1 = spC) {
    case QB_INT:
    case QB_INTEGER:
        var_r31 = 1;
        break;
    case QB_FLOAT:
        var_r31 = 2;
        break;
    case QB_NAME:
    case QB_CHECKSUM:
        var_r31 = 0xD;
        break;
    case QB_STRING:
        var_r31 = 3;
        break;
    case QB_VECTOR:
        var_r31 = 6;
        break;
    case QB_PAIR:
        var_r31 = 5;
        break;
    case QB_ARRAY:
        var_r31 = 0xC;
        break;
    case QB_STRUCTURE:
    case QB_STRUCT:
        var_r31 = 0xA;
        break;
    }
    temp_r3 = fn_8012543C(sp8);
    if (temp_r3 != NULL && temp_r3->unk0x2 == var_r31) {
        return true;
    }
    return false;
}
