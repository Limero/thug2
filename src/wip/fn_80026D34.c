// PARKED 2026-09-26: full hand reconstruction of the spline evaluator (was an
// m2c husk at 1.9%).  Now instruction-for-instruction ISOMORPHIC to the retail
// body -- 626/635 positions have the SAME mnemonic and operand SHAPE; the
// masked score is 5.5% purely because GCC's global register allocation numbers
// every pseudo differently (and 9 instructions are still missing, see below).
// family=m2c range=0x80026D34-0x80027720 size=2540B
// FLAG: -mps-float
//
// WHAT THE FUNCTION IS (fully recovered from the DOL, 0x80026D34..0x80027720):
//   Per-frame evaluation of a two-track keyframe spline, 4 iterations worst case.
//     arg0 : track object   +0x08 = key count, +0x10 = track-A knot array,
//                          +0x14 = track-B knot array, +0x18 = selector id
//     arg1 : out V4 array   (one 16-byte {x,y,z,w} written per iteration)
//     arg2 : out V4 array   (advanced by 0x10 per iteration)
//     farg0: 0..1 position, scaled by lbl_802915F0 (60.0f) into `tgt`
//   Per iteration:
//     n1 = fn_80026A84(obj, sel, i)   track-A knot count
//     n2 = fn_80026AA8(obj, sel, i)   track-B knot count
//     search track A for the sub-interval containing `tgt` -> (lo1,hi1,t1)
//     search track B likewise                             -> (lo2,hi2,t2)
//   Knots are 16 bytes.  Track A: {s32 t; s16 v[3]@+2}  (fixed point 2^-14,
//   lbl_80291600 = 6.103515625e-05) with a parallel FLOAT view at +4/+8/+0xC.
//   Track B: {s16 t; s16 v[3]@+2}, values scaled by 1/32 (lbl_80291608 = 32.0f).
//   fn_80026AD4(obj) is a global "are values stored as raw floats" test: !=0
//   selects the float view, ==0 the s16 view.
//   t==0.0f -> copy the LOW knot out, t==1.0f -> the HIGH knot; both cases set
//   w = sqrt(max(0, 1 - (x*x+y*y+z*z))) and negate it when bit 0x8000 of the
//   knot's time word is set (lhz/and i.).  Otherwise interpolate:
//     track A -> fn_80026140(&vc,&va,&vb,t1), 16-byte copy into arg1;
//     track B -> paired-single
//        D[1] = __builtin_ps_madds0(__builtin_ps_sub(B[1],A[1]),A[1],T)
//        D[0] = __builtin_ps_madds0(__builtin_ps_sub(B[0],A[0]),A[0],T)
//       with A = v1, B = v2 ({x,y,z,1.0} each) and T = t2, preceded by the
//       4-byte no-op call fn_8002B8E4 (a `blr` stub -- real, kept because it is
//       an opaque external call) and followed by fn_8002B8E8 (a psq pair copy).
//
// LEVERS THAT GOT HERE (all verified, keep them if you continue):
//   * the fixed-point/int->double idiom is `(f32)(f64)(((s32)t * 2) >> 0x11)`
//     for the s32 track and `(f32)(f64)(s16)t` for the s16 track.  ngccc 3.9.3
//     emits slwi/srawi/xoris 0x8000 + the 0x43300000 high word + `fsub` of
//     0x4330000080000000 for BOTH -- verified with a 4-function probe.  The
//     `xoris 0x8000` is cc1's own s32->f64 sign step, not a source xor.
//   * `pool` reference to lbl_802915F8 must NOT be hand-written: the plain casts
//     synthesise the same constant into module .rodata, and
//     tools/fix_fp_pool.py retargets it at promote time (doc 14 / §4n).
//   * the object needs -mps-float (the 16-byte copies are psq_l/psq_st, and the
//     tail is real ps_sub/ps_madds0).  `__ps_t` is a cc1 builtin but
//     structs.h typedefs it as `double`, which makes the builtins fail
//     ("unsupported vector operation") -- the local `mode(PS)` sn_ps + PSU
//     union above is the working spelling.
//   * `RecI`/`RecS` MUST be padded to 16 bytes; unpadded they become 12/8 and
//     the search degenerates into walking pointers (mulli 0xc).
//   * the four magnitude blocks must read back out1->x/y/z through the pointer
//     (GCC keeps the stores and reloads them); the clamp must be spelled
//     `len = mag; if (mag <= 0.0f) len = 0.0f;`.  `!(mag > 0.0f)` and
//     `mag >= 0.0f` both drop the score to 2.0% (wrong cror/bso polarity).
//   * the general (t != 0/1) paths need THREE MORE V4 locals in the second half
//     (v1..v4): the original keeps 7 sixteen-byte stack objects, and adding
//     them is what makes the frame 0x158 (exact) instead of 0x118.
//   * out2 store order is x,y,z,w in source (want's x,y,w,z emit order comes
//     out of the scheduler; writing x,y,w,z in source drops the score to 4.7%).
//
// REMAINING BLOCKER (why it is still parked):
//   GCC 2.95's global register allocation.  17 GPRs + 7 FPRs are live across
//   the loop and the retail assignment (r18=obj, r15=sel, r31=i, r30=out1,
//     r29=out2, r22/r26/r28 = base1/lo1/hi1, r23/r25/r27 = base2/lo2/hi2,
//     r21/r20 = n1/n2, r24 = 0x43300000, r19/r16 = pool anchors, r8 = k,
//     r6 = last, r14 = out2+1, r17 = &vb, i+1 and out1+1 SPILLED to 0x84/0x80)
//   is not reproducible from the declaration orders tried (obj r19, sel r16,
//   i r30, out1 r31, lo1 r27, hi2 r26, k r10, ni r14, nout1 r15, nout2 spilled
//   to 0x88).  This is the documented big-function allocator wall (§6y, §6x-89)
//   and REGISTRATION COUNT also differs: 626 insns vs 635.  The 9 missing:
//     3 = the cr0 mfcr/mtcrf save (retail keeps a cr0 field live across the
//         sqrt calls, and no plain-C form here produced one);
//     3 = retail emits `slwi r9,r8,4; lwzx r0,r9,r22; add r10,r9,r22` per search
//         iteration while cc1 strength-reduces `&base1[k]` into a walking
//         pointer (2 extra addi) -- 3 net per search, and the four `mr rX,r22`
//         setup copies differ too;
//     3 = retail caches `mode == 0` in cr4 and reuses it for BOTH knots
//         (cmpwi cr4,r3,0 + 2x beq cr4) but holds the value in the
//         call-clobbered r3 across the sqrt calls; a named `s32 isint` folds to
//         subfic/adde instead and the direct re-test emits two cmpwi.
//   So: same mnemonics everywhere, wrong register numbers.  Do NOT re-grind the
//   source shapes above (they are all verified wins) -- the remaining work is
//   register assignment, i.e. decl-order / web-shape levers, not semantics.
#include "types.h"
#include "structs.h"

