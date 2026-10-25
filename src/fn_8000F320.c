// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000F320-0x8000F35C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Suggested rename: StackTopPop. Pops the top of a per-object fixed stack:
// decrements self->0x110 count, clears the popped slot self+0xd0[count] to -1,
// then rebuilds self->0xcc (stack top) as `count ? self+count*4+0xcc : 0`.
// MATCHED 2026-08-31 (was ~1/15): doc-49 named-pointer stwx lever + count
// pinned to r9 + unsigned `((unsigned)count<<2)` tail spelling (binds the
// scaled term to add's rA, matching want's `add r9,r9,r3`; signed `count*4`
// ranks self to rB = `add r9,r3,r9`, one commutative-add rank off).
#include "types.h"
#include "structs.h"
void fn_8000F320(Unk_F12C5E01 *self) {
    register s32 count __asm__("r9");
    s32 *stack;
    count = self->unk0x110;
    count--;
    self->unk0x110 = count;
    stack = (s32 *)((char *)self + 0xd0);
    stack[count] = -1;
    count = self->unk0x110;
    if (count != 0)
        count = (s32)((s32)((unsigned)count << 2) + (s32)self + 0xcc);
    self->unk0xCC = count;
}