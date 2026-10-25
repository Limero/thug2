// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159F1C-0x80159F94 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 AddChecksum(CStruct *, void *, void *);
bool ScriptGetCurrentSkaterID(void *arg0, Unk_EFC8CFAD *arg1) {
    s32 temp_r30;
    Unk_C8FEE62D *temp_r9;

    temp_r9 = arg1->unk0xBC;
    if ((temp_r9 != NULL) && ((s32) temp_r9->unk0xC8 != 0)) {
        temp_r30 = temp_r9->unk0x18;
        AddChecksum(arg1->unk0x18, QB_OBJID, temp_r30);
        AddInteger(arg1->unk0x18, QB_INTID, temp_r30);
        return true;
    }
    return false;
}
