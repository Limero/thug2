// WIP DRAFT (non-matching) — full hand re-decompile from DOL disassembly
// family=m2c range=0x800BA9C8-0x800BB02C size=1636B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ============================================================================
// UNPARKED 2026-09-27 — the previous header's park reason was FACTUALLY WRONG.
// It claimed tens of illegal-on-Gekko words (Altivec-class encodings).
// Every one of those words hand-decodes to standard paired-single
// arithmetic (subtract / copy / multiply / merge / sum / reciprocal estimates
// plus pair loads and stores) and is emittable from C under the float flag.
//
// This is the §6ag-9/§6ai-153/§6ax-218 mislabel class: capstone and
// powerpc-eabi-objdump print the Gekko A-form as vmsumshm / vmhaddshs / vsel /
// vextdubvlx because Gekko puts frC in the bits VMX uses for VC. The words
// were always plain ps_* arithmetic. So there is NO opcode wall here.
//
// REAL residual: no opcode wall (see the verdict block at the end of this
// header for the measured numbers and the exact per-region list).
//
// ============================================================================
// Per-region decode map (so the analysis never has to be redone)
// prologue sets up a 0xF0 frame with float and integer callee-saved saves,
// link save, locals, GPR save area and float save area, plus a dead tail.
// Fixed registers hold the object, the frame base, the table walker, the
// countdown, the divide magic and the constant page anchors.
// Main loop walks 8 table entries with a countdown latch; radius test reads
// per-entry extents and culls on squared distance plus upper/lower bounds.
// Delta-position block derives and normalises a direction; delta-orientation
// block derives a second direction with three nested early-out returns that
// share the epilogue. Dot block plus soft ramp shape a scalar, with a
// not-positive guard back to the latch and a zeroing step. Copy plus second
// direction block length-limits, guards zero length, accumulates and scales.
// Scale/wrap/normalise block scales, builds a wrap vector, zeroes one lane,
// then dots, estimates and normalises. Wrap-pick block selects one lane from
// the long-lived horizontal delta or a constant or a wrapped sum. Long vector
// pipeline updates several object pair fields and fills frame temporaries.
// Then a helper call plus object field copy with a guarded script callback,
// a shadow-handle lookup with a guarded link removal, a time-guarded percent
// callback pair plus rescheduling of two timestamps, and the matching
// frame-teardown epilogue.
//
// ============================================================================
// VERDICT 2026-09-27: DIFF, 27/375 words (7.2% masked, tools/ps_diff.py);
// test_wip_drafts.py -addr 0x800BA9C8 => DIFF 6.6%. got 1500B / 375 insns vs
// retail 1636B / 409 (36 insns SHORT). Frame 0xF0, 3 saved FPRs and the whole
// epilogue now MATCH; the previous draft (scalar, 1.2%, 1496B) matched almost
// nothing. -mps-float is auto-added by gen_leaves.draft_flags (the body uses
// __ps_t / __builtin_ps_*); no // FLAG: line is needed — the old
// "-Os -fno-rerun-cse-after-loop" pair was a guess for the wrong (scalar) body
// and was DELETED. A full flag sweep (21 singles + pairs, plus -Os/-O3/
// -fno-gcse/-fno-schedule-insns{,2}/-fno-branch-count-reg/-fno-strength-reduce/
// -fno-expensive-optimizations/-mps-float-with-dummy-double) produced ZERO
// improvement over plain -mps-float, so nothing is being left on the table by
// the flag choice.
//
// EXACT residual, region by region (this is a register-allocation + vector-pipeline
// problem, NOT an opcode/emission problem):
//  1. PROLOGUE: the original homes two more callee-saved registers than the
//     draft. The two homes are the hoisted constant-page anchor (live across
//     two square-root calls) and the divide magic kept in a callee-saved
//     register in the draft. The draft instead re-materialises the anchor per
//     use with a fresh address setup plus scalar-indexed load instead of the
//     original displacement fold, and homes the second argument into a
//     callee-saved register, which the original keeps untouched as a
//     passthrough into a later call. The fix direction is to stop homing the
//     argument and to get the anchor hoisted; not found.
//  2. Long vector pipeline: the original runs dozens of paired-single ops in
//     one window with every intermediate kept live in its own pair register;
//     the draft dataflow folds several together, which is where the missing
//     words come from. Recovering it needs the exact lane convention of each
//     pair op plus per-site register naming -- that is the remaining work,
//     and it is a longer job, not a flag fix.
//  3. Condition-cache compare sequences: the draft emits plain C comparisons
//     here. The memory-bitfield route and the split-counter shape have not
//     been tried against this body yet.
//  4. Wrap-lane pick: the original tests the same long-lived horizontal delta
//     computed early; the draft reproduces the value but re-reads the node pair.
// ============================================================================

