// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033198-0x800331F8 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8002BA5C(CStruct *, s32);
void fn_80033198(CStruct *arg0) {
    u32 var_r31;

    var_r31 = 0U;
    while (var_r31 < (u32) *((u32 *)&arg0->unk0x70)) {
        fn_8002BA5C(arg0->unk0x6C + (s32)(var_r31 * 0x14), 1);
        var_r31 += 1;
    }
}
