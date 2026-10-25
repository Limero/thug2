// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CA18-0x8015CA58 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_8019B73C(Unk_9994C3F5 * arg0, s32 arg1);
void ScriptRoundIs(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetInteger(pParams, 0, &sp8, 0);
    fn_8019B73C(((Unk_C2F9BED0 *)lbl_80305EAC)->unk0x370, sp8);
}
