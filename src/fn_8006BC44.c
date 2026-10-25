// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006BC44-0x8006BC80 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Queue struct INIT (larger sibling of fn_8006BC80 which only clears +0/+4).
// Same bounded byte-queue layout (see fn_8006BC90 enqueue / fn_8006BCDC
// dequeue): +0x0 running count, +0x4 chunk size, +0x8 0x4000-byte payload.
// Resets count & size to 0 and memsets the 0x4000-byte payload buffer to 0x3.
// m2c corrupted this into a 4-arg memset FAIL; the real call is 3-arg
// memset(payload_+8, 3, 0x4000). Two levers got it to 100% (was a FAIL, then
// 53%): (1) s32* array form keeps arg0 in caller-saved r9 with a tiny -8
// frame (char/void* forms make ngccc preserve it in r30+stmw); (2) volatile
// stores force the +4-before-+0 write order (ngccc otherwise canonicalizes to
// +0 first). Suggested rename: QueueInit / QueueConstruct.
#include "types.h"
void memset(s32, s32, s32);
void fn_8006BC44(s32 *arg0) {
    *(volatile s32 *)&arg0[1] = 0;
    *(volatile s32 *)&arg0[0] = 0;
    memset((s32)((s32 *)arg0 + 2), 3, 0x4000);
}