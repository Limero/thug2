// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003D9DC-0x8003DA40 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_8003ABA0(void);
void GetChecksum_2(s32, s32, s32 *, s32);
s32 fn_8003D9DC(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 t = fn_8003ABA0();

    if (t) {
        sp8 = 0;
        GetChecksum_2(t, QB_DESC_ID, &sp8, 0);
        return sp8 == QB_CREATEDGRAPHIC;
    }
    return 0;
}
