// WIP DRAFT (non-matching) — paired-single (PS) reconstruction
// family=m2c range=0x800A74A8-0x800A7910 size=1128B
// PARKED 2026-10-06. This slice re-typed two
// argument structs whose field offsets were provably wrong (the PS core is
// otherwise the prior best reconstruction; not re-measured here, no compiler):
//   * Arg0: retail pair1/pair2/scalar/flag sit at 0x418/0x420/0x428/0x42c
//     (psq_l 1048(r3), psq_l 1056(r3), lfs 0x428(r3), lwz 0x42c(r3)).  The old
//     layout packed pair1 straight after index, i.e. 8 bytes low
//     (pair1 0x410 .. flag 0x424), so every field past `index` was read from
//     and written to the wrong address.  Added the 8-byte pad at 0x410.
//   * Arg1: retail stores a@0, b@8, c@0xc — c is the HIGH word of the pair at
//     +8, not a separate f32 at +0x10.  Modelled with a PS2 union so the
//     overlap is declared rather than cast.
// Blocker: paired-single body; object 620B vs 1128B — a redraft needs the full
// tools/ps_disasm.py decode of the PS core (92 `.word op4` operations).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// RECONSTRUCTED 2026-09-26: 3/155 got-words (1.9%), got 620B vs retail 1128B
// (tools/ps_diff.py). The m2c draft modelled this PS-heavy function with
// plain f32 locals; it is rewritten with __ps_t + __builtin_ps_* so the
// paired-single ops (ps_sub/ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte/
// ps_res/ps_muls0/ps_merge10/ps_add) are at least the right OPCODE CLASS.
//
// WHAT THE FUNCTION DOES (semantics recovered from the disasm):
// A sliding-window paired-single filter over a 64-entry ring buffer of
// 16-byte entries (2 PS pairs each) at arg0+0, walked BACKWARDS from
// arg0+(index<<4)+8 with stride -16, wrapping at arg0+0x3f8 (entry 63).
// Window slots A=sp+8, B=sp+0x10 (current), C=sp+0x18, D=sp+0x20 (next).
// Each of the count-1 iterations: f13=D-B; f0=f13*f13; f12=C-A;
// f0=merge00(f0,const@0x80298124); f0=madd(f12,f0,f12); f0=sum0(f0,f0);
// f0=rsqrte(f0); f0=res(f0)  (a 1/sqrt reduction); if (f9<=f0) break;
// A=C; f9-=f0; B=D; advance ring. After the loop: if (f0<=lbl_8029815C)
// return; else f0 = lbl_80298160 / -f0, then a long PS tail writes arg1
// (PS@0, PS@8, f32@0xc) and, on the arg0->flag!=0 path, arg2's six PS
// pairs (0x0..0x28) + f32@0x2c; the flag==0 path writes arg2's f32 slots
// (0x10,0x14,0x18,0x1c,0x24,0x2c) + PS@0,PS@8 instead.
//
// WHY IT DOESN'T MATCH (precise residual): the compiler RESTRUCTURES the
// source — got frame 0xe8 vs retail 0xc0 (+40B of PS temps/alignment), count
// homed in r11 vs retail r8, and the loop head moved (got 0x800a758c vs
// retail 0x800a750c). Every sp offset shifts, so 152/155 words differ. The
// PS opcode CLASSES are now correct (the right builtins are used) but the
// register allocation, frame layout, and instruction scheduling do not
// reproduce the original C's exact structure. The two flag branches
// (0x800A7630-0x800A77EC / 0x800A77F0-0x800A7904, ~170 insns of dense PS
// math with read-back-after-write on arg2) are the largest unmatched block.
// NOTE: scalar-vs-__ps_t compares (f9<=f0) ICE cc1 (optabs.c:3515); the
// draft uses a PU union lane-0 read to dodge it, which is why the loop's
// fcmpu target register differs from retail's f0.
#include "types.h"
#include "structs.h"

extern f32 lbl_8029815C;
extern f32 lbl_80298160;
extern f32 lbl_80298164;
extern __ps_t lbl_80298124;

