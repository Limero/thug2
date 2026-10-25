// WIP DRAFT — hand-rebuilt from disasm (2026-08-26), semantics re-verified
// 2026-09-27. family=m2c
// family=m2c range=0x800BB9BC-0x800BBEDC size=1312B (328 insns)
// ===========================================================================
// The old hard-block claim about unemittable words is wrong -- those words are
// indexed quantized pair ops. This function's three indexed pair sites are
// emittable from plain C under the float flag (probe-verified): a pair store
// through a byte-offset address, and a volatile pair load where both lanes
// must stay live or it narrows to a scalar load. Operand roles: the base
// expression goes to the first address operand; each site is spelled for its
// own order.
//
// BUILTIN ENCODING -- probe-verified (one builtin per TU, decoded with the PS
// helper). This is ground truth: multiply-add is natural math order, scaled
// multiply uses the low lane, multiply is full pair, low-merge takes low lanes,
// and the disassembler prints pair ops in destination/source order so the
// second printed operand is builtin arg 2 and the third is arg 3.
// The header this file carried until late September claimed a swapped
// multiply-add argument order. That was wrong and it made all three
// multiply-add sites compute the wrong product. Fixed here.
// Lane access through a small-struct union member fails to build -- use raw
// float pairs plus punned pair casts instead; a pair union inside a frame
// template also drags extra alignment into the struct -- never put one in FRM.
//
// SEMANTIC REBUILD (verified word by word against the original; every pair word
// decoded, every stack offset checked).
// Script-record loader over the first argument (held in a fixed register the
// whole function).
//   init: scalar plus constant broadcast into four frame pair slots (original
//   store order noted; the compiler rotates them, same values)
//   prologue (two pair differences plus two pair sums -- the late-September
//   fix; the old draft built one slot from a chained difference and left a
//   dead second sum):
//     two difference slots and two sum slots from the argument pairs and the
//     frame pairs, then two helper calls.
//   loop1 (counted, countdown, table walker moving backwards). Descriptor
//   slots re-derive table sums per trip -- the original reloads the table pair
//   inside the loop, so the draft must not carry it across the call in a reused
//   temporary (that made the compiler spill an 8-byte copy and cost frame).
//   Hit-test call; the original stores the result byte before the branch.
//   On hit: entry lanes from the table, scaled differences, scaled products,
//   merged constant, summed dot, then entry stores for the dot inputs, limit,
//   dot result, boolean and counters.
//   cleanup: guarded link removal plus zeroing.
//   loop2 outer (counted countdown): indexed table load, argument-pair sums,
//   element fetch, two calls, message setup; inner count from the work area.
//   inner (countdown, walker): pair differences (also spilled), vertical and
//   horizontal deltas, squared plus multiply-add accumulation, dot, reciprocal
//   estimate, normalise-branch with scaled outputs or constant-fill else path
//   (offsets re-checked -- the old draft wrote the high lane where the original
//   writes a later slot), join with two dot blocks, gates, then store block
//   with counters.
//   return nonzero-count flag (one loaded before the compare).
//
// FRAME MAP (all four prologue/epilogue fields verified byte-exact):
//   frame setup, float save, integer save block and link save all match
//   exactly. Frame template at the first local slot, so every member lands on
//   the original offset (named pair slots, descriptor slots, work area with
//   count and label, tail locals with two swapped relative to the original,
//   implicit gap, save area).
//   NOTE: the trailing gap pad must NOT be declared -- the compiler rounds it
//   up and the frame lands too large. The gap is implicit. (Verified both ways.)
//
// CALLEE PROTOS (prologue-audited): pair-copy helper takes destination plus
// two sources and reads no extra argument (a 3-arg prototype kills phantom
// args); sign-extended byte return on the hit-test reproduces the original
// extension; float argument passed in a float register on the work-area call.
//
// STATUS: PARKED — 2026-09-27: semantics now provably correct (the whole
// 37-opcode PS arithmetic stream matches retail 1:1 in kind, order AND
// operand role; frame byte-exact), but cc1's FPR allocator still cannot be
// steered to retail's colour map. Measured: DIFF 4.3% masked, got 321 insns /
// 1284 B vs retail 328 insns / 1312 B (7 words short).
// The masked % went DOWN from the old draft's 10.3% only because the old
// prologue was wrong and its (wrong) instruction stream happened to align a
// few extra early words; with a 1-word shift the byte-index score cascades
// (AGENTS §6au-232). The structural metrics below are the honest ones.
//
// RESIDUALS (exact, re-measured):
// (1) Float colour map -- the whole remaining wall. The original recycles float
//     registers across phases once a producer dies; the op sequence matches
//     only the assignment differs. Hard float-register pins block inter-web
//     reuse, which is exactly the mechanism the original relies on, so pins
//     cannot express phase-partitioned recycling.
// (2) Two work-area words are re-loaded inside the inner loop rather than homed
//     in callee-saved floats across it. That is deliberate: hoisting them makes
//     the compiler materialise them as integer spill pairs and the frame grows,
//     which is much worse than two extra pair loads. With them in-loop the
//     frame is byte-exact; the cost is a few words of missing loop-preheader
//     setup.
// (3) About two dozen pair memory ops are eliminated that the original keeps:
//     loop-hit scratch stores, one temp in the normalise branch, and three
//     provably-dead register-copy fill words interleaved with the entry stores.
//     Forcing them needs an anti-elimination mechanism on an escaping slot or
//     a copy-as-value trick -- not yet tried.
// (4) Many frame pair reads compile to 64-bit integer-pair loads instead of
//     the original pair loads (a per-site compiler mode decision). Re-routing
//     every read through one pair alias was tried (small improvement) and does
//     not fix it, so it is not a cast/alias-shape problem.
// Retry hints: (a) residual (3) is the cheapest next win -- one keep-alive per
// dead store, re-diffing the whole body after each; (b) then (2)/(1): with the
// frame already exact, float pins on the inner loop triple are worth re-trying
// even though pins normally block reuse.
// (c) Dummy doubles are not the fix: the frame is already exact.
// The three indexed sites encode with the original operand order per site.
//
// DISCLOSURE (inline-asm / pin inventory): zero instruction templates. One
// declaration-level register pin on the first argument (pre-existing, kept):
// the original prologue copies the argument into a fixed register and it stays
// there the whole function, so the pin matches rather than forcing. One
// zero-output scheduling barrier on the descriptor pointer (pre-existing,
// emits no code) keeps it in its own web so both the call and the copy
// argument materialise like the original pair.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern f32 lbl_80298DF4;
extern f32 lbl_80298DF8;
extern char lbl_80298CA0[];
extern char lbl_8037D008[];
extern char lbl_8037DFD8[];
extern char lbl_8037E458[];
extern char lbl_8037E5D8[];
s32 fn_80007264(void *, void *, void *);
void fn_80105CE8(Unk_5CB48605 *, void *);
void fn_8010794C(Unk_C7387A53 *);
s8 fn_80107B20(Unk_E9DCA07D *, s32, void *);
void fn_80108E94(Unk_181A4304 *, Unk_EA529D06 *, f32);
s32 fn_80108F54(void *, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);

