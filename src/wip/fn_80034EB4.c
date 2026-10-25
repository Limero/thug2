// PARKED 2026-10-03: DIFF 0.7%.  Baseline was FAIL (would not compile).
//
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80034EB4
//
// WHY IT IS OUT OF REACH FOR AN m2c-SKELETON ATTEMPT
//   This is a 2924-byte / 731-instruction quaternion -> euler-angle conversion
//   written almost entirely in PAIRED SINGLES (158+ psq_l/psq_st/ps_mul/ps_madd/
//   ps_sum0/ps_merge*/ps_rsqrte words).  It needs `-mps-float` + `__ps_t`; the m2c
//   draft is a *scalar* reinterpretation of that PS body, so the statement
//   skeleton is not merely unscheduled - it is the wrong language.  A correct
//   rewrite is a from-scratch hand-decode, not a draft edit.
//
// WHAT I DID FIX (all provable off the want)
//   * FAIL cause: `sqrtf(arg0)` with a pointer arg.  ngccc's fatal diagnostic is
//     "incompatible type for argument 1 of `sqrtf'" but wibo swallows the exit
//     code, so the scorer prints a bare "compile error" with no text.  => a FAIL
//     with an EMPTY message is always an argument-type error, never a bad #include.
//   * `sqrtf(fn_80036304(out))` - fn_80036304 takes ONE arg and already returns
//     the sum of the four squares (m2c invented 4 args and then sqrtf'd a pointer).
//   * vcall is ONE arg: `((void(*)(void*))a->v->unk0x34)(a + a->v->unk0x30)`.
//     unk0x30 is a sign-extended halfword field.  m2c passes a phantom second arg.
//   * `fn_80036810(handle, id)` - TWO args.  m2c wrote `(arg0, temp_r19)`.  The
//     second arg is the id already sitting in the second-arg register from the
//     node-id load; the register re-use is invisible in a plain read, which is
//     why m2c lost it.
//     `fn_80034E74` returns a HANDLE (0 or fn_800c9780(...)), not an int.
//   * `fn_8002C904(f32*,x,y,z)` stores out[0..2]=f1,f2,f3; `fn_8002C8FC(f32*,w)`
//     stores p[3]=f1 (m2c called it as a 1-arg and dropped the w value).
//   * atan2f takes exactly TWO f32 (m2c emitted four), asinf/acosf/sinf/cosf/sqrtf
//     all f32-in/f32-out.
//   * arg1 is `f32 *` (want scales the index by 16 and adds it to the base),
//     not s32.
//   * the switch really has FOUR arms (0/2/3/default); m2c folded case 0 into
//     `default`, but `default` in the want jumps straight to 0x8003542c.
//   * the 8 file-scope `static s32 sp128/sp150/sp168/sp170/sp198/spC8/spCC/spD0`
//     are m2c names for FRAME SLOTS that the want touches with float
//     loads/stores.  Making them f32 locals removes the bogus .bss (1796 ->
//     1652 bytes of .text).
//   * `Unk_59AB5482 sp48/sp78/sp88/sp38` are plain f32 vectors in the want
//     (frame-slot addresses feeding pair load/store sequences); replaced the
//     struct punning with real f32 locals.
//
// STRUCTURE MAP (want; offsets and counts only)
//   prologue (0x80034EB4-0x80034F57): 0x2b8 frame, GPRs saved from r18, float
//   regs f19..f31, link-register slot at top, locals in the low range.
//   body (0x80034F58-0x800359BC) with a rotated entry test on the node id.
//   latch (0x800359C0): two cursors advance 0x78 per iteration, counter +1,
//   four iterations total; epilogue returns constant 1.
//   Records are 0x78 bytes with the second cursor leading the first by 0x70.
//   Record fields seen: +0x04/+0x08 floats, +0x1C s32 (-1 => skip),
//   +0x24 float, +0x28 s32 (the switch value), +0x30..+0x4C float min/max
//   limits, +0x70..+0x7C float[4] input quaternion, +0x88 s32 clamp-mode flag.
//
// CONSTANTS - float pool at 0x80291DE0 (page base + low offset in the want):
//   E20=1.0 E24=0.0 E28=1.0 E2C=0.0 E30=176.0(double) E38=pi E3C=0.5
//   E40=cos(pi/8) E44=0.2 E48=1e-5 E4C=3.0
//
// ANGLE-REDUCTION TRICK (arms 0 and 2 only; want 0x80035144 / 0x80035270):
//   The sign of the switch value selects +1 or -1 via an integer divide; that
//   word is stored as the LOW word of a frame double whose HIGH word is the
//   2^52 bias, then the pair is loaded as a double, biased down, rounded to
//   single, and scaled twice.  Arms 3 and default SKIP this.  Note the
//   compiler materialises 2^52 INLINE into the frame, so an honest source
//   must build the double in the frame - an f64 literal in the source makes
//   the compiler emit a private 8-byte pool entry, and the DOL has no room
//   for one (this symbol is contiguous 0x80034EB4-0x80035A20).
//
// WHAT I RULED OUT (so it isn't retried)
//   * m2c's `(f32)(f64)var_r0` casts ARE its guess at the trick above.  Replacing
//     them with plain float math removes those int->double conversions but the
//     private 8-byte pool entry SURVIVES.  The surviving one still reaches a
//     sinf/cosf as a frame-double load, bias subtract, round, and two scales
//     (t5.s ~L157/L408), i.e. the compiler evaluates something in double that
//     the want has no double for.  Not identified - start there.
//   * store/assignment reordering (the file's old SEARCHED note: 0.8-1.4%) and any
//     flag/pin sweep: at 1652 vs 2924 bytes every word is misaligned, so
//     masked_pct is pure noise here.  Do not chase the percentage.
//
// MOST PROMISING NEXT IDEA
//   Rewrite from scratch as `__ps_t` paired-single C with `-mps-float`.  Start
//   with 0x80034F7C-0x80035120: that normalise block is IDENTICAL in all four
//   switch arms (pairwise subtract/multiply/add, horizontal sum, reciprocal
//   square root, rescale over a 4-length quaternion), so getting it byte-exact
//   pays off four times over before the duplicated arms are even touched.
//
// family=m2c range=0x80034EB4-0x80035A20 size=2924B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 1.4% ([12]rev->0.8% [1]rev->0.9% [4]rev->1.4% [19]rev->1.4%).
#include "types.h"
#include "structs.h"
extern f32 lbl_80291E24;   /* 0.0f  */
extern f32 lbl_80291E28;   /* 1.0f  */
extern f32 lbl_80291E38;   /* 3.1415927f */
extern f32 lbl_80291E3C;   /* 0.5f  */
extern f32 lbl_80291E40;   /* cos(pi/8) */
extern f32 lbl_80291E44;   /* 0.2f  */

