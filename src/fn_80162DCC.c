// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162DCC-0x80162E54 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005CECC(void *, void *, void *);
s32 fn_8005CF80(Unk_9994C3F5 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
extern Unk_9994C3F5 * lbl_80366474;
bool ScriptCopyTexture(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    GetChecksum_2(pParams, QB_SRC, &sp8, NULL);
    temp_r3 = fn_8005CF80(lbl_80366474, sp8);
    if ((temp_r3 != 0) && (GetChecksum_2(pParams, (s32 *)QB_NEW, &spC, 0) != 0)) {
        fn_8005CECC(lbl_80366474, spC, temp_r3);
    }
    return true;
}
