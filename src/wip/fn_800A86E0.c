// PARKED 2026-10-06 (w66): paired-single frame/allocator wall — see the
// `// PARKED ... blocker note` block at EOF.  One structural error fixed this
// round: the phantom 0x60/0x68 fields were removed (the want never touches
// them).
// WIP DRAFT (non-matching) — hand reconstruction from disassembly.
// family=m2c range=0x800A86E0-0x800A8D04 size=1572B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Reconstructed from a full hand-decode of the 393-word body: an
// "orthonormal frame from two tangent edges" routine (Gram-Schmidt / torsion
// frame).  Structure, all five `return 2` degeneracy guards, the collinearity
// bail-out, the acosf clamp and every field store are read straight out of the
// want.  Return codes: 1 = ok, 0 = flagged or collinear/degenerate,
// 2 = a normalization denominator was exactly 0.
// Constants (.rodata2): lbl_802981FC=0.0, lbl_80298200=2.0, lbl_80298204=6.0,
//   lbl_80298208=1.0, lbl_8029820C=-1.0, lbl_802981C0=(0,0) PS pair.
// The collinearity guard is the GCC-2.95 `||`-of-two-compares idiom:
// fcmpu cr7/cr6 + mfcr + 2x rlwinm + or. + beq (beq keeps when neither
// cr7.LT nor cr6.EQ is set).
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

extern f32 lbl_802981FC;
extern f32 lbl_80298200;
extern f32 lbl_80298204;
extern f32 lbl_80298208;
extern f32 lbl_8029820C;
extern __ps_t lbl_802981C0;

f32 acosf(f32);

typedef union {
    __ps_t p;
    f32 w[2];
} S;

typedef struct {
    char pad0x00[0x8];
    __ps_t v08;
    __ps_t v10;
    char pad0x18[0x8];
    __ps_t v20, v28, v30, v38;
    __ps_t v40, v48;
    char pad0x50[0x10];
    char pad0x60[0x10];
    __ps_t v70, v78, v80, v88;
    char pad0x90[0x18];
    __ps_t vA8;
    f32 vB0;
    s32 vB4;
    f32 vB8;
    __ps_t vC0, vC8, vD0, vD8;
    f32 vE0, vE4, vE8;
} Obj;

