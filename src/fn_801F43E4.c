// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F43E4-0x801F443C (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801F2AE0(Unk_31DE137E *, s32);
void fn_801F43E4(Unk_31DE137E *arg0) {
    s32 i;

    i = 1;
    while (i < *(u8 *) ((char *) arg0 + 0x2BA)) {
        fn_801F2AE0(arg0, i);
        i += 1;
    }

    *(u8 *) ((char *) arg0 + 0x2BB) = 0;
    *(u8 *) ((char *) arg0 + 0x2BD) = 0;
}