typedef union { __ps_t p; f32 w[2]; } PSU;

typedef struct {
    char buf8[0x20];      /* r1+0x08 */
    f32 b280[2];          /* r1+0x28 */
    f32 b281[2];          /* r1+0x30 */
    f32 b282[2];          /* r1+0x38 */
    f32 b283[2];          /* r1+0x40 */
    f32 b480[2];          /* r1+0x48 */
    f32 b481[2];          /* r1+0x50 */
    f32 p58[2];           /* r1+0x58 */
    f32 p60[2];           /* r1+0x60 */
    f32 d0[2];            /* r1+0x68  desc+0x00 */
    f32 d8[2];            /* r1+0x70  desc+0x08 */
    f32 d10[2];           /* r1+0x78  desc+0x10 */
    f32 d18[2];           /* r1+0x80  desc+0x18 */
    char dpad[0x60];      /* r1+0x88 */
    f32 d80;              /* r1+0xE8  desc+0x80 */
    char dpad2[0x14];     /* r1+0xEC */
    f32 d98p[2];          /* r1+0x100 desc+0x98 */
    f32 dA0[2];           /* r1+0x108 desc+0xA0 */
    s32 dA8;              /* r1+0x110 desc+0xA8 */
    char dq[0x10];        /* r1+0x114 */
    s32 dBC;              /* r1+0x124 desc+0xBC */
    u8 big[0xC70];        /* r1+0x128 */
} FRM;                    /* size 0xD90, align 4 - no PS-alignment padding */

