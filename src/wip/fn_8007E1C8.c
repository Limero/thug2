// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly.
// family=m2c range=0x8007E1C8-0x8007E3E4 size=540B
// extra_cflags: -mps-float
//
// 0x8007E1C8 is a paired-single accumulator walk over a circular node list:
//   for each node the vcall fn_8005F28C (table slot 0x25) drops a 16-byte
//   position {ps a, ps b} into a stack temp; two ps accumulators are smoothed
//   toward it and written back to *out as two ps pairs.
// INERT: not registered in splits.txt/configure.py — never compiled.
//
// PARKED 2026-10-05: DIFF, object 512 B vs want 540 B, best masked
// score 5.2% (was 0.7%).  The BODY IS SEMANTICALLY EXACT (see the decode
// below); what is missing is ngccc's PS *spill shape*.
//
// ---- what want actually does (complete decode; all offsets from sp) ----
//
// frame 0xc8; saves f31 @0xc0, r29-r31 @0xb4, lr @0xcc.  arg0 -> r30 (out),
// arg1 -> r31.  NOTE: r31 is REUSED inside the loop as the constant `sp+8`
// (`addi r9,r1,8 ; mr r31,r9`), so 8(r31) = 0x10(sp) = accumulator #1.
//
//   if (arg1->s16_4A == 0) { out->f[3]=out->f[0]=out->f[1]=out->f[2]= 0.0f; return out; }
//   end = arg1->unk10;  it = end ? end->next : NULL;         // r11/r9 dance
//   st 0x48 = it                                          // `it` home
//   fn_8005F28C(sp+0x50, *(void **)it->f0);                 // seed temp 0x50/0x58
//   acc0 = [0x50];  acc1 = [0x58];                         // 0x8 / 0x10, psq_l+st
//   st 0x50 = end;  it = it->next;  if (it == end) goto out;   // `end` SHARES the
//                                                            // seed temp's slot
//   f31 = 0.5f;  r29 = &lbl_802960C0 /* {0.0f,0.0f} */;
//   do {
//       fn_8005F28C(sp+0x60, *(void **)it->f0);            // loop temp 0x60/0x68
//       P = [0x60];  Q = [0x68];
//       d0 = P - acc0;   d1 = Q - acc1;
//       len = ps_res(ps_rsqrte(ps_sum0(ps_madd(d0,d0,ps_merge00(d1*d1,{0,0})))));  // == [0x90]
//       if (len + Q.lo <= acc1.lo) continue;               // fcmpu+cror+bso  0x24 / 0x14
//       if (len + acc1.lo >  Q.lo) { acc0 = P; acc1 = Q; }// else-snap: 0x8 / 0x10
//       else {
//           t   = d1.lo / len;                             // lfs 0x44 ; fdivs ; st 0x98
//           s0  = acc0 + P;   s1 = acc1 + Q;              // 0x28 / 0x30
//           acc1 = muls0(s1 + muls0(d1,t), {.hi=0.5f});      // 0x5f*0.5 -> 0x10
//           acc0 = muls0(s0 + muls0(d0,t), {.hi=0.5f});      //          -> 0x8
//           acc1.lo = (len + s1.lo) * 0.5f;                // stfs 0x14  <-- the
//       }                                                  //   accumulator's own
//   } while ((it = it->next) != end);                       // low half is
//   out->p[1] = acc1;  out->p[0] = acc0;  return out;      // overwritten
//
// `.lo` = the SECOND word of the pair (`psq_l/st` with W=0 put the FPR's high
// word at d and the low at d+4, so `struct { f32 hi, lo; }` maps hi -> d).
// The `acc1.lo = (len + s1.lo) * 0.5f` overwrite is real want behaviour, not a
// decoding artefact: the `psq_st` of acc1 at 0x10 lands immediately before it.
//
// ---- the one change that was worth anything (0.7% -> 5.2%) ----
//
// Hoisting `0.5f` into a plain `f32 half` local initialised BEFORE the loop
// makes ngccc keep it in **f31** for the whole loop (`lfs f31,0x6110(r9)` in the
// pre-loop block, `fmuls f10,f10,f31` at the end) and therefore emit want's
// `stfd f31,0xc0(r1)` / `lfd f31,0xc0(r1)` epilogue.  Writing `lbl_80296110`
// inline instead re-materialises the constant inside the loop and the whole
// function loses its FPR save (frame 0xa0, no stfd).  The ps-pair copy
// `th.flt.hi = half` is still needed: want does `fmr f0,f31 ; stfs f0,0xa0`.
//
// ---- the remaining blocker ----
//
// want spills FOURTEEN ps pairs to the stack inside the loop (0x18, 0x20, 0x28,
// 0x30, 0x38, 0x40, 0x58, 0x60, 0x70, 0x78, 0x80, 0x88, 0x90, 0x98/0xa0) and
// needs 172 bytes of locals (frame 0xc8); this draft needs 136 (frame 0xa8) and
// keeps everything in FPRs.  In other words the ORIGINAL source has ~4 more
// simultaneously-live ps values at the peak of the loop body than this draft
// does, and reproducing that count (and hence the spill/reload pattern) is what
// the remaining ~95% of the words need.  Re-attack by *adding* named ps
// temporaries at the points want spills (each `psq_st` in want is a named
// source variable that GCC could not keep in an FPR), NOT by adding frame
// dummies: with 4 extra `volatile double _dummy` the frame would be right but
// every displacement in the body would still be wrong.
//
// Also unresolved: want keeps `arg1` in r31 and reuses r31 as `sp+8` inside the
// loop, this draft keeps arg1 in r4 and needs r27-r31 (one extra callee-saved
// GPR) - one more live value in the original.
#include "types.h"

