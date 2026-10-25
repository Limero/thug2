// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A79D4-0x800A7A48 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800F078C(CStruct *, Unk_9994C3F5 *);
s32 ContainsFlag(CStruct *, s32);
s32 Mem_NewZero(s32);
void fn_800A79D4(CStruct *arg0, s16 arg1, CStruct *arg2) {
    void *temp_r3;

    temp_r3 = Mem_NewZero(0x20);
    ((Unk_655A82FB *)temp_r3)->unk0x18 =  arg0->unk0x4;
    arg0->unk0x4 = temp_r3;
    ((Unk_655A82FB *)temp_r3)->unk0x1C = arg1;
    ((Unk_655A82FB *)temp_r3)->unk0x1E = ContainsFlag(arg2, QB_CREATEDATSTART);
    ((Unk_655A82FB *)temp_r3)->unk0x1F = 0;
    fn_800F078C(arg2, temp_r3 + 8);
}
