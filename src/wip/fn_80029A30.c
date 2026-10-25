// PARKED 2026-10-05: best measured verdict DIFF — the object is
// 644B (161 words) SHORT of want (1836B vs 2480B) and the frame is 0x70 vs
// want's 0x1a8, so nothing can align yet.  Body left as found (it is the
// best committed body at 1.5%); the notes below are what a rebuild needs.
// family=m2c range=0x80029A30-0x8002A3E0 size=2480B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 1.3% while git revision d105c8962 scores 1.5%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 17 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
//
// ---- structural survey 2026-10-05 (facts, not guesses) --------
// * SHAPE: 620 instructions, and **not one backward branch** (checked every
//   opcode-16 `bc` with AA=1 and every opcode-18 `b/bl` for a negative
//   displacement).  So fn_80029A30 is one huge straight-line / forward-branch
//   if-else chain with NO loops.  The m2c draft's `do { ... } while
//   (var_r26 < self->unk0x2054)` item-list loop is therefore a mis-decode:
//   the loop-shaped code it invented must really be a forward-`beq`-guarded
//   run, or it is the chunk that got lost (which also explains the 644B
//   shortfall).  Start by deleting that loop and see what the size does.
// * CALLS: exactly four, all already declared in this draft —
//   fn_800264FC x1, fn_8002B8E4 x2, fn_8002B8E8 x1.  Nothing else.  So the
//   620 instructions are all local computation + stores.
// * FRAME: want = `stwu -0x1a8`, saves r14..r31 (18 GPRs, 0x140..0x1a4),
//   f28..f31 (0x188..0x1a0), LR@0x1ac  =>  0x140 bytes of *stack locals*
//   (0x00..0x13F).  This draft only needs 0x70 total, i.e. it models ~0x60
//   bytes of locals.  So ~0xE0 bytes of want's stack — roughly 56 dwords or
//   one/two large local structs/arrays that m2c never named — are missing
//   from the reconstruction.  That is the real blocker; the per-statement
//   `Unk_*` casts in this file are secondary.
// * Locals visible in the prologue: a 4-float vector at sp+0x20 (built as
//   {c162c, c162c, c162c, c1630} — the draft already models this one
//   correctly) and two block pointers materialised as `addi r31,r1,0xd0`
//   and `addi r28,r1,0xd8`, i.e. two out-params/refs into the big local
//   area.
// * ARGS: r3=self, r4, r5 held in r30/r29, r7 tested with `or.` at entry,
//   f1 copied to f29 => `s32 (*)(void *self, s32 a1, s32 a2, s32 a3, s32 a4,
//   ..., f32 farg)`-ish; the draft's 5-arg prototype is probably short.
#include "types.h"
#include "structs.h"
static s32 sp10;
static s32 sp100;
static s32 sp14;
static s32 sp18;
static s32 sp80;
static s32 sp84;
static s32 sp88;
static s32 spC;

