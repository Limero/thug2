// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF7EC-0x800AF844 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_800AF7EC(Unk_6849630D *arg0, CStruct *arg1) {
    arg0->unk0x34C0 = arg1;
    arg0->unk0x34D0 = 0;
    GetFloat(fn_80129528(arg1, 0), QB_TIME, (char *)arg0 + 0x34CC, 1);
}
