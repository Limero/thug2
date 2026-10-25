// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x800679A0-0x800679D8 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802945E8[];
extern char lbl_80294600[];
void fn_80062DBC(Unk_C8FEE62D *);
void fn_800679A0(Unk_C8FEE62D *arg0) {
    arg0->unk0x20 = (s32)lbl_802945E8;
    arg0->unk0x8 = (s32)lbl_80294600;
    fn_80062DBC(arg0);
}