#include "types.h"
#include "qb_constants.h"

// True layout of arg0. NOTE: the shared class types part of this range as a
// byte pad; the original pair-loads those slots as pairs, so this file
// declares its own layout.
typedef struct {
    char pad0x00[0x0C];
    s32 unk0x0C;
    char pad0x10[0xC];
    f32 unk0x1C;
    char pad0x20[0x24];
    f32 unk0x44;
    f32 unk0x48;
    f32 unk0x4C;
    f32 unk0x50;
    f32 unk0x54;
    f32 unk0x58;
    char pad0x5C[0x6C];
    f32 unk0xC8;
    s32 unk0xCC;
    char pad0xD0[0x0C];
    s32 unk0xDC;
    s32 unk0xE0;
    char pad0xE4[0x04];
    u32 unk0xE8;
    u32 unk0xEC;
    char pad0xF0[0x08];
    s32 unk0xF8;
    char pad0xFC[0x1C];
    __ps_t v118;
    __ps_t v120;
    __ps_t v128;
    __ps_t v130;
    __ps_t v138;
    __ps_t v140;
    __ps_t v148;
    __ps_t v150;
    char pad0x158[0x44];
    f32 unk0x19C;
    char pad0x1A0[0x04];
    s32 unk0x1A4;
} Obj_t;

typedef struct {
    char pad0x00[0x58];
    __ps_t v58;
    __ps_t v60;
    char pad0x68[0x50];
    __ps_t vB8;
    __ps_t vC0;
} Node_t;

// Frame template: pins the exact sp slots retail uses (§6q-86). 0x58/0x5C are
// the only gap; 0x98.. is the dead tail (see header).
/* PS->scalar extraction. cc1 ICEs (expmed.c:1115) on any compare that reads a
   mode(PS) value as a float; the volatile-union route is the documented
   workaround (§6am-190). */
typedef union {
    __ps_t ps;
    struct {
        f32 hi, lo;
    } flt;
} Vu_t;

typedef struct {
    __ps_t v08; /* 0x08 delta-position  */
    __ps_t v10; /* 0x10                 */
    __ps_t v18; /* 0x18 delta-orientation */
    __ps_t v20; /* 0x20                 */
    __ps_t v28; /* 0x28 direction        */
    __ps_t v30; /* 0x30                 */
    __ps_t v38; /* 0x38 wrap vector     */
    __ps_t v40; /* 0x40                 */
    __ps_t v48; /* 0x48                 */
    __ps_t v50; /* 0x50                 */
    s32 gap58;
    s32 gap5C;
    __ps_t v60; /* 0x60                 */
    __ps_t v68; /* 0x68 {obj.54*f31, *} */
    __ps_t v70; /* 0x70 {obj.48, 0}     */
    __ps_t v78; /* 0x78 {rsqrte, 1}     */
    __ps_t v80; /* 0x80                 */
    __ps_t v88; /* 0x88                 */
    __ps_t v90; /* 0x90                 */
} Fr_t;

#define LO(p) (*(f32 *)&(p))
#define HI(p) (*(f32 *)((char *)&(p) + 4))

extern char lbl_8037E778[];
extern f32 lbl_803CA200[8];
extern f32 lbl_803CAF6C;
extern f32 lbl_80298DA8;
extern f32 lbl_80298DAC;
extern f32 lbl_80298DB0;
extern f32 lbl_80298DB4;
extern f32 lbl_80298DB8;
extern f32 lbl_80298DBC;
extern f32 lbl_80298DC0;
extern f32 lbl_80298DC4;
extern f32 lbl_80298DC8;
extern f32 lbl_80298DCC;
extern __ps_t lbl_80298CA0;
extern char lbl_80298DA0[];
extern s32 lbl_80301B1C;

extern f32 sqrtf(f32);
extern void fn_800BA64C(Obj_t *);
extern void *fn_8009F27C(void *, void *, s32, s32, s32);
extern s32 fn_801309EC(u8 *);
extern void *fn_80054E40(void);
extern s32 fn_80055E74(void *, s32); /* per-caller: retail ORs the result */
extern u32 fn_8000A7F8(u32, s8 *);
extern void fn_80057D90(void *, s32);
extern s32 fn_800145AC(void);
extern void fn_8012772C(void *, s32, f32);
extern void fn_800CCD34(void *, void *);
extern s32 Mth_Rnd(s32);

