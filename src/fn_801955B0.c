// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801955B0-0x80195668 (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801270B4(CStruct *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80127C14(CStruct *, s32, CStruct *);
s32 CStruct_delete(CStruct *, s32);
s32 AddInteger(CStruct *, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8018C080(Unk_672A1C0D *);
void fn_801955B0(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 temp_r3;

    fn_801270B4(arg0->unk0x20, QB_COMPLETEDGAPS);
    temp_r3 = CStruct_ctor(CStruct_new(8));
    fn_80127C14(arg0->unk0x20, QB_COMPLETEDGAPS, temp_r3);
    if (temp_r3 != 0) {
        CStruct_delete(temp_r3, 3);
    }
    AddInteger(arg0->unk0x20, QB_UNKNOWN_0xF1E59083, 0);
    AddInteger(arg0->unk0x20, QB_NUMBER_COLLECTED, 0);
    GetInteger(arg0->unk0x20, QB_NUM_GAPS_TO_FIND, &sp8, 1);
    fn_8018C080(arg0);
}
