// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CB28-0x8022CB58 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022CB28(Unk_950BD505 *arg0, void *arg1) {
    if ((void *) arg0->unk0x4 == NULL) {
        arg0->unk0x4 = arg1;
    } else {
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x8) + 0x1C) = arg1;
    }
    arg0->unk0x8 = arg1;
    arg0->unk0xC = (u16) (arg0->unk0xC + 1);
}
