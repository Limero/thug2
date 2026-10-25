// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FE04-0x8009FE44 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012788C(s32, s32, s32, f32, f32, f32);
bool fn_8009FE04(CStruct *arg0, void *arg1, CScript *arg2) {
    fn_8012788C(arg2->unk0x18, QB_POS, arg2, *((f32 *)&arg0->unk0x58), *((f32 *)&arg0->unk0x5C), *((f32 *)&arg0->unk0x60));
    return true;
}