typedef struct {
    char _pad[0x408];
    s32 count;       /* 0x408 (lwz) */
    s32 index;       /* 0x40c (lwz) */
    char _pad2[0x8]; /* 0x410..0x417 unused; retail pair1 starts at 0x418 */
    __ps_t pair1;    /* 0x418 (psq_l 1048(r3)) */
    __ps_t pair2;    /* 0x420 (psq_l 1056(r3)) */
    f32 scalar;      /* 0x428 (lfs) */
    s32 flag;        /* 0x42c (lwz) */
} Arg0;

typedef union {
    __ps_t pair;
    struct {
        f32 lo;
        f32 hi;
    } f;
} PS2;

/* Retail writes arg1+0 (psq_st a), arg1+8 (psq_st b) and arg1+0xc (stfs c):
   c is the high word of the 8-byte pair at +8, i.e. it OVERLAPS b — it is not
   a separate f32 at +0x10. */
typedef struct {
    __ps_t a; /* 0x0 */
    PS2 b;    /* 0x8, with c == b.f.hi at 0xc */
} Arg1;

typedef union {
    struct { __ps_t a, b, c, d, e, f; } ps;
    f32 raw[12];
} Arg2;

typedef union {
    __ps_t p;
    f32 w[2];
} PU;

typedef struct {
    char _pre[8];
    __ps_t A;
    __ps_t B;
    __ps_t C;
    __ps_t D;
    __ps_t s28;
    __ps_t s30;
    __ps_t s38;
    __ps_t s40;
    __ps_t s48;
    __ps_t s50;
    __ps_t s58;
    __ps_t s60;
    __ps_t s68;
    PU d70;
    PU d78;
    char _post[0x40];
} Locals;

