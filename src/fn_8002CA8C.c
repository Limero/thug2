// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002CA8C-0x8002CAE4 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 memset(s32, s32, s32);
void fn_8002CA8C(CScript *arg0) {
    memset((char *)arg0 + 4, 0, 0xF0);
    memset((char *)arg0 + 0xF4, 0, 0xF0);
    arg0->unk0x1E4 = (s32) ((arg0->unk0x1E4 & 0x1FFFF) | 0x10000);
}
