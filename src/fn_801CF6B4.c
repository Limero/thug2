// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CF6B4-0x801CF72C (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8012772C(CStruct *, s32, f32);
bool fn_801CF6B4(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    fn_8012772C(arg2->unk0x18, QB_X, *(f32 *)(arg0->unk0xC + (s32)0x88));
    fn_8012772C(arg2->unk0x18, QB_Y, *(f32 *)(arg0->unk0xC + (s32)0x8C));
    fn_8012772C(arg2->unk0x18, QB_Z, *(f32 *)(arg0->unk0xC + (s32)0x90));
    return true;
}
