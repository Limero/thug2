// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B5C0-0x8015B61C (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 fn_80174A58(void *, CStruct *);
s32 fn_801A5848();
void AddComponent(CStruct *, s32, s32, void *);
register s32 r31_guard __asm__("r31");
bool ScriptGetCurrentProDisplayInfo(s32 arg0, CScript *arg1) {
    s32 temp_r29;

    fn_80174A58(lbl_80305EAC, 0);
    temp_r29 = arg1->unk0x18;
    AddComponent(temp_r29, QB_STRING, 3, fn_801A5848());
    return true;
}
