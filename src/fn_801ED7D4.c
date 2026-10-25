// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED7D4-0x801ED88C (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD94C;
void *fn_801403CC(void *);
s32 CStruct_new(s32);
void *CStruct_ctor(void *);
void AddChecksum(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_801ED7D4(Unk_DFF20570 *arg0) {
    CStruct *temp_r3;
    void *temp_r31;

    if (arg0->unk0x358 == 0) {
        return;
    }
    if ((temp_r3 = fn_801403CC(arg0->unk0xC)) == NULL) {
        return;
    }
    if (*((f32 *)&temp_r3->unk0x4) > lbl_802AD94C) {
        *((f32 *)&temp_r3->unk0x4) = *((f32 *)&temp_r3->unk0x4) - arg0->unk0x94;
        return;
    }
    AddChecksum(temp_r31 = CStruct_ctor((void *)CStruct_new(8)), QB_TIMELIMIT, 1);
    Script_RunScript(QB_KILLSPECIAL, temp_r31, arg0->unk0xC, 0, 0);
    if (temp_r31 != NULL) {
        CStruct_delete(temp_r31, 3);
    }
}