extern f32 lbl_802915EC;
extern f32 lbl_802915F0;
extern f64 lbl_802915F8;
extern f32 lbl_80291600;
extern f32 lbl_80291604;
extern f32 lbl_80291608;

s32 fn_80026A84(Unk_C8FEE62D *obj, s32 sel, s32 i);
s32 fn_80026AA8(Unk_C8FEE62D *obj, s32 sel, s32 i);
s32 fn_80026AD4(Unk_C8FEE62D *obj);
f32 sqrtf(f32 x);
void fn_80026140(void *out, void *a, void *b, f32 t);
void fn_8002B8E4(void *p);
void fn_8002B8E8(void *dst, void *src);

typedef struct { s32 t; s16 v[3]; char pad[6]; } RecI;
typedef struct { s16 t; s16 v[3]; char pad[8]; } RecS;
typedef struct { s32 t; f32 v[3]; } RecF;
typedef struct { f32 x, y, z, w; } V4;
typedef float sn_ps __attribute__((mode(PS)));
typedef union SN_PS_type { sn_ps ps; struct { float hi, lo; } flt; } PSU;

#define CND32(x) ((f32)(f64)((((x) * 2) >> 0x11)))
#define CND16(x) ((f32)(f64)(s16)(x))

s32 fn_80026D34(Unk_C8FEE62D *arg0, V4 *arg1, V4 *arg2, f32 farg0) {
    RecI *hi1 = (RecI *)arg0->unk0x10;
    RecS *hi2 = (RecS *)arg0->unk0x14;
    s32 i = 0;
    f32 t2 = lbl_802915EC;
    V4 *out1 = arg1;
    V4 *out2 = arg2;
    f32 t1 = t2;
    s32 sel = arg0->unk0x18;
    f32 tgt = farg0 * lbl_802915F0;
    RecI *lo1 = hi1;
    RecI *base1 = hi1;
    RecS *lo2 = hi2;
    RecS *base2 = hi2;
    s32 k;
    s32 last;
    f32 k16 = lbl_80291600;
    f32 one = lbl_80291604;
    f32 k32 = lbl_80291608;
    f64 pool = lbl_802915F8;
    f32 mag;

    while (i < arg0->unk0x8) {
        s32 ni = i + 1;
        s32 n1 = fn_80026A84(arg0, sel, i);
        s32 n2 = fn_80026AA8(arg0, sel, i);
        V4 *nout2 = out2 + 1;
        V4 *nout1 = out1 + 1;
        s32 mode;
        f32 len;
        V4 va, vb, vc, vd;
        V4 v1, v2, v3, v4;

        k = 0;
        if (k < n1) {
            last = n1 - 1;
            if (k == last) {
                lo1 = hi1 = base1;
                t1 = 0.0f;
            } else {
                do {
                    f32 ta = CND32(base1[k].t);
                    if (tgt >= ta) {
                        f32 tb = CND32(base1[k + 1].t);
                        if (tgt <= tb) {
                            lo1 = &base1[k];
                            hi1 = &base1[k + 1];
                            t1 = (tgt - ta) / (tb - ta);
                            goto d1;
                        }
                    }
                    k++;
                    if (k >= n1) goto d1;
                } while (k != last);
                lo1 = hi1 = &base1[last];
                t1 = 0.0f;
            }
        }
    d1:
        mode = fn_80026AD4(arg0);
        if (t1 == 0.0f) {
            if (mode != 0) {
                out1->x = ((RecF *)lo1)->v[0];
                out1->y = ((RecF *)lo1)->v[1];
                out1->z = ((RecF *)lo1)->v[2];
            } else {
                out1->x = CND16(lo1->v[0]) * k16;
                out1->y = CND16(lo1->v[1]) * k16;
                out1->z = CND16(lo1->v[2]) * k16;
            }
            mag = ((one - out1->x * out1->x) - out1->y * out1->y) - out1->z * out1->z;
            len = mag;
            if (mag <= 0.0f) len = 0.0f;
            len = sqrtf(len);
            out1->w = len;
            if (lo1->t & 0x8000) out1->w = -len;
        } else if (t1 == one) {
            if (mode != 0) {
                out1->x = ((RecF *)hi1)->v[0];
                out1->y = ((RecF *)hi1)->v[1];
                out1->z = ((RecF *)hi1)->v[2];
            } else {
                out1->x = CND16(hi1->v[0]) * k16;
                out1->y = CND16(hi1->v[1]) * k16;
                out1->z = CND16(hi1->v[2]) * k16;
            }
            mag = ((one - out1->x * out1->x) - out1->y * out1->y) - out1->z * out1->z;
            len = mag;
            if (mag <= 0.0f) len = 0.0f;
            len = sqrtf(len);
            out1->w = len;
            if (hi1->t & 0x8000) out1->w = -len;
        } else {
            va.x = 0.0f; va.y = 0.0f; va.z = 0.0f; va.w = one;
            vb.x = 0.0f; vb.y = 0.0f; vb.z = 0.0f; vb.w = one;
            if (mode != 0) {
                va.x = ((RecF *)lo1)->v[0];
                va.y = ((RecF *)lo1)->v[1];
                va.z = ((RecF *)lo1)->v[2];
            } else {
                va.x = CND16(lo1->v[0]) * k16;
                va.y = CND16(lo1->v[1]) * k16;
                va.z = CND16(lo1->v[2]) * k16;
            }
            mag = ((one - va.x * va.x) - va.y * va.y) - va.z * va.z;
            len = mag;
            if (mag <= 0.0f) len = 0.0f;
            len = sqrtf(len);
            va.w = len;
            if (lo1->t & 0x8000) va.w = -len;
            if (mode != 0) {
                vb.x = ((RecF *)hi1)->v[0];
                vb.y = ((RecF *)hi1)->v[1];
                vb.z = ((RecF *)hi1)->v[2];
            } else {
                vb.x = CND16(hi1->v[0]) * k16;
                vb.y = CND16(hi1->v[1]) * k16;
                vb.z = CND16(hi1->v[2]) * k16;
            }
            mag = ((one - vb.x * vb.x) - vb.y * vb.y) - vb.z * vb.z;
            len = mag;
            if (mag <= 0.0f) len = 0.0f;
            len = sqrtf(len);
            vb.w = len;
            if (hi1->t & 0x8000) vb.w = -len;
            fn_80026140(&vc, &va, &vb, t1);
            ((sn_ps *)out1)[0] = ((sn_ps *)&vc)[0];
            ((sn_ps *)out1)[1] = ((sn_ps *)&vc)[1];
        }

        k = 0;
        if (k < n2) {
            last = n2 - 1;
            if (k == last) {
                lo2 = hi2 = base2;
                t2 = 0.0f;
            } else {
                do {
                    f32 ta = CND16(base2[k].t);
                    if (tgt >= ta) {
                        f32 tb = CND16(base2[k + 1].t);
                        if (tgt <= tb) {
                            lo2 = &base2[k];
                            hi2 = &base2[k + 1];
                            t2 = (tgt - ta) / (tb - ta);
                            goto d2;
                        }
                    }
                    k++;
                    if (k >= n2) goto d2;
                } while (k != last);
                lo2 = hi2 = &base2[last];
                t2 = 0.0f;
            }
        }
    d2:
        mode = fn_80026AD4(arg0);
        if (t2 == 0.0f) {
            if (mode != 0) {
                out2->x = ((RecF *)lo2)->v[0];
                out2->y = ((RecF *)lo2)->v[1];
                out2->z = ((RecF *)lo2)->v[2];
                out2->w = one;
            } else {
                out2->x = CND16(lo2->v[0]) / k32;
                out2->y = CND16(lo2->v[1]) / k32;
                out2->z = CND16(lo2->v[2]) / k32;
                out2->w = one;
            }
        } else if (t2 == one) {
            if (mode != 0) {
                out2->x = ((RecF *)hi2)->v[0];
                out2->y = ((RecF *)hi2)->v[1];
                out2->z = ((RecF *)hi2)->v[2];
                out2->w = one;
            } else {
                out2->x = CND16(hi2->v[0]) / k32;
                out2->y = CND16(hi2->v[1]) / k32;
                out2->z = CND16(hi2->v[2]) / k32;
                out2->w = one;
            }
        } else {
            if (mode != 0) {
                v1.x = ((RecF *)lo2)->v[0];
                v1.y = ((RecF *)lo2)->v[1];
                v1.z = ((RecF *)lo2)->v[2];
                v1.w = one;
                v2.x = ((RecF *)hi2)->v[0];
                v2.y = ((RecF *)hi2)->v[1];
                v2.z = ((RecF *)hi2)->v[2];
                v2.w = one;
            } else {
                v1.x = CND16(lo2->v[0]) / k32;
                v1.y = CND16(lo2->v[1]) / k32;
                v1.z = CND16(lo2->v[2]) / k32;
                v1.w = one;
                v2.x = CND16(hi2->v[0]) / k32;
                v2.y = CND16(hi2->v[1]) / k32;
                v2.z = CND16(hi2->v[2]) / k32;
                v2.w = one;
            }
            fn_8002B8E4(&v3);
            {
                sn_ps *A = (sn_ps *)&v1;
                sn_ps *B = (sn_ps *)&v2;
                sn_ps *D = (sn_ps *)&v3;
                PSU T;
                T.flt.hi = t2;
                D[1] = __builtin_ps_madds0(__builtin_ps_sub(B[1], A[1]), A[1], T.ps);
                D[0] = __builtin_ps_madds0(__builtin_ps_sub(B[0], A[0]), A[0], T.ps);
            }
            fn_8002B8E8(&v4, &v3);
            ((sn_ps *)out2)[0] = ((sn_ps *)&v4)[0];
            ((sn_ps *)out2)[1] = ((sn_ps *)&v4)[1];
        }

        base2 += n2 * 0x10;
        i = ni;
        base1 += n1 * 0x10;
        out1 = nout1;
        out2 = nout2;
    }
    return 1;
}
