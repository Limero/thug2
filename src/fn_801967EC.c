// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801967EC-0x801968A8 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 ContainsFlag(CStruct *, s32);
void AddChecksum(CStruct *, s32, s32);
void fn_8012720C(CStruct *, s32);
s32 fn_8018C580(Unk_C8FEE62D *);

s32 fn_801967EC(Unk_C8FEE62D *arg0) {
    s32 temp_r30;
    Unk_0E2E8431 *temp_r9;

    temp_r30 = ContainsFlag(arg0->unk0x20, QB_TESTING_GOAL);
    AddChecksum(arg0->unk0x20, 0, QB_JUST_WON_GOAL);
    temp_r9 = *((void * *)&arg0->unk0x14);
    ((void (*)(void *, s32, s32)) temp_r9->unk0x74)(
        (char *)arg0 + temp_r9->unk0x70, 0, 1);
    fn_8012720C(arg0->unk0x20, QB_JUST_WON_GOAL);
    if (temp_r30 != 0) {
        AddChecksum(arg0->unk0x20, 0, QB_TESTING_GOAL);
    }
    temp_r30 = fn_8018C580((s32)arg0);
    fn_8012720C(arg0->unk0x20, QB_TESTING_GOAL);
    return temp_r30;
}
