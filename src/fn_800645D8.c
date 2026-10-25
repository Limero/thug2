// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800645D8-0x80064618 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800645D8(Unk_785A711F *arg0, CStruct *arg1) {
    s32 var_r9;

    var_r9 = 1;
    if (!(arg0->unk0x128 & 0x10000)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        arg0->unk0x68 = (f32) *((f32 *)&arg1->unk0x0);
        arg0->unk0x6C = (f32) *((f32 *)&arg1->unk0x4);
        arg0->unk0x70 = (f32) *((f32 *)&arg1->unk0x8);
        arg0->unk0x74 = (f32) *((f32 *)&arg1->unk0xC);
    }
}