void fn_800BA9C8(Obj_t *arg0, void *arg1) {
    Fr_t fr;
    Node_t **pp;
    Node_t *nd;
    s32 i;
    f32 e, k0, f7, f30, f31, dx;
    pp = (Node_t **)((char *)lbl_8037E778 + 0x54);
    i = 7;
    for (;;) {
        nd = *pp;
        if (nd != NULL) {
            e = lbl_803CA200[i];
            k0 = lbl_80298DAC;
            f30 = k0;
            /* --- radius / extent cull --- */
            {
                f32 dy = LO(arg0->v120) - LO(nd->v60);
                f32 dx = LO(arg0->v118) - LO(nd->v58);
                f32 r = arg0->unk0x44 + e;
                if (((dx * dx) + (dy * dy)) > (r * r)) {
                    goto next;
                }
            }
            {
                f32 lim;
                dx = HI(nd->v58) - HI(arg0->v118);
                lim = arg0->unk0x48 + e;
                if (dx > lim) {
                    goto next;
                }
                if (dx < -(lim + lbl_803CAF6C)) {
                    goto next;
                }
                /* --- delta position, normalised --- */
                fr.v08 = arg0->v118;
                fr.v10 = arg0->v120;
                fr.v08 = fr.v08 - nd->v58;
                fr.v10 = fr.v10 - nd->v60;
                f7 = sqrtf((LO(fr.v10) * LO(fr.v10)) +
                                 (LO(fr.v08) * LO(fr.v08)));
                LO(fr.v08) = LO(fr.v08) / f7;
                LO(fr.v10) = LO(fr.v10) / f7;
                /* --- delta orientation --- */
                fr.v18 = nd->vB8;
                fr.v20 = nd->vC0;
                fr.v18 = fr.v18 - arg0->v128;
                fr.v20 = fr.v20 - arg0->v130;
                if ((__builtin_fabsf(LO(fr.v18) - k0) < lbl_80298DA8) &&
                    (__builtin_fabsf(HI(fr.v18) - k0) < lbl_80298DA8) &&
                    (__builtin_fabsf(LO(fr.v20) - k0) < lbl_80298DA8)) {
                    return;
                }
                f31 = ((LO(fr.v18) * LO(fr.v08)) + (LO(fr.v20) * LO(fr.v10))) +
                      __builtin_fabsf(HI(fr.v18) / lbl_80298DB0);
                if (!(f31 > k0)) {
                    goto next;
                }
                HI(fr.v18) = k0;
                if (f31 > lbl_80298DB4) {
                    f31 = f31 + lbl_80298DB8;
                } else if (f31 > lbl_80298DBC) {
                    f31 = f31 + ((f31 - lbl_80298DBC) + lbl_80298DBC);
                } else {
                    f31 = f31 + f31;
                }
                /* --- second direction, length-limited, scaled --- */
                fr.v30 = fr.v20;
                fr.v28 = fr.v18;
                f7 = sqrtf((LO(fr.v30) * LO(fr.v30)) +
                                 (LO(fr.v28) * LO(fr.v28)));
                if (f7 == f30) {
                    f7 = lbl_80298DA8;
                }
                LO(fr.v28) = (LO(fr.v28) / f7) + LO(fr.v08);
                LO(fr.v30) = (LO(fr.v30) / f7) + LO(fr.v10);
                f7 = sqrtf((LO(fr.v28) * LO(fr.v28)) +
                                 (LO(fr.v30) * LO(fr.v30)));
                if (f7 == f30) {
                    f7 = lbl_80298DA8;
                }
                HI(fr.v30) = lbl_80298DC0;
                HI(fr.v28) = arg0->unk0x50;
                LO(fr.v70) = arg0->unk0x48;
                LO(fr.v28) = (LO(fr.v28) / f7) * arg0->unk0x4C;
                LO(fr.v30) = (LO(fr.v30) / f7) * arg0->unk0x4C;
                LO(fr.v68) = arg0->unk0x54 * f31;
                HI(fr.v70) = f30;
                /* --- PS-A: scale, wrap vector, normalise --- */
                fr.v30 = __builtin_ps_muls0(fr.v30, fr.v68);
                fr.v28 = __builtin_ps_muls0(fr.v28, fr.v68);
                fr.v38 = nd->v58;
                fr.v40 = nd->v60;
                LO(fr.v38) = LO(fr.v38) - LO(arg0->v118);
                HI(fr.v38) = f30;
                LO(fr.v40) = LO(fr.v40) - LO(arg0->v120);
                {
                    volatile Vu_t vq;
                    __ps_t a = fr.v40;
                    __ps_t b = fr.v38;
                    __ps_t c = __builtin_ps_mul(a, a);
                    c = __builtin_ps_merge01(c, fr.v70);
                    c = __builtin_ps_madd(b, b, c);
                    c = __builtin_ps_sum0(c, c, c);
                    vq.ps = c;
                    if (vq.flt.lo > f30) {
                        c = __builtin_ps_rsqrte(c);
                        c = __builtin_ps_muls0(c, fr.v70);
                        fr.v78 = c;
                        HI(fr.v78) = lbl_80298DC0;
                        c = __builtin_ps_muls0(b, c);
                        fr.v38 = c;
                        c = __builtin_ps_mul(a, fr.v78);
                        fr.v40 = c;
                    }
                }
                /* --- wrap-lane pick --- */
                {
                    if (dx > f30) {
                        LO(fr.v38) = dx;
                    } else if (dx >= -lbl_803CAF6C) {
                        LO(fr.v38) = lbl_80298DC4;
                    } else {
                        LO(fr.v38) = (HI(nd->v58) + lbl_803CAF6C) -
                                      HI(arg0->v118);
                    }
                }
                /* --- PS-B: the long vector pipeline --- */
                {
                    __ps_t t0, t1, t2, t3, t4, t5, t6, t7;
                    t0 = __builtin_ps_merge10(fr.v28, fr.v30);
                    t1 = arg0->v128;
                    t0 = __builtin_ps_mul(fr.v38, t0);
                    t1 = __builtin_ps_add(t1, fr.v28);
                    arg0->v128 = t1;
                    t2 = arg0->v130;
                    t2 = __builtin_ps_add(t2, fr.v30);
                    arg0->v130 = t2;
                    t3 = __builtin_ps_merge10(fr.v38, fr.v40);
                    t0 = __builtin_ps_mul(t3, fr.v28);
                    t3 = __builtin_ps_sub(t0, t3);
                    t4 = __builtin_ps_merge00(fr.v28, fr.v30);
                    t5 = __builtin_ps_merge00(fr.v40, fr.v38);
                    t0 = __builtin_ps_merge00(t3, t3);
                    fr.v80 = t0;
                    HI(fr.v80) = lbl_80298DC0;
                    t5 = __builtin_ps_mul(t5, t4);
                    t0 = __builtin_ps_merge10(t5, t5);
                    t5 = __builtin_ps_sub(t5, t0);
                    t0 = __builtin_ps_merge10(t3, t5);
                    fr.v88 = t0;
                    t6 = arg0->v148;
                    t7 = arg0->v150;
                    LO(fr.v88) = arg0->unk0x58 * lbl_80298DC8 * arg0->unk0x1C;
                    t0 = __builtin_ps_muls0(fr.v80, fr.v88);
                    t1 = __builtin_ps_muls0(t0, fr.v88);
                    fr.v50 = t0;
                    fr.v48 = t1;
                    t6 = __builtin_ps_add(t6, t1);
                    arg0->v148 = t6;
                    t7 = __builtin_ps_add(t7, t0);
                    arg0->v150 = t7;
                    fr.v60 = t0;
                }
                fn_800BA64C(arg0);
            }
            arg0->unk0x19C = arg0->unk0xC8;
            if (arg0->unk0xCC != 0) {
                fn_801309EC((u8 *)fn_8009F27C(arg0->unk0x0C, arg1,
                                              arg0->unk0xDC, 0, 0));
            }
            {
                void *p = fn_80054E40();
                s32 h = fn_8000A7F8(*(s32 *)(arg0->unk0x0C + 0x18),
                                    (s8 *)lbl_80298DA0);
                if (fn_80055E74(p, h) != 0) {
                    fn_80057D90(p, 0);
                }
            }
            {
                s32 now = fn_800145AC();
                if (((now - arg0->unk0xF8) > 0) &&
                    ((now - lbl_80301B1C) > 0) &&
                    (arg0->unk0x1A4 != 0) && (arg0->unk0xE0 != 0)) {
                    fn_8012772C((void *)arg0->unk0xE0, QB_PERCENT,
                                LO(fr.v90) * lbl_80298DCC);
                    fn_800CCD34((void *)arg0->unk0x1A4, (void *)arg0->unk0xE0);
                    arg0->unk0xF8 = fn_800145AC() +
                                    (((u32)(Mth_Rnd(100) + 50) * arg0->unk0xE8) /
                                     100u);
                    lbl_80301B1C = fn_800145AC() +
                                   (((u32)(Mth_Rnd(100) + 50) * arg0->unk0xEC) /
                                    100u);
                }
            }
            return;
        }
    next:
        pp -= 3;
        i -= 1;
        if (i != 0) {
            continue;
        }
        break;
    }
}
