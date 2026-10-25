// WIP DRAFT — hand re-match (PS normalise-and-store leaf)
// family=m2c range=0x8020D1F4-0x8020D2E4 size=240B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// DECODE (2026-10-02, ps_disasm + raw opcode-4 word decode; same PS idiom as
// fn_8020F938 / fn_801B19DC / fn_8020D530):
//   fn_8020D2E4(this, 1);                       // r3=this, r4=1, NO crclr
//   p = this->unk0xC;
//   this->v1958 = p->f[0..1];  this->v1960 = p->f[2..3];    // psq_l/psq_st pairs
//   this->v1958.hi = lbl_802AF4C0;                        // 0.0f
//   sq  = ps_merge00(ps_mul(this->v1960, this->v1960), lbl_802AF450 /*(0,0)*/);
//   sq  = ps_madd(this->v1958, this->v1958, sq);
//   sq  = ps_sum0(sq, sq, sq);        inv = sq;   // ps_mr f13,f0
//   if (inv.lo > lbl_802AF4C0) {      // fcmpu f13,f31 + "ble" skip  (word
//                                     //  0x40810030 = branch-if-!GT)
//       inv = ps_rsqrte(inv);
//       *(volatile __ps_t *)&sp8 = inv;  sp8.hi = lbl_802AF4C4;  // 1.0f
//       this->v1958 = ps_muls0(this->v1958, inv);
//       this->v1960 = ps_mul(this->v1960, *(volatile __ps_t *)&sp8);
//   }                                       // the reload is the CLOBBERED
//                                           //  value: hi lane was just set
//                                           //  to 1.0 -> hi mul result = v.hi
//   fn_80212C54(this, &p->f[0], &p->f[1]);    // r4=p+0xB8, r5=p+0xBC
//   this->v1968 = p->f[0..1];  this->v1970 = p->f[2..3];
//   this->v1968.hi = lbl_802AF4C0;
// Layout: this+0x1958/0x1960/0x1968/0x1970 are 8-byte PS pairs with a scalar
// f32 overlapping the HIGH lane of 0x1958 / 0x1968 — hence `union { __ps_t;
// f32[2]; }` members, not separate members. `p` (0xB8-based) is read through
// THREE separate `arg0->ent` expressions: caching it in one local makes GCC
// hoist the load above the intervening call and allocate a callee-saved GPR
// (stmw r30 + r30) instead of want's r10 (pre-call group) / lwz r4 (call arg)
// / r10 (post-call group) reload pattern.
//
// TWO REUSABLE LEVERS FOUND HERE (both confirmed by the 78.3% -> 90.0% step
// and by re-testing, not guessed):
//  * `extern const f32 lbl_802AF4C0;` — the alias-oracle lever (AGENTS
//    recipes "const qualifier on a rodata2 FLOAT", fn_80212B18 / §6bt2).
//    The store to this->v1958.hi sits between the `z` load and the `fcmpu`,
//    but z is a local so only the STORE could be an alias barrier; making
//    the global `const` tells reload nothing writes it, so the `lis`/`lfs`
//    pair for the float splits and SINKs past the first `psq_l` exactly like
//    want (want: addi r7 / lis r9 / addi r8 / psq_l / lis r11 / lfs / addi r11
//    / psq_st). Without `const` GCC always emits `lis+lfs` as an adjacent
//    pair at the very top of the block. Same lever on lbl_802AF4C4 was inert.
//  * the frame slot: one 8-byte `volatile` PS-union local at sp+8 serves as
//    BOTH the rsqrte spill (psq_st/psq_l f13,8(r1)) and the home of the dead
//    `stfs <1.0>,0xc(r1)` — so a `__ps_t` local + a separate `volatile f32`
//    can NOT work (they would need 0x8..0xf and 0x10).
//
// PARKED 2026-10-10: 96.7% (58/60 words), object SIZE-EXACT
//   (240B). The 2026-10-07 batch re-sweep stripped `volatile` from `PU sp8`
//   (`volatile PU sp8` -> `PU sp8`), which fixed the whole FPR-colour block
//   the 10-02 note describes below (that 6-word residual is STALE — colours
//   now match; do not re-try its listed variants, they predate the strip).
//   CURRENT residual, 2 words at +0x88/+0x8C (one latency-scheduling swap):
//   the want spills the f13 pair to 8(r1) before loading f0 from the C4
//   float at lbl_802AF4C4, while this draft loads f0 first and spills second.
//   The 3-cycle `lfs` floats above the 1-cycle spill to hide latency;
//   source order is inert (spill already first in source). Measured
//   2026-10-10: `// FLAG: -fno-schedule-insns2` fixes the pair but regresses
//   globally to 70.0% (kills the const-sink lever + pair-load order), so no
//   flag. This is the same latency-hoist wall as fn_80005A90's f10/f11.
// 2026-10-10: emitting want's order in source (muls0 before the
//   spill) leaves the pair swapped — the lfs hoist is independent of the
//   spill/muls0 order. Reverted; the tie needs a dep-chain pin, none exists.
//
// STALE NOTE 2026-10-02 (w75/0x8020D1F4, kept for the lever history):
//   90.0% (54/60 words), object SIZE-EXACT
// (240B, frame 0x28, correct epilogue + call sequence). Residual = ONE block,
// 0x8020D26C-0x8020D284, 6 words, and it is purely FPR COLOUR + the two store
// emissions it drags with it:
//   The want takes the reciprocal square root of f0 into f13, loads the r9
//   high half, scales f12 by lane 0 of f13 into f0, stores the f0 pair to
//   0(r7), spills the f13 pair to 8(r1), loads f0 from -0xB3C(r9), and stores
//   f0 to 0xc(r1). This draft instead takes the reciprocal square root in
//   place in f0, scales f12 by lane 0 of f0 into f13, stores the f0 pair to
//   8(r1), loads f12 from 0(r9), stores the f13 pair to 0(r7), and stores
//   f12 to 0xc(r1).
// i.e. ngccc coalesces the rsqrte destination with the dying `sq` register
// f0, freeing f13 for the muls0 result; want keeps `inv` in the register the
// `ps_mr` put it in (f13) and keeps f0 continuously live as its scratch.
// Tried (all 90.0% or worse, all verified by want|got):
//   - volatile spill store before / after the muls0 store in source
//     (one gives want's colours but puts `this->v1958` in f11; the other
//     gives f12 but the swapped rsqrte/muls0 pair — one degree of freedom,
//     two mutually exclusive solutions),
//   - rsqrte applied to `sq` instead of `inv` (semantically identical),
//   - rsqrte result in a fresh `__ps_t` local,
//   - `this->v1958` read into a local `av` before the branch,
//   - `volatile f32` pun read for the 1.0 constant (pins the lfs to the
//     source slot but then f0/f12 differ and 0x288 shifts; 88.3%),
//   - volatile-qualified store pun on this->v1958, volatile struct members
//     (duplicates the pair loads: 18.3%), address-taken `PU *pa/*pb`,
//   - `extern const __ps_t lbl_802AF450` (shifts the pair loads: 83.3%),
//   - -fno-sched-spec (inert), -fno-schedule-insns (46.7%).
// FPR/GPR colouring walls of this shape are already catalogued
// (docs/parkings/06 M5.0o/M5.0r; fn_80005A18 "no source shape reproduces it").
//
// RE-AUDITED 2026-10-20: the 2-word psq_st/lfs transposition stands. Two more
// shapes measured and rejected: a plain `__ps_t` slot with the high lane
// written through `((f32 *)&sp8)[1]` does not compile (the union view is what
// lets the pair be reloaded), and taking the address of the union slot right
// after the pair store drops the body to 50.8%. No flag moves it.
#include "types.h"

