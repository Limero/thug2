// === PARKED 2026-10-01 === 53.8% (37/80 words), object .text = 320B
// == want (symbols.txt size:0x140) == header marker.
// family=m2c range=0x800A85A0-0x800A86E0 size=320B
// FLAG: -mps-float -fno-expensive-optimizations
// INERT: not registered in splits.txt/configure.py - never compiled, not
// counted in objdiff progress.  activate via tools/wip.py.
//
// SIGNATURE: fn_800A9298 (0x800A9298) only reads its r3 argument (mr r31,r3 in
// its prologue) => the call here is a ONE-ARG call and r3 is never reloaded, so
// `fn_800A9298(arg0)`.  Declared (not left implicit) => no spurious crclr.
//
// SEMANTICS (hand-decoded with tools/ps_diff.py's dec(); the six paired-single
// pairs are all PS ops on the same object, offsets are its own):
//   dA=v10-v78  dB=v08-v70  dC=v78-v88  -dF=v70-v80  dF=v80-v70  dE=v88-v78
//   dot_i = sum0( merge00( x*x, lbl_802981C0 ) + y*y )      (three times)
//   r1 = res(rsqrte(dot1)) ; r2 = res(rsqrte(dot2))
//   f_b0 = r1 ; f_b0 = r1 + f_b8 ; f_b8 = lbl_802981F4 ; fac = r2
//   out[4]=dF out[5]=dE ; if (dot3 > lbl_802981F4) {
//        out[4]=muls0(dF,r3) ; rr={r3,lbl_802981F8} ; out[5]=dE*rr }
//   fn_800A9298(this); return 1;
// i.e. three 2-D normalise+reciprocal-length passes over the point pairs
// (v08,v10)-(v70,v78), (v70,v78)-(v80,v88), (v80,v88)-(v70,v78).
//
// WHAT IS ALREADY EXACT (measured, do not undo):
//  * object .text = 320B == symbols.txt size:0x140; every displacement matches
//    (frame 0x50, Gsave 0x50, LR 0x54, the nine locals at sp+0x08..0x48 in the
//    right order, out base = arg0+0x20 in r10 via the asm-output wedge, and the
//    struct offsets fac=0xAC f_b0=0xB0 f_b8=0xB8);
//  * the OPCODE SEQUENCE is want's, instruction for instruction (80/80), with
//    one exception: want has TWO register copies (`fmr f9,f0` @0x78 and
//    `fmr f0,f13` @0xc4) that no C spelling reproduced - see RESIDUAL (A);
//    got puts a second `lfs` from the same slot in place of the 2nd copy so the
//    word count stays 80 (that is the duplicated `vo->fac = q2.f;` below);
//  * all six dead volatile stores (sp+0x08..0x28) and the dead `stfs` at
//    sp+0x4C are reproduced - they are NOT spills, they are what ProDG emits
//    for writes to volatile locals that are never read (the same mechanism
//    gives fn_800A86E0 its 15 dead stores);
//  * three separate `lbl_802981C0` loads: only a *volatile* read of the symbol
//    gives three loads (a plain read CSEs to one);
//  * -fno-expensive-optimizations is worth +8.8 points on its own (45.0 ->
//    53.8 together with the fr11/fr6 pins); -fno-schedule-insns2 (what the
//    parked sibling fn_800A9200 needed) is WORSE here (35.0%), and so is every
//    other scheduling / gcse / peephole flag measured (all 45.0% or below).
//
// RESIDUAL (37 of 80 words):
//  (A) THE TWO `fmr`s - the single biggest item (16 words: the copies plus the
//      1-word shift they cause through the rest of the body).  want:
//        0x70 lfs f0,0x38(r1) | 0x78 fmr f9,f0 | 0x7c stfs f9,0xb0(r3)
//        0xbc lfs f13,0x40(r1)| 0xc4 fmr f0,f13| 0xc8 stfs f0,0xac(r3)
//      A copy of an f32 read out of a union appears ONLY when the union is
//      NON-volatile (probe: `PSU u; u.ps = x; if (u.flt.lo > v3) v1 = u.flt.lo;`
//      -> `lfs 13,12(1); fmr 0,13`, because GCC then has both a MEM and a
//      register form and picks the MEM + a reload copy).  But ProDG gives
//      every `volatile` local its frame slot first, in declaration order, and
//      non-volatile ones only afterwards, so non-volatile q1/q2 land at
//      sp+0x40/0x48 instead of 0x38/0x40 (measured: 11.25%).  Making all three
//      of q1/q2/rr non-volatile DOES give the right slots (0x38/0x40/0x48) but
//      then rr's `psq_st` lands at sp+0x50 and the frame grows to 0x58 with
//      three extra r0/r12 spills (measured 19%, 336B).  Dead end for now.
//  (B) GPR allocation of the two constant addresses: want r9 = &lbl_802981C0
//      and r11 = &lbl_802981F4, got has them swapped; not movable by source
//      order (measured both orders of the two `lfs`-feeding statements) or by
//      the asm-wedge position.
//  (C) `dF` needs fr4: `register __ps_t dF __asm__("fr4")` makes the ps_sub
//      write fr3 and insert `ps_mr f4,f3` (1 extra word, 5 diffs); unpinning
//      dF loses 4 words of code altogether (312B, 24%).
//  (D) the s6 reload / dE web wants `ps_mr f12,f0` + `ps_mul f0,f12,f12`;
//      got reuses the load register for both.  Pinning dA to fr12 was tried
//      (j1) - no change.
//
// NOT TRIED: forcing the (A) copies with an explicit second named f32
// (`f32 y; y = q1.f; s = y;`) - GCC coalesces it away every time (measured,
// 4 spellings incl. comma-expressions and a `"+f"` barrier); reordering the
// volatile locals so that a *different* pair of scalars occupies sp+0x38/0x40;
// and whether the copies come from ProDG's `reload` pseudos being visible in
// `cc1 -dr` (the post-reload RTL of this body still matches want's shape).
#include "types.h"

