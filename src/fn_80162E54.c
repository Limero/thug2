// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162E54-0x80162F40 (236B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern Unk_9994C3F5 * lbl_80366474;
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_8005CF80(Unk_9994C3F5 *, s32);
extern void fn_8005CF34(CStruct *, s32, s32, s32, s32);
extern s32 fn_8005C6E8(s32, s32, s32);

bool ScriptCombineTextures(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 bool_r31;
    s32 texA;
    register s32 texB __asm__("r6");

    sp10 = 0;
    GetChecksum_2(pParams, QB_SRC, &sp8, 0);
    GetChecksum_2(pParams, QB_TOP, &spC, 0);
    GetChecksum_2(pParams, QB_NEW, &sp10, 0);
    bool_r31 = ContainsFlag(pParams, QB_NO_PALETTE_GEN) == 0;
    texA = fn_8005CF80(lbl_80366474, sp8);
    if (texA != 0) {
        texB = fn_8005CF80(lbl_80366474, spC);
        if (texB != 0) {
            if (sp10 != 0) {
                fn_8005CF34(lbl_80366474, sp10, texA, texB, bool_r31);
            } else {
                fn_8005C6E8(texA, texB, bool_r31);
            }
        }
    }
    return true;
}
