// WIP DRAFT (non-matching) — hand-written from retail disassembly + mwcc iteration.
// family=gxtev range=0x8028B408-0x8028B47C size=116B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Identity: GXSetTevColor(GXTevRegID id, GXColor color) — GXTev.o color trio #1.
// VERDICT: PARKED 34.5% (mwcc_verify: DIFF 19/29 words, size 116B exact).
// Same instruction SET as retail (29 insns); residual is the documented
// scheduler coin-flip of docs/parkings/19-gxtev-color-sched.md:
// retail loads color bytes a,r,b,g and defers li-0x61/lis-page/gx-load to
// pos 9-11; every source shape/pragma/compiler tried hoists g early.
// Further checks confirmed via single-file mwcc_verify harness:
// direct-field form (v1), data-temp form (v2, BEST, this body), regBG-first
// reorder (v3), single-expression fold (v5, loses an insn), addr-first (v9),
// #pragma scheduling off (worse), #pragma peephole off (neutral).
// Promotion needs mwcc + <dolphin/gx.h>/<dolphin/os.h>/<dolphin/gx/GX.h>/
// <dolphin/gx/GXInit.h> includes; no .data/.sdata2 sections in object.
//
// RE-VERIFIED 2026-10-02 (doc is current, not stale). Fresh checks, all
// agreeing with 19-gxtev-color-sched.md:
//  * The instruction OPCODE MULTISET is byte-for-byte the same as retail
//    (29/29, Counter equality) — so this is purely ordering, and the
//    semantics in this body are already correct. Only positions 0-19 differ;
//    positions 20-28 (the FIFO tail + `sth` + `blr`) already match exactly.
//  * Compiler sweep re-run: GC/1.2.5 and 1.2.5n both give 116B / 10-of-29,
//    opcode-set equal. 1.3 -> 128B, 1.3.2 -> 128B, 2.6 -> 124B (size
//    mismatch, as the doc records for 1.3+). No version yields retail's order.
//  * Four NEW source shapes tried this round, all C89-correct (extra locals
//    must go in the declaration block — mwcc rejects declarations after
//    statements, which is an easy trap when hand-writing variants):
//      bind all four bytes to locals in retail order a,r,b,g  -> 9/29
//      hoist only the `b` load so source mentions b before g    -> 6/29
//      compute regBG's address early (retail fills stb->stw)  -> 10/29 (tie)
//      both of the above combined                              -> 9/29
//    None beats this body. Making the SOURCE mention `b` before `g` — the
//    one thing that would in principle pin the load order — makes it
//    strictly worse, which is the same scheduler-robustness result the doc
//    reached with 630 interleavings and 40,320 permuter runs.
// => This body IS the best known form. The only remaining avenue is inline
// asm, which project policy rejects (and which is worse than a park: it
// fakes the match rather than reconstructing the code). Do not reopen.
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

void GXSetTevColor(GXTevRegID id, GXColor color) {
    u32 data;
    u32 regRA;
    u32 regBG;

    CHECK_GXBEGIN(740, "GXSetTevColor");

    data = color.a << 12;
    SET_REG_FIELD(745, data, 8, 0, color.r);
    regRA = (0xE0 + id * 2) << 24;
    SET_REG_FIELD(746, regRA, 20, 0, data);

    data = color.g << 12;
    SET_REG_FIELD(749, data, 8, 0, color.b);
    regBG = (0xE1 + id * 2) << 24;
    SET_REG_FIELD(750, regBG, 20, 0, data);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);

    gx->bpSentNot = 0;
}
