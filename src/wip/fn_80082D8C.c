// WIP DRAFT (non-matching) — semantic reconstruction of fn_80082D8C.
// family=m2c range=0x80082D8C-0x80082EB8 size=300B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-19: PS body decoded + reconstructed, 264B/300B DIFF (all
// opcodes present; residual is pure regalloc/spill scheduling, M5.0o class).
// The old tooling wall is GONE: tools/ps_diff.py dec() decodes every op4
// word (capstone labels them `.word`/VMX garbage). Full decoded op list:
//   subs(9): f4-=f5 f9-=f5 f7-=f0 f10-=f0 f12-=f0 f11-=f13 f6-=f5 f9-=f10 f12-=f0
//   muls(7): f13=f8*f7 f11=f10*f11 f8=f8*f12 f13=f10*f13 f12=f9*f12 f9=f9*f7
//     f8=s0a*s0b(reloaded pair, E60)
//   merge10(7): f8={f10[1],f9[0]} f11={f7[1],f4[0]} f13={f12[1],f6[0]}
//     f10={f9[1],f9[0]} f0={f12[1],f12[0]} f11+={f9} f13+={f12}
//   merge00(6): f0={f11,f11} f9={f9,f10} f12={f12,f6} f0={f13,f13}
//     f7={f7,f4} f8={f8,(0,0)}
//   mr(2): f0=f8 (E30, saved across f8 reassign, spilled 16) f0=f10 (E5C,
//     saved across f10 reassign, spilled 32)
//   madd f11+=f13*f8; sum0 f11; exit (x>=0.0f) via fcmpu+cror+mfcr+clrlwi.
// Spills(11 psq_st + 2 dead stfs 1.0f): 48,40,56,72,64,16,80,32,8,24,88;
// reloads: 72->f8(E24), 16->f8(E54), 80->f10(E58). f3=(0,0) pool pair
// @0x802964D8; f2=0.0f @0x80296544; 1.0f @0x80296540 (both spills dead).
// Current body (below) emits the same op census minus 2 psq_st / 3 psq_l /
// 1 mr (copy coalesced: s0a/s0b stay in regs so the E30/E54 save+reload
// dance has no pressure reason to exist), frame 0x58 vs want 0x60.
// Load order is scheduler-driven (reordering source assigns: no change).
// Next lever (untried): struct-member ORDER matched to want spill offsets
// (48/40/56/72/64/16/80/32/8/24/88) so surviving spills land in place.
// OLD NOTE 2026-10-06: semantics = same-side-of-edge test (point-in-triangle
// primitive; caller fn_80082EB8 ANDs 3 permuted calls); scalar body replaced
// by the PS body below. Sibling fn_8008279C shares the module idiom.
//
// ---------------------------------------------------------------------------
// SIGNATURE (high confidence — read off the MATCHED caller chain, not guessed)
// ---------------------------------------------------------------------------
// fn_80082D8C is a 4-pointer predicate, NOT the (s32,s32,s32,s32) the m2c draft
// declared.  Evidence:
//   * src/fn_80082EB8.c (MATCHED, 128B, byte-identical) is
//         if (fn_80082D8C(arg0,arg1,arg2,arg3) != 0)
//           if (fn_80082D8C(arg0,arg2,arg1,arg3) != 0)
//             if (fn_80082D8C(arg0,arg3,arg1,arg2) != 0) return 1;
//         return 0;
//     i.e. it calls fn_80082D8C three times with the (2nd,3rd,4th) arguments
//     permuted as (A,B,C) / (B,A,C) / (C,A,B) and ANDs the results.
//   * src/wip/fn_80082F38.c:85 calls it as
//         fn_80082EB8(var_r31, &sp48, &sp58, &sp68)
//     where var_r31 walks four 16-byte stack points (address-taken floats) and
//     sp48/sp58/sp68 are three more 16-byte stack points.  So arg0 is a POINT
//     POINTER (the query point), not a context, and args 1..3 are the triangle
//     vertices — all four are 16-byte homogeneous {x,y,z,w} vectors.
//   * src/fn_8008741C.c (MATCHED) forwards straight into fn_80082F38, and
//     src/wip/fn_80083564.c:818 guards that call with an axis-aligned box test
//     ({0x80296548,0x8029654C,0x80296550} corners), so fn_80082F38 is the
//     triangle-vs-box public helper and fn_80082EB8 is its point-in-triangle
//     core.  docs/thpg-func-names.tsv carries the real symbol name
//     `point_in_triangle` (p_nxtopology.o, ~172B) — the same 3-half-plane test.
//
// RECOVERED SEMANTICS (high confidence): fn_80082D8C(P, V, E0, E1) is the
// "same side of an edge" primitive used by the classic point-in-triangle test.
// It returns nonzero iff P and V lie on the same side of the directed line
// through E0,E1, i.e. sign(cross(E1-E0, P-E0)) == sign(cross(E1-E0, V-E0)).
// fn_80082EB8 then feeds (vertex V, opposite edge (E0,E1)) triples for each of
// the three sides — the standard 3-sign-test point-in-triangle predicate.
//
// INFERRED (lower confidence, NOT verified): the retail encoding is the module's
// PS "house idiom" (cf. fn_8008279C: pair-pair psq_l loads, ps_mul/ps_merge00/
// ps_madd/ps_sum0 with w merged from a 1.0f constant — lbl_80296540 at
// .rodata2:0x80296540 is exactly `1.0f`, confirmed in src/r2d_80296540.c).  The
// m2c husk's two `sp4C/sp54 = *(f32 *)0x80296540` loads are consistent with the
// w=1.0 homogeneous fill.  The precise op order, the merge00 operand and the
// final comparison form (product-vs-zero vs sign equality vs `cror`) must be
// read from the PS decode before any byte match is attempted — do NOT treat the
// body below as byte-close.
//
// Body below is the semantic reference (readable scalar form, no asm, no casts)
// kept as the current best match so the file is no longer a 0% husk.
#include "types.h"
#include "dolphin/SN_PS.h"

