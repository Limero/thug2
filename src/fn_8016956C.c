// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016956C-0x801695A0 (52B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
bool ScriptGetMaxTHPS4FilesAllowed(void *arg0, CScript *arg1) {
    AddInteger(arg1->unk0x18, QB_MAXTHPS4FILESALLOWED, 0x32);
    return true;
}