s32 fn_800A86E0(Obj *o) {
    S a1, a2, a3, a4, a5, a6;
    S n1, n2, rt;
    S half;
    S s1, s2, s3;
    S q70, q78, s8, s9;
    S q90, q98, sa, cr;
    S sb, qb8, sc, sd, qd0;
    S P0, P1, Q, R0, P2, P3;
    S u, v, w, x, y, z;
    f32 zero, two, six, one, minus_one;
    f32 f3, t1, t2, t3, t4, f1;
    s32 flags;

    zero = lbl_802981FC;
    two = lbl_80298200;
    six = lbl_80298204;
    one = lbl_80298208;
    minus_one = lbl_8029820C;

    P0.p = o->v70;
    Q.p = o->v10;
    P1.p = o->v78;
    R0.p = o->v08;
    P2.p = o->v80;
    P3.p = o->v88;

    /* ---- edge differences ---- */
    x.p = __builtin_ps_sub(Q.p, P1.p);  /* Q - P1 */
    y.p = __builtin_ps_sub(R0.p, P0.p); /* R0 - P0 */
    a1.p = __builtin_ps_sub(P2.p, P0.p);
    a2.p = __builtin_ps_sub(P3.p, P1.p);
    a3.p = y.p;
    a4.p = x.p;
    w.p = __builtin_ps_mul(x.p, x.p);
    a5.p = a1.p;
    w.p = __builtin_ps_merge00(w.p, lbl_802981C0);
    o->vD0 = P0.p;
    o->vD8 = P1.p;
    y.p = __builtin_ps_madd(y.p, y.p, w.p);
    n1.p = __builtin_ps_res(__builtin_ps_rsqrte(__builtin_ps_sum0(y.p, y.p, y.p)));
    x.p = __builtin_ps_mul(a2.p, a2.p);
    flags = o->vB4;
    x.p = __builtin_ps_merge00(x.p, lbl_802981C0);
    y.p = __builtin_ps_madd(a1.p, a1.p, x.p);
    n2.p = __builtin_ps_res(__builtin_ps_rsqrte(__builtin_ps_sum0(y.p, y.p, y.p)));

    f3 = n1.w[0];
    rt.w[0] = f3 / n2.w[0];
    x.p = rt.p;
    a1.p = __builtin_ps_muls0(a1.p, x.p);
    a2.p = __builtin_ps_muls0(a2.p, x.p);
    u.p = __builtin_ps_add(P0.p, a1.p);
    v.p = __builtin_ps_add(P1.p, a2.p);
    o->vD0 = u.p;
    o->vD8 = v.p;

    if (flags & 1)
        return 0;
    if (f3 == zero)
        return 2;

    /* ---- bisect the two edges, check for collinearity ---- */
    x.p = o->v10;
    u.p = __builtin_ps_sub(u.p, R0.p);
    v.p = __builtin_ps_sub(v.p, x.p);
    a1.p = u.p;
    a4.p = v.p;
    half.w[0] = two;
    half.w[1] = two;
    a5.p = u.p;
    a2.p = v.p;
    z.p = __builtin_ps_res(half.p);
    a1.p = __builtin_ps_muls0(a1.p, z.p);
    a2.p = __builtin_ps_muls0(a2.p, z.p);
    w.p = __builtin_ps_mul(a2.p, a2.p);
    w.p = __builtin_ps_merge00(w.p, lbl_802981C0);
    a6.p = __builtin_ps_add(x.p, a2.p);
    u.p = __builtin_ps_sub(a6.p, P1.p);
    a4.p = u.p;
    z.p = __builtin_ps_mul(u.p, u.p);
    z.p = __builtin_ps_merge00(z.p, lbl_802981C0);
    y.p = __builtin_ps_add(R0.p, a1.p);
    a5.p = y.p;
    x.p = __builtin_ps_sub(y.p, P0.p);
    a3.p = x.p;
    y.p = __builtin_ps_madd(x.p, x.p, z.p);
    s1.p = __builtin_ps_res(__builtin_ps_rsqrte(__builtin_ps_sum0(y.p, y.p, y.p)));
    z.p = __builtin_ps_madd(a1.p, a1.p, w.p);
    s2.p = __builtin_ps_res(__builtin_ps_rsqrte(__builtin_ps_sum0(z.p, z.p, z.p)));

    t1 = s1.w[0];
    t2 = s2.w[0];
    if (t1 == zero || t1 * six < t2)
        return 0;

    o->vE8 = t2 * f3 / t1;
    if (o->vE8 == zero)
        return 2;

    /* ---- normalize the mid-edge pair into o->vC0 / o->vC8 ---- */
    o->vC0 = P1.p;
    o->vC8 = u.p;
    w.p = __builtin_ps_madd(P0.p, P0.p, __builtin_ps_merge00(z.p, lbl_802981C0));
    w.p = __builtin_ps_sum0(w.p, w.p, w.p);
    s3.p = __builtin_ps_res(__builtin_ps_rsqrte(w.p));
    t3 = f3 * f3 / s3.w[0];
    q70.w[0] = t3;
    q70.w[1] = zero;
    z.p = q70.p;
    w.p = __builtin_ps_madd(P0.p, P0.p, __builtin_ps_merge01(z.p, z.p));
    w.p = __builtin_ps_sum0(w.p, w.p, w.p);
    t4 = w.w[0];
    if (t4 > zero) {
        w.p = __builtin_ps_muls0(__builtin_ps_rsqrte(w.p), z.p);
        o->vC0 = __builtin_ps_muls0(P0.p, w.p);
        q78.w[0] = w.w[0];
        q78.w[1] = one;
        o->vC8 = __builtin_ps_mul(u.p, q78.p);
    }

    x.p = __builtin_ps_add(o->vC0, q70.p);
    y.p = __builtin_ps_add(o->vC8, q78.p);
    o->vC0 = x.p;
    o->vC8 = y.p;
    o->v20 = __builtin_ps_sub(x.p, R0.p);
    o->v28 = __builtin_ps_sub(y.p, o->v10);
    o->v40 = __builtin_ps_sub(x.p, o->vD0);
    o->v48 = __builtin_ps_sub(y.p, o->vD8);
    a5.p = __builtin_ps_sub(x.p, o->vD0);
    a6.p = __builtin_ps_sub(y.p, o->vD8);

    /* ---- normalize o->v20 / o->v28 ---- */
    x.p = o->v28;
    z.p = __builtin_ps_mul(x.p, x.p);
    z.p = __builtin_ps_merge00(z.p, lbl_802981C0);
    y.p = __builtin_ps_madd(o->v20, o->v20, z.p);
    y.p = __builtin_ps_sum0(y.p, y.p, y.p);
    w.p = __builtin_ps_rsqrte(y.p);
    s8.p = __builtin_ps_res(w.p);
    t1 = s8.w[0];
    if (t1 == zero)
        return 2;
    z.p = __builtin_ps_mul(o->v48, o->v48);
    z.p = __builtin_ps_merge00(z.p, lbl_802981C0);
    z.p = __builtin_ps_madd(a5.p, a5.p, z.p);
    z.p = __builtin_ps_sum0(z.p, z.p, z.p);
    u.p = __builtin_ps_rsqrte(z.p);
    s9.p = __builtin_ps_res(u.p);
    t2 = s9.w[0];
    if (t2 == zero)
        return 2;
    t3 = y.w[0];
    if (t3 > zero) {
        o->v20 = __builtin_ps_muls0(o->v20, w.p);
        q90.w[0] = w.w[0];
        q90.w[1] = one;
        o->v28 = __builtin_ps_mul(x.p, q90.p);
    }
    x.p = o->v28;
    y.p = o->v20;
    z.p = __builtin_ps_mul(a6.p, a6.p);
    z.p = __builtin_ps_merge00(z.p, lbl_802981C0);
    w.p = __builtin_ps_madd(a5.p, a5.p, z.p);
    w.p = __builtin_ps_sum0(w.p, w.p, w.p);
    v.p = __builtin_ps_rsqrte(w.p);
    t4 = w.w[0];
    if (t4 > zero) {
        a5.p = __builtin_ps_muls0(a5.p, v.p);
        q98.w[0] = v.w[0];
        q98.w[1] = one;
        a6.p = __builtin_ps_mul(a6.p, q98.p);
    }

    /* ---- acos of the normalised dot product ---- */
    x.p = o->v28;
    y.p = o->v20;
    z.p = __builtin_ps_madd(a5.p, y.p,
                            __builtin_ps_merge00(__builtin_ps_mul(x.p, a6.p), lbl_802981C0));
    z.p = __builtin_ps_sum0(z.p, z.p, z.p);
    sa.p = z.p;
    f1 = sa.w[0];
    if (f1 > one)
        f1 = one;
    if (f1 < minus_one)
        f1 = minus_one;
    f1 = acosf(f1);
    o->vE0 = f1;
    o->vE4 = o->vE8 * f1;

    /* ---- cross product o->v30 / o->v38 ---- */
    x.p = o->v20;
    y.p = o->v28;
    z.p = a5.p;
    w.p = a6.p;
    u.p = __builtin_ps_mul(__builtin_ps_merge10(x.p, y.p), z.p);
    v.p = __builtin_ps_mul(x.p, __builtin_ps_merge10(z.p, w.p));
    z.p = __builtin_ps_merge00(z.p, w.p);
    y.p = __builtin_ps_merge00(y.p, x.p);
    v.p = __builtin_ps_sub(v.p, u.p);
    u.p = __builtin_ps_mul(y.p, z.p);
    cr.p = __builtin_ps_merge00(v.p, v.p);
    z.p = __builtin_ps_merge10(u.p, u.p);
    cr.w[1] = one;
    u.p = __builtin_ps_sub(u.p, z.p);
    z.p = __builtin_ps_merge10(v.p, u.p);
    o->v30 = z.p;
    u.p = cr.p;
    o->v38 = u.p;
    z.p = __builtin_ps_merge00(__builtin_ps_mul(u.p, u.p), lbl_802981C0);
    w.p = __builtin_ps_madd(z.p, z.p, z.p);
    w.p = __builtin_ps_sum0(w.p, w.p, w.p);
    v.p = __builtin_ps_rsqrte(w.p);
    sb.p = __builtin_ps_res(v.p);
    t1 = sb.w[0];
    if (t1 == zero)
        return 2;
    t2 = w.w[0];
    if (t2 > zero) {
        qb8.w[0] = v.w[0];
        qb8.w[1] = one;
        o->v30 = __builtin_ps_muls0(z.p, v.p);
        o->v38 = __builtin_ps_mul(u.p, qb8.p);
    }

    /* ---- cross product o->v40 / o->v48 ---- */
    x.p = o->v20;
    y.p = o->v28;
    z.p = o->v30;
    w.p = o->v38;
    u.p = __builtin_ps_mul(__builtin_ps_merge10(x.p, y.p), z.p);
    v.p = __builtin_ps_mul(x.p, __builtin_ps_merge10(z.p, w.p));
    z.p = __builtin_ps_merge00(z.p, w.p);
    y.p = __builtin_ps_merge00(y.p, x.p);
    v.p = __builtin_ps_sub(v.p, u.p);
    u.p = __builtin_ps_mul(y.p, z.p);
    sc.p = __builtin_ps_merge00(v.p, v.p);
    sc.w[1] = one;
    w.p = __builtin_ps_sub(u.p, __builtin_ps_merge10(u.p, u.p));
    o->v40 = __builtin_ps_merge10(v.p, w.p);
    o->v48 = sc.p;
    a5.p = __builtin_ps_merge10(v.p, w.p);
    a6.p = sc.p;
    z.p = __builtin_ps_merge00(__builtin_ps_mul(a6.p, a6.p), lbl_802981C0);
    z.p = __builtin_ps_madd(a5.p, a5.p, z.p);
    w.p = __builtin_ps_sum0(z.p, z.p, z.p);
    v.p = __builtin_ps_rsqrte(w.p);
    sd.p = __builtin_ps_res(v.p);
    t3 = sd.w[0];
    if (t3 == zero)
        return 2;
    t4 = w.w[0];
    if (t4 > zero) {
        qd0.w[0] = v.w[0];
        qd0.w[1] = one;
        o->v40 = __builtin_ps_muls0(a5.p, v.p);
        o->v48 = __builtin_ps_mul(a6.p, qd0.p);
    }

    t1 = o->vB8;
    o->vB8 = zero;
    o->vB0 = t1;
    return 1;
}

