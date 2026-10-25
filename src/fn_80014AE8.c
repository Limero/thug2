// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014AE8-0x80014B34 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_803CAF54[];

typedef struct {
    char pad0[0x10];
    s16 unk0x10;
    char pad1[2];
    s32 unk0x14;
} V14AE8;

typedef struct {
    char pad0[0x14];
    s32 unk0x14;
    char pad1[0x14];
    s32 unk0x2C;
    char pad2[0xC];
    V14AE8 *unk0x3C;
} O14AE8;

void fn_80014AE8(O14AE8 *arg0) {
    O14AE8 *g = *(O14AE8 **)lbl_803CAF54;
    V14AE8 *v = g->unk0x3C;

    ((void (*)(char *, s32, s32, O14AE8 *, s32))v->unk0x14)(
        (char *)g + v->unk0x10, g->unk0x14, 0, arg0, g->unk0x2C);
}
