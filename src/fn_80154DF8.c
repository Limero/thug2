// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154DF8-0x80154E48 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_80128E34(CStruct *, void *, void *, s32);

bool ScriptLevelIs(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_71062261 *temp_r30;

    temp_r30 = *(void **)&lbl_80305EAC;
    fn_80128E34(pParams, 0, &sp8, 1);
    return (temp_r30->unk0x388 ^ sp8) == 0;
}
