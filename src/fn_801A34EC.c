// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A34EC-0x801A3538 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_801A26E0(Unk_31DE137E *, s32);
typedef struct {
    char p0[0x50];
    s16 off;
    char p1[2];
    void *fn;
} VT34EC;
s32 fn_801A34EC(Unk_31DE137E *arg0) {
    void *temp_r3;
    VT34EC *vt;

    temp_r3 = fn_801A26E0(arg0, 0);
    if (temp_r3 != NULL) {
        vt = (VT34EC *)((Unk_C8FEE62D *)temp_r3)->unk0x14;
        return ((s32 (*)(void *))vt->fn)((char *)temp_r3 + vt->off);
    }
    return 1;
}
