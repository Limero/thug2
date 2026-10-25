// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0430-0x801B04AC (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80127E70(s32, s32, s32, s32);
void AddComponent(CStruct *, s32, s32, void *);
s32 fn_801B0168(void *);
void fn_801B0430(CStruct *arg0, CStruct *arg1) {
    fn_80127E70(arg1, QB_VALUE, 1, arg0->unk0x8);
    fn_80127E70(arg1, QB_NUMBER, 1, arg0->unk0xC);
    AddComponent(arg1, QB_INITIALS, 3, fn_801B0168(arg0->unk0x4));
}
