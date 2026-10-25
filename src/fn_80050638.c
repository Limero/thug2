// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80050638-0x8005069C (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Vector / dynamic-array CONSTRUCTOR. arg0 = { +0x0 data*, +0x4 capacity, +0x8
// count }. Sets capacity = arg1, count = 0, then the payload is null (data* =
// NULL when arg1 == 0, else allocs arg1*4 bytes via Mem_Alloc and zeroes
// them). fn_8005069C is the RESERVE sibling. Keys that made it match (was a
// FAIL — m2c emitted corrupt `memset(0, size)`): (1) 3-arg memset with dst =
// the fresh alloc result; (2) memset size read from a RELOADED arg0[0x4]
// (not the precomputed arg1*4) so ngccc keeps arg1 only in caller-saved r4 and
// shrinks to a leader -0x10 frame; (3) volatile stores (arg0[4]=arg1,
// arg0[8]=0, arg0[0]=0) to fix the store order. Suggested rename:
// VectorAllocate / Fn_ArrayInitWithSize.
#include "types.h"
#include "structs.h"
#include "mem.h"
void memset(s32, s32, s32);
void *fn_80050638(CStruct *arg0, s32 arg1) {
    *((volatile s32 *)&arg0->unk0x4) = arg1;
    *((volatile s32 *)&arg0->unk0x8) = 0;
    *((volatile s32 *)&arg0->unk0x0) = 0;
    if (arg1 != 0) {
        arg0->unk0x0 = (s32)Mem_Alloc(arg1 * 4);
        memset(arg0->unk0x0, 0, arg0->unk0x4 * 4);
    }
    return arg0;
}