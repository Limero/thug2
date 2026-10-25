// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5DD8-0x801A5E38 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A4540(s32, CStruct *);
s32 fn_801A65EC(Unk_C8FEE62D *, s32 *, s32 *);
void fn_801A5DD8(Unk_9994C3F5 *arg0) {
    s32 spC;
    u32 sp8;
    u32 var_r31;
    u32 limit;

    limit = arg0->unk0x8;
    for (var_r31 = 0U; var_r31 < limit; var_r31++) {
        sp8 = var_r31;
        fn_801A4540(fn_801A65EC((char *)arg0 + 4, &sp8, &spC), 0);
    }
}