typedef union {
    __ps_t ps;
    f32 f;
} PSF;

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU;

typedef struct {
    char pad0x00[0x08];
    __ps_t v08;
    __ps_t v10;
    char pad0x18[0x58];
    __ps_t v70;
    __ps_t v78;
    __ps_t v80;
    __ps_t v88;
    char pad0x90[0x1C];
    f32 fac;
    f32 f_b0;
    char pad0xB4[0x04];
    f32 f_b8;
} OBJ;

extern __ps_t lbl_802981C0;
// A *volatile* read is what makes cc1 emit three separate psq_l of the zero
// constant (one per ps_merge00); a plain read is CSE'd to a single load.
#define ZC (*(volatile __ps_t *)&lbl_802981C0)
extern f32 lbl_802981F4;
extern f32 lbl_802981F8;

s32 fn_800A9298(void *);

s32 fn_800A85A0(OBJ *arg0) {
    volatile OBJ *vo = arg0;
    register __ps_t v78 __asm__("fr8");
    __ps_t dA;
    register __ps_t v70 __asm__("fr13");
    register __ps_t dB __asm__("fr12");
    register __ps_t v88 __asm__("fr10");
    register __ps_t v80 __asm__("fr7");
    register __ps_t dF __asm__("fr4");
    __ps_t d4;
    __ps_t d5;
    __ps_t nd;
    // The six stores at sp+0x08..0x30 are dead in want; volatile locals are
    // what make ProDG emit them (see header RESIDUAL note on dead stores).
    volatile __ps_t s1;
    volatile __ps_t s2;
    volatile __ps_t s3;
    volatile __ps_t s4;
    volatile __ps_t s5;
    volatile __ps_t s6;
    // sp+0x38 / sp+0x40: `volatile` is required for the psq_st + lfs round
    // trip AND to land on these two slots (see header RESIDUAL (A)).
    volatile PSF q1;
    volatile PSF q2;
    f32 s;
    register __ps_t t __asm__("fr0");
    register __ps_t zc __asm__("fr11");
    register f32 b8 __asm__("fr6");
    volatile PSU rr;
    register __ps_t *out __asm__("r10");

    v78 = vo->v78;
    dA = vo->v10;
    zc = ZC;
    v70 = vo->v70;

    s2 = __builtin_ps_sub(dA, v78);
    t = __builtin_ps_mul(dA, dA);
    dB = vo->v08;
    t = __builtin_ps_merge00(t, zc);
    v88 = vo->v88;
    dB = __builtin_ps_sub(dB, v70);
    v80 = vo->v80;
    t = __builtin_ps_madd(dB, dB, t);
    b8 = vo->f_b8;
    s1 = dB;
    t = __builtin_ps_sum0(t, t, t);
    t = __builtin_ps_res(__builtin_ps_rsqrte(t));
    q1.ps = t;

    // asm-output wedge: keeps the out base in r10 instead of folding +0x20
    // into the psq_st displacements.
    __asm__("" : "=r"(out) : "r"((char *)arg0 + 0x20));
    dF = __builtin_ps_sub(v80, v70);
    s = q1.f;
    nd = __builtin_ps_sub(v70, v80);
    vo->f_b0 = s;
    d4 = __builtin_ps_sub(v78, v88);
    s4 = d4;
    t = __builtin_ps_mul(d4, d4);
    zc = ZC;
    s = s + b8;
    vo->f_b8 = lbl_802981F4;
    d5 = __builtin_ps_sub(v88, v78);
    s3 = nd;
    t = __builtin_ps_merge00(t, zc);
    nd = __builtin_ps_madd(nd, nd, t);
    s5 = dF;
    nd = __builtin_ps_sum0(nd, nd, nd);
    nd = __builtin_ps_res(__builtin_ps_rsqrte(nd));
    q2.ps = nd;
    vo->f_b0 = s;
    // The second read is a stand-in for want's `fmr f0,f13` at 0xc4 - see
    // header RESIDUAL (A).  Same value, same address, so it is a no-op.
    vo->fac = q2.f;
    vo->fac = q2.f;

    s6 = d5;
    out[4] = dF;
    dA = s6;
    out[5] = dA;
    t = __builtin_ps_mul(dA, dA);
    t = __builtin_ps_merge00(t, ZC);
    t = __builtin_ps_madd(dF, dF, t);
    t = __builtin_ps_sum0(t, t, t);
    {
        PSU dot;
        register __ps_t r0 __asm__("fr13");
        r0 = t;
        dot.ps = r0;
        if (dot.flt.hi > lbl_802981F4) {
            register __ps_t r13 __asm__("fr13");
            register __ps_t res __asm__("fr0");
            r13 = __builtin_ps_rsqrte(r0);
            out[4] = __builtin_ps_muls0(dF, r13);
            rr.ps = r13;
            rr.flt.lo = lbl_802981F8;
            res = __builtin_ps_mul(dA, rr.ps);
            out[5] = res;
        }
    }
    fn_800A9298(arg0);
    return 1;
}
