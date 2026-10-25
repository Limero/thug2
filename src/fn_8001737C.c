// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001737C-0x800173CC (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0xA8];
    void *unk0xA8;
} Obj1737C;

void fn_80017128(void *, void *);
void PSMTX_Identity(f32 *);

void fn_8001737C(Obj1737C *arg0) {
    f32 sp8[12];
    void *unk;

    unk = arg0->unk0xA8;
    if (unk != NULL) {
        fn_80017128(arg0, unk);
        return;
    }
    PSMTX_Identity(sp8);
    fn_80017128(arg0, sp8);
}
