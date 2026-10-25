// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189114-0x801891C4 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern u8 lbl_802A9498;
extern char lbl_802A9594[];
extern void strcat(s32, s32);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern s32 AddString(CStruct *, s32, void *);

bool ScriptGoalManager_GetProsetNotPrefix(CStruct *pParams, CScript *pScript) {
    u8 sp8[128];
    void *sp88;
    char *p;
    s32 var_r8;

    GetString(pParams, 0, &sp88, 1);
    var_r8 = 0;
    p = (char *)sp88;
    sp8[0] = lbl_802A9498;
    if (((Unk_1D62F22E_2 *)p)->unk0x1 != 0) {
        do {
            sp8[var_r8] = *(u8 *)(p + var_r8);
            var_r8++;
            p = (char *)sp88;
        } while (*(u8 *)((char *)(var_r8 + (s32)p) + 1) != 0);
    }
    sp8[var_r8] = 0;
    strcat((s32)sp8, (s32)lbl_802A9594);
    AddString(pScript->unk0x18, QB_PROSET_NOT_PREFIX, (s32)sp8);
    return true;
}
