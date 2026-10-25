// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E948-0x8005E988 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[0x28]; s16 unk0x28; char pad2[2]; s32 unk0x2C; } DispE;
typedef struct {
    char pad0[0x24];
    f32 unk0x24;
    char pad1[0xC];
    s32 unk0x34;
    char pad2[0x14];
    void *unk0x4C;
} O5E948;
void fn_8005E948(O5E948 *arg0, f32 farg0) {
    DispE *obj;
    arg0->unk0x24 = farg0;
    arg0->unk0x34 = 0;
    obj = (DispE *)arg0->unk0x4C;
    ((void (*)(void *))obj->unk0x2C)((char *)arg0 + obj->unk0x28);
}
