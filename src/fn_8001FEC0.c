// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FEC0-0x8001FEF4 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: dispatch-setter through fn-ptr table lbl_80300280 — sets
// (arg0<<6)|0x43000000; prototyped (**) cast, no crclr (doc-51 recipe).
#include "types.h"
#include "qb_constants.h"
extern char lbl_80300280[];
s32 fn_8001FEC0(s32 arg0) {
    return (*(s32 (**)(s32))lbl_80300280)((arg0 << 6) | QB_UNKNOWN_0x43000000);
}
