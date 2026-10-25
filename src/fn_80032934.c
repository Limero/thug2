// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032934-0x800329A8 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80032A60(Unk_31DE137E *);
s32 fn_80032A68(Unk_31DE137E *, void *);
extern f32 lbl_80291B38;
bool fn_80032934(Unk_31DE137E *arg0, f32 farg0) {
    volatile double _dummy;

    if (farg0 == lbl_80291B38) {
        fn_80032A68(arg0, NULL);
    }
    if (fn_80032A60(arg0) != 2) {
        return false;
    }
    fn_80032A68(arg0, (void *)1);
    *(f32 *)&arg0->unk0x60 = farg0;
    return true;
}
