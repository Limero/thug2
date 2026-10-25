// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D2FE8-0x801D30E0 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802AD278[];

f32 fn_801417B8(void *obj, u32 tag);

/* state->unk0x24 is a sub block; WANT reads +0x2C of it via a materialised
   `addi r11, r9, 0x24`, hence the two-level form rather than a flat +0x50. */
typedef struct Sub801D2FE8 {
    char pad0x0[0x2C];
    u32 unk0x2C;
} Sub801D2FE8;

/* arg0 layout from the WANT: 0xC = vector object, 0x320/0x360/0x370 = flags,
   0x15A0 = state block, 0x15BC = sub block holding the crouch flag at +0x28. */
typedef struct Obj801D2FE8 {
    char pad0x0[0xC];
    Unk_412E16CE *unk0xC;
    char pad0x10[0x310];
    u32 unk0x320;
    char pad0x324[0x3C];
    u32 unk0x360;
    char pad0x364[0xC];
    u32 unk0x370;
    char pad0x374[0x122C];
    char *unk0x15A0;
    char pad0x15A4[0x18];
    char *unk0x15BC;
} Obj801D2FE8;

typedef union Pair801D2FE8 {
    __ps_t ps;
    f32 f[2];
} Pair801D2FE8;

bool fn_801D2FE8(Obj801D2FE8 *arg0) {
    Sub801D2FE8 *sub;
    register char *cblk __asm__("r10");
    char *state;
    Unk_412E16CE *vec;
    Unk_412E16CE *arg1v;
    Pair801D2FE8 wk;
    __ps_t cv;
    __ps_t zv;
    __ps_t sq;
    __ps_t bv;
    __ps_t mg;
    __ps_t md;
    f32 dist;
    f32 lim;
    f32 lim2;

    state = arg0->unk0x15A0;
    sub = (Sub801D2FE8 *)(state + 0x24);
    if (arg0->unk0x370 != 0) {
        goto ret0;
    }
    if (arg0->unk0x320 == 0 && *(u32 *)(state + 0x1B8) == 0) {
        goto ret0;
    }
    if (sub->unk0x2C != 0) {
        goto ret0;
    }

    cblk = arg0->unk0x15BC;
    vec = arg0->unk0xC;
    zv = *(__ps_t *)&lbl_802AD278;
    cv = vec->unk0xC0;
    arg1v = vec;
    __asm__ volatile ("" : "+r"(vec));
    sq = __builtin_ps_mul(cv, cv);
    bv = vec->unk0xB8;
    mg = __builtin_ps_merge00(sq, zv);
    md = __builtin_ps_madd(bv, bv, mg);
    md = __builtin_ps_sum0(md, md, md);
    md = __builtin_ps_rsqrte(md);
    md = __builtin_ps_res(md);

    wk.ps = md;
    dist = wk.f[0];

    if (*(u32 *)(cblk + 0x28) != 0) {
        goto crouch;
    }
    if (arg0->unk0x360 != 0) {
        goto crouch;
    }
    lim = fn_801417B8(arg1v, QB_SKATER_MAX_STANDING_KICK_SPEED_STAT);
    if (!(dist > lim)) {
        goto ret1;
    }
ret0:
    return false;

crouch:
    lim2 = fn_801417B8(arg1v, QB_SKATER_MAX_CROUCHED_KICK_SPEED_STAT);
    if (dist > lim2) {
        return false;
    }
ret1:
    return true;
}

// MATCHED 2026-10-15: EXACT 62/62 via ps_diff (248B). Technique notes:
//   (1) The early-out chain falls THROUGH to the standing path; every test
//       branches to `crouch` (the drafter's first version wrongly returned 0).
//   (2) `sub` is computed EAGERLY in the entry block. The addi lives in the
//       entry block while its load sits three blocks down, so combine cannot
//       fold them (computing it inside the if fuses to one `lwz 0x50(r9)`).
//   (3) STANDING TAIL: plain `if (dist <= lim) return 1; return 0;` gets
//       VALUEISED by ngccc (fcmpu cr7 + cror + mfcr boolean; verified in
//       isolation). General rule: `<=`-with-returns booleanises, `>`-with-
//       returns branches. The exact shape needs `if (!(dist > lim))` (the `!`
//       survives to RTL and emits a direct `ble`) PLUS `goto ret1` so the
//       `li r3,1` tail is shared out-of-line with the crouch path.
//   (4) `mr r8,r11` (vec staged for both call args) needs TWO parts: a
//       NAMED `arg1v = vec` copy placed BEFORE vec's last PS use (sched
//       floats the long-lived copy up to slot 0x5C; placed after, it
//       coalesces away), PLUS an empty `+r(vec)` barrier between the copy
//       and the last use so copyprop cannot forward arg1v into the 2nd
//       psq_l (else it reads 184(r8)). The barrier alone splits vec's range
//       and flips vec/cblk to r10/r11, so a `register __asm__("r10")` pin
//       on cblk is also required: r10 taken early forces both vec parts to
//       r11 (reusing sub's dead reg) and cblk stays r10. Both asms emit
//       zero instructions. A pin on vec instead is wrong: it reserves r11
//       function-wide (sub loses it) and coalesces the copy away.
//   (5) The three early tests target the shared `ret0` (li0+b), NOT crouch:
//       branch-target audit caught this (masked diffs hide it). In source
//       the early `goto ret0`s plus a `ret0: return 0;` label between the
//       standing test and `crouch:` reproduce the layout; plain `return 0`
//       reorders the allocator (vec/cblk swap, copy lost).
