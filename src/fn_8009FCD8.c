// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FCD8-0x8009FD6C (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
void fn_800F0870(s32, s32);
void fn_800F078C(CStruct *, Unk_9994C3F5 *);
void fn_8009E1F0(Unk_C8FEE62D *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8009FCD8(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;

    if (GetChecksum_2(arg1, QB_NAME, &sp8, 0) != 0) {
        fn_8009E1F0(arg0, sp8);
    }
    fn_800F078C(arg1, (char *)arg0 + 0x58);
    fn_800F0870(arg1, (char *)arg0 + 0x78);
    if (ContainsFlag(arg1, QB_PERMANENT) != 0) {
        arg0->unk0xC = (s32) (arg0->unk0xC | 2);
    }
}
