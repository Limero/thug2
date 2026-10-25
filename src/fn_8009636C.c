// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009636C-0x800963D0 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u8 pad0[4];
    u16 unk4;
    u8 pad1[2];
    s32 unk8;
    u8 pad2[4];
    s32 unk10;
    void *unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1a;
    u8 unk1b;
} Unk_9636C;

s32 fn_800145AC(void);

Unk_9636C *fn_8009636C(Unk_9636C *arg0) {
    void *unk14_init = 0;
    arg0->unk4 = 2;
    arg0->unk8 = 0xFF;
    arg0->unk14 = unk14_init;
    arg0->unk18 = 0x80;
    arg0->unk19 = 0x80;
    arg0->unk1a = 0x80;
    arg0->unk1b = 0x80;
    arg0->unk10 = fn_800145AC() | 0x80000000;
    return arg0;
}
