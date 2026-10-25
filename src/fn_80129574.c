// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129574-0x8012966C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

CStruct *fn_801259C8(s32, s32);
s32 GetChecksum(CStruct *, s32);
void *fn_8012CBD4(void *, u16);
void *fn_8012CB7C(void *, s32);

void *fn_80129574(void *arg0, u8 arg1, s32 arg2) {
    CStruct *tbl;
    void *val;
    s32 i;
    s32 n;

    tbl = fn_801259C8(QB_WRITETOBUFFER_COMPRESSIONLOOKUPTABLE_8, 0);
    n = tbl->unk0x4;
    for (i = 0; i < n; i++) {
        if (GetChecksum(tbl, i) == arg2) {
            *(s8 *)arg0 = arg1 | 0x80;
            arg0++;
            *(s8 *)arg0 = (s8)i;
            return arg0 + 1;
        }
    }

    tbl = fn_801259C8(QB_WRITETOBUFFER_COMPRESSIONLOOKUPTABLE_16, 0);
    val = arg0 + 1;
    n = tbl->unk0x4;
    for (i = 0; i < n; i++) {
        if (GetChecksum(tbl, i) == arg2) {
            *(s8 *)arg0 = arg1 | 0x40;
            return fn_8012CBD4(val, (u16) i);
        }
    }

    *(s8 *)arg0 = arg1;
    return fn_8012CB7C(val, arg2);
}
