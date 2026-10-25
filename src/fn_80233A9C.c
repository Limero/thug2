// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233A9C-0x80233AE4 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305FF8;
void AddChecksum(CStruct *, s32, s32);
bool ScriptGetParkEditorTimeOfDayScript(s32 arg0, CScript *arg1) {
    s32 t;

    t = ((Unk_3784EA79 *)lbl_80305FF8)->unk0x7C;
    if (t != 0) {
        AddChecksum(arg1->unk0x18, QB_TOD_SCRIPT, t);
        return true;
    }
    return false;
}
