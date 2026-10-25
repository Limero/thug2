// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192C68-0x80192C8C (36B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80192C68(Unk_C7387A53 *arg0) {
    if ((arg0->unk0x70 & 0x80000) == 0) {
        return arg0->unk0x54 <= 0;
    }
    return 0;
}
