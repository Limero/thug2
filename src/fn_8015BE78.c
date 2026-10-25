// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BE78-0x8015BEB8 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
extern char lbl_80305EAC[];
bool ScriptGetCurrentChapter(void *arg0, CScript *arg1) {
    Unk_93C2DF4D *temp_r9;

    temp_r9 = *(s32 *)((char *)(*(void * *)&lbl_80305EAC) + 0x24);
    AddInteger(arg1->unk0x18, QB_CHAPTER, temp_r9->unk0x634);
    return true;
}
