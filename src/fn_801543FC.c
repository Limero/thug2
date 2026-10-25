// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801543FC-0x80154438 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
extern char lbl_80305EAC[];
bool ScriptGetLevelStructureName(void *arg0, CScript *arg1) {
    AddChecksum(arg1->unk0x18, QB_LEVEL_STRUCTURE_NAME, *(s32 *)((char *)(*(void * *)&lbl_80305EAC) + 0x390));
    return true;
}
