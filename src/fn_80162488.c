// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162488-0x80162540 (184B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005C1B4(s32);
s32 fn_8005C1E8(s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
// FLAG: -fno-schedule-insns2
void GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 lbl_80366474;
bool ScriptFlipTexture(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    GetChecksum_2(pParams, 0, &sp8, 0);
    spC = 0;
    sp10 = 0;
    if ((temp_r3 = fn_8005CF80(lbl_80366474, sp8)) != 0) {
        GetInteger(pParams, QB_HORIZ, &spC, 0);
        GetInteger(pParams, QB_VERT, &sp10, 0);
        if (spC != 0) {
            fn_8005C1B4(temp_r3);
        }
        if (sp10 != 0) {
            fn_8005C1E8(temp_r3);
        }
    }
    return true;
}
