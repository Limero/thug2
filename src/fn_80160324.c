// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160324-0x80160368 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 fn_8005581C(void);
bool ScriptGetNumSoundtracks(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_8005581C();
    AddInteger(arg1->unk0x18, QB_NUMSOUNDTRACKS, temp_r5);
    return true;
}
