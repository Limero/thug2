// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D6848-0x800D68AC (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_800D67D0(Unk_6A70655D *, s32);
void fn_800D6848(Unk_31DE137E *arg0, CStruct *arg1) {
    s32 sp8;
    if (GetChecksum_2(arg1, QB_NAME, &sp8, 0) != 0) {
        fn_800D67D0(arg0, sp8);
        arg0->unk0x1C = (arg0->unk0x1C | 0x10) & ~0x8;
    }
}
