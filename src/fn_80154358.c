// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154358-0x801543B8 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 fn_80127E70(void *, void *, void *, void *);
extern char lbl_80305EAC[];
bool ScriptGetCurrentLevel(void *arg0, CScript *arg1) {
    Unk_B668C38D *temp_r29;

    temp_r29 = *(void * *)&lbl_80305EAC;
    fn_80127E70(arg1->unk0x18, QB_LEVEL, 0xD, temp_r29->unk0x384);
    AddChecksum(arg1->unk0x18, QB_LEVEL_STRUCTURE, temp_r29->unk0x390);
    return true;
}
