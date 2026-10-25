// FPR-frame fix: volatile double dummy (issue 01, M4.92)
// WIP DRAFT (non-matching) — C body reconstructed from the DOL disassembly
// family=m2c range=0x80204928-0x80204DF4 size=1228B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.5% ([11]rev->1.8% [0]rev->2.2% [10]rev->2.5%).
// REBUILT 2026-10-06 (hand): the m2c body was replaced with a decode of the
// whole WANT.  The old body carried literal `0;` statements, a bogus
// M2C_CARRY, use-before-def temps, a Tmr_GetTime() call with two arguments
// and several mis-decoded branches; its `-fno-expensive-optimizations` pin
// was tuned for that body and is dropped here.  Every call site (26), both
// gear-shift arms, the airborne arm, both clamped lerps and the sound-event
// tail are now accounted for; the paired-single head is written with the
// in-tree SN_PS.h interface.  Blocker: see the PARKED note at EOF.
// FLAG: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "dolphin/SN_PS.h"

/* Per-function view of the engine object.  The corpus-merged Unk_DB0E2BAB
   types 0xA8 as s32 even though this function does lfs/stfs on it, and has
   no gear table at 0x48, so this unit declares its own layout (declared
   types, not casts — the want's lfs/lfsx/psq_l come from these). */
typedef struct EngineState_024928 {
    char  pad0x00[0x0C];
    char *unk0x0C;           /* 0x0C: vehicle/sound data block */
    char  pad0x10[0x0C];
    char *unk0x1C;           /* 0x1C: controller/physics state */
    char  pad0x20[0x04];
    char *unk0x24;           /* 0x24: engine/audio parameter block */
    char  pad0x28[0x08];
    s32   unk0x30;           /* 0x30: sound handle (fn_8011A56C result) */
    char  pad0x34[0x08];
    s32   unk0x3C;           /* 0x3C: sound id */
    char  pad0x40[0x04];
    s32   unk0x44;           /* 0x44: number of gear entries */
    f32   gearTab[4][4];     /* 0x48: {lo, up, rpmLo, rpmHi} per gear (stride 0x10) */
    char  pad0x88[0x20];
    f32   unk0xA8;           /* 0xA8: current effective speed */
    s32   unk0xAC;           /* 0xAC: current gear index */
    f32   unk0xB0;           /* 0xB0: current rpm */
    u32   unk0xB4;           /* 0xB4: timestamp of the last gear change */
} EngineState_024928;

/* opaque ~0x38-byte sound-event scratch built on the stack (r1+8) */
typedef struct SoundEvent_024928 {
    char data[0x38];
} SoundEvent_024928;

f32  fn_800144C8(void);
f32  fn_80205278(EngineState_024928 *, u32);
f32  fn_80205248(EngineState_024928 *, u32);
u32  Tmr_GetTime(void);
void fn_801195DC(SoundEvent_024928 *);
void fn_8011AA4C(s32, s32);
void fn_8011ADD4(s32, SoundEvent_024928 *, void *, s32, s32, s32);
void fn_80119668(SoundEvent_024928 *, f32);
s32  fn_8011A56C(s32, s32, SoundEvent_024928 *, s32, s32, s32);
void fn_8011AACC(s32, SoundEvent_024928 *);
void fn_80119640(SoundEvent_024928 *, s32);

extern char lbl_802AF010[];  /* pair of f32 constants used by the PS head */
extern char lbl_802AF040[];  /* speed scale A */
extern char lbl_802AF044[];  /* speed scale B */
extern char lbl_802AF048[];  /* speed scale C (also the gear-0 lower bound) */
extern char lbl_802AF04C[];  /* speed scale D (applied twice) */
extern char lbl_802AF050[];  /* scalar clamp minimum */
extern char lbl_802AF054[];  /* scalar clamp maximum */
extern char lbl_80302C34[];  /* global audio manager pointer */
extern char lbl_80303150[];  /* global time base (u32) */

