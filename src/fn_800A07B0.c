// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A07B0-0x800A07F0 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012788C(s32, s32, s32, f32, f32, f32);
bool fn_800A07B0(Unk_FFAD6788 *arg0, void *arg1, CScript *arg2) {
    fn_8012788C(arg2->unk0x18, QB_VEL, arg2, *((f32 *)&arg0->unk0xB8), *((f32 *)&arg0->unk0xBC), *((f32 *)&arg0->unk0xC0));
    return true;
}
