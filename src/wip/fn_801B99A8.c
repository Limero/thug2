// WIP DRAFT (non-matching) — hand reconstruction from PS disasm
// family=m2c range=0x801B99A8-0x801B9BFC size=596B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// PARKED 2026-10-05: DIFF, best 36.43% strict / got 560B vs want 596B
// (tools/venv/bin/python tools/score_wip.py 0x801B99A8 src/wip/fn_801B99A8.c
//  "-mps-float"). Was an m2c stub at 7.55% / 212B; the whole body below is a
// real reconstruction. EXACT so far: prologue+epilogue (`stwu -0x78`,
// `stw r31,0x74`, `stw r0,0x7c`, r31-only save area), the entire call chain
// through `bl 0x8009fdd8`, and the frame layout (t@0x08, c@0x18, b@0x28,
// SN_PS_type s@0x68). Semantic facts recovered (all verified against want):
//  * `fn_800F05C0` returns s32 — its result stays in r3 and is the same stale
//    r3 that `fn_800F0838` receives, so `t0 = f05c0(f0f84(a->0x58,1),0)` +
//    `a->0x5C = t0` + `f0838(t0, a+0x78)` is the only shape that emits
//    `[mr r0,r3][stw r0,0x5c][bl]` (a void callee makes GCC park t0 in r30).
//  * `fn_800A8018` has THREE args; arg0 is `fn_800A7F38()`'s return, so it must
//    be written `f8018(f800A7F38(), a->unk0xC, a->unk5C)` (nested call fills r3).
//  * dot/normalize idiom (matched twin src/fn_8006AC08.c:90):
//    `s.ps = sum0(..); if (s.flt.hi > k1) { s.ps = rsqrte(s.ps); s.flt.lo = k2;
//     rd = s.ps; }` is the ONLY spelling that gives want's `ps_mr`+`fcmpu` with
//    NO spill — `(f32)psvar` and `mag = sum0(..)` both emit a `psq_st` temp.
//  * globs: thr = lbl_802AC268 (0.0f), eps = lbl_802AC26C (1.0f), pair K =
//    lbl_802ABFB8 ({0.0f,0.0f}); `(f32)lbl_802AC268`-style casts and any local
//    `mag` spill, so keep the SN_PS_type union `s`.
// REMAINING RESIDUAL (want 149 words, got 140):
//  1. 11-word empty-countdown window missing at 0x801B9AA4..0x801B9ACC: retail
//     loads count 4 into r0, loads the 0xC field into r11, derives r1+8 into
//     r9, paired-single-loads 32(r1) into f0, and moves r0 to the count
//     register; then paired-single-stores f13 to 8(r1), copies r9 to r10,
//     paired-single-stores f0 to 8(r9), and bumps r11 by 0xd0; finally it
//     derives r1+0x28 into r3 and decrements-and-branches to itself
//     (self-targeting, displacement 0 — doc 30).
//     `for (i=4;i!=0;i--){}` and `...{__asm__ volatile("");}` BOTH emit the
//     li/mtctr + sunk window content but a FORWARD-displaced bdnz, and the
//     countdown loop makes GCC hoist the last loop's base into r30
//     (prologue -> `stmw r30,0x70`, +4 words lost): 33.6% vs 36.4%. Left out.
//     `.long 0x42000000` (doc 30 promotion-safe form) is the untried escape.
//  2. FPR f12/f13 role swap, 10 words: want `ps_sub f12,f12,f13` (dx in the
//     FIRST operand's reg) + `ps_mr f13,f0`/`fcmpu cr0,f13,f10`/`lfs f13`/
//     `stfs f13,0x6c` scratch in f13; got swaps the pair wholesale.
//     Ruled out: `register __ps_t dx __asm__("fr12")` (silently ignored —
//     pins only bind on load-fed webs), dx/dy statement-order swaps,
//     dy-first + store-order swap, hoisting `k1`/`pk` above the ps_subs.
//  3. `psq_l f11,K` (pk) is scheduled one slot after `psq_l f12,0x78(r31)`;
//     want loads pk first. Source order of the pk/k1 statements is a no-op.
//  4. t-block: want stores 0x08 TWICE (2nd overwrites 1st = dead) via two
//     different address forms (8(r1), 8(r9)) and reloads it for b[4]/b[5]
//     (`psq_l f0,8(r1)`, `psq_l f13,8(r10)`); got DCEs the dead store, emits
//     one `ps_mr f12,f0` and forwards the register into both stores (t and b
//     are fields of one struct so GCC proves no alias). Tried: `volatile PU
//     t[2]` (keeps both stores but all 4 accesses go r1-relative, order flips);
//     `__asm__("" : : "m"(fr.t[0].ps))` DSE keep-alive (recipes 192) DOES
//     reproduce the dead store (142B object, 35.2%) but costs ~1% index-aligned
//     and needs inline asm, so the pure-C form is kept.
#include "types.h"
#include "dolphin/SN_PS.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_800F0F84(s32, s32);
extern s32 fn_800F05C0(void *, s32);
extern void fn_800F0838(void *, void *);
extern void fn_801B6A60(void *);
extern s32 fn_800A7F38(void);
extern s32 fn_800A8018(void *, void *, s32);
extern void *GetChecksum_3(void *, s32);
extern void fn_80004518(s32, s32);
extern float lbl_802AC268[1];
extern float lbl_802AC26C[1];
extern char lbl_802ABFB8[];

