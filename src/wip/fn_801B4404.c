// WIP DRAFT (non-matching) — hand-structured reconstruction .
// family=m2c range=0x801B4404-0x801B4664 size=608B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// FLAG: -mps-float
//
// STRUCTURE RECOVERED FROM WANT (leaf, frame 0x70, no LR save, 152 insns):
//   * two pool constants: f8 = *(f32*)0x802AC060 (1.0f), f13 = *(f32*)0x802AC064
//     (0.0f).  f13 is also the threshold of `fcmpu f12,f13; ble` where
//     f12 = arg1[2], i.e. `if (arg1[2] > 0.0f)`.
//   * an 8-pair (4x4, 16-float) block at r1+0x08 built from {one,zero,x,z}
//     (x = arg1[0], z = arg1[2]); the final value of each pair is unambiguous
//     from the last write to each slot.  The three trailing groups are plain
//     copies of that block:
//       arg0->unk0C + 0xD0  <- { result, m[1..7] }   (8 pairs, result replaces m[0])
//       arg0->unk0C + 0x78  <- m[0..7]
//       (char*)arg0 + 0x148 <- m[0..7]
//     Each is emitted fully unrolled as psq_l m[k] / psq_st dest[k].
//
// BLOCKER (why this is parked): the ~34 op-4 (paired-single) words between
// `psq_l f12,0(lbl_802ABFB8)` and the first copy group are the actual transform
// math, and the available tooling cannot decode them: tools/disasm.py (capstone,
// no PS support) prints them as bare `.word # op4` with no register operands, so
// the FRT/FRA/FRB/FRC fields are unrecoverable in this (terminal-less) slice.
// The scalar/matrix build above and the three copy-outs below are exact C, but
// the PS compute phase is a plausible idiom only.  A faithful redraft needs
// `tools/ps_disasm.py` to decode the 34 op-4 words, and it needs `-mps-float`
// plus a working `__ps_t` allocator (this is the known PS-regalloc wall).
#include "types.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSV;

typedef struct {
    char pad0[0xC];
    void *unk0C;
} Obj;

extern f32 lbl_802AC060;    /* pool constant 1.0f  (want lfs -0x3fa0(lis 0x802B)) */
extern f32 lbl_802AC064;    /* pool constant 0.0f  (want lfs -0x3f9c(lis 0x802B)) */
extern __ps_t lbl_802ABFB8; /* rodata PS pair loaded at 0x801B448C */

void fn_801B4404(Obj *arg0, f32 *arg1) {
    PSV m[8];               /* r1+0x08 : the 4x4 transform, 8 pairs */
    PSV t[4];               /* r1+0x48 : PS scratch pairs */
    __ps_t result;          /* f9 : written to arg0->unk0C + 0xD0 */
    f32 one;
    f32 zero;
    f32 x;
    f32 z;
    void *p;

    one = lbl_802AC060;
    zero = lbl_802AC064;
    x = arg1[0];
    z = arg1[2];

    /* Build the block, statements in want's store order (ascending source order
       does NOT reproduce the interleave; this order is read off the WANT). */
    m[0].flt.lo = zero;
    m[0].flt.hi = one;
    m[1].flt.hi = zero;
    m[4].flt.hi = x;
    m[4].flt.lo = zero;
    m[5].flt.hi = one;
    m[5].flt.lo = zero;
    m[1].flt.lo = zero;
    m[2].flt.hi = zero;
    m[2].flt.lo = one;
    m[3].flt.hi = zero;
    m[3].flt.lo = zero;
    m[6].flt.hi = zero;
    m[6].flt.lo = zero;
    m[7].flt.hi = zero;
    m[7].flt.lo = one;
    m[5].flt.hi = z;
    m[5].flt.lo = one;
    m[4].flt.lo = zero;

    /* PS compute phase — APPROXIMATE (see BLOCKER above).  Want sequence:
       psq_l m[5] ; psq_l lbl_802ABFB8 ; <op4> ; psq_l m[4] ; <op4 x4> ;
       fcmpu z,0 ; ble skip ; <op4 x2, psq_st 0x58/0x48/0x50, fmr, stfs> ;
       <op4 x30> ; three unrolled copy groups. */
    t[0].ps = __builtin_ps_mul(m[5].ps, lbl_802ABFB8);
    t[1].ps = __builtin_ps_merge00(t[0].ps, m[5].ps);
    t[2].ps = __builtin_ps_sum0(t[1].ps, t[1].ps, t[1].ps);
    t[3].ps = t[2].ps;
    if (z > zero) {
        t[2].ps = __builtin_ps_sub(t[3].ps, t[3].ps);
        t[3].ps = t[2].ps;
        t[2].ps = __builtin_ps_merge00(t[3].ps, t[3].ps);
    }
    result = t[2].ps;
    result = __builtin_ps_madd(result, m[4].ps, t[1].ps);

    /* Three unrolled copies of the working block. */
    p = arg0->unk0C;
    ((__ps_t *)p)[26] = result;
    ((__ps_t *)p)[27] = m[1].ps;
    ((__ps_t *)p)[28] = m[2].ps;
    ((__ps_t *)p)[29] = m[3].ps;
    ((__ps_t *)p)[30] = m[4].ps;
    ((__ps_t *)p)[31] = m[5].ps;
    ((__ps_t *)p)[32] = m[6].ps;
    ((__ps_t *)p)[33] = m[7].ps;

    p = arg0->unk0C;
    ((__ps_t *)p)[15] = m[0].ps;
    ((__ps_t *)p)[16] = m[1].ps;
    ((__ps_t *)p)[17] = m[2].ps;
    ((__ps_t *)p)[18] = m[3].ps;
    ((__ps_t *)p)[19] = m[4].ps;
    ((__ps_t *)p)[20] = m[5].ps;
    ((__ps_t *)p)[21] = m[6].ps;
    ((__ps_t *)p)[22] = m[7].ps;

    ((__ps_t *)((char *)arg0 + 0x148))[0] = m[0].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[1] = m[1].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[2] = m[2].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[3] = m[3].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[4] = m[4].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[5] = m[5].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[6] = m[6].ps;
    ((__ps_t *)((char *)arg0 + 0x148))[7] = m[7].ps;
}

// NOTE: retained facts that a redraft should preserve — arg0 is an object whose
// +0xC pointer field receives the transform; arg1 is a float vec3 read at +0
// (x) and +8 (z); the two pool constants are 1.0f @0x802AC060 and 0.0f
// @0x802AC064; the 4x4 build and the three unrolled copy groups (dest offsets
// 0xD0/0x78 on arg0->unk0C and 0x148 on arg0) are exact.  The PC/original
// first 4 instructions (li r0,4 / mtctr / addi r7 / addi r8 / bdnz-self) are an
// empty 4-iteration CTR loop the source almost certainly had (a dead 4x
// unrolled clear) — not expressible as matching C.
// PARKED 2026-10-06: PS compute phase (34 op-4 words) is undecodable with
// capstone (no register operands) and the PS register allocator is the known
// wall.  Best structured body above; WANT vs GOT will differ in the PS block
// and therefore in register/stack colouring.  Redraft with tools/ps_disasm.py.
