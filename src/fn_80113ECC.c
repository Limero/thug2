// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113ECC-0x80113F10 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8011E5C8(void);
void AddInteger(CStruct *, s32, s32);

bool ScriptGetCurrentTrack(void *arg0, CScript *arg1) {
    s32 temp_r5;

    temp_r5 = fn_8011E5C8();
    AddInteger(arg1->unk0x18, QB_CURRENT_TRACK, temp_r5);
    return true;
}