typedef union {
    __ps_t ps;
    f32 f[2];
} PU;

/* the motion-context object this QB handler writes through */
typedef struct {
    char pad00[0xC];
    void *unk0xC;
    char pad10[0xC];
    s32 unk1C;
    char pad20[4];
    s32 unk24;
    char pad28[0x30];
    s32 unk58;
    s32 unk5C;
    char pad60[8];
    __ps_t v68;
    __ps_t v70;
    __ps_t v78;
    __ps_t v80;
    char pad88[0x18];
    s32 unkA0;
    char padA4[0xA4];
    __ps_t f148;
    __ps_t f150;
    __ps_t f158;
    __ps_t f160;
    __ps_t f168;
    __ps_t f170;
    __ps_t f178;
    __ps_t f180;
    __ps_t f188[10];
} MOTION;

s32 fn_801B99A8(MOTION *arg0) {
    struct {
        PU t[2];
        PU c[2];
        PU b[8];
    } fr;
    SN_PS_type s;
    __ps_t pk, t3, ee, rr, rd, dx, dy;
    f32 k1;
    s32 t0;
    s32 i;
    __ps_t *m1, *m2, *m3;

    t0 = fn_800F05C0(fn_800F0F84(arg0->unk58, 1), 0);
    arg0->unk5C = t0;
    fn_800F0838((void *)t0, (char *)arg0 + 0x78);
    fn_801B6A60(arg0);
    arg0->unk24 |= 2;
    arg0->unkA0 = fn_800A8018(fn_800A7F38(), arg0->unk0xC, arg0->unk5C);
    *(s32 *)((char *)GetChecksum_3(arg0->unk0xC, QB_MOTION) + 0x1C) |= 0x10;
    dx = __builtin_ps_sub(arg0->v78, arg0->v68);
    fr.c[0].ps = dx;
    dy = __builtin_ps_sub(arg0->v80, arg0->v70);
    fr.c[1].ps = dy;
    k1 = lbl_802AC268[0];
    pk = *(__ps_t *)&lbl_802ABFB8[0];
    t3 = __builtin_ps_mul(dy, dy);
    t3 = __builtin_ps_merge00(t3, pk);
    ee = __builtin_ps_madd(dx, dx, t3);
    s.ps = __builtin_ps_sum0(ee, ee, ee);
    if (s.flt.hi > k1) {
        rr = __builtin_ps_rsqrte(s.ps);
        s.ps = rr;
        s.flt.lo = lbl_802AC26C[0];
        rd = s.ps;
        fr.c[0].ps = __builtin_ps_muls0(dx, rr);
        fr.c[1].ps = __builtin_ps_mul(dy, rd);
    }
    m1 = (__ps_t *)arg0->unk0xC;
    fr.b[0].ps = m1[26];
    fr.b[1].ps = m1[27];
    fr.b[2].ps = m1[28];
    fr.b[3].ps = m1[29];
    fr.b[4].ps = m1[30];
    fr.b[5].ps = m1[31];
    fr.b[6].ps = m1[32];
    fr.b[7].ps = m1[33];
    fr.t[0].ps = fr.c[0].ps;
    fr.t[0].ps = fr.c[1].ps;
    fr.b[4].ps = fr.t[0].ps;
    fr.b[5].ps = fr.t[0].ps;
    fn_80004518((s32)&fr.b[0], 2);
    m2 = (__ps_t *)arg0->unk0xC;
    m2[26] = fr.b[0].ps;
    m2[27] = fr.b[1].ps;
    m2[28] = fr.b[2].ps;
    m2[29] = fr.b[3].ps;
    m2[30] = fr.b[4].ps;
    m2[31] = fr.b[5].ps;
    m2[32] = fr.b[6].ps;
    m2[33] = fr.b[7].ps;
    arg0->f148 = fr.b[0].ps;
    arg0->f150 = fr.b[1].ps;
    arg0->f158 = fr.b[2].ps;
    arg0->f160 = fr.b[3].ps;
    arg0->f168 = fr.b[4].ps;
    arg0->f170 = fr.b[5].ps;
    arg0->f178 = fr.b[6].ps;
    arg0->f180 = fr.b[7].ps;
    m3 = (__ps_t *)arg0->unk0xC;
    fr.c[0].ps = m3[11];
    fr.c[1].ps = m3[12];
    {
        __ps_t *d = arg0->f188;
        for (i = 5; i != 0; i--) {
            d[0] = fr.c[0].ps;
            d[1] = fr.c[1].ps;
            d += 2;
        }
    }
    return 1;
}
// RE-TRIAGE 2026-10-12: PS recon at 36.4% (560/596B); needs PS-idiom work, out of round scope; no body change.
