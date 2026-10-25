// WIP DRAFT (non-matching) — reconstructed from the retail bytes by hand
// (tools/want_dis.py + tools/ps_diff.py view); the previous body was the
// uncorrected m2c skeleton (DIFF 6.5%, 368B object vs 912B want).
// Semantics SOLVED — see the type/prototype notes inline.
// PARKED 2026-10-05 (w_801B3EE8): best 34.2% (DIFF, reloc-masked, index
// aligned), object EXACTLY 912B = want, frame EXACTLY -0x88. Residual is
// register/FPR allocation + two missing compiler spill slots, not semantics;
// full note at the bottom of this file.
// family=m2c range=0x801B3EE8-0x801B4278 size=912B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct { char p0[0xC]; void *unk0xC; char p10[0x18]; s32 unk0x28; char p2C[0x3C];
                 __ps_t unk0x68; __ps_t unk0x70; char p78[0x2C]; f32 unk0xA4; } A0;
typedef struct { char p0[0x18]; s32 unk0x18; char p1C[0x3C]; __ps_t unk0x58; __ps_t unk0x60; } SCR;
typedef struct { char p0[0x58]; __ps_t unk0x58; __ps_t unk0x60; } PED;
typedef struct { char p0[0x30]; f32 unk0x30; } MOT;
typedef union { __ps_t p; f32 w[2]; } S8;
typedef struct { S8 a; S8 b; union { struct { f32 x, y, z, w; } f; struct { __ps_t xy, zw; } p; } c; } WK;
typedef struct { S8 a; S8 b; } OLDP;

extern char lbl_80305EAC[];
extern f32 lbl_80305F2C;
extern f32 lbl_80305F34;
extern char lbl_802ABFB8[];
extern char lbl_802AC03C[];
extern f64 lbl_802AC040;
extern f32 lbl_802AC048;
extern f32 lbl_802AC04C;
extern f32 lbl_802AC050;

void *fn_801745B4(void *);
MOT *GetChecksum_3(void *, s32);
s32 fn_8009E3D0(void *, s32, s32 *);
void fn_801B4404(void *, void *);
void *fn_80019D08(s32);
S8 *fn_80126EAC(S8 *);
void AddChecksum(S8 *, s32, s32);
void fn_801B3220(void *, s32, s32, void *);
void fn_8012701C(void *, s32);
void Script_RunScript(s32, s32, void *, s32, s32);
s32 fn_801B9444(void *, void *, s32, f32);
void fn_801B5BBC(void *);
void fn_801B7484(void *, void *);
void fn_800D9DB0(MOT *);

