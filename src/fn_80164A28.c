// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80164A28-0x80164ABC (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern Unk_9994C3F5 * lbl_80366478;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_80174A58(void *, CStruct *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_802069BC(Unk_C7387A53 *);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8005C070(s32, s32);

bool ScriptSyncCAGWorkspace(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;

    GetInteger(pParams, QB_SKATER, &sp8, 1);
    temp_r29 = fn_801746A4(lbl_80305EAC, sp8);
    fn_80174A58(lbl_80305EAC, 0);
    temp_r30 = fn_802069BC(GetChecksum_3(temp_r29, QB_TAGGING));
    if (temp_r30 != 0) {
        fn_8005C070(fn_8005CF80(lbl_80366478, QB_CAG_WORKSPACE), temp_r30);
    }
    return true;
}
