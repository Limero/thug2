// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801686A4-0x80168714 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFF6C;
void PauseMusic(s32);
void PauseStream(s32);
s32 fn_80015A58(void *, s32, s32);
s32 fn_80015AC0(Unk_C8FEE62D *);

s32 ScriptFormatCard(CStruct *pParams, CScript *pScript) {
    s32 var_r31;
    s32 temp_r3;

    var_r31 = 0;
    PauseMusic(1);
    PauseStream(1);
    temp_r3 = fn_80015A58(lbl_802FFF6C, 0, 0);
    if (temp_r3 != 0) {
        var_r31 = fn_80015AC0((void *)temp_r3);
    }
    PauseMusic(-1);
    PauseStream(-1);
    return var_r31;
}
