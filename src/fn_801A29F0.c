// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A29F0-0x801A2A58 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A269C(Unk_31DE137E *);
void *fn_801A26E0(Unk_31DE137E *, s32);
s32 fn_801A29F0(Unk_31DE137E *arg0) {
    s32 var_r31;
    void *temp_r3;
    Unk_EFE13F4E *temp_r9;

    var_r31 = 0;
    while (var_r31 < fn_801A269C(arg0)) {
        temp_r3 = fn_801A26E0(arg0, var_r31);
        temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
        ((void (*)(void *))temp_r9->unk0x4C)(temp_r3 + temp_r9->unk0x48);
        var_r31 += 1;
    }
}
