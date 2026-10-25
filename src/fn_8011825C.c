// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011825C-0x801182BC (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000F68C(Unk_B0F19D72 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
extern char lbl_802FFE98[];
bool ScriptAnalyzeHeap(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    temp_r31 = *(s32 *)&lbl_802FFE98;
    sp8 = QB_BOTTOMUPHEAP;
    if (pParams != 0) {
        GetChecksum_2(pParams, 0, &sp8, 0);
    }
    fn_8000F68C(temp_r31, sp8);
    return true;
}
