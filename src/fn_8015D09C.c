// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D09C-0x8015D174 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305EC0[];
extern s32 IsTrue(s32 obj, void * hash);
extern s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern s32 fn_801A7178(Unk_93C2DF4D * a, s32 b);
extern s32 fn_80174A58(void * obj, CStruct * idx);
extern s32 fn_801A5278(s32 a, s32 b);
extern s32 Script_RunScript(s32 a, s32 b, s32 c, s32 d, s32 e);
bool ScriptAwardStatPoint(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r30_2;

    if (IsTrue(*(s32 *)&lbl_80305EC0, QB_IS_CLASSIC) != 0) {
        temp_r30 = *(s32 *)((char *)*(void **)&lbl_80305EAC + 0x24);
        sp8 = 1;
        GetInteger(pParams, 0, &sp8, 0);
        fn_801A7178(temp_r30, sp8);
    } else {
        temp_r30_2 = fn_80174A58(*(s32 *)&lbl_80305EAC, 0);
        spC = 1;
        GetInteger(pParams, 0, &spC, 0);
        fn_801A5278(temp_r30_2, spC);
    }
    Script_RunScript(QB_STAT_PLAY_WIN_SOUND, 0, 0, 0, 0);
    return true;
}
