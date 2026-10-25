// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151468-0x80151534 (204B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A7D28[];
extern char lbl_802A7D34[];
extern char lbl_802A7D40[];
extern u8 lbl_8039FB90[];
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum_4(CStruct *, void *, void *, s32);
extern s32 fn_80176F28(s32, s32);
extern s32 fn_8013FF5C(s32, s32);
extern s32 fn_80128170(CStruct *, void *, void *, s32);
void fn_801275D4(CStruct *, void *, void *);
bool ScriptGetPreferencePassword(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    char *sp10;
    s32 temp_r29;
    s32 var_r31;

    temp_r29 = pScript->unk0x18;
    GetChecksum_2(pParams, 0, &sp8, 0);
    var_r31 = 0;
    GetChecksum_4(pParams, (s32)lbl_802A7D28, &spC, 0);
    fn_80128170(fn_8013FF5C(fn_80176F28(spC, 1), sp8), (s32)lbl_802A7D34, &sp10, 0);
    while (var_r31 < strlen(sp10)) {
        lbl_8039FB90[var_r31] = '*';
        var_r31 += 1;
    }
    lbl_8039FB90[var_r31] = 0;
    fn_801275D4(temp_r29, (s32)lbl_802A7D40, (s32)lbl_8039FB90);
    return true;
}
