// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80006F6C-0x80006FA8 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8028FDFC[];
void fn_800063B4(void *);
void *fn_80006F6C(Unk_C7387A53 *arg0) {
    fn_800063B4(arg0);
    *(f32 *)&arg0->unk0x20 = lbl_8028FDFC[0];
    return arg0;
}
