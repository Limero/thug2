// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CA58-0x8015CAA8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000F2F8(Unk_9F352E7C *, void *);
s32 fn_8000F320(Unk_F12C5E01 *);
s32 fn_8019B754(Unk_31DE137E *);
extern char lbl_802FFE98[];
extern char lbl_80305EAC[];
bool ScriptEndCompetition(CStruct *pParams, CScript *pScript) {
    Unk_B0F19D72 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x5F8);
    fn_8019B754(*(s32 *)((char *)(*(void * *)&lbl_80305EAC) + 0x370));
    fn_8000F320(*(void * *)&lbl_802FFE98);
    return true;
}
