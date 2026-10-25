// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012154-0x80012170 (28B). Byte-identical.
#include "types.h"
#include "structs.h"
// CompactPool_Free @ 0x80012154
void CompactPool_Free(Unk_C8FEE62D *arg0, s32 *arg1) {
    arg0->unk0x10 = (s32) (arg0->unk0x10 - 1);
    *arg1 = arg0->unk0x14;
    arg0->unk0x14 = arg1;
}
