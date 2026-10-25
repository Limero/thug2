// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118104-0x80118184 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void GetChecksum_2(void *, void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000A778(s32);
s32 GetText(CStruct *, void *, void *, void *);
extern char lbl_802FFE98[];
s32 fn_80010544(s32, s32, s32);
void ScriptMemDeleteHeap(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    if (GetText(pParams, QB_NAME, &sp8, 0) != 0) {
        spC = fn_8000A778(sp8);
    } else {
        GetChecksum_2(pParams, QB_NAME, &spC, 1);
    }
    fn_80010544(*(s32 *)&lbl_802FFE98, spC, 0);
}
