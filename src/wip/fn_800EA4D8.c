// WIP DRAFT (non-matching) — hand-rebuilt from the PS disassembly.
// family=m2c range=0x800EA4D8-0x800EA7D0 size=760B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// === PARKED (2026-10-01) — NEAR 51.6%, object .text 760B ==
//
// SCORE: NEAR 51.6% (98/190 masked words), object .text = 0x2F8 = 760B == the
// want size EXACTLY. Up from the m2c draft's 1.6% / 468B.
//
// SEMANTICS RECOVERED (all of it, want-verified instruction by instruction):
//   collision-resolve helper. arg1/arg2 = 4-float vecs; arg3 = struct with
//   pair fields @0x20/@0x28; arg0 = struct with pairs @0x28/@0x30/@0x50/@0x58;
//   arg4 = out vec4. Steps: b.y>c.y -> 0; d=c.xy-b.xy, e=c.zw-b.zw (both
//   parked in a volatile pair array), normalise by 1/sqrt(|e|^2+|d|^2) when
//   the magnitude > 0, bail if the normalised y < 0.995, then a dot product
//   vs cosf(qbFloat * PI/180), then three lerp-ish blocks using qb floats
//   0x5296E3FD / 0x35B3BBDA / 6.0, each preceded by GetStructure(0x6775E538,0)
//   CHAINED as GetFloat's arg0 (recipes 6a/6e-32/23 — the chained call is why
//   there is no `mr r3` between the two `bl`s). Tail: fn_80107B20(&V[6],1,0),
//   refcount shuffle on X[0], return 0/1.
//   lbl_8029AC14=0.0f, AC18=1.0f, AC1C=0.995f, AC20=deg2rad, AC24=6.0f,
//   lbl_8029ABB0={0.0f,0.0f} (all hand-decoded from the lis/addi pairs).
//
// LOAD-BEARING FIXES (in order of value):
//   1. `typedef union {__ps_t p; f32 w[2];} S;` + `volatile S V[]/W[]` (the
//      promoted fn_801B19DC idiom). 32 psq_l + 26 psq_st + all ps_* opcodes
//      reproduce from this and NOTHING else — the m2c scalar draft emits 0.
//   2. Local frame solved: `volatile S V[27]` @0x08, `s32 X[6]` @0xE0,
//      `f32 o[3]` @0xF8, `volatile S W[6]` @0x108. That reproduces every
//      stack displacement AND the 0x158 frame / Gsave 0x138 / stfd f31 0x150
//      (the W[6] tail is what buys the last +8; W[5] lands 0x150). Worth a
//      lot: frame, stmw, and all ~30 displacement words.
//   3. Per-value temps instead of re-reading the volatile array. GCC does NOT
//      forward a volatile store to the following volatile load (probed), so
//      `V[0].p = muls0(V[0].p, r)` costs an extra psq_l; going through a temp
//      keeps the value in a register exactly like want. Also: read W[k].p ONCE
//      into a temp — reading it twice emits two psq_l where want emits one
//      psq_l + one ps_mr.
//   4. `register volatile S *pv __asm__("r28") = &V[0];` assigned late, and
//      the a/d/e parameter pins REMOVED. That combination is what produces
//      want's whole prologue (mr r27,r4 / mr r26,r3 / mr r29,r6 / mr r31,r7 /
//      addi r28,r1,8) — with a/d/e pinned, GCC puts b in r31 and emits an
//      extra `mr r27,r31` (-24 pts). +14 pts.
//   5. `register f32 ang __asm__("fr31") = ang2;` with a pinned fr13 temp
//      gives want's `lfs f13; fmr f31,f13` instead of a folded `lfs f31`;
//      same trick with fr12 for the ps_mr feeding fcmpu, and fr13 for the
//      scalar fed to ps_muls0. Each pin bought one exact instruction word.
//
// RESIDUAL / WHY IT IS STUCK:
//   The instruction MULTISET is now identical to want (checked with a
//   register-normalised census: 32 psq_l, 26 psq_st, 4 ps_mr, 12 lfs, 4 stfs,
//   0 differences). Every branch addend also matches (7x REL14 + 1x REL24
//   intra-.text, verified by hand against want's targets — the masked compare
//   hides this, §6bw/§6bq). So the front end + expand are RIGHT and the
//   blocker is below it: (a) FPR colouring — want puts the first pair-difference
//   web in f0 and the second in f11, GCC picks f11/f10 and then cycles
//   f13/f12/f0 for the argument pair loads; (b) intra-BB scheduling — want
//   hoists ALL FOUR arg pair loads above both ps_subs, GCC interleaves
//   (2 loads, sub, 2 loads, sub). Note 14 of the ~92 remaining diffs are
//   unreachable by construction: 8 REL14 (mask keeps the top 16 bits, which
//   hold a real displacement in want and a 0 placeholder in the object) plus
//   6 `lis` with ADDR16_HA (mask keeps the page field) => practical ceiling
//   ~92.6%.
//
//   Measured and rejected (each = no change or worse):
//     * `register __ps_t t __asm__("fr0")` / `u`->fr11: -40 pts, size 772B —
//       pinning a multiply-assigned web makes GCC spill through r0/r1 `lq`.
//     * pinning the parameter b to r27 directly: extra `mr r27,r31`, -4 pts.
//     * pinning the 0.0f constant to fr13: -0.5 pts.
//     * `-fno-schedule-insns` (-17), `-fno-schedule-insns2` (-6); the other
//       ten -fno-* flags are exactly inert.
//     * 4 hand-chosen source orders of the two difference statements and 4
//       orders of the local declarations: bit-identical output (GCC's local
//       scheduler normalises the block).
//   Not tried: RTL-level ordering constraints / a manual reload pass.
//
// INLINE ASM DISCLOSURE: 4 emitted instructions, all `ps_mr` (one for the
// fcmpu operand copy, three for the W[2]/W[3]/W[4] scalar-pair copies) =
// 4/190 = 2.1% of the body, all of them register-to-register moves that plain
// C cannot express (see the `__builtin_ps_mr` ICE at optabs.c:4116).
// No private .rodata in the object.
#include "types.h"

