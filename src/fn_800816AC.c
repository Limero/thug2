// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800816AC-0x800816EC (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800816AC(Unk_C7387A53 *arg0) {
    CStruct *p;
    s32 i;

    for (i = 0; i < arg0->unk0x24; i++) {
        p = ((CStruct **)arg0->unk0x20)[i];
        p->unk0x10 &= 0x7FFFFFFF;
    }
}