void fn_80204928(EngineState_024928 *arg0) {
    volatile double _dummy;
    union SN_PS_type res;
    SoundEvent_024928 ev;
    char *veh;
    char *par;
    char *ctlp;
    sn_ps pxy;
    sn_ps pzw;
    sn_ps cst;
    f32  dt;
    f32  speed;
    f32  cur;
    f32  next;
    f32  shift;
    f32  prev;
    f32  band;
    f32  ratio;
    f32  delta;
    f32  k;
    f32  minScalar;
    f32  maxScalar;
    f32  level;
    f32  mag;
    f32  volume;
    f32  pitch;
    s32  air;
    s32  gear;
    u32  ts;

    dt = fn_800144C8();

    veh = arg0->unk0x0C;
    par = arg0->unk0x24;
    ctlp = arg0->unk0x1C;

    /* Paired-single head: the want loads the pair at veh+0xC0 and the pair at
       veh+0xB8, squares the former, folds the pooled pair at lbl_802AF010 in
       with ps_merge00, ps_madds the sum, then ps_rsqrte/ps_res.  Only the low
       half of the result survives (psq_st to r1+0x20, then lfs r1+0x20). */
    pzw = *(sn_ps *)(veh + 0xC0);
    cst = *(sn_ps *)lbl_802AF010;
    pzw = ps_mul(pzw, pzw);
    pxy = *(sn_ps *)(veh + 0xB8);
    pzw = ps_merge00(pzw, cst);
    pxy = ps_madd(pxy, pxy, pzw);
    pxy = ps_sum0(pxy, pxy, pxy);
    pxy = ps_res(ps_rsqrte(pxy));
    res.ps = pxy;
    speed = res.flt.hi;

    k = *(f32 *)lbl_802AF04C;
    speed = ((speed * *(f32 *)lbl_802AF040) / *(f32 *)lbl_802AF044)
            / *(f32 *)lbl_802AF048;
    speed = speed * k * k;

    air = 0;
    if (*(s32 *)(par + 0x200) != 0) {
        air = *(s32 *)(par + 0x50) != 0;
    }
    if (air == 0) {
        speed = speed * fn_80205278(arg0, QB_IDLE_ENGINE_EFFECTIVE_SPEED_FACTOR);
    }

    /* effective speed: lerp toward the target, then clamp the step */
    cur = ((arg0->unk0xA8 - speed)
           * (fn_80205278(arg0, QB_EFFECTIVE_SPEED_LERP_RATE) * dt)) + speed;
    arg0->unk0xA8 = cur;
    if (cur < speed) {
        next = (fn_80205278(arg0, QB_EFFECTIVE_SPEED_ADJUST_UP_RATE) * dt) + cur;
        arg0->unk0xA8 = (next <= cur) ? next : cur;
    } else {
        next = cur - (fn_80205278(arg0, QB_EFFECTIVE_SPEED_ADJUST_DOWN_RATE) * dt);
        arg0->unk0xA8 = (next >= cur) ? next : cur;
    }

    /* gear selection (airborne-or-not is ctlp->0x15BC->0x1C) */
    air = *(s32 *)(*(char **)(ctlp + 0x15BC) + 0x1C);
    if (air != 0) {
        if (arg0->unk0xAC < arg0->unk0x44 - 1
                && arg0->unk0xA8 > arg0->gearTab[arg0->unk0xAC][0]) {
            arg0->unk0xAC = arg0->unk0xAC + 1;
            arg0->unk0xB4 = *(u32 *)lbl_80303150 + Tmr_GetTime();
        } else if (arg0->unk0xAC > 0
                && arg0->unk0xA8 < arg0->gearTab[arg0->unk0xAC][1]) {
            arg0->unk0xAC = arg0->unk0xAC - 1;
            arg0->unk0xB4 = *(u32 *)lbl_80303150 + Tmr_GetTime();
        }
    } else {
        delta = (f32)(*(u32 *)lbl_80303150 + Tmr_GetTime()
                      - *(u32 *)(ctlp + 0x3F8));
        if (delta > fn_80205278(arg0, QB_ENGINE_AIRBORNE_DELAY)) {
            arg0->unk0xAC = air;
        }
    }

    /* gear-shift volume factor, ramped over the adjustment duration */
    shift = fn_80205278(arg0, QB_GEAR_SHIFT_MIN_VOL_FACTOR);
    ts = arg0->unk0xB4;
    delta = (f32)(*(u32 *)lbl_80303150 + Tmr_GetTime() - ts);
    minScalar = *(f32 *)lbl_802AF050;
    maxScalar = *(f32 *)lbl_802AF054;
    ratio = (delta - minScalar)
            / (fn_80205278(arg0, QB_GEAR_SHIFT_VOL_ADJUSTMENT_DURATION)
               - minScalar);
    volume = ((maxScalar - shift) * ratio) + shift;
    if (volume > maxScalar) {
        volume = maxScalar;
    }

    /* rpm for the current gear */
    gear = arg0->unk0xAC;
    prev = (gear != 0) ? arg0->gearTab[gear - 1][0] : *(f32 *)lbl_802AF048;
    ratio = (arg0->unk0xA8 - prev)
            / (arg0->gearTab[gear][0] - prev);
    band = arg0->gearTab[gear][3] - arg0->gearTab[gear][2];
    arg0->unk0xB0 = ((band * ratio + arg0->gearTab[gear][2]) - arg0->unk0xB0)
                    * (fn_80205278(arg0, QB_ENGINE_RPM_LERP_RATE) * dt)
                    + arg0->unk0xB0;

    /* normalize rpm into the min/max scalars and clamp to [min, max] */
    k = fn_80205248(arg0, QB_MINENGINERPM);
    ratio = ((arg0->unk0xB0 - k)
             / (fn_80205248(arg0, QB_MAXENGINERPM) - k)) + minScalar;
    level = (ratio > maxScalar) ? maxScalar : ratio;
    mag = (level < minScalar) ? minScalar : level;

    /* build the sound event and push volume/pitch at it */
    fn_801195DC(&ev);
    fn_8011AA4C(*(s32 *)lbl_80302C34, arg0->unk0x3C);
    fn_8011ADD4(*(s32 *)lbl_80302C34, &ev, veh + 0x58, 0, 0, 0);

    k = fn_80205248(arg0, QB_MINENGINEVOL);
    fn_80119668(&ev, volume
                * (((fn_80205248(arg0, QB_MAXENGINEVOL) - k) * mag) + k));

    /* NOTE: the want computes this pitch lerp (MINENGINEPITCH/MAXENGINEPITCH,
       fmadds at 0x80204D88) and then drops it — nothing reads the result
       before the calls below clobber f1.  It is reproduced as a dead local
       rather than invented as an argument. */
    k = fn_80205248(arg0, QB_MINENGINEPITCH);
    pitch = ((fn_80205248(arg0, QB_MAXENGINEPITCH) - k) * mag) + k;

    if (arg0->unk0x30 == 0) {
        arg0->unk0x30 = fn_8011A56C(*(s32 *)lbl_80302C34, arg0->unk0x3C, &ev,
                                    0, 0, 0);
    } else {
        fn_8011AACC(*(s32 *)lbl_80302C34, &ev);
    }
    fn_80119640(&ev, 2);
}

