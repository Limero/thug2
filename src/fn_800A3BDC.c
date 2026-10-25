// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3BDC-0x800A3C24 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_800A3BDC(s32 arg0) {
    s32 sp8;

    arg0 = *(s32 *)(arg0 + 0x10);
    sp8 = 0;
    if (arg0 != 0) {
        GetInteger((CStruct *)arg0, QB_CONTROLLER, &sp8, 0);
    }
    return sp8;
}
