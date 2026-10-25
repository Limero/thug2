// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E988-0x8005E9C8 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[0x28]; s16 unk0x28; char pad2[2]; s32 unk0x2C; } Disp5E9;
void fn_8005E988(Unk_C7387A53 *arg0, s32 arg1) {
    Disp5E9 *obj;
    arg0->unk0x28 = arg1;
    arg0->unk0x34 = 1;
    obj = (Disp5E9 *)arg0->unk0x4C;
    ((void (*)(void *))obj->unk0x2C)((char *)arg0 + obj->unk0x28);
}
