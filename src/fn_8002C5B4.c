// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002C5B4-0x8002C638 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009F498(s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
void fn_80125A3C(void *, s32);
bool fn_8002C5B4(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 temp_r3;
    void *temp_r3_2;
    Unk_C6B642AC *temp_r9;

    fn_80125A3C(QB_MOVIECAM_DEBUG, 0);
    temp_r3 = GetStructure(arg0->unk0xC, 1);
    if (temp_r3 != 0) {
        GetChecksum_2(temp_r3, QB_NAME, &sp8, 1);
        temp_r3_2 = fn_8009F498(sp8);
        temp_r9 = ((Unk_9994C3F5 *)temp_r3_2)->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x3C)(temp_r3_2 + temp_r9->unk0x38);
    }
    return true;
}
