// WIP DRAFT (non-matching) — semantic rebuild from the WANT disassembly.
// family=m2c range=0x80204E30-0x80205084 size=596B
// WORKER REBUILD 2026-10-06: the m2c body scored 4.7% (142/149
// word diffs, frame 0x50, several wrong callee arities).  This body is decoded
// line-by-line from the WANT and cross-checked against the byte-identical
// sibling src/fn_800EE55C.c (same 596-byte shape, same callee set) plus the
// paired-single decode already recorded in src/wip/fn_80204928.c.
// Key semantic fixes vs the old body:
//   * arg0->unk0xBC and the three lbl_802AF0{60,64,68} constants are f32
//     (the old body made unk0xBC an int and read 0x802AF060 as an s32, which
//     is what produced the divw/fctiwz/noradix int<->double junk in the diff).
//   * fn_801195DC takes ONE argument (&sp8), not three.
//   * fn_8011AACC is (mgr, arg0->0x34, &sp8, pitch) — the handle is its 2nd
//     argument (the old body omitted it).
//   * fn_8011A56C is 6 ints + f32 and gets the pitch as the trailing f32.
//   * fn_8011A6A8 takes (mgr, handle).  fn_8011970C takes (&sp8, delta).
//   * the head is a paired-single normalize, not an integer compare.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "dolphin/SN_PS.h"

typedef struct Par_04E30 {
    char pad0x00[0x50];
    s32  unk0x50;
} Par_04E30;

typedef struct Snd_04E30 {
    char pad0x00[0x1C];
    s32  unk0x1C;
} Snd_04E30;

typedef struct Ctl_04E30 {
    char pad0x0000[0x15BC];
    Snd_04E30 *unk0x15BC;
} Ctl_04E30;

typedef struct Obj_04E30 {
    char pad0x00[0x0C];
    char *unk0x0C;          /* 0x0C: vehicle/tire data block */
    char pad0x10[0x0C];
    Ctl_04E30 *unk0x1C;     /* 0x1C: controller/physics state */
    char pad0x20[0x04];
    Par_04E30 *unk0x24;     /* 0x24: tire/audio parameter block */
    char pad0x28[0x0C];
    s32  unk0x34;           /* 0x34: sound handle (fn_8011A56C result) */
    char pad0x38[0x08];
    s32  unk0x40;           /* 0x40: sound id */
    char pad0x44[0x78];
    f32  unk0xBC;           /* 0xBC: current slip (0..1 after the clamp) */
} Obj_04E30;

/* 0x28-byte sound-event scratch built on the stack at r1+8 (same shape as
   fn_800EE55C's vector). */
typedef struct Vec_04E30 {
    f32  unk0x00[5];
    s32  unk0x14;
    char pad0x18[0x10];
} Vec_04E30;

f32  fn_800144C8(void);
f32  fn_80205278(Obj_04E30 *, u32);
f32  fn_80205248(Obj_04E30 *, u32);
void fn_801195DC(Vec_04E30 *);
void fn_8011AA4C(s32, s32);
void fn_8011ADD4(s32, Vec_04E30 *, char *, s32, s32, s32);
void fn_80119668(Vec_04E30 *, f32);
s32  fn_8011970C(Vec_04E30 *, f32);
s32  fn_8011A56C(s32, s32, Vec_04E30 *, s32, s32, s32, f32);
void fn_8011AACC(s32, s32, Vec_04E30 *, f32);
void fn_8011A6A8(s32, s32);
void fn_80119640(Vec_04E30 *, s32);

extern f32 lbl_802AF060;  /* 0.0f  */
extern f32 lbl_802AF064;  /* 3.0f  */
extern f32 lbl_802AF068;  /* 1.0f  */
extern char lbl_802AF010[];   /* pair of f32 constants folded into the PS sum */
extern s32 lbl_80302C34;      /* global audio manager handle */

