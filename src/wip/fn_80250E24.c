// WIP DRAFT (non-matching) — hand-reconstructed bit-reader head.
// family=m2c range=0x80250E24-0x80250E6C size=72B
// FLAG: -O1
//
// Extracts arg1 bits starting at arg0->bit_pos from the 64-bit stream
// {word0, word1}: mask off the already-consumed low bits of word0, and when
// the request crosses the word boundary (t = arg1 - 32 + bit_pos > 0) splice
// in the top bits of word1, else shift the remainder down.  The two tails are
// separate basic blocks ending in their own `blr`.
//
// PARKED 2026-10-24: 15/18 words at -O1 (18/18 at -O2 is 10/18: -O2 hoists the
// three loads above the `addi` that forms t, so every position after it
// shifts).  -O1 keeps want's head order exactly (addi t, lwz bit_pos,
// li -1 mask, lwz word0) and reproduces both tails, including the `add.` that
// feeds `ble`; the three remaining words are the ORDER of
// {add. r7,r7,r5 / srw r8,r8,r5 / and r6,r6,r8} - want runs add. first, this
// build sinks add. to just before the `ble` it sets cr0 for.  Source order of
// those three statements (all 6 permutations), -O1 combined with
// -fno-schedule-insns[2] / -fno-delayed-branch / -fno-expensive-optimizations /
// -fno-peephole / -fno-gcse / -fno-cse-follow-jumps / -fno-thread-jumps /
// -fno-optimize-register-move / -fno-inline / -fno-defer-pop / -fno-force-mem /
// -fno-function-cse all stay at 15/18; the add. placement is the
// record-setting add being scheduled against its own branch.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
register s32 rn __asm__("r5");
register u32 rlo __asm__("r6");
register u32 rm __asm__("r8");
register s32 rk __asm__("r9");
register s32 rh __asm__("r9");

u32 fn_80250E24(CStruct *arg0, s32 arg1) {
    register s32 t __asm__("r7");

    t = arg1 - 0x20;
    rn = arg0->unk0x8;
    rm = QB_UINT32_MAX;
    rlo = *((u32 *)&arg0->unk0x0);
    rlo &= rm;
    t += rn;
    rm >>= rn;
    if (t <= 0) {
        rk = 0x20 - rn;
        rk -= arg1;
        return rlo >> rk;
    }
    {
        u32 hi = *((u32 *)&arg0->unk0x4);
        rlo <<= t;
        rh = 0x20 - t;
        return ((hi >> rh) | rlo);
    }
}
