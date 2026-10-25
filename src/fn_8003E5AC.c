// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E5AC-0x8003E5F8 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern Unk_9994C3F5 * lbl_80366474;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_8003DB00(s32);

bool ScriptSetFaceMassageTextureOverlay(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 0);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if (temp_r3 != 0) {
        fn_8003DB00(temp_r3);
    }
    return true;
}
