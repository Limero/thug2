// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CC0C-0x8012CC30 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern int lbl_803032B0;
void *fn_8012CC0C(CStruct *self) {
    int c = lbl_803032B0;
    *((int *)&self->unk0x5C) = 0;
    *((int *)&self->unk0x60) = 0;
    lbl_803032B0 = c + 1;
    return self;
}
