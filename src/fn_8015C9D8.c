// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C9D8-0x8015CA18 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_8019B728(Unk_31DE137E * arg0, s32 arg1);

void ScriptPlaceIs(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetInteger(pParams, 0, &sp8, 0);
    fn_8019B728(((Unk_7251BA8A *)lbl_80305EAC)->unk0x370, sp8);
}
