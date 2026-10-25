// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9D4C-0x801B9D9C (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
extern void fn_8012772C(CStruct * arg0, u32 arg1, f32 arg2);
bool fn_801B9D4C(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    f32 v;
    v = *(f32 *)((char *)GetChecksum_3(arg0->unk0xC, QB_MOTION) + (s32)0x34);
    fn_8012772C(arg2->unk0x18, QB_VELOCITY, v);
    return true;
}