typedef float sn_ps __attribute__((mode(PS)));

typedef union {
    sn_ps ps;
    struct {
        f32 hi, lo;
    } flt;
} U;

typedef struct {
    U a, b;
} V;

typedef union {
    sn_ps p[2];
    f32 f[4];
} Vec4;

typedef struct Nd {
    void *f0;
    struct Nd *next;
} Nd;

typedef struct Arg1 {
    char pad0x0[0x10];
    void *unk10;
    char pad0x14[0x36];
    s16 unk4A;
} Arg1;

extern f32 lbl_8029610C;   /* 0.0f */
extern f32 lbl_80296110;   /* 0.5f */
extern sn_ps lbl_802960C0; /* {0.0f, 0.0f} */
extern void fn_8005F28C(void *o, void *other);

Vec4 *fn_8007E1C8(Vec4 *out, Arg1 *arg1) {
    U acc0, acc1, p0, p1, s0, s1, d0, d1;
    Nd *it;
    V v0, v1;
    U q0, q1, q2, q3, q4, ts, th;
    volatile double _dummy;
    f32 half;
    Nd *end;

    if (arg1->unk4A == 0) {
        out->f[3] = lbl_8029610C;
        out->f[0] = lbl_8029610C;
        out->f[1] = lbl_8029610C;
        out->f[2] = lbl_8029610C;
        return out;
    }
    half = lbl_80296110;
    end = (Nd *)arg1->unk10;
    it = end ? end->next : (Nd *)0;
    fn_8005F28C(&v0, *(void **)it->f0);
    acc0.ps = v0.a.ps;
    acc1.ps = v0.b.ps;
    for (it = it->next; it != end; it = it->next) {
        fn_8005F28C(&v1, *(void **)it->f0);
        p0.ps = v1.a.ps;
        p1.ps = v1.b.ps;
        d0.ps = v1.a.ps - acc0.ps;
        d1.ps = v1.b.ps - acc1.ps;
        q4.ps = __builtin_ps_madd(d0.ps, d0.ps,
                                 __builtin_ps_merge00(d1.ps * d1.ps, lbl_802960C0));
        q4.ps = __builtin_ps_sum0(q4.ps, q4.ps, q4.ps);
        q4.ps = __builtin_ps_res(__builtin_ps_rsqrte(q4.ps));
        if (!(q4.flt.hi + p1.flt.lo <= acc1.flt.lo)) {
            if (!(q4.flt.hi + acc1.flt.lo <= p1.flt.lo)) {
                ts.flt.hi = d1.flt.lo / q4.flt.hi;
                th.flt.hi = half;
                s0.ps = acc0.ps + v1.a.ps;
                s1.ps = acc1.ps + v1.b.ps;
                q0.ps = __builtin_ps_muls0(d1.ps, ts.ps);
                q1.ps = __builtin_ps_muls0(d0.ps, ts.ps);
                q2.ps = s1.ps + q0.ps;
                q3.ps = s0.ps + q1.ps;
                acc1.ps = __builtin_ps_muls0(q2.ps, th.ps);
                acc0.ps = __builtin_ps_muls0(q3.ps, th.ps);
                acc1.flt.lo = (q4.flt.hi + s1.flt.lo) * half;
            } else {
                acc0.ps = v1.a.ps;
                acc1.ps = v1.b.ps;
            }
        }
    }
    out->p[0] = acc0.ps;
    out->p[1] = acc1.ps;
    return out;
}