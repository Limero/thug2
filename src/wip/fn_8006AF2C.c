// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 0.5% while git revision fd28c841b scores 0.9%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 11 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
// family=m2c range=0x8006AF2C-0x8006B5FC size=1744B
//
// PARKED 2026-10-07: 0.92% — this body is an m2c husk, not a
// reconstruction, and no 1:1 type edit can move it; it needs a full rebuild.
// First divergence = INSTRUCTION 0 (the frame).  Facts established this round:
//   PROLOGUE (want): stwu r1,-0x170 / stfd f26,0x140 / f27,0x148 / f28,0x150 /
//     f29,0x158 / f30,0x160 / f31,0x168 / stmw r30,0x138 / stw r0,0x174.
//     GOT: stwu r1,-0x50 / stmw r25 (7 GPRs) / no stfd at all — the draft has
//     no live f32 values (its "matrices" are integer `*(s32*)` products), so
//     nothing is callee-saved: frame 0x50 vs 0x170.
//   WHY it is a husk:
//    (1) the file-scope `static s32 sp4C..spC4` block is fabricated — the want
//        touches NOTHING static; every operand is r1-/r31-relative.  If reused
//        at all these must be LOCALS.
//    (2) m2c modelled the f32 matrix slots as s32: every
//        `(*(s32 *)((char *)&sp8 + N) * spM)` must be f32 (want emits lfs +
//        fmuls/fmadds), and `s32 sp8` must be the 0x40-byte 4x4 at r1+8 (want
//        `addi r3,r1,8`, `psq_st ...,8(r1)`).
//    (3) the three empty `do { ctr -= 1; } while (ctr)` loops are a degenerate
//        m2c stand-in for want's three SELF-TARGETING `li r0,4 / mtctr r0 /
//        bdnz $` store windows (doc-30 scheduler-sunk stores).
//   WANT STRUCTURE (from the PS decode, for the next attempt):
//     a. psq_l arg0+0x88/0x90/0x98/0xA0 -> ps_add with the pairs at
//        lbl_80294AF0/lbl_80294AF4 -> psq_st to r1+0xC8 and r1+0xD0.
//     b. r0 = *(u32 *)(arg0+0xCC); `if (r0 & 2)` -> bl 0x8000433C(r3=r1+0x48,
//        f1=x->0x68, f2=f1, f3=lbl_80294AF8, f4=x->0xA8): 4x4 f32 multiply,
//        16 outputs fmuls/fmadds into r1+0xE8..0x128.  `if (r0 & 4)` ->
//        bl 0x80004404(r3=r1+0x88, f1=x->0x6C, f2=x->0x70, f3=lbl_80294AF8,
//        f4=x->0xA8): the same 16-output chain.
//     c. tail: psq_l r1+0x100/0xE8/0xF0/0xF8 -> psq_st arg0+0x40/0x28/0x30/0x38;
//        psq_l r1+0x108/0x110/0x118/0x120 -> psq_st r11+0x20/0x28/0x30;
//        then `b 0x8006B5CC` (still inside the function).
//   NOTE: the draft's `fn_80004104(&sp8, arg0+0x98, &spC8, &spD8, 0x80290000,
//        ...)` call does NOT exist in the want — it is an m2c fabrication.
//
// 1:1 EDITS MADE THIS ROUND (want instruction each reproduces):
//   * declared the two callees' real signatures (verified against the promoted
//     sources src/fn_8000433C.c = `void (s32, f32, f32, f32, f32)` and
//     src/fn_80004404.c = `void *(Matrix44 *, f32, f32, f32, f32)`; want here
//     has r3 = stack matrix and f1-f4 = lfs'd SINGLE floats).  Without the
//     prototype the float args were promoted to double and the call sites
//     emitted f64 arithmetic (GOT 0xD0-0x150 `lfd/fsub/frsp`).
//   * the five operands at those sites were read as `*(s32*)` and converted to
//     float; want uses `lfs` for exactly those four slots (0x68/0x6C/0x70/0xA8)
//     and the lbl_80294AF8 constant — changed the reads to `*(f32 *)`.
static s32 sp128;
static s32 sp12C;
static s32 sp130;
static s32 sp134;
static s32 sp4C;
static s32 sp50;
static s32 sp54;
static s32 sp58;
static s32 sp5C;
static s32 sp60;
static s32 sp64;
static s32 sp68;
static s32 sp6C;
static s32 sp70;
static s32 sp74;
static s32 sp78;
static s32 sp7C;
static s32 sp80;
static s32 sp84;
static s32 sp8C;
static s32 sp90;
static s32 sp94;
static s32 sp98;
static s32 sp9C;
static s32 spA0;
static s32 spA4;
static s32 spA8;
static s32 spAC;
static s32 spB0;
static s32 spB4;
static s32 spB8;
static s32 spBC;
static s32 spC0;
static s32 spC4;

