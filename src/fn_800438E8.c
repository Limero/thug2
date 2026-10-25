// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800438E8-0x800439B0 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_80058F00(s32);
void Mem_Free(void *);

void fn_800438E8(Unk_E80761A5 *arg0, s32 arg1) {
    s32 i;
    s32 off;

    if (arg0->unk0x1A0 != 0) {
        i = 0;
        if (i < arg0->unk0x1A4) {
            off = 0;
            do {
                i = i + 1;
                fn_80058F00(*(s32 *)((char *)(off + (s32)arg0->unk0x1A0)));
                off = off + 4;
            } while (i < arg0->unk0x1A4);
        }
        Mem_Free((void *)arg0->unk0x1A0);
        arg0->unk0x1A0 = 0;
    }
    if (arg1 == 0) {
        i = 0;
        if (i < arg0->unk0x1A4) {
            off = 0;
            do {
                i = i + 1;
                fn_80058F00(*(s32 *)((char *)(off + (s32)arg0->unk0x19C)));
                off = off + 4;
            } while (i < arg0->unk0x1A4);
        }
        Mem_Free((void *)arg0->unk0x19C);
        arg0->unk0x1A4 = 0;
    }
}
