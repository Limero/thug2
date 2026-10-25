// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F054C-0x800F0598 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);

s32 fn_800F054C(CStruct *arg0) {
    s32 sp8;

    sp8 = 0;
    GetArray(arg0, QB_LINKS, &sp8, 0);
    if (sp8 == 0) {
        return 0;
    }
    return ((CStruct *)sp8)->unk0x4;
}
