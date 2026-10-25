// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058EE4-0x80058F00 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S_80058EE4 {
    char pad0x0[0x4C];
    struct S_80058EE4 *unk0x4C;
} S_80058EE4;
extern S_80058EE4 *lbl_80300474;
S_80058EE4 *fn_80058EE4(void) {
    S_80058EE4 *p;

    p = lbl_80300474;
    if (p != NULL) {
        lbl_80300474 = p->unk0x4C;
    }
    return p;
}