extern f32 lbl_8029AC14;
extern f32 lbl_8029AC18;
extern f32 lbl_8029AC1C;
extern f32 lbl_8029AC20;
extern f32 lbl_8029AC24;
extern __ps_t lbl_8029ABB0[15];

s32 GetStructure(s32 arg0, s32 arg1);
s32 GetFloat(void *arg0, s32 arg1, f32 *arg2, s32 arg3);
f32 cosf(f32 arg0);
s32 fn_8010794C(void *arg0);
s32 fn_80107B20(void *arg0, s32 arg1, s32 arg2);
void CObject_RemoveRefLink(void *arg0, void *arg1);

typedef union {
    __ps_t p;
    f32 w[2];
} S;

typedef union {
    __ps_t p[2];
    f32 f[4];
} Vec4;

typedef struct {
    char pad0x00[0x28];
    __ps_t a40;
    __ps_t a48;
    char pad0x50[0x18];
    __ps_t a80;
    __ps_t a88;
} Ent;

typedef struct {
    char pad0x00[0x20];
    __ps_t d32;
    __ps_t d40;
} Seg;

typedef struct {
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t p3;
} Out;

s32 fn_800EA4D8(Ent *a0, Vec4 *b0, Vec4 *c, Seg *d0, Out *e0) {
    Ent *a = a0;
    Vec4 *b = b0;
    Seg *d = d0;
    Out *e = e0;
    volatile S V[27];
    s32 X[6];
    f32 o[3];
    volatile S W[6];
    __ps_t t;
    __ps_t u;
    __ps_t x;
    __ps_t y;
    register volatile S *pv __asm__("r28");
    register __ps_t w10 __asm__("fr10");
    __ps_t w;
    __ps_t r;
    __ps_t z;
    f32 magx;
    register __ps_t mc __asm__("fr12");
    register f32 ang2 __asm__("fr13");
    register f32 ang __asm__("fr31");
    s32 ret;

    if (b->f[1] > c->f[1]) {
        return 0;
    }
    t = __builtin_ps_sub(c->p[1], b->p[1]);
    V[1].p = t;
    u = __builtin_ps_sub(c->p[0], b->p[0]);
    V[0].p = u;
    pv = &V[0];
    t = pv[1].p;
    t = __builtin_ps_mul(t, t);
    t = __builtin_ps_merge00(t, lbl_8029ABB0[0]);
    t = __builtin_ps_madd(u, u, t);
    t = __builtin_ps_sum0(t, t, t);
    __asm__("ps_mr %0, %1" : "=f"(mc) : "f"(t));
    __asm__("" : "=f"(magx) : "f"(mc));
    if (magx > lbl_8029AC14) {
        r = __builtin_ps_rsqrte(t);
        W[0].p = r;
        z = __builtin_ps_muls0(u, r);
        V[0].p = z;
        W[0].w[1] = lbl_8029AC18;
        pv[1].p = __builtin_ps_mul(pv[1].p, W[0].p);
    }
    if (V[0].w[1] < lbl_8029AC1C) {
        return 0;
    }
    t = __builtin_ps_mul(a->a88, d->d40);
    t = __builtin_ps_merge00(t, lbl_8029ABB0[0]);
    t = __builtin_ps_madd(a->a80, d->d32, t);
    t = __builtin_ps_sum0(t, t, t);
    W[1].p = t;
    ang2 = W[1].w[0];
    ang = ang2;
    GetFloat((void *)GetStructure(0x6775E538, 0), 0x456F216D, &o[0], 1);
    if (ang < cosf(o[0] * lbl_8029AC20)) {
        return 0;
    }
    GetFloat((void *)GetStructure(0x6775E538, 0), 0x5296E3FD, &o[1], 1);
    W[2].w[0] = o[1];
    w = W[2].p;
    __asm__("ps_mr %0, %1" : "=f"(w10) : "f"(w));
    t = __builtin_ps_muls0(pv[1].p, w10);
    x = __builtin_ps_muls0(V[0].p, w10);
    V[5].p = t;
    V[4].p = x;
    y = __builtin_ps_add(b->p[0], x);
    x = __builtin_ps_add(b->p[1], t);
    e->p0 = y;
    e->p1 = x;
    V[2].p = y;
    V[3].p = x;
    GetFloat((void *)GetStructure(0x6775E538, 0), 0x35B3BBDA, &o[2], 1);
    W[3].w[0] = o[2];
    w = W[3].p;
    __asm__("ps_mr %0, %1" : "=f"(w10) : "f"(w));
    t = __builtin_ps_muls0(d->d32, w10);
    u = __builtin_ps_muls0(d->d40, w10);
    V[2].p = t;
    V[3].p = u;
    t = __builtin_ps_sub(e->p0, t);
    u = __builtin_ps_sub(e->p1, u);
    e->p0 = t;
    e->p1 = u;
    fn_8010794C(&V[6]);
    W[4].w[0] = lbl_8029AC24;
    V[7].p = a->a48;
    w = W[4].p;
    __asm__("ps_mr %0, %1" : "=f"(w10) : "f"(w));
    t = __builtin_ps_muls0(d->d32, w10);
    u = __builtin_ps_muls0(d->d40, w10);
    V[4].p = t;
    V[5].p = u;
    t = __builtin_ps_sub(e->p0, t);
    u = __builtin_ps_sub(e->p1, u);
    V[9].p = u;
    V[8].p = t;
    V[2].p = t;
    V[6].p = a->a40;
    V[3].p = u;
    ret = fn_80107B20(&V[6], 1, 0);
    if (ret != 0) {
        if (X[0] != 0) {
            CObject_RemoveRefLink((void *)X[0], &X[0]);
            X[0] = 0;
        }
        return 0;
    }
    e->p2 = d->d32;
    e->p3 = d->d40;
    if (X[0] != 0) {
        CObject_RemoveRefLink((void *)X[0], &X[0]);
        X[0] = ret;
    }
    return 1;
}