// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FCEF8-0x800FCF18 (32B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C160;

void *fn_800FCEF8(CStruct *arg0) {
    f32 v = lbl_8029C160;
    *((f32 *)&arg0->unk0x0) = v;
    *((f32 *)&arg0->unk0x4) = v;
    *((f32 *)&arg0->unk0x8) = v;
    *((f32 *)&arg0->unk0xC) = v;
    return arg0;
}