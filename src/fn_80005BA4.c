// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80005BA4-0x80005BD4 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8028FD28;
void fn_80005BA4(CStruct *arg0) {
    f32 temp_f12;

    temp_f12 = lbl_8028FD28;
    *((f32 *)&arg0->unk0x0) = *((f32 *)&arg0->unk0x0) / temp_f12;
    *((f32 *)&arg0->unk0x4) = *((f32 *)&arg0->unk0x4) / temp_f12;
    *((f32 *)&arg0->unk0x8) = *((f32 *)&arg0->unk0x8) / temp_f12;
}