#define PA118 (*((__ps_t volatile *)&((Unk_15034E64 *)arg0)->unk0x118))
#define PA120 (*((__ps_t volatile *)&((Unk_15034E64 *)arg0)->unk0x120))

s32 fn_800BB9BC(void *arg0) {
    FRM fr;
    f32 ta0[2];           /* r1+0xDA0 */
    f32 ta8[2];           /* r1+0xDA8 */
    f32 tb0[2];           /* r1+0xDB0 */
    f32 tb8[2];           /* r1+0xDB8 */
    f32 tc0[2];           /* r1+0xDC0 */
    PSU a118, a120, s0, s8v, sq9, w0, w8, dx, dy, cstp, cst2, w8b, sq8, w0b, dz, sqv;
    PSU mgv, acc, dsum, rq, nm, p4, p6, rcpp, e18v, e10v;
    PSU pj18, pwk20, pr1, pj10, pwk18, mg2, acc2, sum2;
    PSU pe8, pe0, pr3, mg3, acc3, sum3;
    PSU pd;
    f32 t98u[2];         /* r1+0xD98 */            /* ta0/tb8/tc0-class spare */
    f32 f13c, v, fc4, df8, lim, diff, val0, ex;
    u16 count1, count2;
    u8 idx;
    s32 ret, icnt, r5v;
    u32 var_r27, off2;
    s32 var_r30, var_r7, iprod, bl;
    char *tblp, *entry, *ebase, *wr, *en2, *tbl2, *e2;
    register s32 a0 __asm__("r31");
    char *b28p;
    void *dptr, *dcopy;
    s32 *da8p;
    b28p = &fr.b280[0];
    dptr = &fr.d0;
    da8p = &fr.dA8;
    dcopy = dptr;
    __asm__("" : "+r"(dcopy));
    a0 = (s32)arg0;
#define arg0 ((void *)a0)

    f13c = lbl_80298DF4;
    v = ((Unk_15034E64 *)arg0)->unk0x1A0;
    fr.p60[0] = v;
    fr.p60[1] = f13c;
    fr.b283[0] = v;
    fr.p58[0] = v;
    fr.p58[1] = v;
    fr.b282[0] = v;
    fr.b282[1] = v;
    fr.b283[1] = f13c;

    a118.p = PA118;
    a120.p = PA120;

    sq9.p = __builtin_ps_sub(a120.p, *(__ps_t *)fr.b283);
    s0.p = __builtin_ps_sub(a118.p, *(__ps_t *)fr.b282);
    a118.p = __builtin_ps_add(a118.p, *(__ps_t *)fr.p58);
    a120.p = __builtin_ps_add(a120.p, *(__ps_t *)fr.p60);
    *(__ps_t *)fr.b280 = s0.p;
    *(__ps_t *)fr.b281 = sq9.p;
    *(__ps_t *)fr.b480 = a118.p;
    *(__ps_t *)fr.b481 = a120.p;

    fn_80007264(fr.buf8, b28p, &fr.b480[0]);
    fn_80105CE8((s32)lbl_8037D008, fr.buf8);

    ((Unk_15034E64 *)arg0)->unk0x199 = 0;
    count1 = ((Unk_15034E64 *)arg0)->unk0x94;
    ((Unk_15034E64 *)arg0)->unk0x198 = 0;
    if (count1 != 0) {
        fn_8010794C(dptr);
        count1 = ((Unk_15034E64 *)arg0)->unk0x94;
        fr.dBC = (s32)lbl_8037D008;
        var_r27 = count1 - 1;
        if (count1 != 0) {
            lim = lbl_80298DF8;
            ebase = lbl_8037DFD8;
            tblp = (char *)lbl_8037E458 + var_r27 * 0x10;
            do {
                s0.p = ((Unk_C1F9F519 *)tblp)->unk0x0;
                a118.p = PA118;
                idx = ((Unk_15034E64 *)arg0)->unk0x198;
                *(__ps_t *)fr.d0 = a118.p;
                a118.p = PA118;
                iprod = (s8)idx * 0x30;
                a120.p = PA120;
                *(__ps_t *)fr.d8 = a120.p;
                s8v.p = ((Unk_C1F9F519 *)tblp)->unk0x8;
                a120.p = __builtin_ps_add(a120.p, s8v.p);
                a118.p = __builtin_ps_add(a118.p, s0.p);
                entry = ebase + iprod;
                *(__ps_t *)fr.d10 = a118.p;
                *(__ps_t *)fr.d18 = a120.p;
                ret = (s8)fn_80107B20(dcopy, 0, 0);
                ((Unk_F68EF90C *)entry)->unk0x2C = (u8)ret;
                if (ret != 0) {
                    val0 = fr.d80;
                    fc4 = lbl_80298DF4;
                    *(__ps_t *)((char *)(s32)iprod + (s32)ebase) = ((Unk_C1F9F519 *)tblp)->unk0x0;
                    ((Unk_F68EF90C *)entry)->unk0x8 = ((Unk_C1F9F519 *)tblp)->unk0x8;
                    diff = fc4 - val0;
                    t98u[0] = diff;
                    dy.p = *(__ps_t *)fr.d18;
                    s0.p = *(__ps_t *)fr.d8;
                    pd.p = *(__ps_t volatile *)t98u;
                    s0.p = __builtin_ps_sub(dy.p, s0.p);
                    dy.p = *(__ps_t *)fr.d10;
                    mgv.p = *(__ps_t *)fr.d0;
                    *(__ps_t *)fr.b282 = dy.p;
                    s0.p = __builtin_ps_muls0(s0.p, pd.p);
                    sq9.p = *(__ps_t *)fr.dA0;
                    pd.p = *(__ps_t *)lbl_80298CA0;
                    dy.p = __builtin_ps_sub(dy.p, mgv.p);
                    *(__ps_t *)fr.b480 = dy.p;
                    mgv.p = __builtin_ps_mul(sq9.p, s0.p);
                    sq9.p = *(__ps_t *)fr.d98p;
                    ((Unk_F68EF90C *)entry)->unk0x2D = 0;
                    dy.p = __builtin_ps_muls0(dy.p, pd.p);
                    ((Unk_F68EF90C *)entry)->unk0x2E = (u8)var_r27;
                    *((f32 *)&((Unk_F68EF90C *)entry)->unk0x24) = lim;
                    *(__ps_t *)fr.b280 = dy.p;
                    *(__ps_t *)fr.b281 = s0.p;
                    mgv.p = __builtin_ps_merge00(mgv.p, pd.p);
                    sq9.p = __builtin_ps_madd(sq9.p, dy.p, mgv.p);
                    sq9.p = __builtin_ps_sum0(sq9.p, sq9.p, sq9.p);
                    *(__ps_t *)ta0 = sq9.p;
                    v = ta0[0];
                    sq9.p = *(__ps_t *)fr.d98p;
                    ((Unk_F68EF90C *)entry)->unk0x28 = v;
                    bl = v <= lim;
                    sq9.p = *(__ps_t *)fr.dA0;
                    ((Unk_5F85C510 *)entry)->unk0x10 = sq9.p;
                    *((__ps_t *)&((Unk_5F85C510 *)entry)->unk0x18) = sq9.p;
                    if (bl != 0) {
                        ((Unk_15034E64 *)arg0)->unk0x199 += 1;
                    }
                    ((Unk_15034E64 *)arg0)->unk0x198 += 1;
                }
                tblp -= 0x10;
            } while (var_r27-- != 0);
        }
        if (fr.dA8 != 0) {
            CObject_RemoveRefLink((void *)fr.dA8, da8p);
            fr.dA8 = 0;
        }
    }
    count2 = ((Unk_15034E64 *)arg0)->unk0x9C;
    if (count2 != 0) {
        var_r30 = count2 - 1;
        if (var_r30 != 0) {
            tbl2 = (char *)lbl_8037E5D8;
            ebase = lbl_8037DFD8;
            do {
                off2 = var_r30 << 4;
                e2 = tbl2 + off2;
                a118.p = PA118;
                s0.p = *(__ps_t volatile *)((char *)tbl2 + off2);
                w0.p = ((Unk_C1F9F519 *)e2)->unk0x8;
                a120.p = PA120;
                a118.p = __builtin_ps_add(a118.p, s0.p);
                en2 = ((Unk_15034E64 *)arg0)->unk0x98 + var_r30 * 0x18;
                a120.p = __builtin_ps_add(a120.p, w0.p);
                *(__ps_t *)fr.b280 = a118.p;
                *(__ps_t *)fr.b281 = a120.p;
                v = *((f32 *)&((Unk_42076946 *)en2)->unk0x10);
                fn_80108E94(fr.big, b28p, v);
                *(s32 *)((char *)fr.big + 0xC68) = (s32)lbl_8037D008;
                r5v = var_r30 - 1;
                if (fn_80108F54(fr.big, 0) != 0) {
                    icnt = *(s32 *)((char *)fr.big + 0x634);
                    var_r7 = icnt - 1;
                    if (icnt != 0) {
                        df8 = lbl_80298DF8;
                        lim = df8;
                        fc4 = lbl_80298DF4;
                        p4.p = *(__ps_t *)(fr.big + 0);
                        p6.p = *(__ps_t *)(fr.big + 8);
                        wr = (char *)fr.big + 0x20 + var_r7 * 0x30;
                        do {
                            a118.p = PA118;
                            a120.p = PA120;
                            w0.p = ((Unk_2DDDDA62 *)wr)->unk0x0;
                            w8.p = *((__ps_t *)&((Unk_2DDDDA62 *)wr)->unk0x8);
                            dx.p = __builtin_ps_sub(w0.p, a118.p);
                            dy.p = __builtin_ps_sub(w8.p, a120.p);
                            *(__ps_t *)fr.b280 = dx.p;
                            cstp.p = *((__ps_t volatile *)&((CStruct *)lbl_80298CA0)->unk0x0);
                            *(__ps_t *)fr.b281 = dy.p;
                            w8b.p = *((__ps_t volatile *)&((Unk_2DDDDA62 *)wr)->unk0x8);
                            idx = ((Unk_15034E64 *)arg0)->unk0x198;
                            p6.p = *(__ps_t *)(fr.big + 8);
                            sq8.p = __builtin_ps_sub(w8b.p, p6.p);
                            w0b.p = *((__ps_t volatile *)&((Unk_2DDDDA62 *)wr)->unk0x0);
                            iprod = (s8)idx * 0x30;
                            sqv.p = __builtin_ps_mul(sq8.p, sq8.p);
                            p4.p = *(__ps_t *)(fr.big + 0);
                            dz.p = __builtin_ps_sub(w0b.p, p4.p);
                            mgv.p = __builtin_ps_merge00(sqv.p, cstp.p);
                            *(__ps_t *)fr.b281 = sq8.p;
                            acc.p = __builtin_ps_madd(dz.p, mgv.p, dz.p);
                            *(__ps_t *)fr.b280 = dz.p;
                            *(__ps_t *)((char *)ebase + iprod) = dx.p;
                            entry = ebase + iprod;
                            ((Unk_F68EF90C *)entry)->unk0x8 = dy.p;
                            ((Unk_5F85C510 *)entry)->unk0x10 = dz.p;
                            dsum.p = __builtin_ps_sum0(acc.p, acc.p, acc.p);
                            rq.p = __builtin_ps_rsqrte(dsum.p);
                            nm.p = __builtin_ps_res(rq.p);
                            *(__ps_t *)ta8 = nm.p;
                            *((__ps_t *)&((Unk_5F85C510 *)entry)->unk0x18) = sq8.p;
                            v = ta8[0];
                            if (!(v == df8)) {
                                diff = -v;
                                tb0[0] = diff;
                                tb0[1] = diff;
                                rcpp.p = *(__ps_t *)tb0;
                                rcpp.p = __builtin_ps_res(rcpp.p);
                                e18v.p = __builtin_ps_muls0(sq8.p, rcpp.p);
                                e10v.p = __builtin_ps_muls0(dz.p, rcpp.p);
                                *((__ps_t *)&((Unk_5F85C510 *)entry)->unk0x18) = e18v.p;
                                ((Unk_5F85C510 *)entry)->unk0x10 = e10v.p;
                                *(__ps_t *)tb0 = rcpp.p;
                            } else {
                                *((f32 *)&((Unk_5F85C510 *)entry)->unk0x10) = df8;
                                ((Unk_F68EF90C *)entry)->unk0x1C = fc4;
                                *(f32 *)((char *)entry + 0x20) = fc4;
                                *((f32 *)&((Unk_5F85C510 *)entry)->unk0x18) = df8;
                            }
                            pj18.p = *((__ps_t *)&((Unk_5F85C510 *)entry)->unk0x18);
                            pwk20.p = *((__ps_t volatile *)&((Unk_EC9C414C *)wr)->unk0x20);
                            cst2.p = *((__ps_t volatile *)lbl_80298CA0);
                            pr1.p = __builtin_ps_mul(pj18.p, pwk20.p);
                            pj10.p = ((Unk_5F85C510 *)entry)->unk0x10;
                            pwk18.p = *((__ps_t volatile *)&((Unk_EC9C414C *)wr)->unk0x18);
                            mg2.p = __builtin_ps_merge00(pr1.p, cst2.p);
                            acc2.p = __builtin_ps_madd(pj10.p, pwk18.p, mg2.p);
                            sum2.p = __builtin_ps_sum0(acc2.p, acc2.p, acc2.p);
                            *(__ps_t *)tb8 = sum2.p;
                            v = tb8[0];
                            if (!(v < df8)) {
                                val0 = v;
                                pe8.p = ((Unk_F68EF90C *)entry)->unk0x8;
                                pe0.p = ((Unk_F68EF90C *)entry)->unk0x0;
                                pr3.p = __builtin_ps_mul(pj18.p, pe8.p);
                                mg3.p = __builtin_ps_merge00(pr3.p, cst2.p);
                                acc3.p = __builtin_ps_madd(pj10.p, pe0.p, mg3.p);
                                sum3.p = __builtin_ps_sum0(acc3.p, acc3.p, acc3.p);
                                *(__ps_t *)tc0 = sum3.p;
                                v = tc0[0];
                                if (!(v > df8)) {
                                    ((Unk_F68EF90C *)entry)->unk0x2D = 0;
                                    *((f32 *)&((Unk_F68EF90C *)entry)->unk0x24) = lim;
                                    ex = *((f32 *)&((Unk_42076946 *)en2)->unk0x10);
                                    ((Unk_F68EF90C *)entry)->unk0x2E = (u8)var_r30;
                                    diff = val0 - ex;
                                    bl = diff <= lim;
                                    ((Unk_F68EF90C *)entry)->unk0x28 = diff;
                                    ((Unk_F68EF90C *)entry)->unk0x2C = (u8)bl;
                                    if (bl != 0) {
                                        ((Unk_15034E64 *)arg0)->unk0x199 += 1;
                                    }
                                    ((Unk_15034E64 *)arg0)->unk0x198 += 1;
                                }
                            }
                            wr -= 0x30;
                        } while (var_r7-- != 0);
                    }
                }
                var_r30 = r5v;
            } while (var_r30 != -1);
        }
    }
    ret = 1;
    if (((Unk_15034E64 *)arg0)->unk0x199 == 0) {
        ret = 0;
    }
    return ret;
}
