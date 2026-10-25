// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145008-0x80145058 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_80145008(Unk_FFAD6788 *arg0) {
    if ((s32) arg0->unk0xC8 == 0) {
        GetChecksum_3(arg0, QB_SKATERNONLOCALNETLOGIC);
        fn_801C6AF0();
    }
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x2A8) + 0x1C) = 0;
}