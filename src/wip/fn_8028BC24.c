// WIP DRAFT (non-matching) — hand-written from retail disassembly + mwcc iteration.
// family=gxpixel range=0x8028BC24-0x8028BD24 size=256B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Identity: GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable *table).
// VERDICT: PARKED 20.0% (mwcc_verify: DIFF 52/65 words, got 260B vs 256B).
// Confirms docs/parkings/20-gxpixel-fog-sched.md with sharper detail:
// - Retail is a FULLY UNROLLED 5-iteration loop (regs 0xE9..0xED) with ONE
//   materialized pointer bump fused into lhzu r10,4(r5) between iteration 1
//   and 2; later iterations use constant displacements off the bumped base.
// - mwcc 1.2.5n DOES fully unroll the array-index loop (this body) and even
//   performs the single-bump IV rematerialization (addi r5,r5,4), but never
//   fuses it into lhzu from any source shape tried: array-index loop,
//   u16-pointer walk, byte-pointer walk, lo-staged-first, hand-unrolled
//   *(p+=2) expression (that one also folds the reg-byte constants, losing
//   li r7,k entirely — the reg byte must come from the live loop IV).
// - Per-block merge forms confirmed: hi<<12 via slwi, lo via NEW-style
//   SET_REG_FIELD (rlwimi — plain `or` if old-form, since low 12 bits are
//   provably zero), reg byte via OLD mask+or form. Tail range_c built with
//   three OLD-style sets ((center+342)&0x3FF | enable<<10 | 0xE8000000).
// Promotion needs mwcc + dolphin gx/os includes; no .data/.sdata2 sections.
// 2026-10-10: re-verified 1.2.5n = DIFF 52/65 (20.0%); closed the 1.3.x gap:
// GC/1.3.2 keeps the loop rolled (136B, 5.9%) — dead like 2.7. NEW negatives
// (all sched-off unless noted): tail-split (stb-before-oris + early gx)
// fixes tail order but perturbs loop alloc globally (9.4%, worse); hi-first
// source (any form: swap/pointer-walk) KILLS lhzu fusion (260B, 3.1%) —
// fusion needs lo-first adjacency, incompatible with want order; combined
// `*(p+=2)` does NOT emit lhzu (expands to addi+lhz, zero update-loads);
// hand-unrolled x5 folds reg-li to lis (248B, 1.6%); peeled iter0 also
// 10.9%. Doc-20 park stands: sched-ON order + sched-OFF fusion incompatible.
// RE-TRIAGED 2026-10-19: test_wip_drafts reports FAIL (compile error — the
// sweep harness does not build the gxpixel/mwcc family; the 20.0% verdict
// above is from mwcc_verify under 1.2.5n). No source change; wall stands.
#include "types.h"
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>

#ifdef SET_REG_FIELD
#undef SET_REG_FIELD
#endif
#define SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size), 31 - (shift))); \
} while (0)

#ifndef OLD_SET_REG_FIELD
#define OLD_SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)); \
} while (0)
#endif

#ifndef CHECK_GXBEGIN
#define CHECK_GXBEGIN(line, name) ASSERTMSGLINE(line, !__GXinBegin, "'" name "' is not allowed between GXBegin/GXEnd")
#endif

#ifndef __GXinBegin
extern u8 __GXinBegin;
#endif

#ifndef GX_WRITE_RAS_REG
#define GX_WRITE_RAS_REG(value) \
do { \
    GX_WRITE_U8(0x61); \
    GX_WRITE_U32(value); \
} while (0)
#endif

void GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable *table) {
    u32 i;
    u32 range_adj;
    u32 range_c;

    CHECK_GXBEGIN(331, "GXSetFogRangeAdj");

    if (enable) {
        for (i = 0; i < 10; i += 2) {
            u32 lo = table->fogVals[i];
            range_adj = (u32)table->fogVals[i + 1] << 12;
            SET_REG_FIELD(338, range_adj, 12, 0, lo);
            OLD_SET_REG_FIELD(339, range_adj, 8, 24, (i >> 1) + 0xE9);
            GX_WRITE_RAS_REG(range_adj);
        }
    }

    range_c = 0;
    OLD_SET_REG_FIELD(345, range_c, 10, 0, center + 342);
    OLD_SET_REG_FIELD(346, range_c, 1, 10, enable);
    OLD_SET_REG_FIELD(347, range_c, 8, 24, 0xE8);
    GX_WRITE_RAS_REG(range_c);

    gx->bpSentNot = 0;
}