void fn_800A74A8(Arg0 *arg0, Arg1 *arg1, Arg2 *arg2) {
    Locals L;
    __ps_t f0, f13, f12, f11, f10, f9ps, f6;
    f32 f9, f7, f8;
    s32 r9, r0;
    __ps_t *r11;

    if (arg0->count <= 0) return;
    f0 = arg0->pair1;
    L.A = f0;
    L.B = arg0->pair2;
    r11 = (__ps_t *)((char *)arg0 + (arg0->index << 4) + 8);
    L.C = r11[0];
    L.D = r11[1];
    f9 = arg0->scalar;
    r9 = arg0->count - 1;
    r0 = arg0->index;

    do {
        f13 = __builtin_ps_sub(L.D, L.B);
        f0 = __builtin_ps_mul(f13, f13);
        L.s40 = f13;
        L.s30 = f13;
        f12 = __builtin_ps_sub(L.C, L.A);
        f0 = __builtin_ps_merge00(f0, lbl_80298124);
        L.s38 = f12;
        f0 = __builtin_ps_madd(f12, f0, f12);
        f0 = __builtin_ps_sum0(f0, f0, f0);
        f0 = __builtin_ps_rsqrte(f0);
        f0 = __builtin_ps_res(f0);
        L.s68 = f0;
        {
            PU u;
            u.p = L.s68;
            if (f9 <= u.w[0]) break;
        }
        L.A = L.C;
        f9 -= f0;
        L.B = L.D;
        if (r9 == 0) break;
        r11 -= 2;
        r0 -= 1;
        if (r0 < 0) {
            r11 = (__ps_t *)((char *)arg0 + 0x3f8);
            r0 = 63;
        }
        L.C = r11[0];
        L.D = r11[1];
        r9 -= 1;
    } while (1);

    f7 = lbl_8029815C;
    {
        PU u;
        u.p = f0;
        if (u.w[0] <= f7) return;
    }
    f0 = __builtin_ps_neg(f0);
    f8 = lbl_80298160;
    L.d78.w[0] = f9;
    f0 = f8 / f0;
    f9ps = L.s30;
    f11 = L.d78.p;
    f10 = L.s28;
    f12 = L.A;
    L.d70.w[0] = f0;
    f13 = f11;
    f6 = L.d70.p;
    f11 = L.B;
    f0 = f6;
    f9ps = __builtin_ps_muls0(f9ps, f0);
    f10 = __builtin_ps_muls0(f10, f0);
    L.s40 = f9ps;
    f0 = __builtin_ps_muls0(f9ps, f13);
    L.s38 = f10;
    f13 = __builtin_ps_muls0(f10, f13);
    L.s60 = f0;
    L.s58 = f13;
    f11 = __builtin_ps_sub(f11, f0);
    arg1->b.pair = f11;
    f12 = __builtin_ps_sub(f12, f13);
    arg1->b.f.hi = f8;
    arg1->a = f12;
    L.s48 = f12;
    r0 = arg0->flag;
    L.s50 = f11;
    if (r0 == 0) goto branch0;

    f11 = L.s50;
    f13 = L.s58;
    f10 = L.s28;
    f12 = L.s48;
    f0 = L.s60;
    f9ps = L.s40;
    f13 = __builtin_ps_merge10(f13, f12);
    f11 = __builtin_ps_merge10(f11, f10);
    f10 = __builtin_ps_mul(f11, f12);
    f13 = __builtin_ps_mul(f10, f13);
    f12 = __builtin_ps_merge00(f12, f12);
    f0 = __builtin_ps_merge00(f0, f0);
    f13 = __builtin_ps_sub(f13, f11);
    f12 = __builtin_ps_merge00(f12, f13);
    f0 = __builtin_ps_sub(f0, f12);
    arg2->ps.f = f11;
    arg2->ps.e = f13;
    arg2->ps.d = f12;
    f11 = L.B;
    f13 = L.s58;
    f12 = L.s48;
    f0 = L.s60;
    f9ps = L.s40;
    f13 = __builtin_ps_merge10(f13, f12);
    f11 = __builtin_ps_merge10(f11, f10);
    f10 = __builtin_ps_mul(f11, f12);
    f13 = __builtin_ps_mul(f10, f13);
    f12 = __builtin_ps_merge00(f12, f12);
    f0 = __builtin_ps_merge00(f0, f0);
    f13 = __builtin_ps_sub(f13, f11);
    f12 = __builtin_ps_merge00(f12, f13);
    f0 = __builtin_ps_sub(f0, f12);
    arg2->ps.c = f13;
    arg2->ps.b = f12;
    arg2->ps.a = f0;
    arg2->ps.f = f13;
    arg2->ps.e = f12;
    goto done;

branch0:
    f8 = lbl_80298160;
    f0 = L.s28;
    f11 = L.s60;
    f13 = L.s58;
    f10 = L.s28;
    f12 = L.s48;
    f13 = __builtin_ps_merge10(f13, f12);
    f11 = __builtin_ps_merge10(f11, f10);
    f10 = __builtin_ps_mul(f11, f12);
    f13 = __builtin_ps_mul(f10, f13);
    f12 = __builtin_ps_merge00(f12, f12);
    f0 = __builtin_ps_merge00(f0, f0);
    f13 = __builtin_ps_sub(f13, f11);
    f12 = __builtin_ps_merge00(f12, f13);
    f0 = __builtin_ps_sub(f0, f12);
    arg2->raw[9] = f7;
    arg2->raw[4] = f7;
    arg2->raw[6] = f7;
    arg2->raw[7] = f8;
    arg2->raw[5] = f8;
    arg2->raw[11] = f8;
    arg2->ps.b = f12;
    arg2->ps.a = f13;

done:
    return;
}

// NOTE: the only body-level change this slice made is the two struct-layout
// corrections documented at the top (Arg0 0x418/0x420/0x428/0x42c, Arg1 c at
// 0xc).  Everything else is the prior best reconstruction.  Residual: the PS
// core is still short (620B vs 1128B) and the frame is 0xe8 vs retail 0xc0,
// i.e. ngccc spills the 92 undecoded op4 PS temporaries that psq_l/psq_st
// cannot express; full match needs tools/ps_disasm.py plus a rewrite that keeps
// the PS values in the retail scratch slots instead of named locals.
