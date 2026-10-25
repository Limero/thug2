// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004549C-0x800454F4 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800405A0(void);
void fn_8012772C(CStruct *, s32, f32);
void AddChecksum(CStruct *, s32, s32);
void fn_8004549C(Unk_31DE137E *arg0, CStruct *arg1) {
    fn_800405A0();
    fn_8012772C(arg1, QB_ROT_ANGLE, *((f32 *)&arg0->unk0xC4));
    AddChecksum(arg1, QB_TEXTURE, arg0->unk0x190);
}