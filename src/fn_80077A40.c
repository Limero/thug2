// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077A40-0x80077A90 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[0x28]; s16 unk0x28; char pad2[2]; s32 unk0x2C; } Disp77A;
void fn_80077A40(CScript *arg0) {
    s8 sp8[4];
    Disp77A *obj;
    sp8[0] = -0x80;
    sp8[1] = -0x80;
    sp8[2] = -0x80;
    sp8[3] = -0x80;
    obj = (Disp77A *)arg0->unk0x18;
    ((void (*)(void *, void *))obj->unk0x2C)((char *)arg0 + obj->unk0x28, sp8);
}