/* game math lib (all f32-in/f32-out, f1 arg / f1 result) */
extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 acosf(f32);
extern f32 asinf(f32);
extern f32 sqrtf(f32);
extern f32 atan2f(f32, f32);
extern f32 fabsf(f32);
/* game helpers */
extern void fn_8002C904(f32 *out, f32 x, f32 y, f32 z);   /* out[0..2] = x,y,z */
extern void fn_8002C8FC(f32 *p, f32 w);                    /* p[3] = w        */
extern f32 fn_80036304(const f32 *v);                      /* sum of squares  */
extern void *fn_80034E74(void *self);                      /* script handle   */
extern s32 fn_80036810(void *handle, s32 id);              /* id -> slot, -1  */

s32 fn_80034EB4(Unk_C8FEE62D *arg0, f32 *arg1) {
    f32 sp1A0;
    f32 sp194;
    f32 sp188;
    f32 sp180;
    f32 sp178;
    f32 sp164;
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp14C;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp134;
    f32 sp124;
    f32 sp118;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 sp198;
    f32 sp170;
    f32 sp168;
    f32 sp150;
    f32 sp128;
    f32 sp3C;
    f32 sp38;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f10;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f11_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f13;
    f32 temp_f19;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f29_3;
    f32 temp_f29_4;
    f32 temp_f29_5;
    f32 temp_f29_6;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f31;
    f32 temp_f31_10;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_5;
    f32 temp_f31_6;
    f32 temp_f31_7;
    f32 temp_f31_8;
    f32 temp_f31_9;
    f32 temp_f3;
    f32 temp_f7;
    f32 temp_f8;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f11;
    f32 var_f11_2;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f13;
    f32 var_f13_2;
    f32 var_f13_3;
    f32 var_f13_4;
    f32 var_f1;
    f32 var_f1_2;
    s32 temp_r0;
    s32 temp_r11;
    void *temp_r19;
    s32 temp_r3;
    s32 temp_r9_2;
    s32 var_r0;
    s32 var_r0_2;
    u32 var_r20;
    f32 *temp_r31;
    Unk_C7387A53 *temp_r9;
    void *var_r28;
    void *var_r29;

    /* unk0x14 is typed s32 in the shared Unk_C8FEE62D but is the vtable
     * pointer here (want: lwz r9,0x14(r25) / lha r3,0x30(r9) / lwz r0,0x34(r9)) */
    temp_r9 = (Unk_C7387A53 *)(void *)arg0->unk0x14;
    var_r20 = 0U;
    var_r29 = (char *)arg0 + 0x70;
    var_r28 = arg0;
    /* want 0x80034F10: lha r3,0x30(r9) / lwz r0,0x34(r9) / add r3,r25,r3 /
     * mtlr r0 / blrl  -> ONE-arg indirect call through the vtable slot. */
    ((void (*)(void *))temp_r9->unk0x34)((char *)arg0 + temp_r9->unk0x30);
    temp_f22 = lbl_80291E24;
    temp_f21 = lbl_80291E3C;
    temp_f19 = lbl_80291E38;
    temp_r19 = (void *)fn_80034E74(arg0);
    do {
        /* r4 (the node id) is set once here and re-used as the SECOND
         * argument of fn_80036810 -- want 0x80034F58 lwz r4,-0x54(r29) ... */
        temp_r3 = *(s32 *)((char *)var_r29 - 0x54);
        if (temp_r3 != -1) {
            temp_r3 = fn_80036810(temp_r19, temp_r3);
            if (temp_r3 != -1) {
                0;
                0;
                0;
                temp_f29 = lbl_80291E24;
                0;
                0;
                0;
                if (0 > temp_f29) {
                    sp124 = lbl_80291E28;
                    0;
                }
                temp_r31 = arg1 + temp_r3 * 4;
                0;
                temp_f31 = acosf(sp128);
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                sp134 = lbl_80291E28;
                0;
                0;
                0;
                0;
                0;
                0;
                if (0 > temp_f29) {
                    0;
                    0;
                    sp13C = lbl_80291E28;
                    0;
                }
                temp_r9_2 = *(s32 *)((char *)var_r29 - 0x48);
                temp_f11 = lbl_80291E28;
                temp_r11 = temp_r9_2 >> 0x1F;
                sp48 = temp_f29;
                sp4C = temp_f29;
                temp_r0 = (temp_r11 ^ temp_r9_2) - temp_r11;
                sp50 = temp_f29;
                sp54 = temp_f11;
                switch (temp_r0) {
                case 0:
                    if (temp_r9_2 < 0) {
                        var_r0 = (s32) -temp_r9_2 / temp_r9_2;
                    } else {
                        var_r0 = temp_r9_2 / temp_r9_2;
                    }
                    temp_f2 = lbl_80291E24;
                    sp144 = temp_f1_2;
                    sp140 = temp_f1_2;
                    sp14C = temp_f1;
                    temp_f1_2 = cosf(temp_f31_2);
                    sp148 = temp_f1;
                    temp_f1 = sinf(temp_f31_2);
                    temp_f31_2 = (f32) var_r0 * temp_f19 * temp_f21;
                    temp_f29_2 = temp_f31 * temp_f21;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    if (sp150 > temp_f2) {
                        var_f0 = lbl_80291E28 / sp150;
                    } else {
                        var_f0 = temp_f2;
                    }
                    temp_f31_3 = var_f0 * sinf(temp_f29_2);
                    fn_8002C904(&sp58, temp_f31_3 * sp38, temp_f31_3 * sp3C, temp_f31_3 * sp40);
                    var_f1 = temp_f29_2;
block_30:
                    fn_8002C8FC(&sp58, cosf(var_f1));
                    0;
                    0;
                    break;
                default:
                    break;
                case 2:
                    if (temp_r9_2 < 0) {
                        var_r0_2 = (s32) -temp_r9_2 / temp_r9_2;
                    } else {
                        var_r0_2 = temp_r9_2 / temp_r9_2;
                    }
                    temp_f29_3 = temp_f31 * temp_f21;
                    temp_f31_4 = (f32) var_r0_2 * temp_f19 * temp_f21;
                    temp_f1_3 = sinf(temp_f31_4);
                    sp160 = temp_f1_3;
                    temp_f1_4 = cosf(temp_f31_4);
                    sp164 = -temp_f1_3;
                    sp15C = temp_f1_4;
                    sp158 = temp_f1_4;
                    temp_f2_2 = lbl_80291E24;
                    0;
                    0;
                    0;
                    0;
                    if (sp168 > temp_f2_2) {
                        var_f0_2 = lbl_80291E28 / sp168;
                    } else {
                        var_f0_2 = temp_f2_2;
                    }
                    temp_f31_5 = var_f0_2 * sinf(temp_f29_3);
                    fn_8002C904(&sp58, temp_f31_5 * sp38, temp_f31_5 * sp3C, temp_f31_5 * sp40);
                    var_f1 = temp_f29_3;
                    goto block_30;
                case 3:
                    temp_f30 = temp_f31 * temp_f21;
                    0;
                    0;
                    0;
                    if (sp170 > temp_f29) {
                        var_f1_2 = temp_f11 / sp170;
                    } else {
                        var_f1_2 = temp_f29;
                    }
                    temp_f31_6 = var_f1_2 * sinf(temp_f30);
                    fn_8002C904(&sp58, temp_f31_6 * sp38, temp_f31_6 * sp3C, temp_f31_6 * sp40);
                    var_f1 = temp_f30;
                    goto block_30;
                }
                temp_f29_4 = sp54 * sp54;
                temp_f12 = sp48 * sp48;
                temp_f11_2 = sp4C * sp4C;
                temp_f0 = sp50 * sp50;
                temp_f28 = atan2f(2.0f * ((sp50 * sp4C) + (sp48 * sp54)), ((temp_f29_4 - temp_f12) - temp_f11_2) + temp_f0);
                temp_f31_7 = asinf(-(2.0f * ((sp50 * sp48) - (sp4C * sp54))));
                temp_f1_5 = atan2f(2.0f * ((sp48 * sp4C) + (sp50 * sp54)), ((temp_f29_4 + temp_f12) - temp_f11_2) - temp_f0);
                sp58 = temp_f28;
                sp5C = temp_f31_7;
                sp60 = temp_f1_5;
                sp64 = lbl_80291E28;
                if ((s32) ((Unk_DB0E2BAB *)var_r29)->unk0x18 != 0) {
                    0;
                    temp_f12_2 = *(s32 *)((char *)var_r29 - 0x30);
                    0;
                    var_f13 = sp88;
                    if (sp88 > temp_f12_2) {
                        var_f13 = temp_f12_2;
                    }
                    temp_f0_2 = ((Unk_C7387A53 *)var_r28)->unk0x30;
                    var_f12 = var_f13;
                    if (var_f13 < temp_f0_2) {
                        var_f12 = temp_f0_2;
                    }
                    sp88 = var_f12;
                    temp_f12_3 = ((Unk_C7387A53 *)var_r28)->unk0x44;
                    temp_f0_3 = sp8C;
                    var_f13_2 = temp_f0_3;
                    if (temp_f0_3 > temp_f12_3) {
                        var_f13_2 = temp_f12_3;
                    }
                    temp_f0_4 = ((Unk_C7387A53 *)var_r28)->unk0x34;
                    var_f11 = var_f13_2;
                    if (var_f13_2 < temp_f0_4) {
                        var_f11 = temp_f0_4;
                    }
                    temp_f0_5 = sp90;
                    temp_f12_4 = ((Unk_C7387A53 *)var_r28)->unk0x48;
                    sp8C = var_f11;
                    var_f13_3 = temp_f0_5;
                    if (temp_f0_5 > temp_f12_4) {
                        var_f13_3 = temp_f12_4;
                    }
                    temp_f0_6 = ((Unk_C7387A53 *)var_r28)->unk0x38;
                    var_f11_2 = var_f13_3;
                    if (var_f13_3 < temp_f0_6) {
                        var_f11_2 = temp_f0_6;
                    }
                    var_f13_4 = temp_f0_7;
                    sp90 = var_f11_2;
                    temp_f12_5 = ((Unk_C7387A53 *)var_r28)->unk0x4C;
                    temp_f0_7 = sp94;
                    if (temp_f0_7 > temp_f12_5) {
                        var_f13_4 = temp_f12_5;
                    }
                    temp_f0_8 = ((Unk_C7387A53 *)var_r28)->unk0x3C;
                    var_f12_2 = var_f13_4;
                    if (var_f13_4 < temp_f0_8) {
                        var_f12_2 = temp_f0_8;
                    }
                    sp94 = var_f12_2;
                    sp178 = *(s32 *)((char *)var_r29 - 0x4C);
                    0;
                    0;
                    0;
                    0;
                } else {
                    if (temp_f28 < ((Unk_C7387A53 *)var_r28)->unk0x30) {
                        sp58 = temp_f22;
                    }
                    if (temp_f31_7 < ((Unk_C7387A53 *)var_r28)->unk0x34) {
                        sp5C = temp_f22;
                    }
                    if (temp_f1_5 < ((Unk_C7387A53 *)var_r28)->unk0x38) {
                        sp60 = temp_f22;
                    }
                    if (sp58 > ((Unk_C7387A53 *)var_r28)->unk0x40) {
                        sp58 = temp_f22;
                    }
                    if (sp5C > ((Unk_C7387A53 *)var_r28)->unk0x44) {
                        sp5C = temp_f22;
                    }
                    if (sp60 > ((Unk_C7387A53 *)var_r28)->unk0x48) {
                        sp60 = temp_f22;
                    }
                }
                temp_f24 = lbl_80291E24;
                temp_f23 = lbl_80291E28;
                sp78 = temp_f24;
                sp7C = temp_f24;
                sp80 = temp_f24;
                sp84 = temp_f23;
                temp_f25 = *(s32 *)&lbl_80291E3C;
                temp_f31_8 = sp60 * temp_f25;
                temp_f30_2 = sp5C * temp_f25;
                temp_f29_5 = cosf(temp_f31_8);
                temp_f28_2 = sp58 * temp_f25;
                temp_f26 = cosf(temp_f30_2);
                temp_f27 = cosf(temp_f28_2);
                temp_f31_9 = sinf(temp_f31_8);
                temp_f30_3 = sinf(temp_f30_2);
                temp_f1_6 = sinf(temp_f28_2);
                temp_f0_9 = temp_f31_9 * temp_f26;
                temp_f2_3 = temp_r31[3];
                temp_f31_10 = temp_f31_9 * temp_f30_3;
                temp_f13 = temp_f29_5 * temp_f30_3;
                temp_f29_6 = temp_f29_5 * temp_f26;
                temp_f1_7 = (temp_f29_6 * temp_f1_6) - (temp_f31_10 * temp_f27);
                sp78 = temp_f1_7;
                sp188 = temp_f2_3;
                sp80 = (temp_f0_9 * temp_f27) - (temp_f13 * temp_f1_6);
                sp7C = (temp_f13 * temp_f27) + (temp_f0_9 * temp_f1_6);
                sp84 = (temp_f29_6 * temp_f27) + (temp_f31_10 * temp_f1_6);
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                sp180 = spA4;
                sp194 = temp_f23;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                spA4 = temp_f3;
                spA0 = spD0;
                temp_f3 = (spA4 * temp_f2_3) - sp198;
                sp9C = spCC;
                sp98 = spC8;
                0;
                0;
                0;
                /* want 0x80035860: mr r3,r31 / bl fn_80036304 / bl sqrtf --
                 * fn_80036304 already returns the sum of the 4 squares. */
                temp_f1_8 = sqrtf(fn_80036304(temp_r31));
                if (temp_f1_8 > temp_f24) {
                    sp1A0 = temp_f23 / temp_f1_8;
                    0;
                    0;
                }
                temp_f8 = temp_r31[1];
                temp_f10 = temp_r31[0];
                temp_f9 = temp_r31[2];
                temp_f11_3 = temp_r31[3];
                temp_f7 = lbl_80291E40;
                temp_f12_6 = (((Unk_DB0E2BAB *)var_r29)->unk0xC * temp_f11_3) + ((((Unk_DB0E2BAB *)var_r29)->unk0x8 * temp_f9) + ((((Unk_DB0E2BAB *)var_r29)->unk0x0 * temp_f10) + (((Unk_DB0E2BAB *)var_r29)->unk0x4 * temp_f8)));
                if (temp_f12_6 < temp_f7) {
                    sp118 = (fabsf(temp_f12_6) * lbl_80291E44) / temp_f7;
                    if (temp_f12_6 < temp_f24) {
                        sp78 = -temp_f10;
                        sp7C = -temp_f8;
                        sp84 = -temp_f11_3;
                        sp80 = -temp_f9;
                        0;
                        0;
                    }
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                }
                0;
                0;
            }
        }
        var_r20 += 1;
        var_r29 += 0x78;
        var_r28 += 0x78;
    } while (var_r20 <= 3U);
    return 1;
}