void fn_80204E30(Obj_04E30 *arg0) {
    Vec_04E30 sp8;
    Par_04E30 *par;
    Ctl_04E30 *ctl;
    char *veh;
    union SN_PS_type res;
    sn_ps pzw;
    sn_ps pxy;
    sn_ps cst;
    f32 speed;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 var_f13_2;
    f32 var_f30;
    f32 var_f30_2;
    s32 temp_r29;

    var_f30 = lbl_802AF060;
    par = arg0->unk0x24;
    if (par->unk0x50 != 0) {
        ctl = arg0->unk0x1C;
        if (ctl->unk0x15BC->unk0x1C == 0) {
            veh = arg0->unk0x0C;
            pzw = *(sn_ps *)(veh + 0xC0);
            cst = *(sn_ps *)lbl_802AF010;
            pzw = ps_mul(pzw, pzw);
            pxy = *(sn_ps *)(veh + 0xB8);
            temp_f11 = lbl_802AF064;
            pzw = ps_merge00(pzw, cst);
            pxy = ps_madd(pxy, pxy, pzw);
            pxy = ps_sum0(pxy, pxy, pxy);
            pxy = ps_res(ps_rsqrte(pxy));
            res.ps = pxy;
            speed = res.flt.hi;
            temp_f13 = speed * temp_f11;
            temp_f0 = temp_f13;
            if (var_f30 > temp_f13) {
                temp_f0 = var_f30;
            }
            var_f30 = temp_f0;
        }
    }

    temp_f31 = fn_80205278(arg0, QB_TIRE_SLIP_LERP_RATE);
    temp_f31 = temp_f31 * fn_800144C8();
    temp_f13 = arg0->unk0xBC;
    arg0->unk0xBC = (var_f30 - temp_f13) * temp_f31 + temp_f13;
    temp_f0_2 = arg0->unk0xBC / fn_80205248(arg0, QB_FULLTIRESLIPVELOCITY);
    temp_f12 = lbl_802AF068;
    temp_f11 = lbl_802AF060;
    var_f13_2 = temp_f0_2;
    if (temp_f0_2 > temp_f12) {
        var_f13_2 = temp_f12;
    }
    var_f30_2 = var_f13_2;
    if (var_f13_2 < temp_f11) {
        var_f30_2 = temp_f11;
    }

    fn_801195DC(&sp8);
    temp_r29 = lbl_80302C34;
    veh = arg0->unk0x0C;
    fn_8011AA4C(temp_r29, arg0->unk0x40);
    fn_8011ADD4(temp_r29, &sp8, veh + 0x58, 0, 0, 0);
    temp_f31_2 = fn_80205248(arg0, QB_MINTIREVOL);
    fn_80119668(&sp8, ((fn_80205248(arg0, QB_MAXTIREVOL) - temp_f31_2) * var_f30_2) + temp_f31_2);
    temp_f31_3 = fn_80205248(arg0, QB_MINTIREPITCH);
    temp_f1 = fn_80205248(arg0, QB_MAXTIREPITCH) - temp_f31_3;
    temp_f31_4 = (temp_f1 * var_f30_2) + temp_f31_3;
    if (fn_8011970C(&sp8, temp_f1) == 0) {
        if (arg0->unk0x34 == 0) {
            arg0->unk0x34 = fn_8011A56C(temp_r29, arg0->unk0x40, &sp8, 0, 0, 0, temp_f31_4);
        } else {
            fn_8011AACC(temp_r29, arg0->unk0x34, &sp8, temp_f31_4);
        }
    } else if (arg0->unk0x34 != 0) {
        fn_8011A6A8(temp_r29, arg0->unk0x34);
        arg0->unk0x34 = 0;
    }
    fn_80119640(&sp8, 2);
}

// PARKED 2026-10-06: not matched — parked on the paired-single head and the
// resulting frame/colour, not on the scalar decode.
//
// The scalar tail is a straight port of the byte-identical sibling
// src/fn_800EE55C.c (fn_80205278/fn_80205248 in place of fn_800EEB10/
// fn_800EEAE0, slip at arg0+0xBC instead of arg0+0xB0, sound id at arg0+0x40
// instead of arg0+0x34, handle at arg0+0x34): every call site, argument list
// and clamp is taken from that matched object, so its codegen should fall out
// unchanged once the frame matches.
//
// Blocker 1 — the PS head.  The six opcode-4 words decode (same field layout
// as src/wip/fn_80204928.c) as a squaring of the veh+0xC0 pair in f13
// (word 0x11AD0372), a merge of that with the lbl_802AF010 pair from f12
// back into f13 (word 0x11AD6420), an accumulation of the veh+0xB8 pair
// from f0 with f13 into f0 (word 0x1000683A), a lane sum in f0 (word
// 0x10000014), a reciprocal square root in f0 (word 0x10000034), and a
// reciprocal estimate in f0 (word 0x10000030); the pair is then stored
// to 32(r1) and only its high half is reloaded into f0 from 0x20(r1).
// Written with SN_PS.h's ps_* macros under -mps-float.  This head has NOT
// been compiled (this worker has no toolchain): expect a possible compile-FAIL
// or a ps_mr/psq_st-colour residual, per docs/parkings/06.
//
// Blocker 2 — frame/colour.  WANT frame 0x58 with stfd f30,0x48 / stfd
// f31,0x50 / stmw r28,0x38 (i.e. 4 GPRs r28..r31 plus f30/f31 live).  The
// two live FPRs are var_f30 (slip) and temp_f31* (the volume/pitch chain),
// and r28..r31 are the mgr pointer plus the three call temps.  test_wip_drafts
// classifies this want as the 8-aligned ambiguous FPR frame
// (want_fpr_frame -> ambig8, frame 0x58), so it will try the body both as-is
// and with a `volatile double _dummy;`; the winning variant is the honest one.
//
// Blocker 3 — ordering.  The want hoists `addi r30,r30,0x58` above the
// fn_8011AA4C call and moves `lis r28` to the page of lbl_80302C34 right after
// fn_801195DC returns; the source order above mirrors that group.  Residual
// ordering is a sched2 ready-list artefact (doc-15 family), not a shape bug.
//
// Regression policy: the previous body scored 4.7%.  Any score at or above
// that is acceptable as the new base; do NOT revert to the old m2c body (its
// bare `0;` statements were not a faithful decode).  If this body FAILs to
// compile, the only self-contained part is the PS head (8 statements) —
// cutting it and keeping the tail is preferable to reverting.