// RE-TRIAGED 2026-10-13: still 4B SHORT (1224/1228B). Hand-recon
// body early-stage on 1228B FPR-frame fn; PS head + frame/regalloc blockers per
// header. No body change; out of round scope.
// PARKED 2026-10-06: not matched — parked on the paired-single head plus
// frame/regalloc, not on the scalar decode.
//
// What is now exact-by-construction (verified by re-reading the WANT line by
// line against this body): the 26 call sites and their argument lists, all
// ten constant ids (0xEC67BC97 / 0x02A7095B / 0xCA5EFD91 / 0x77C8E7C8 /
// 0xBFA32092 / 0xFB6BD20E / 0x3DD9C040 / 0x05AC84A3 / 0x95DF9449 /
// 0xB8F81277 / 0x288B029D / 0x2660AF3B / 0x9F46344A / 0xC0F451D4), the
// gear up/down arms (0x48/0x4C table fields, stride 0x10, count 0x44), the
// airborne arm (ctlp->0x15BC->0x1C and ctlp->0x3F8), the two double
// conversions via the 0x4330/2^52 idiom, and the two clamps that both use
// lbl_802AF050/lbl_802AF054.
//
// Blocker 1 — the PS head.  The six opcode-4 words decode (tools/ps_diff.dec
// field layout) as a squaring of the veh+0xC0 pair in f13 (word
// 0x11AD0372), a merge of that with the lbl_802AF010 pair from f12 back
// into f13 (word 0x11AD6420), an accumulation of the veh+0xB8 pair from
// f0 with f13 into f0 (word 0x1000683A), a lane sum into f0 yielding
// double the low lane plus the high lane (word 0x10000014), a reciprocal
// square root in f0 (word 0x10000034), and a reciprocal estimate in f0
// (word 0x10000030); the pair is then stored to 32(r1) and only its low
// half is reloaded into f9 from 0x20(r1).
// The body above writes this with SN_PS.h's ps_* macros under -mps-float.
// It has NOT been compiled (workers have no toolchain): expect a compile-FAIL
// on the first sweep if the builtin spelling/macro set is wrong, and note
// that docs/parkings/06 records the allocator/coalescing failures for the
// ps_mr/psq_st shapes.  The scalar tail is independent of this — if the PS
// head has to be cut out to get a compilable body, only these 8 statements
// are involved.
//
// Blocker 2 — frame/allocation.  WANT frame 0x80 with stfd f28..f31 at
// 0x60..0x78 and stmw r28 at 0x50; the `volatile double _dummy` above is the
// old issue-01 pad (test_wip_drafts.want_fpr_frame() returns None for this
// address, so the sweep will NOT inject a dummy of its own).  Whether the pad
// is still needed for this body is unmeasured.
//
// Blocker 3 — dead pitch.  The MINENGINEPITCH/MAXENGINEPITCH lerp at
// 0x80204D5C..0x80204D88 has no consumer in the object; the source that
// produced it must have had a store that the retail build elided (or an
// argument this decode missed).  Left as a dead local.
//
// Regression policy: the previous body scored 2.5% (tools/store_order_search
// history above) but was not a faithful decode (it reads arg0->unk0xAC as a
// float array, calls Tmr_GetTime with two arguments, and computes the gear
// shift before selecting a gear).  If the sweep shows this body scoring worse
// than 2.5% it should still be preferred as the base for the next attempt:
// fix the PS head / frame rather than reverting to the `0;`-statement body.
// RE-TRIAGE 2026-10-12: scored 9.48% (1224/1228B, 1 insn short) with -mps-float (score_wip CLI flag; the file FLAG line is honored only by test_wip_drafts). Hand-recon body still early-stage on this 1228B FPR-frame function; out of round scope; no body change.