void fn_80004104(s32, s32, s32, s32, s32, s32, s32);
/* want 0xD0 / 0x3CC: r3 = stack matrix pointer, f1-f4 = single-precision args
   (lfs, NOT promoted doubles). */
void fn_8000433C(void *, f32, f32, f32, f32);
void *fn_80004404(void *, f32, f32, f32, f32);
void fn_8006AF2C(void *arg0) {
    f32 *sp134;
    s32 *sp130;
    f32 *sp12C;
    s32 *sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 sp88;
    f32 sp48;
    s32 sp8;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f1;
    s32 temp_r0;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;

    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_ctr_2 = 4;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_ctr_3 = 4;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    0;
    temp_f12 = *(f32 *)0x80294AF0;
    0;
    temp_f11 = *(f32 *)0x80294AF4;
    0;
    0;
    spD8 = temp_f12;
    *(s32 *)((char *)&spD8 + 0x4) = temp_f11;
    *(s32 *)((char *)&spD8 + 0xC) = temp_f12;
    *(s32 *)((char *)&spD8 + 0x8) = temp_f12;
    fn_80004104(&sp8, arg0 + 0x98, &spC8, &spD8, 0x80290000, temp_f11, temp_f12);
    temp_r0 = *(s32 *)((char *)arg0 + (s32)0xCC);
    if (temp_r0 & 2) {
        temp_f1 = *(f32 *)((char *)arg0 + (s32)0x68);
        fn_8000433C(&sp48, temp_f1, temp_f1, *(f32 *)0x80294AF8, *(f32 *)((char *)arg0 + (s32)0xA8));
        sp12C = &sp48;
        sp128 = &sp8;
        spE8 = (*(s32 *)((char *)&sp8 + 0xC) * sp78) + ((*(s32 *)((char *)&sp8 + 0x8) * sp68) + ((*(s32 *)((char *)&sp8 + 0x0) * sp48) + (*(s32 *)((char *)&sp8 + 0x4) * sp58)));
        spEC = (*(s32 *)((char *)&sp8 + 0xC) * sp7C) + ((*(s32 *)((char *)&sp8 + 0x8) * sp6C) + ((*(s32 *)((char *)&sp8 + 0x0) * sp4C) + (*(s32 *)((char *)&sp8 + 0x4) * sp5C)));
        spF0 = (*(s32 *)((char *)&sp8 + 0xC) * sp80) + ((*(s32 *)((char *)&sp8 + 0x8) * sp70) + ((*(s32 *)((char *)&sp8 + 0x0) * sp50) + (*(s32 *)((char *)&sp8 + 0x4) * sp60)));
        spF4 = (*(s32 *)((char *)&sp8 + 0xC) * sp84) + ((*(s32 *)((char *)&sp8 + 0x8) * sp74) + ((*(s32 *)((char *)&sp8 + 0x0) * sp54) + (*(s32 *)((char *)&sp8 + 0x4) * sp64)));
        spF8 = (*(s32 *)((char *)&sp8 + 0x1C) * sp78) + ((*(s32 *)((char *)&sp8 + 0x18) * sp68) + ((*(s32 *)((char *)&sp8 + 0x10) * sp48) + (*(s32 *)((char *)&sp8 + 0x14) * sp58)));
        spFC = (*(s32 *)((char *)&sp8 + 0x1C) * sp7C) + ((*(s32 *)((char *)&sp8 + 0x18) * sp6C) + ((*(s32 *)((char *)&sp8 + 0x10) * sp4C) + (*(s32 *)((char *)&sp8 + 0x14) * sp5C)));
        sp100 = (*(s32 *)((char *)&sp8 + 0x1C) * sp80) + ((*(s32 *)((char *)&sp8 + 0x18) * sp70) + ((*(s32 *)((char *)&sp8 + 0x10) * sp50) + (*(s32 *)((char *)&sp8 + 0x14) * sp60)));
        sp104 = (*(s32 *)((char *)&sp8 + 0x1C) * sp84) + ((*(s32 *)((char *)&sp8 + 0x18) * sp74) + ((*(s32 *)((char *)&sp8 + 0x10) * sp54) + (*(s32 *)((char *)&sp8 + 0x14) * sp64)));
        sp108 = (*(s32 *)((char *)&sp8 + 0x2C) * sp78) + ((*(s32 *)((char *)&sp8 + 0x28) * sp68) + ((*(s32 *)((char *)&sp8 + 0x20) * sp48) + (*(s32 *)((char *)&sp8 + 0x24) * sp58)));
        sp10C = (*(s32 *)((char *)&sp8 + 0x2C) * sp7C) + ((*(s32 *)((char *)&sp8 + 0x28) * sp6C) + ((*(s32 *)((char *)&sp8 + 0x20) * sp4C) + (*(s32 *)((char *)&sp8 + 0x24) * sp5C)));
        sp110 = (*(s32 *)((char *)&sp8 + 0x2C) * sp80) + ((*(s32 *)((char *)&sp8 + 0x28) * sp70) + ((*(s32 *)((char *)&sp8 + 0x20) * sp50) + (*(s32 *)((char *)&sp8 + 0x24) * sp60)));
        sp114 = (*(s32 *)((char *)&sp8 + 0x2C) * sp84) + ((*(s32 *)((char *)&sp8 + 0x28) * sp74) + ((*(s32 *)((char *)&sp8 + 0x20) * sp54) + (*(s32 *)((char *)&sp8 + 0x24) * sp64)));
        sp118 = (*(s32 *)((char *)&sp8 + 0x3C) * sp78) + ((*(s32 *)((char *)&sp8 + 0x38) * sp68) + ((*(s32 *)((char *)&sp8 + 0x30) * sp48) + (*(s32 *)((char *)&sp8 + 0x34) * sp58)));
        sp11C = (*(s32 *)((char *)&sp8 + 0x3C) * sp7C) + ((*(s32 *)((char *)&sp8 + 0x38) * sp6C) + ((*(s32 *)((char *)&sp8 + 0x30) * sp4C) + (*(s32 *)((char *)&sp8 + 0x34) * sp5C)));
        sp120 = (*(s32 *)((char *)&sp8 + 0x3C) * sp80) + ((*(s32 *)((char *)&sp8 + 0x38) * sp70) + ((*(s32 *)((char *)&sp8 + 0x30) * sp50) + (*(s32 *)((char *)&sp8 + 0x34) * sp60)));
        sp124 = (*(s32 *)((char *)&sp8 + 0x3C) * sp84) + ((*(s32 *)((char *)&sp8 + 0x38) * sp74) + ((*(s32 *)((char *)&sp8 + 0x30) * sp54) + (*(s32 *)((char *)&sp8 + 0x34) * sp64)));
        0;
        0;
        0;
        0;
        goto block_10;
    }
    if (temp_r0 & 4) {
        fn_80004404(&sp88, *(f32 *)((char *)arg0 + (s32)0x6C), *(f32 *)((char *)arg0 + (s32)0x70), *(f32 *)0x80294AF8, *(f32 *)((char *)arg0 + (s32)0xA8));
        sp134 = &sp88;
        sp130 = &sp8;
        spC8 = (*(s32 *)((char *)&sp8 + 0xC) * spB8) + ((*(s32 *)((char *)&sp8 + 0x8) * spA8) + ((*(s32 *)((char *)&sp8 + 0x0) * sp88) + (*(s32 *)((char *)&sp8 + 0x4) * sp98)));
        spCC = (*(s32 *)((char *)&sp8 + 0xC) * spBC) + ((*(s32 *)((char *)&sp8 + 0x8) * spAC) + ((*(s32 *)((char *)&sp8 + 0x0) * sp8C) + (*(s32 *)((char *)&sp8 + 0x4) * sp9C)));
        spD0 = (*(s32 *)((char *)&sp8 + 0xC) * spC0) + ((*(s32 *)((char *)&sp8 + 0x8) * spB0) + ((*(s32 *)((char *)&sp8 + 0x0) * sp90) + (*(s32 *)((char *)&sp8 + 0x4) * spA0)));
        spD4 = (*(s32 *)((char *)&sp8 + 0xC) * spC4) + ((*(s32 *)((char *)&sp8 + 0x8) * spB4) + ((*(s32 *)((char *)&sp8 + 0x0) * sp94) + (*(s32 *)((char *)&sp8 + 0x4) * spA4)));
        spD8 = (*(s32 *)((char *)&sp8 + 0x1C) * spB8) + ((*(s32 *)((char *)&sp8 + 0x18) * spA8) + ((*(s32 *)((char *)&sp8 + 0x10) * sp88) + (*(s32 *)((char *)&sp8 + 0x14) * sp98)));
        spDC = (*(s32 *)((char *)&sp8 + 0x1C) * spBC) + ((*(s32 *)((char *)&sp8 + 0x18) * spAC) + ((*(s32 *)((char *)&sp8 + 0x10) * sp8C) + (*(s32 *)((char *)&sp8 + 0x14) * sp9C)));
        spE0 = (*(s32 *)((char *)&sp8 + 0x1C) * spC0) + ((*(s32 *)((char *)&sp8 + 0x18) * spB0) + ((*(s32 *)((char *)&sp8 + 0x10) * sp90) + (*(s32 *)((char *)&sp8 + 0x14) * spA0)));
        spE4 = (*(s32 *)((char *)&sp8 + 0x1C) * spC4) + ((*(s32 *)((char *)&sp8 + 0x18) * spB4) + ((*(s32 *)((char *)&sp8 + 0x10) * sp94) + (*(s32 *)((char *)&sp8 + 0x14) * spA4)));
        spE8 = (*(s32 *)((char *)&sp8 + 0x2C) * spB8) + ((*(s32 *)((char *)&sp8 + 0x28) * spA8) + ((*(s32 *)((char *)&sp8 + 0x20) * sp88) + (*(s32 *)((char *)&sp8 + 0x24) * sp98)));
        spEC = (*(s32 *)((char *)&sp8 + 0x2C) * spBC) + ((*(s32 *)((char *)&sp8 + 0x28) * spAC) + ((*(s32 *)((char *)&sp8 + 0x20) * sp8C) + (*(s32 *)((char *)&sp8 + 0x24) * sp9C)));
        spF0 = (*(s32 *)((char *)&sp8 + 0x2C) * spC0) + ((*(s32 *)((char *)&sp8 + 0x28) * spB0) + ((*(s32 *)((char *)&sp8 + 0x20) * sp90) + (*(s32 *)((char *)&sp8 + 0x24) * spA0)));
        spF4 = (*(s32 *)((char *)&sp8 + 0x2C) * spC4) + ((*(s32 *)((char *)&sp8 + 0x28) * spB4) + ((*(s32 *)((char *)&sp8 + 0x20) * sp94) + (*(s32 *)((char *)&sp8 + 0x24) * spA4)));
        spF8 = (*(s32 *)((char *)&sp8 + 0x3C) * spB8) + ((*(s32 *)((char *)&sp8 + 0x38) * spA8) + ((*(s32 *)((char *)&sp8 + 0x30) * sp88) + (*(s32 *)((char *)&sp8 + 0x34) * sp98)));
        spFC = (*(s32 *)((char *)&sp8 + 0x3C) * spBC) + ((*(s32 *)((char *)&sp8 + 0x38) * spAC) + ((*(s32 *)((char *)&sp8 + 0x30) * sp8C) + (*(s32 *)((char *)&sp8 + 0x34) * sp9C)));
        sp100 = (*(s32 *)((char *)&sp8 + 0x3C) * spC0) + ((*(s32 *)((char *)&sp8 + 0x38) * spB0) + ((*(s32 *)((char *)&sp8 + 0x30) * sp90) + (*(s32 *)((char *)&sp8 + 0x34) * spA0)));
        sp104 = (*(s32 *)((char *)&sp8 + 0x3C) * spC4) + ((*(s32 *)((char *)&sp8 + 0x38) * spB4) + ((*(s32 *)((char *)&sp8 + 0x30) * sp94) + (*(s32 *)((char *)&sp8 + 0x34) * spA4)));
        0;
        0;
        0;
        0;
block_10:
        0;
    }
}