extern char lbl_802AF450[];
extern const f32 lbl_802AF4C0;
extern f32 lbl_802AF4C4;
void fn_8020D2E4(void *, s32);
void fn_80212C54(void *, f32 *, f32 *);

typedef union {
    __ps_t p;
    f32 f[2];
} PU;

typedef struct {
    char pad0x0[0xB8];
    f32 v[4];
} Ent;

typedef struct {
    char pad0x0[0xC];
    Ent *ent;
    char pad0x10[0x1948];
    PU a;
    PU b;
    PU c;
    PU d;
} Cls;

void fn_8020D1F4(Cls *arg0) {
    PU sp8;
    PU inv;
    __ps_t sq;
    f32 z;

    fn_8020D2E4(arg0, 1);
    z = lbl_802AF4C0;
    {
        Ent *e = arg0->ent;
        arg0->a.p = *(__ps_t *)&e->v[0];
        arg0->b.p = *(__ps_t *)&e->v[2];
    }
    arg0->a.f[1] = z;

    sq = __builtin_ps_merge00(__builtin_ps_mul(arg0->b.p, arg0->b.p), *(__ps_t *)&lbl_802AF450[0]);
    sq = __builtin_ps_madd(arg0->a.p, arg0->a.p, sq);
    sq = __builtin_ps_sum0(sq, sq, sq);
    inv.p = sq;
    if (inv.f[0] > z) {
        inv.p = __builtin_ps_rsqrte(inv.p);
        sp8.p = inv.p;
        arg0->a.p = __builtin_ps_muls0(arg0->a.p, inv.p);
        sp8.f[1] = lbl_802AF4C4;
        arg0->b.p = __builtin_ps_mul(arg0->b.p, sp8.p);
    }

    fn_80212C54(arg0, &arg0->ent->v[0], &arg0->ent->v[1]);
    {
        Ent *e = arg0->ent;
        arg0->c.p = *(__ps_t *)&e->v[0];
        arg0->d.p = *(__ps_t *)&e->v[2];
    }
    arg0->c.f[1] = z;
}
