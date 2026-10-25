// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013725C-0x801372B8 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 memset(s32, s32, s32);
void *fn_8013725C(Unk_1624B368 *arg0) {
    arg0->unk0xC04 = 0;
    arg0->unk0x1408 = 0;
    arg0->unk0x140C = 0;
    memset((char *)arg0 + 0xC08, 0, 0x400);
    memset((char *)arg0 + 0x1008, 0, 0x400);
    return arg0;
}
