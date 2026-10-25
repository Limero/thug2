// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016EC4-0x80016EDC (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} T16;
extern T16 lbl_802FFF80[];
s32 fn_80016EC4(s32 arg0) {
    return lbl_802FFF80[arg0].d;
}
