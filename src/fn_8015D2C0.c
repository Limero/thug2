// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D2C0-0x8015D324 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 lbl_80305F24;
extern s32 fn_801A6CCC(Unk_93C2DF4D * obj);
extern s32 fn_801B0F94(Unk_C7387A53 * obj, s32 idx);
extern s32 fn_801B0F68(Unk_9994C3F5 * obj);
extern s32 fn_801B0ACC(Unk_C8FEE62D * a, void * b);
bool ScriptUpdateInitials(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;
    s32 temp_r29;
    s32 temp_r30;

    temp_r3 = fn_801A6CCC(*(s32 *)((char *)*(void **)&lbl_80305EAC + 0x24));
    temp_r30 = lbl_80305F24;
    temp_r29 = fn_801B0F94(temp_r30, temp_r3);
    fn_801B0ACC(temp_r29, fn_801B0F68(temp_r30));
    return true;
}
