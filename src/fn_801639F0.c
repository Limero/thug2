// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801639F0-0x80163A44 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern Unk_9994C3F5 * lbl_80305F24;
s32 fn_801B0F68(Unk_9994C3F5 *);
s32 fn_801B0168(void *);
void AddComponent(CStruct *, s32, s32, void *);
bool ScriptGetInitialsString(s32 arg0, CScript *arg1) {
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    AddComponent(temp_r30, QB_STRING, 3, fn_801B0168(fn_801B0F68(lbl_80305F24)));
    return true;
}
