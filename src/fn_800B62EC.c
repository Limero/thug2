// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B62EC-0x800B6344 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800B63D8(void *);

void fn_800B62EC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 i = 0;
    Unk_C8FEE62D *p = arg0;
    register s32 one __asm__("r30") = 1;
loop:
    if (p->unk0x14 >= 0) {
        fn_800B63D8((char *)p);
        arg0->unk0x90 = one;
        return;
    }
    i++;
    p = (char *)p + 0x18;
    if (i > 5) {
        return;
    }
    goto loop;
}