void fn_801B3EE8(A0 *arg0) {
    SCR *script;
    MOT *mot;
    PED *ped;
    S8 *o;
    volatile S8 A;
    volatile S8 B;
    volatile WK wk;
    OLDP old;
    s32 sp48;
    union { u32 w[2]; f64 d; } cvt;
    f32 sg;
    __ps_t t;

    script = (SCR *)fn_801745B4(*(void **)&lbl_80305EAC);
    if (script == 0) {
        return;
    }
    mot = (MOT *)GetChecksum_3(arg0->unk0xC, QB_MOTION);
    ped = (PED *)arg0->unk0xC;
    A.p = script->unk0x58 - ped->unk0x58;
    B.p = script->unk0x60 - ped->unk0x60;
    A.w[1] = *(f32 *)&lbl_802AC03C;
    B.w[1] = *(f32 *)&lbl_802AC03C;
    t = __builtin_ps_madd(A.p, A.p,
             __builtin_ps_merge00(__builtin_ps_mul(B.p, B.p),
                                  *(const __ps_t *)&lbl_802ABFB8[0]));
    sg = __builtin_ps_sum0(t, t, t);
    if (sg <= lbl_80305F2C) {
        fn_801B4404(arg0, (void *)&A);
        o = fn_80126EAC(fn_80019D08(8));
        AddChecksum(o, QB_GRABOBJID, script->unk0x18);
        fn_801B3220(arg0, QB_STATE_CHASECATCH, 0, o);
        if (o != 0) {
            fn_8012701C(o, 3);
        }
    } else {
        if (sg > lbl_80305F34) {
            goto run_script;
        }
        sp48 = 0;
        if (fn_8009E3D0(ped, QB_MAXHOMEDIST, &sp48) == 0) {
            goto cont;
        }
        if (sp48 <= 0) {
            goto cont;
        }
        wk.b.p = arg0->unk0x70 - ped->unk0x60;
        wk.a.p = arg0->unk0x68 - ped->unk0x58;
        t = __builtin_ps_madd(wk.a.p, wk.a.p,
                 __builtin_ps_merge00(__builtin_ps_mul(wk.b.p, wk.b.p),
                                      *(const __ps_t *)&lbl_802ABFB8[0]));
        sg = __builtin_ps_sum0(t, t, t);
        cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
        cvt.w[1] = (u32)(sp48 * sp48) ^ 0x80000000;
        if (sg >= (f32)(cvt.d - lbl_802AC040)) {
        run_script:
            Script_RunScript(QB_PED_UTILS_ENDPLAYERCHASE, 0, ped, 0, 0);
            return;
        }
    cont:
        wk.a.p = A.p;
        wk.b.p = B.p;
        if (fn_801B9444(arg0, (void *)&wk.a, 0, lbl_802AC048) != 0) {
            goto pause;
        }
        if (arg0->unk0x28 != QB_STATE_CHASE) {
            fn_801B3220(arg0, QB_STATE_CHASE, 0, 0);
        }
        mot->unk0x30 = lbl_802AC04C;
        t = __builtin_ps_madd(A.p, A.p,
                 __builtin_ps_merge00(__builtin_ps_mul(B.p, B.p),
                                      *(const __ps_t *)&lbl_802ABFB8[0]));
        t = __builtin_ps_sum0(t, t, t);
        sg = t;
        if (sg > *(f32 *)&lbl_802AC03C) {
            t = __builtin_ps_rsqrte(t);
            B.p = __builtin_ps_mul(B.p, t);
            A.p = __builtin_ps_muls0(A.p, t);
        }
        fn_801B5BBC(arg0);
        ped = (PED *)arg0->unk0xC;
        wk.a.p = ped->unk0x58;
        wk.b.p = ped->unk0x60;
        wk.c.f.x = A.w[0] * mot->unk0x30 * arg0->unk0xA4 + wk.a.w[0];
        wk.c.f.y = wk.a.w[1];
        wk.c.f.z = B.w[0] * mot->unk0x30 * arg0->unk0xA4 + wk.b.w[0];
        wk.c.f.w = lbl_802AC050;
        ped->unk0x58 = wk.c.p.xy;
        ped->unk0x60 = wk.c.p.zw;
        old.a.p = wk.a.p;
        old.b.p = wk.b.p;
        fn_801B7484(arg0, &old);
        fn_800D9DB0(mot);
    }
    return;
pause:
    if (arg0->unk0x28 != QB_STATE_CHASEPAUSE) {
        fn_801B3220(arg0, QB_STATE_CHASEPAUSE, 0, 0);
    }
}
// ---------------------------------------------------------------------------
// PARKED 2026-10-05 (w_801B3EE8) — best 34.2% masked, object EXACTLY 912B,
// frame EXACTLY -0x88. Was DIFF 6.5% / 368B (uncorrected m2c skeleton).
//
// Semantics are SOLVED (decoded from retail; every callee arity/return type
// checked against the promoted callees):
//   * lbl_80305EAC is a *pointer* global (deref, not the address) passed to
//     the 1-arg `fn_801745B4`; QB_MOTION=0x0A015E17 via lis+ori (bare literal
//     per recipes §174 — it is a compared/stored VALUE, not an address).
//   * A = script->[0x58] - ped->[0x58], B = script->[0x60] - ped->[0x60],
//     then A.y = B.y = *(f32*)lbl_802AC03C  (=> `psq_st` + one `stfs` each).
//   * mag = ps_sum0( ps_madd(A,A, ps_merge00(ps_mul(B,B), *(vec2*)lbl_802ABFB8)) )
//     — lbl_802ABFB8 is the {0,0} pair constant; THREE of these sites exist.
//   * `if (mag <= lbl_80305F2C /*3047.04f*/)` -> grab arm (CHASECATCH),
//     `else` -> the whole rest of the function (that if/else shape is what
//     produces retail's `fcmpu / cror cr0un,cr0eq,cr0lt / bns`).
//   * r31 in the else arm is `&A` (NOT the malloc'd object — the grab arm
//     returns first), so the 4 `psq_l/psq_st ...,8(r31)` sites are B, not o.
//   * int->double via the recipes §6j-1 cvt union (0x43300000 hi word,
//     `^0x80000000` lo word, then `- lbl_802AC040` == 2^52+2^31) -> the
//     `(f32)(dist*dist)` obfuscated compare. Recipe reproduced verbatim.
//   * working position is a 32-byte struct {vec2 a; vec2 b; f32 x,y,z,w} at
//     0x18(r1) — NOT a union (the pair views at 0x28/0x30 are read back with
//     `psq_l`, which a 16-byte union cannot express). `old` (the
//     fn_801B7484 out-param) is a separate 16-byte struct at 0x38(r1).
//
// RESIDUAL (150/228 words), all allocator-level, no semantic disagreement:
//  (1) 2 EXTRA CALLEE-SAVED GPRs -> `stmw r25,0x6c` vs want `stmw r27,0x74`
//      (7 saved vs 5). The two extras are exactly the cvt constants:
//      ngccc colours `xoris rX,r0,0x8000` (lo word) and `lis rY,0x4330`
//      (hi word) into callee-saved regs; want keeps both volatile (r0 / r11).
//      Tried and measured, all identical 34.21%: `register u32 lo __asm__("r0")`
//      + `hi __asm__("r11")` pins (ngccc 2.95 ignores them, picks r12/r11),
//      plain `u32 clo/chi` temporaries, splitting the cvt stores into two
//      statements (ngccc always emits hi-then-lo, want is lo-then-hi), and
//      removing the `ped`/`cvt` address-taken-ness. Dropping `ped` to a
//      volatile reload is what retail does (`lwz r5,0xc(r30)` appears TWICE
//      in want) and DOES free a register, but it shrinks the frame to -0x80
//      and scores 19.7% — the freed slot has to be re-filled by hand.
//  (2) WANT SPILLS SUMS #1/#3 TO STACK SLOTS 0x50 (psq_st) / 0x58+0x5c
//      (rsqrte pair + a dead `stfs 1.0f` to the pair's HIGH lane = the
//      `__ps_t`+`w[1]` volatile-union idiom of doc 81 §1). Ours keeps the
//      sums in FPRs and instead has ONE `stfs` home store for the `__ps_t`
//      temp (recipe 173: every `__ps_t` local reserves a slot). Adding a
//      `volatile S8 tmp8` for the rsqrte fixes the 0x58 pair but adds 8 bytes
//      and 2 more saved regs -> 21.9%.
//  (3) `ps_mr f0,f13` + `fcmpu` (want) vs `fcmpu` on the sum0 destination
//      register (ours): pure FPR-colour choice; a `f32 x = __ps_t_expr`
//      assignment is FREE in ngccc (same FPR, no instruction), so ngccc
//      never needs the copy. Confirmed with probes; `register __ps_t __asm__("fr13")`
//      does not change it.
//  (4) DUPLICATE `volatile` PAIR RELOADS: in the 3rd magnitude ours emits
//      `psq_l f13,16(r1)` + `psq_l f13,8(r1)` (A and B read twice) where
//      want reads each once. Making A/B non-volatile removes the reloads but
//      also the `psq_st 8(r1)` re-stores -> 7.9%. This is a real open lever:
//      want's 4 separate `8(r1)`/`16(r1)` loads at 4 different use sites with
//      only ONE store each is ngccc's own `__ps_t`-local behaviour; we could
//      not reproduce it with either `volatile` or plain locals.
//  (5) `addi r10,r1,8` (want, hoisted early into r10->r31) vs our
//      `addi r4,r1,8` at the call site; `lwz r31,0xc(r30)` vs want's
//      re-load into r5. Both follow from (1).
// Flags swept: plain `-mps-float` is best. `-fno-schedule-insns` 6.4% (940B),
// `-fno-sched-interblock` / `-fno-sched-spec` == baseline.
// Ruled out: higher `sum0` arity / 0-args (ngccc ICEs: `__builtin_ps_sum0`
// needs all three args to be `__ps_t`); `__ps_t > f32` comparison (ICE
// optabs.c:3515 — must go through an `f32` copy); `__builtin_ps_mr` (ICE);
// `*(f32*)&__ps_t_var` (ICE expmed.c:1115 — use the union `w[]` view);
// inlining the whole `sum0(madd(...),...,...)` chain three times (988B, 1.2%).
// This is the same PS/FPR-frame + register-colour wall as the neighbouring
// fn_801B36FC / fn_801B4278 / fn_801B5DC4 / fn_801B5EE8 parks.
