// WIP DRAFT (non-matching) — hand-written from disasm 2026-09-24
// family=m2c range=0x80105C74-0x80105CE8 size=116B
// FLAG: -mps-float -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// PARKED 2026-09-24 at 51.7% (15/29 words, SIZE-EXACT 116B).  Semantics
// fully recovered: build a 4-float stack temp v[4] = {A,A,A,B}
// (A=lbl_8029CA34, B=lbl_8029CA38), copy it as two __ps_t pairs to
// dst[0]/dst[1] of the object in arg0, then v = {C,C,C,B} (C=lbl_8029CA3C)
// and copy as pairs to dst[3]/dst[2] (note the SWAPPED 3/2 order), and zero
// the three words at arg0+0xfc0/0xfc4/0xfc8 (which interleave between the
// pair ops).  B is re-assigned to v[3] before EACH pair block (want keeps
// both stores of the same value), and B is loaded through a named temp
// (`bb = lbl_B;`) BEFORE the A stores — that is what gives want's FPR
// colouring (A->f0, B->f13) instead of the swapped assignment.
//
// Residual (3 independent scheduler artifacts, 14 words):
//   1. A-run store order: want stfs 0x10, 8, 0xc ; got 0xc, 8, 0x10.
//      Permuting the source statements does NOT move it (all 6 orders of
//      the three `v[i] = A;` statements scored identically) — ngccc picks
//      the rotation itself.
//   2. Second pair load: want `psq_l f0,16(r1)` (reuses f0 after A dies);
//      got uses f13/f12 for it because the C load is scheduled before the
//      pair store.  Adding a memory barrier to serialize it costs more
//      than it wins (34.5%).
//   3. The three `stw r0,0xfcX` placement: want 0xfc8,0xfc0 / dst[3] /
//      0xfc4 / dst[2]; got sinks them in a different interleave. Source
//      order permutations of those three stores plateau at 51.7%.
// TRIED: source-order permutations of the A run (4), of the stw group (6),
// stw block before/around/after the pair stores, C staged through a named
// local, `__ps_t *dst` vs direct `((__ps_t *)arg0)[i]`, `-fno-schedule-insns`
// memories.  See AGENTS.md recipe 24/64/274 (store-rotation family).
#include "types.h"

extern f32 lbl_8029CA34;
extern f32 lbl_8029CA38;
extern f32 lbl_8029CA3C;

void fn_80105C74(char *arg0) {
    f32 v[4];
    f32 bb;
    __ps_t *dst;
    dst = (__ps_t *)arg0;
    bb = lbl_8029CA38;
    v[2] = lbl_8029CA34;
    v[0] = lbl_8029CA34;
    v[1] = lbl_8029CA34;
    v[3] = bb;
    dst[0] = ((__ps_t *)v)[0];
    dst[1] = ((__ps_t *)v)[1];
    v[3] = bb;
    v[0] = lbl_8029CA3C;
    v[1] = lbl_8029CA3C;
    v[2] = lbl_8029CA3C;
    dst[3] = ((__ps_t *)v)[1];
    *(s32 *)((char *)arg0 + 0xfc0) = 0;
    *(s32 *)((char *)arg0 + 0xfc8) = 0;
    *(s32 *)((char *)arg0 + 0xfc4) = 0;
    dst[2] = ((__ps_t *)v)[0];
}
