// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80047D7C-0x80047DFC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800624AC(CStruct *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_80047D7C(void *arg0) {
    char *base;
    char *it;
    s32 i;
    s32 mask;
    s32 elem;

    base = arg0;
    mask = 1 << ((Unk_6BF005A1 *)base)->unk0x578;
    i = 0;
    if (i < ((Unk_6BF005A1 *)base)->unk0x4B0) {
        it = base + (s32)0x190;
        do {
            elem = *(s32 *)it;
            if (elem != 0) {
                fn_800624AC(*(s32 *)((char *)GetChecksum_3(elem, QB_MODEL) + (s32)0x210), mask);
            }
            i++;
            it += 0x20;
        } while (i < ((Unk_6BF005A1 *)base)->unk0x4B0);
    }
}