void fn_8002B8E8(s32, s32);
void fn_8002B8E4(s32);
void fn_800264FC(s32, s32);
s32 fn_80029A30(void *arg0, void *arg1, s32 arg2, void *arg4, f32 farg0) {
    f32 sp110;
    f32 sp108;
    f32 spFC;
    f32 spF0;
    f32 spE8;
    f32 spE0;
    s32 spD8;
    s32 spD0;
    s32 sp70;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f28;
    s16 var_r10_2;
    s16 var_r6;
    s32 temp_r0_2;
    s32 temp_r0_5;
    s32 temp_r11;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r9;
    s32 var_r0;
    s32 var_r10;
    s32 var_r10_3;
    s32 var_r11;
    s32 var_r11_2;
    s32 var_r20;
    s32 var_r24;
    s32 var_r9;
    u16 *var_r22;
    u16 *var_r23;
    u16 temp_r0_6;
    u16 var_r9_2;
    u16 var_r9_3;
    u16 var_r9_4;
    u8 *var_r11_5;
    u8 temp_r0;
    u8 temp_r0_3;
    u8 temp_r0_4;
    void *temp_r11_2;
    void *temp_r9_2;
    void *temp_r9_3;
    void *var_r11_3;
    void *var_r11_4;
    void *var_r11_6;
    void *var_r11_7;
    void *var_r25;
    void *var_r27;
    void *var_r30;

    temp_f0 = *(f32 *)0x8029162C;
    sp20 = temp_f0;
    ((Unk_59AB5482 *)&sp20)->unk0x8 = temp_f0;
    var_r30 = arg1;
    ((Unk_E266FB50 *)&sp20)->unk0xC = (f32) *(f32 *)0x80291630;
    ((Unk_59AB5482 *)&sp20)->unk0x4 = temp_f0;
    var_r27 = ((Unk_C8FEE62D *)arg0)->unk0x10;
    var_r25 = ((Unk_C8FEE62D *)arg0)->unk0x14;
    var_r22 = ((Unk_C8FEE62D *)arg0)->unk0x2C;
    var_r23 = ((Unk_C8FEE62D *)arg0)->unk0x30;
    if ((arg4 != NULL) && ((s32) ((CScript *)arg4)->unk0x208 != 0)) {
        var_r20 = 1 << ((CScript *)arg4)->unk0x210;
    } else {
        var_r20 = 0;
    }
    var_r24 = 0;
    if ((s32) ((Unk_C8FEE62D *)arg0)->unk0x8 > 0) {
        temp_f28 = *(f32 *)0x80291640;
        do {
            if (var_r20 != 0) {
                
                var_r11 = ((!(*((s32 *)((char *)((CScript *)arg4)->unk0x20C + (var_r24 * 4))) & var_r20)) == 0 ? 0 : 1);
            } else {
                var_r11 = 0;
            }
            if (((Unk_C8FEE62D *)arg0)->unk0x4 & 0x80000) {
                var_r11_2 = var_r24;
                if (var_r24 < 0) {
                    var_r11_2 = var_r24 + 0x1F;
                }
                temp_r11 = var_r11_2 >> 5;
                var_r11 = (*((s32 *)((Unk_C8FEE62D *)arg0)->unk0x20 + ((temp_r11 * 4) + 4)) & (1 << (var_r24 - (temp_r11 << 5)))) == 0;
            }
            if (var_r11 == 0) {
                if ((s32) *((s32 *)var_r22) != 0) {
                    temp_r7 = ((Unk_C8FEE62D *)arg0)->unk0x4;
                    var_r6 = 0;
                    temp_r8 = ((Unk_C8FEE62D *)arg0)->unk0xC;
                    if (temp_r7 & 0x100) {
                        var_r6 = ((Unk_41A32F3B *)var_r27)->unk0x0 | (*(s32 *)((char *)var_r27 + (s32)0x1) << 8);
                        var_r10_2 = *(s32 *)((char *)var_r27 + (s32)0x2) | (*(s32 *)((char *)var_r27 + (s32)0x3) << 8);
                        var_r0 = var_r6 & 0x7FFF;
                        var_r9 = var_r10_2 & 0x8000;
                        var_r11_3 = var_r27 + 4;
                    } else {
                        var_r11_3 = var_r27 + 2;
                        var_r10_2 = ((Unk_41A32F3B *)var_r27)->unk0x0 | (*(s32 *)((char *)var_r27 + (s32)0x1) << 8);
                        var_r9 = var_r10_2 & 0x8000;
                        var_r0 = var_r10_2 & 0x7FFF;
                    }
                    ((Unk_D1545B29 *)&spD0)->unk0x0 = (u16) (var_r0 | var_r9);
                    if (var_r10_2 & 0x4000) {
                        if (!(var_r10_2 & 0x3800)) {
                            temp_r0 = ((Unk_8C3FE072_2 *)var_r11_3)->unk0x0;
                            if (temp_r7 & 0x2000) {
                                temp_r9 = temp_r0 * 6;
                                temp_r9_2 = temp_r8 + temp_r9;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) *((s32 *)temp_r8 + (s32)temp_r9);
                                ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) ((Unk_5B449B03 *)temp_r9_2)->unk0x2;
                                ((Unk_D1545B29 *)&spD0)->unk0x0 = (u16) (((Unk_D1545B29 *)&spD0)->unk0x0 & 0x87FF);
                                ((Unk_B0EC4F37 *)&spD0)->unk0x6 = (u16) ((Unk_5B449B03 *)temp_r9_2)->unk0x4;
                            } else {
                                temp_r0_2 = temp_r0 * 8;
                                temp_r9_3 = temp_r0_2 + 0x80362CD8;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) *(u16 *)((char *)temp_r0_2 + (s32)0x80362CD8);
                                ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) ((Unk_5B449B03 *)temp_r9_3)->unk0x2;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x6 = (u16) ((Unk_5B449B03 *)temp_r9_3)->unk0x4;
                                ((Unk_D1545B29 *)&spD0)->unk0x0 = (u16) (((Unk_D1545B29 *)&spD0)->unk0x0 & 0x87FF);
                            }
                        } else {
                            if (temp_r7 & 0x10000) {
                                if (var_r10_2 & 0x2000) {
                                    var_r11_4 = var_r11_3 + 1;
                                    var_r9_2 = *(s32 *)((s32 *)(((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 * 8) + 0x80362CDE);
                                    goto block_31;
                                }
                                if (temp_r7 & 0x8000) {
                                    var_r11_4 = var_r11_3 + 1;
                                    ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) (((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 << 8);
                                } else {
                                    var_r11_4 = var_r11_3 + 2;
                                    var_r9_2 = ((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 | (*(s32 *)((char *)var_r11_3 + (s32)0x1) << 8);
block_31:
                                    ((Unk_B0EC4F37 *)&spD0)->unk0x2 = var_r9_2;
                                }
                                if (var_r10_2 & 0x1000) {
                                    var_r11_5 = var_r11_4 + 1;
                                    var_r9_3 = *(s32 *)((s32 *)(((Unk_9F066EC1 *)var_r11_4)->unk0x0 * 8) + 0x80362CDE);
                                    goto block_37;
                                }
                                if (temp_r7 & 0x8000) {
                                    var_r11_5 = var_r11_4 + 1;
                                    ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) (((Unk_9F066EC1 *)var_r11_4)->unk0x0 << 8);
                                } else {
                                    var_r11_5 = var_r11_4 + 2;
                                    var_r9_3 = ((Unk_9F066EC1 *)var_r11_4)->unk0x0 | (*(s32 *)((char *)var_r11_4 + (s32)0x1) << 8);
block_37:
                                    ((Unk_B0EC4F37 *)&spD0)->unk0x4 = var_r9_3;
                                }
                                if (var_r10_2 & 0x800) {
                                    var_r9_4 = *(s32 *)((s32 *)(*((s32 *)var_r11_5) * 8) + 0x80362CDE);
                                    goto block_57;
                                }
                                if (!(temp_r7 & 0x8000)) {
                                    goto block_56;
                                }
                                goto block_55;
                            }
                            if (var_r10_2 & 0x2000) {
                                var_r11_6 = var_r11_3 + 1;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) ((Unk_8C3FE072_2 *)var_r11_3)->unk0x0;
                            } else if (temp_r7 & 0x8000) {
                                var_r11_6 = var_r11_3 + 1;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) (((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 << 8);
                            } else {
                                var_r11_6 = var_r11_3 + 2;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) (((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 | (*(s32 *)((char *)var_r11_3 + (s32)0x1) << 8));
                            }
                            if (var_r10_2 & 0x1000) {
                                var_r11_5 = var_r11_6 + 1;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) ((Unk_D1545B29 *)var_r11_6)->unk0x0;
                            } else if (temp_r7 & 0x8000) {
                                var_r11_5 = var_r11_6 + 1;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) (((Unk_D1545B29 *)var_r11_6)->unk0x0 << 8);
                            } else {
                                var_r11_5 = var_r11_6 + 2;
                                ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) (((Unk_D1545B29 *)var_r11_6)->unk0x0 | (*(u16 *)((char *)var_r11_6 + (s32)0x1) << 8));
                            }
                            if (var_r10_2 & 0x800) {
                                ((Unk_B0EC4F37 *)&spD0)->unk0x6 = (u16) *((s32 *)var_r11_5);
                            } else if (temp_r7 & 0x8000) {
block_55:
                                ((Unk_B0EC4F37 *)&spD0)->unk0x6 = (u16) (*((s32 *)var_r11_5) << 8);
                            } else {
block_56:
                                var_r9_4 = ((Unk_9F066EC1 *)var_r11_5)->unk0x0 | (*(s32 *)((char *)var_r11_5 + (s32)0x1) << 8);
block_57:
                                ((Unk_B0EC4F37 *)&spD0)->unk0x6 = var_r9_4;
                            }
                            ((Unk_D1545B29 *)&spD0)->unk0x0 = (u16) (((Unk_D1545B29 *)&spD0)->unk0x0 & 0x87FF);
                        }
                    } else if (temp_r7 & 0x8000) {
                        ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) (((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 << 8);
                        ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) (*(s32 *)((char *)var_r11_3 + (s32)0x1) << 8);
                        ((Unk_B0EC4F37 *)&spD0)->unk0x6 = (u16) (((Unk_85F80354 *)var_r11_3)->unk0x2 << 8);
                    } else {
                        ((Unk_B0EC4F37 *)&spD0)->unk0x2 = (u16) (((Unk_8C3FE072_2 *)var_r11_3)->unk0x0 | (*(s32 *)((char *)var_r11_3 + (s32)0x1) << 8));
                        ((Unk_B0EC4F37 *)&spD0)->unk0x4 = (u16) (((Unk_85F80354 *)var_r11_3)->unk0x2 | (*(u16 *)((char *)var_r11_3 + (s32)0x3) << 8));
                        ((Unk_B0EC4F37 *)&spD0)->unk0x6 = (u16) (((Unk_8C3FE072_2 *)var_r11_3)->unk0x4 | (*(u16 *)((char *)var_r11_3 + (s32)0x5) << 8));
                    }
                    if (temp_r7 & 0x100) {
                        ((Unk_D1545B29 *)&spD0)->unk0x0 = (u16) ((((Unk_D1545B29 *)&spD0)->unk0x0 & 0x8000) | (var_r6 & 0x7FFF));
                    }
                    fn_800264FC(&sp8, &spD0);
                    0;
                    spF0 = sp18;
                    0;
                    sp20 = spC;
                    sp24 = sp10;
                    sp28 = sp14;
                    sp2C = sp18;
                    0;
                    0;
                    0;
                    spE8 = sp5C;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    spFC = *(s32 *)0x80291630;
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
                    sp50 = sp80;
                    sp54 = sp84;
                    sp58 = sp88;
                    sp5C = (sp5C * sp18) - sp100;
                    0;
                    0;
                    spE0 = farg0;
                    if (((((CStruct *)var_r30)->unk0xC * sp2C) + ((((CStruct *)var_r30)->unk0x8 * sp28) + ((((CStruct *)var_r30)->unk0x0 * sp20) + (((CStruct *)var_r30)->unk0x4 * sp24)))) < *(s32 *)0x8029162C) {
                        sp50 = -sp20;
                        sp54 = -sp24;
                        sp5C = -sp2C;
                        sp58 = -sp28;
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
                    0;
                    0;
                    0;
                }
                if (!(((Unk_C8FEE62D *)arg0)->unk0x4 & 0x20000) || ((s32) *((s32 *)var_r23) != 0)) {
                    temp_r0_3 = ((Unk_8C3FE072_6 *)var_r25)->unk0x0;
                    var_r10_3 = 0;
                    var_r11_7 = var_r25 + 1;
                    if (temp_r0_3 & 0x80) {
                        var_r10_3 = 1;
                    }
                    if (temp_r0_3 & 0x40) {
                        ((Unk_B0EC4F37 *)&spD8)->unk0x0 = (s16) (temp_r0_3 & 0x3F);
                    } else {
                        temp_r0_4 = *(s32 *)((char *)var_r11_7 + (s32)0x1);
                        var_r11_7 = var_r25 + 3;
                        ((Unk_B0EC4F37 *)&spD8)->unk0x0 = (s16) (*(s16 *)((char *)var_r25 + (s32)0x1) | (temp_r0_4 << 8));
                    }
                    if (var_r10_3 != 0) {
                        temp_r0_5 = ((Unk_8C3FE072_2 *)var_r11_7)->unk0x0 * 8;
                        temp_r11_2 = temp_r0_5 + 0x803634D8;
                        ((Unk_B0EC4F37 *)&spD8)->unk0x2 = (u16) *(u16 *)((char *)temp_r0_5 + (s32)0x803634D8);
                        ((Unk_B0EC4F37 *)&spD8)->unk0x4 = (u16) ((Unk_5B449B03 *)temp_r11_2)->unk0x2;
                        ((Unk_B0EC4F37 *)&spD8)->unk0x6 = (u16) ((Unk_5B449B03 *)temp_r11_2)->unk0x4;
                    } else {
                        ((Unk_B0EC4F37 *)&spD8)->unk0x2 = (u16) (((Unk_8C3FE072_2 *)var_r11_7)->unk0x0 | (*(s32 *)((char *)var_r11_7 + (s32)0x1) << 8));
                        ((Unk_B0EC4F37 *)&spD8)->unk0x4 = (u16) (((Unk_85F80354 *)var_r11_7)->unk0x2 | (*(u16 *)((char *)var_r11_7 + (s32)0x3) << 8));
                        ((Unk_B0EC4F37 *)&spD8)->unk0x6 = (u16) (((Unk_8C3FE072_2 *)var_r11_7)->unk0x4 | (*(u16 *)((char *)var_r11_7 + (s32)0x5) << 8));
                    }
                    0;
                    0;
                    sp30 = (f32) (f64) (s16) ((Unk_B0EC4F37 *)&spD8)->unk0x2 / temp_f28;
                    sp34 = (f32) (f64) (s16) ((Unk_B0EC4F37 *)&spD8)->unk0x4 / temp_f28;
                    sp3C = *(s32 *)0x80291630;
                    sp38 = (f32) (f64) (s16) ((Unk_B0EC4F37 *)&spD8)->unk0x6 / temp_f28;
                    if ((s32) (((Unk_C8FEE62D *)arg0)->unk0x4 & 0x24000) == 0x24000) {
                        sp108 = farg0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        fn_8002B8E4(&sp70);
                    } else {
                        sp110 = farg0;
                        0;
                        0;
                        fn_8002B8E4(&sp70);
                    }
                    0;
                    0;
                    0;
                    0;
                    fn_8002B8E8(&sp50, &sp70);
                    0;
                    0;
                }
            }
            temp_r0_6 = *((s32 *)var_r22);
            var_r24 += 1;
            var_r22 += 2;
            var_r27 += temp_r0_6;
            var_r25 += *((s32 *)var_r23);
            var_r23 += 2;
            var_r30 += 0x10;
        } while (var_r24 < (s32) ((Unk_C8FEE62D *)arg0)->unk0x8);
    }
    return 1;
}
