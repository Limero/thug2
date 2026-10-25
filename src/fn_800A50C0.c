// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A50C0-0x800A514C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A3D34(void *, s32);
void fn_800A50C0(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2) {
    Unk_DB0E2BAB *p;

    p = arg0->unk0x14;
    while (p != NULL) {
        p->unk0x14 = p->unk0x14 + 1;
        if (arg2 == 0 || p->unk0x0 == arg2) {
            fn_800A3D34(p, arg1);
        }
        p->unk0x14 = p->unk0x14 - 1;
        p = p->unk0xC;
    }
}
