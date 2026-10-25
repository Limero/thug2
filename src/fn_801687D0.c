// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801687D0-0x80168890 (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305E84;
extern s32 lbl_80305E88;
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void s_generate_summary_info(s32 arg0, s32 arg1, CStruct * arg2);
extern s32 Game_GetGoalManager(void);
extern void fn_8018568C(Unk_526DA6F2 * arg0);
bool ScriptGetSummaryInfo(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r0;

    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    spC = 0;
    GetInteger(pParams, QB_VAULTDATA, &spC, 0);
    if (spC != 0) {
        temp_r0 = lbl_80305E88;
        sp8 = temp_r0;
        s_generate_summary_info(pScript->unk0x18, temp_r0, lbl_80305E84);
    } else {
        if (sp8 == QB_OPTIONSANDPROS) {
            fn_8018568C(Game_GetGoalManager());
        }
        s_generate_summary_info(pScript->unk0x18, sp8, 0);
    }
    return true;
}
