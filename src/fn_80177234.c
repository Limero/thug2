// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80177234-0x80177284 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8012EE64(Unk_069CE08E *, s32);
s32 fn_80177234(Unk_F8CDD391 *arg0) {
    s32 result;
    s32 field;

    field = arg0->unk0x428;
    if (field != 0) {
        fn_8012EE64((Unk_069CE08E *)field, 3);
        arg0->unk0x428 = 0;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}