// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CFC8-0x8000D028 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8000CFC8(Unk_C8FEE62D *arg0, s32 arg1) {
    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0x8) != 0) {
        Mem_Free(*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0x8));
    }
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0x8) = 0;
    if (arg1 != 0) {
        arg0->unk0x14 = (s32) (arg0->unk0x14 - 1);
    }
}
