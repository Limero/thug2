// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058DC0-0x80058E00 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[0x28]; s16 unk0x28; char pad2[2]; s32 unk0x2C; } DispC;
void fn_80058DC0(Unk_C7387A53 *arg0, s32 arg1) {
    DispC *obj;
    arg0->unk0x30 = arg1;
    arg0->unk0x44 = 1;
    obj = (DispC *)arg0->unk0x50;
    ((void (*)(void *))obj->unk0x2C)((char *)arg0 + obj->unk0x28);
}
