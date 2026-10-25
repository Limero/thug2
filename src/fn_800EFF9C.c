// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFF9C-0x800EFFE8 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_800F116C(CStruct *);
s32 fn_800F1180(CStruct *, s32 *);
void fn_800EFD48(s32);

void fn_800EFF9C(void *arg0) {
    s32 r;

    fn_800F116C(*(CStruct **)((char *)arg0 + 4));
    while ((r = fn_800F1180(*(CStruct **)((char *)arg0 + 4), 0)) != 0) {
        fn_800EFD48(r);
    }
}
