// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801554C4-0x8015552C (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_8016D1A8(void);
s32 fn_8016CFDC(Unk_C7387A53 *);
void AddChecksum(CStruct *, s32, s32);

bool ScriptGetViewerObjectID(void *arg0, CScript *arg1) {
    CScript *var_r30;
    s32 temp_r3;

    temp_r3 = fn_8016D1A8();
    if (temp_r3 != 0) {
        var_r30 = fn_8016CFDC(temp_r3);
        AddChecksum(arg1->unk0x18, QB_OBJID, var_r30->unk0x18);
        AddChecksum(arg1->unk0x18, QB_VIEWEROBJECTID, var_r30->unk0x18);
    }
    return true;
}
