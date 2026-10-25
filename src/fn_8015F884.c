// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015F884-0x8015F96C (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
extern void* lbl_80305F9C;
s32 fn_8009CF2C(CStruct *);
s32 fn_801745B4(s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801A5D9C(s32, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_80206EA4(Unk_59E38960 *, void *);
s32 GetInteger(CStruct *, s32, s32 *, s32);
bool ScriptUpdateTrickMappings(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    register s32 var_r29 __asm__("r29");
    register s32 var_r30 __asm__("r30");
    register s32 var_r31 __asm__("r31");

    var_r30 = lbl_80305EAC;
    var_r31 = lbl_80305EFC;
    if (fn_8009CF2C(lbl_80305F9C) != 0) {
        var_r29 = fn_801745B4(var_r30);
        var_r30 = fn_801A5D9C(var_r31, 0);
        fn_80206EA4(GetChecksum_3(var_r29, QB_TRICK), var_r30);
    } else {
        GetInteger(pParams, QB_SKATER, &sp8, 1);
        var_r29 = fn_801746A4(var_r30, sp8);
        var_r30 = fn_801A5D9C(var_r31, sp8);
        if (var_r29 != 0 && var_r30 != 0) {
            fn_80206EA4(GetChecksum_3(var_r29, QB_TRICK), var_r30);
        }
    }
    return true;
}
