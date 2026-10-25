// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3754-0x800F3794 (64B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_800F3754(Unk_C7387A53 *arg0) {
    void *node = *((void * *)&arg0->unk0x50);
    s32 off = ((Unk_0E2E8431 *)node)->unk0x70;
    void (*fn)(void *, s32, s32) = (void (*)(void *, s32, s32))*((void * *)&((Unk_0E2E8431 *)node)->unk0x74);
    fn((char *)arg0 + off, arg0->unk0x24, arg0->unk0x28);
}
