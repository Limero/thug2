// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9DE0-0x801B9E14 (52B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8012772C(CStruct * arg0, u32 arg1, f32 arg2);
bool fn_801B9DE0(Unk_FFAD6788 *arg0, s32 arg1, CScript *arg2) {
    fn_8012772C(arg2->unk0x18, QB_ORIGINAL_MAX_VELOCITY, *((f32 *)&arg0->unk0xE4));
    return true;
}