typedef struct {
    __ps_t lo;
    __ps_t hi;
} VecP;

extern __ps_t lbl_802964D8;
extern f32 lbl_80296540;
extern f32 lbl_80296544;

// PS dataflow decoded 2026-10-19 via tools/ps_diff.py dec() (capstone
// stalls on every op4 word): edge-relative differences of the four
// 16-byte vectors, merge10 Lane shuffles, pairwise muls, two running
// differences, reloaded splats, final madd+sum0, (x >= 0.0f) exit.
// r3=P r4=V r5=E0 r6=E1; f3=(0,0) pool pair; f2=0.0f; 1.0f spilled.
typedef struct {
    __ps_t s9;
    __ps_t s10;
    __ps_t s12;
    __ps_t s0a;
    __ps_t s6;
    __ps_t s0b;
    __ps_t s0c;
    __ps_t s11;
    __ps_t s13;
    f32 one_a;
    f32 one_b;
} Spill;

s32 fn_80082D8C(const VecP *p, const VecP *v, const VecP *e0, const VecP *e1) {
    Spill sp;
    __ps_t f5;
    __ps_t f4;
    __ps_t f7;
    __ps_t f0;
    __ps_t f12;
    __ps_t f3;
    __ps_t f8;
    __ps_t f11;
    __ps_t f13;
    f32 f2;
    f32 x;
    SN_PS_type res;

    f5 = e0->hi;
    f4 = p->hi;
    f7 = p->lo;
    sp.s9 = e1->hi;
    f0 = e0->lo;
    sp.s10 = e1->lo;
    f12 = v->lo;
    sp.s6 = v->hi;
    f3 = lbl_802964D8;
    f2 = lbl_80296544;
    sp.one_a = lbl_80296540;
    sp.one_b = lbl_80296540;

    f4 = __builtin_ps_sub(f4, f5);
    sp.s9 = __builtin_ps_sub(sp.s9, f5);
    f7 = __builtin_ps_sub(f7, f0);
    sp.s10 = __builtin_ps_sub(sp.s10, f0);
    f8 = __builtin_ps_merge10(sp.s10, sp.s9);
    f11 = __builtin_ps_merge10(f7, f4);
    f13 = __builtin_ps_mul(f8, f7);
    f11 = __builtin_ps_mul(sp.s10, f11);
    f12 = __builtin_ps_sub(f12, f0);
    f11 = __builtin_ps_sub(f11, f13);
    sp.s0a = __builtin_ps_merge00(f11, f11);
    sp.s6 = __builtin_ps_sub(sp.s6, f5);
    f13 = __builtin_ps_merge10(f12, sp.s6);
    f8 = __builtin_ps_mul(f8, f12);
    f13 = __builtin_ps_mul(sp.s10, f13);
    f13 = __builtin_ps_sub(f13, f8);
    sp.s9 = __builtin_ps_merge00(sp.s9, sp.s10);
    sp.s12 = __builtin_ps_merge00(f12, sp.s6);
    f0 = f8;
    sp.s12 = __builtin_ps_mul(sp.s9, sp.s12);
    sp.s0b = __builtin_ps_merge00(f13, f13);
    f7 = __builtin_ps_merge00(f7, f4);
    sp.s9 = __builtin_ps_mul(sp.s9, f7);
    f0 = sp.s10;
    f8 = __builtin_ps_mul(sp.s0a, sp.s0b);
    sp.s10 = __builtin_ps_merge10(sp.s9, sp.s9);
    sp.s0c = __builtin_ps_merge10(sp.s12, sp.s12);
    sp.s9 = __builtin_ps_sub(sp.s9, sp.s10);
    sp.s12 = __builtin_ps_sub(sp.s12, sp.s0c);
    sp.s11 = __builtin_ps_merge10(f11, sp.s9);
    sp.s13 = __builtin_ps_merge10(f13, sp.s12);
    f8 = __builtin_ps_merge00(f8, f3);
    sp.s11 = __builtin_ps_madd(sp.s11, sp.s13, f8);
    sp.s11 = __builtin_ps_sum0(sp.s11, sp.s11, sp.s11);
    res.ps = sp.s11;
    x = res.flt.hi;
    return x >= f2;
}
