// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001EFF4-0x8001F03C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern void (*lbl_80300280)(s32, s32);
void fn_8001EFF4(s32 arg0, s32 arg1) {
    lbl_80300280((arg0 << 8) | arg0 | (arg1 << 0x10) | (arg1 << 0x13) | QB_UNKNOWN_0x22000000, arg1 << 0x13);
}