// PARKED 2026-10-06 (w66) — blocker note.
//
// fn_800A86E0 is a 393-instruction paired-single "orthonormal frame from two
// edge vectors" builder: 127 psq_l/psq_st, 136 Gekko opcode-4 PS words and 43
// scalar-single ops, plus acosf.  The body above is honest C over the real
// `__ps_t` builtins (no inline asm, no transcription).
//
// STRUCTURAL FIX THIS ROUND.  The previous body invented two object fields at
// 0x60/0x68 (`v60`/`v68`) and used them for the second normalized edge pair.
// The want never reads or writes 0x60(r31)/0x68(r31) — every r31-relative
// access in the 393 words is 0x8, 0x20, 0x28, 0x30, 0x38, 0x40, 0x48, 0x70,
// 0x78, 0x80, 0x88, 0xb0, 0xb4, 0xb8, 0xc0, 0xc8, 0xd0, 0xd8, 0xe0, 0xe4,
// 0xe8.  The second pair lives at 0x40/0x48, reached as 32(r30)/40(r30) with
// r30 = r31+0x20 (set at 0x800A8994); in this draft those are the `a5`/`a6`
// aliases.  All six sites now use a5/a6 and the struct pad is `pad0x60[0x10]`.
//
// The operand roles of that block were re-decoded from their encodings
// (Gekko A-form, frD/frA/frB/frC = bits 25-21/20-16/15-11/10-6, XO5 = bits
// 5-1):
//   At 0x800A8A90 retail multiplies v48 by itself (word 0x100B02F2, f0 from
//   f11 holding v48); at 0x800A8A98 it merges the result with the zero pair
//   (word 0x10006C20, f13 holding (0,0)); at 0x800A8A9C it multiply-adds v40
//   squared into that (word 0x100C033A, f12 holding v40); at 0x800A8AAC it
//   sums the pair (word 0x10000014); and at 0x800A8AA4 it copies the sum to
//   f9 (word 0x11200090). The scaled store to 32(r30), i.e. object offset
//   0x40, at 0x800A8AB8 multiplies v40 by the zero pair (word 0x100C0358),
//   and the store to 40(r30), i.e. offset 0x48, at 0x800A8AD0 multiplies v48
//   by the zero pair (word 0x100B0372).
// so the previous `mul(a5,a5); merge00; madd(o->v60,o->v60,..)` had the
// mul/madd operands swapped and the follow-up multiplied v40 where the want
// multiplies v48.  The acos dot product at 0x800A8AD8-0x800A8B00 uses the
// same pair (ps_mul f13,f13(v28),f12(v48); ps_merge00; ps_madd
// f0,f0(v20),f12(v40),f13), which the `a5`/`a6` form now mirrors.
//
// WHAT STILL BLOCKS AN EXACT MATCH (four independent walls, none fixable
// without running the compiler):
//   1. PS/GPR allocator.  The want keeps the pair vectors in f0..f13 with
//      aggressive reuse (ps_mr f9,f0 then the same pair stored twice), while
//      named C locals force extra copies and different frD choices.
//   2. Store interleaving in the post-acos tail (0x800A8B34-0x800A8CE4): the
//      want writes 0x30/0x38 twice (0x800A8B94/0x800A8B9C then
//      0x800A8BFC/0x800A8C04) before the 0x40/0x48 pair lands at
//      0x800A8C64/0x800A8C6C; the body models two independent cross products
//      (0x30/0x38 then 0x40/0x48) and so cannot reproduce that interleaving.
//   3. Round-trips through the caller frame (48(r1)/60(r1)/80(r1)/96(r1)/
//      112(r1)/120(r1)/128(r1)/136(r1)/144(r1)/152(r1)/160(r1)/168(r1)/
//      176(r1)/184(r1)/192(r1)/208(r1)) exist so a pair can gain a literal
//      high half (lfs 1.0f + stfs into the hi word).  In C those pairs have to
//      be real locals; the compiler decides their homes, and the want's
//      choices (and its 0x108 frame) are not reproducible from the source
//      shapes available here.
//   4. The five `return 2` guards read the low half after `ps_res(ps_rsqrte)`
//      (0x800A8A14/0x800A8A44) — modelled, but the guard's 0x80(r1) spill
//      order is allocator-dependent.
// Net: the C is structurally faithful and semantically complete (all guards,
// the acos clamp, the final vB8->vB0 rotation and both cross products are
// present), but the PS register/stack allocation is the known project wall;
// a byte-exact body needs a compiler-in-the-loop allocator search, not more
// hand-shaping.