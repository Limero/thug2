// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80176F28-0x80176FA8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];
s32 fn_8021E024(s32);
s32 fn_8021E02C(s32);
s32 fn_8017480C(s32);
s32 fn_80176F28(s32 arg0) {
    if (arg0 == QB_NETWORK) {
        return fn_8021E024(*(s32 *)lbl_80305F9C);
    }
    if (arg0 == QB_TAUNT) {
        return fn_8021E02C(*(s32 *)lbl_80305F9C);
    }
    if (arg0 == 0x06AB02F2) {
        return fn_8017480C(*(s32 *)lbl_80305EAC);
    }
    return 0;
}
