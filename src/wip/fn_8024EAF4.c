// WIP DRAFT (non-matching) — rebuilt from disasm (heap block-search alloc)
// RE-TRIAGED 2026-10-19: sweep still DIFF — frameless leaf, low %; wall stands. Parked as-is.
// family=m2c range=0x8024EAF4-0x8024EBD8 size=228B
//
// PARKED ~low % (structure semantically complete; frameless leaf, no calls).
// Blocker: want's entry homes BOTH params into scratch webs before any use
// ([mr r6,r3][mr r10,r4], lock load via the COPY r6) and keeps TWO aliases
// of *heap alive simultaneously (r7 store-alias via mr r7,r9, r8
// load-alias via later mr r8,r7) — every C shape tried coalesces them;
// decl copies, named-alias + \"+r\" barrier, hp/n temps all fold back.
// Same family wall as parked fn_8024EBD8 below it (register-role
// rotation / allocator context), plus flags (-fno-schedule-insns,
// -fno-gcse, -fno-expensive-optimizations, -fno-sched-spec) all no-op.
// Retry hint: a source shape producing the double base-alias without a
// barrier would likely crack this whole heap-allocator cluster.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *fn_8024EAF4(s32 **heap, s32 size) {
    u32 aligned = (size + 3) & QB_UNKNOWN_0xFFFFFFFC;
    u32 limit;
    u32 hi;
    u32 sv;
    u32 lw;
    s32 *cur;
    s32 idx = 0;

    if (((CStruct *)heap)->unk0x4 != 0) {
        return NULL;
    }
    cur = *heap;
    limit = aligned + 4;
    if (*cur == -1) {
        return NULL;
    }
    __asm__ volatile("" ::: "memory");
    hi = aligned + 12;
    sv = ((((u32)aligned + 7) >> 2) & 0xFFFFFF) | QB_UNKNOWN_0x01000000;
    lw = limit >> 2;
    for (;;) {
        s32 v = cur[idx];
        if (!(v & QB_UNKNOWN_0x01000000)) {
            u32 vsz = (v * 4) & QB_UNKNOWN_0x03FFFFFC;
            if (vsz >= limit) {
                if (vsz > hi) {
                    cur[idx] = (s32)sv;
                    *((s32 *)*heap + idx + lw) = (s32)((((vsz - limit + 3) >> 2) & 0xFFFFFF));
                } else {
                    cur[idx] = (s32)(((vsz >> 2) & 0xFFFFFF) | QB_UNKNOWN_0x01000000);
                }
                return (char *)*heap + (idx << 2) + 4;
            }
        }
        idx += cur[idx] & 0xFFFFFF;
        if (cur[idx] == -1) {
            break;
        }
    }
    return NULL;
}
