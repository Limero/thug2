// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801279CC-0x80127A18 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000A778(s32);
void fn_8012788C(CStruct *, s32, f32, f32, f32);
void fn_801279CC(CStruct *arg0, void *arg1, CStruct *arg2) {
    fn_8012788C(arg0, fn_8000A778(arg1), *((f32 *)&arg2->unk0x0), *((f32 *)&arg2->unk0x4), *((f32 *)&arg2->unk0x8));
}
