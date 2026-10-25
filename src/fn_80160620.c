// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160620-0x80160750 (304B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_80174A58(void *, CStruct *);
s32 fn_801A568C(s32, s32);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
s32 fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 GetChecksum(CStruct *, s32);
s32 fn_8015F510(s32, s32, s32);
s32 fn_801A5388(s32);
void s_find_trick_in_mapping(void *, void *, s32);
void fn_801292A8(CStruct *, s32, s32);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);

bool ScriptGetKeyComboArrayFromTrickArray(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    void *sp18;
    s32 temp_r22;
    s32 temp_r23;
    s32 temp_r24;
    s32 temp_r25;
    s32 temp_r28;
    s32 temp_r30;
    s32 var_r27;
    s32 var_r29;
    s32 var_r31;

    GetArray(pParams, QB_TRICKS, &sp18, 1);
    temp_r25 = fn_80174A58(lbl_80305EAC, 0);
    temp_r22 = fn_801A568C(temp_r25, QB_TRICK_MAPPING);
    temp_r23 = ((CStruct *)sp18)->unk0x4;
    temp_r24 = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(temp_r24, temp_r23, 0xD);
    for (var_r27 = 0; var_r27 < temp_r23; var_r27++) {
        temp_r28 = GetChecksum(sp18, var_r27);
        var_r29 = fn_8015F510(temp_r22, temp_r28, 0);
        if (var_r29 == 0) {
            temp_r30 = fn_801A5388(temp_r25);
            for (var_r31 = 0; var_r31 < temp_r30; var_r31++) {
                s_find_trick_in_mapping((void *)sp8, temp_r25, var_r31);
                if (sp8[1] == temp_r28) {
                    var_r29 = sp8[2];
                    break;
                }
            }
        }
        fn_801292A8(temp_r24, var_r27, var_r29);
    }
    fn_80127AAC(pScript->unk0x18, QB_KEYCOMBOS, temp_r24);
    return true;
}
