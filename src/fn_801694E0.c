// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801694E0-0x80169518 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
extern CStruct * lbl_80305E88;
bool ScriptGetMemCardDataForUpload(void *arg0, CScript *arg1) {
    AddChecksum(arg1->unk0x18, QB_TYPE, lbl_80305E88);
    return true;
}
