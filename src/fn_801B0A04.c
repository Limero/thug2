// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0A04-0x801B0ACC (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct CAT_t {
    char pad0x0[0x4];
    void *unk0x4;
    void *unk0x8;
    void *unk0xC;
    void *unk0x10;
    void *unk0x14;
    void *unk0x18;
    void *unk0x1C;
} CAT_t;

void fn_801B01C0(void *, s32);
void fn_801B05B8(void *, s32);
void Mem_Free(void *);

void fn_801B0A04(CAT_t *arg0, s32 arg1) {
    if (arg0->unk0x14 != 0) {
        fn_801B01C0(arg0->unk0x14, 3);
    }
    if (arg0->unk0x18 != 0) {
        fn_801B01C0(arg0->unk0x18, 3);
    }
    if (arg0->unk0x10 != 0) {
        fn_801B01C0(arg0->unk0x10, 3);
    }
    if (arg0->unk0x1C != 0) {
        fn_801B01C0(arg0->unk0x1C, 3);
    }
    if (arg0->unk0x8 != 0) {
        fn_801B05B8(arg0->unk0x8, 3);
    }
    if (arg0->unk0x4 != 0) {
        fn_801B05B8(arg0->unk0x4, 3);
    }
    if (arg0->unk0xC != 0) {
        fn_801B05B8(arg0->unk0xC, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
