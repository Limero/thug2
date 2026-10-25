// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80179654-0x801796B4 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8017471C(s32 arg0, s32 arg1);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
s32 fn_80179654(Unk_DB0E2BAB *arg0) {
    Unk_C71E6DE1 *temp_r31;
    s32 temp_r3;

    temp_r31 = *((s32 * *)&arg0->unk0x0);
    temp_r3 = fn_8017471C(arg0->unk0x18, (s8) *((s8 *)&temp_r31->unk0x0));
    if (temp_r3 == 0) {
        return 4;
    }
    *(s32 *)((char *)GetChecksum_3(temp_r3, QB_SKATERSTATEHISTORY) + (s32)0x11F8) = temp_r31->unk0x4;
    return 1;
}
