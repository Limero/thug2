// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058D80-0x80058DC0 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0[0x28];
    s16 unk0x28;
    char pad1[2];
    s32 unk0x2C;
} V58D80;

typedef struct {
    char pad0[0x28];
    f32 unk0x28;
    char pad1[0x18];
    s32 unk0x44;
    char pad2[8];
    V58D80 *unk0x50;
} O58D80;

void fn_80058D80(O58D80 *arg0, f32 farg0) {
    V58D80 *v;

    arg0->unk0x28 = farg0;
    arg0->unk0x44 = 0;
    v = arg0->unk0x50;
    ((void (*)(char *))v->unk0x2C)((char *)arg0 + v->unk0x28);
}
