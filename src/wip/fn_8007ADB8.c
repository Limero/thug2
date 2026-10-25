// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// PARKED 2026-10-07: first divergence is the STACK MODEL — want
//   `stwu r1,-0xa8` with locals r1+8..0x5b filled by two 8-entry tables
//   (`void *bufs[8]` at r1+0x08, `s32 sizes[8]` at r1+0x28) plus scalars at
//   0x48/0x4c/0x50/0x54/0x58; got `stwu -0x78` because m2c modelled the tables as
//   sp8/sp28 with +/-0x20 byte arithmetic.  want's iterator is also a pre-increment
//   pointer walk (`lwzu r20,4(r28)` + `addi r28,r28,4`).
// scored 11.9% while git revision fd28c841b scores 12.1%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 25 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
// 2026-09-22 literal->symbol substitution: 12.1 -> 12.3 (symbol for 0x802958D8)
// family=m2c range=0x8007ADB8-0x8007B380 size=1480B
// RE-MEASURED 2026-10-07: the 2026-10-07 HEAD body was a compile FAIL
// (ngccc syntax error); this is the newest body that actually compiles, at
// 12.34% masked (restored from commit a27df3aab).
//
// CORRECTED DIAGNOSIS 2026-10-07 — the earlier note's
// "stack model / stwu -0x78" claim is STALE for this body.  The regenerated
// packet shows got `stwu r1,-0xb0` vs want `-0xa8`: the frame is only 8 bytes
// off, so declaring bufs[8]/sizes[8] would OVERSHOOT (the body's many byte-
// arithmetic temporaries already claim that space).  The real prologue diffs,
// verified instruction-by-instruction against build/b34pkt/fn_8007ADB8.diff.txt,
// are as follows. At packet offset 8DD8 the want stores r4 to 0x4c while the
// output stores r19 to 0x58 there, which is one extra dead store. At 8DDC the
// want materialises zero in r16 while the output stores r19 to 0x4c, shifted
// by that extra store. At 8DE4 the want loads r20 with an update-form word
// load from r28 and bumps r28 by 4 at 8DE8, while the output instead adds 8
// to r9 into r24 at 8DE0 and issues a plain word load into r15 from 4(r9)
// at 8DE4.
// Fixes applied this round:
//   1. deleted the unused local `s32 sp5C;` and its `sp5C = 0;` store — the
//      only writer, never read; this removes want-absent `stw r19,0x58` and is
//      the exact source of the 8-byte frame difference, and it realigns the
//      rest of the prologue to want's order (li r19,0 / stw r4,0x4c / li r16,0
//      / stw r19,0x50).
//   2. `void *temp_r28` -> `s32 *temp_r28` and the pointer-advance written as
//      `temp_r20 = *++temp_r28; var_r28 = temp_r28 + 1;` so ngccc emits want's
//      fused `lwzu r20,4(r28)` + `addi r28,r28,4` (var_r28 must start at
//      *arg0+8, which is what the increment-then-+1 produces).
// STILL OPEN: the rest of the var_r28 walk is written with m2c's byte-arithmetic
// on an `s32 *` (`var_r28 = temp_r28_5 + 4 + 4`, `var_r28 + 4`), i.e. +8 ELEMENTS
// where want advances 8 BYTES; those sites need the same `+ 2` element spelling
// and were deliberately left alone this round to keep the diff evaluable.
extern char lbl_802958D8[];
void fn_80010D94(s32, s32);
void fn_80009A44(s32);
s32 fn_8000F10C(s32, s32, s32, s32);
void fn_8007ADB8(void **arg0, s32 arg1) {
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp28;
    s32 sp8;
    s32 *var_r30;
    s32 *var_r30_2;
    s32 *var_r31;
    s32 *var_r31_3;
    s16 var_r22;
    s32 *var_r28;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r0_8;
    s32 temp_r11;
    s32 temp_r20;
    s32 temp_r25;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r8;
    s32 var_cr0_eq;
    s32 var_cr0_gt;
    s32 var_ctr;
    s32 var_r15;
    s32 var_r16;
    s32 var_r17;
    s32 var_r19;
    s32 var_r27;
    s32 var_r27_3;
    s32 var_r8;
    s8 var_r0;
    u16 temp_r9;
    u16 temp_r9_2;
    u16 temp_r9_4;
    u16 var_r0_2;
    u16 var_r11;
    u32 temp_r0_3;
    u32 var_r26;
    u32 var_r26_2;
    u32 var_r27_2;
    u32 var_r27_4;
    u8 temp_r0_7;
    u8 temp_r24;
    u8 temp_r9_3;
    u8 var_r10;
    u8 var_r10_2;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r11_2;
    s32 *temp_r28;
    void *temp_r28_2;
    void *temp_r28_3;
    void *temp_r28_4;
    void *temp_r28_5;
    void *temp_r28_6;
    void *temp_r28_7;
    void *temp_r3;
    void *temp_r3_2;
    void *temp_r3_3;
    void *temp_r3_4;
    void *temp_r3_5;
    void *temp_r3_6;
    void *var_r31_2;
    void *var_r31_4;

    temp_r28 = *arg0;
    var_r19 = 0;
    sp4C = arg1;
    var_r16 = 0;
    sp50 = 0;
    temp_r20 = *++temp_r28;
    var_r28 = temp_r28 + 1;
    if ((temp_r20 == 0) || (temp_r3 = *(void **)0x802FFE98, temp_r29 = temp_r20 * 2, temp_r0 = *(void **)0x802FFE98, var_r19 = fn_8000F10C(temp_r3, temp_r20 * 4, 1, *(s32 *)((char *)temp_r3 + (s32)0x118)), temp_r0_2 = *(void **)0x802FFE98, sp50 = fn_8000F10C(temp_r0, temp_r29, 1, *(s32 *)((char *)temp_r0 + (s32)0x118)), var_r16 = fn_8000F10C(temp_r0_2, temp_r29, 1, *(s32 *)((char *)temp_r0_2 + (s32)0x118)), ((var_r19 == 0) == 0))) {
        var_r15 = 0;
        var_r22 = 0;
        if (temp_r20 > 0) {
            var_r17 = 0;
            0;
            do {
                fn_80009A44(0x1C);
                temp_r3_2 = fn_8009B5D8();
                *((s32 *)var_r19 + (var_r22 * 4)) = temp_r3_2;
                var_r10 = 3;
                *(s32 *)((char *)temp_r3_2 + (s32)0x0) = (s32) *(s32 *)((char *)var_r28 + (s32)0x0);
                temp_r28_2 = var_r28 + 4;
                sp48 = *(s32 *)((char *)var_r28 + (s32)0x4);
                temp_r28_3 = temp_r28_2 + 4;
                temp_r9 = *(s32 *)((char *)&sp48 + 0x2);
                sp48 = *(s32 *)((char *)temp_r28_2 + (s32)0x4);
                temp_r28_4 = temp_r28_3 + 4;
                temp_r9_2 = *(s32 *)((char *)&sp48 + 0x2);
                temp_r8 = (temp_r9 + 3) & 0xFFFFFFFC;
                sp48 = *(s32 *)((char *)temp_r28_3 + (s32)0x4);
                temp_r28_5 = temp_r28_4 + 4;
                temp_r11 = (temp_r9_2 + 3) & 0xFFFFFFFC;
                *(u8 *)((char *)temp_r3_2 + (s32)0x8) = (u8) *(u8 *)((char *)&sp48 + 0x3);
                if (temp_r8 > 8) {
                    do {
                        var_r10 += 1;
                    } while ((s32) (1 << var_r10) < temp_r8);
                }
                *(s32 *)((char *)temp_r3_2 + (s32)0x6) = var_r10;
                0;
                var_r10_2 = 3;
                if (temp_r11 > 8) {
                    do {
                        var_r10_2 += 1;
                    } while ((s32) (1 << var_r10_2) < temp_r11);
                }
                *(s32 *)((char *)temp_r3_2 + (s32)0x7) = var_r10_2;
                *(u8 *)((char *)temp_r3_2 + (s32)0x4) = (u8) (temp_r8 - temp_r9);
                *(u8 *)((char *)temp_r3_2 + (s32)0x5) = (u8) (temp_r11 - temp_r9_2);
                if (((s32) (u16) (1 << *(s32 *)((char *)temp_r3_2 + (s32)0x6)) != temp_r8) || ((s32) (u16) (1 << var_r10_2) != temp_r11)) {
                    fn_802640C4(0x8029587C, 0);
                }
                if (((s32) (u16) ((1 << *(s32 *)((char *)temp_r3_2 + (s32)0x6)) - *(u8 *)((char *)temp_r3_2 + (s32)0x4)) != (s32) temp_r9) || ((s32) (u16) ((1 << *(s32 *)((char *)temp_r3_2 + (s32)0x7)) - *(u8 *)((char *)temp_r3_2 + (s32)0x5)) != (s32) temp_r9_2)) {
                    fn_802640C4(lbl_802958D8, 0);
                }
                temp_r0_3 = *(s32 *)((char *)temp_r28_4 + (s32)0x4);
                temp_r25 = temp_r0_3 & 0xF;
                temp_r24 = (u8) (temp_r0_3 >> 8U);
                switch (temp_r25) {                 
                case 0:
                    var_r0 = 0xE;
block_25:
                    *(s32 *)((char *)temp_r3_2 + (s32)0x9) = var_r0;
                    break;
                case 1:
                    var_r0 = 0xE;
                    goto block_25;
                case 2:
                    var_r0 = 6;
                    goto block_25;
                }
                var_r11 = 1;
                *(s32 *)((char *)temp_r3_2 + (s32)0xA) = 0U;
                var_r28 = temp_r28_5 + 4 + 4;
                if ((s32) *(s32 *)((char *)temp_r28_5 + (s32)0x4) == 0) {
                    var_r11 = 0;
                }
                var_r27 = 0;
                *(s32 *)((char *)temp_r3_2 + (s32)0xA) = var_r11;
                var_r26 = 0U;
                if ((u8) *(u8 *)((char *)temp_r3_2 + (s32)0x8) > 0U) {
                    var_r31 = &sp8;
                    do {
                        temp_r3_3 = *(s32 *)0x802FFE98;
                        temp_r30 = *((s32 *)var_r28);
                        var_r26 += 1;
                        temp_r28_6 = var_r28 + 4;
                        var_r27 += temp_r30;
                        temp_r0_4 = fn_8000F10C(temp_r3_3, temp_r30, 1, *(s32 *)((char *)temp_r3_3 + (s32)0x168));
                        *(s32 *)((char *)var_r31 + (s32)0x20) = temp_r30;
                        *(s32 *)((char *)var_r31 + (s32)0x0) = temp_r0_4;
                        fn_8026AE28(temp_r28_6, temp_r30);
                        var_r28 = temp_r28_6 + temp_r30;
                        var_r31 += 4;
                    } while (var_r26 < (u8) *(u8 *)((char *)temp_r3_2 + (s32)0x8));
                }
                fn_80010D94(*(s32 *)((s32 *)(*(s32 *)0x802FFE98) + 0x11C), 0x20);
                temp_r3_4 = fn_80009A78(var_r27);
                *(s32 *)((char *)temp_r3_2 + (s32)0xC) = var_r27;
                *(s32 *)((char *)temp_r3_2 + (s32)0x10) = temp_r3_4;
                fn_80010E78(*(s32 *)((s32 *)(*(s32 *)0x802FFE98) + 0x11C));
                if (0) {
                    fn_8000F320(*(s32 *)0x802FFE98);
                }
                var_r27_2 = 0U;
                var_r31_2 = *(s32 *)((char *)temp_r3_2 + (s32)0x10);
                if ((u8) *(u8 *)((char *)temp_r3_2 + (s32)0x8) > 0U) {
                    var_r30 = &sp28;
                    do {
                        var_r27_2 += 1;
                        fn_8026AE28(var_r31_2, *(s32 *)((char *)var_r30 - 0x20), *(s32 *)((char *)var_r30 + (s32)0x0));
                        fn_80009AAC(*(s32 *)((char *)var_r30 - 0x20));
                        temp_r0_5 = *(s32 *)((char *)var_r30 + (s32)0x0);
                        var_r30 += 4;
                        var_r31_2 += temp_r0_5;
                    } while (var_r27_2 < (u8) *(u8 *)((char *)temp_r3_2 + (s32)0x8));
                }
                if (temp_r25 == 1) {
                    if ((s32) temp_r24 == 0) {
                        var_r27_3 = 0;
                        var_r26_2 = 0U;
                        0;
                        if ((u8) *(u8 *)((char *)temp_r3_2 + (s32)0x8) > 0U) {
                            var_r31_3 = &sp8;
                            do {
                                temp_r3_5 = *(s32 *)0x802FFE98;
                                temp_r30_2 = *((s32 *)var_r28);
                                var_r26_2 += 1;
                                temp_r28_7 = var_r28 + 4;
                                var_r27_3 += temp_r30_2;
                                temp_r0_6 = fn_8000F10C(temp_r3_5, temp_r30_2, 1, *(s32 *)((char *)temp_r3_5 + (s32)0x168));
                                *(s32 *)((char *)var_r31_3 + (s32)0x20) = temp_r30_2;
                                *(s32 *)((char *)var_r31_3 + (s32)0x0) = temp_r0_6;
                                fn_8026AE28(temp_r28_7, temp_r30_2);
                                var_r28 = temp_r28_7 + temp_r30_2;
                                var_r31_3 += 4;
                            } while (var_r26_2 < (u8) *(u8 *)((char *)temp_r3_2 + (s32)0x8));
                        }
                        fn_80010D94(*(s32 *)((s32 *)(*(s32 *)0x802FFE98) + 0x11C), 0x20);
                        *(s32 *)((char *)temp_r3_2 + (s32)0x14) = fn_80009A78(var_r27_3);
                        fn_80010E78(*(s32 *)((s32 *)(*(s32 *)0x802FFE98) + 0x11C));
                        if (0) {
                            fn_8000F320(*(s32 *)0x802FFE98);
                        }
                        temp_r0_7 = *(u8 *)((char *)temp_r3_2 + (s32)0x8);
                        var_r27_4 = 0U;
                        var_r31_4 = *(s32 *)((char *)temp_r3_2 + (s32)0x14);
                        var_cr0_eq = temp_r0_7 == 0;
                        var_cr0_gt = temp_r0_7 < 0U;
                        if (temp_r0_7 > 0U) {
                            var_r30_2 = &sp28;
                            do {
                                var_r27_4 += 1;
                                fn_8026AE28(var_r31_4, *(s32 *)((char *)var_r30_2 - 0x20), *(s32 *)((char *)var_r30_2 + (s32)0x0));
                                fn_80009AAC(*(s32 *)((char *)var_r30_2 - 0x20));
                                temp_r0_8 = *(s32 *)((char *)var_r30_2 + (s32)0x0);
                                temp_r9_3 = *(u8 *)((char *)temp_r3_2 + (s32)0x8);
                                var_r30_2 += 4;
                                var_r31_4 += temp_r0_8;
                                var_cr0_eq = var_r27_4 == temp_r9_3;
                                var_cr0_gt = var_r27_4 > temp_r9_3;
                            } while (var_r27_4 < temp_r9_3);
                        }
                        *(s32 *)((char *)temp_r3_2 + (s32)0xA) = (u16) (*(s32 *)((char *)temp_r3_2 + (s32)0xA) | 2);
                    } else {
                        var_r15 += 1;
                        0;
                        *(s32 *)((char *)temp_r3_2 + (s32)0xA) = (u16) (*(s32 *)((char *)temp_r3_2 + (s32)0xA) | 2);
                        *((s32 *)var_r17 + (s32)sp50) = var_r22;
                        *((s32 *)var_r17 + (s32)var_r16) = (s16) (temp_r0_3 >> 0x10U);
                        var_r17 += 2;
                    }
                    if (var_cr0_eq == 0) {
                        if ((var_cr0_gt == 0) || ((s32) temp_r24 != 2)) {
                            var_r0_2 = *(s32 *)((char *)temp_r3_2 + (s32)0xA) | 4;
                        } else {
                            var_r0_2 = *(s32 *)((char *)temp_r3_2 + (s32)0xA) | 0x10;
                        }
                    } else {
                        var_r0_2 = *(s32 *)((char *)temp_r3_2 + (s32)0xA) | 8;
                    }
                    *(s32 *)((char *)temp_r3_2 + (s32)0xA) = var_r0_2;
                    *(s32 *)((char *)temp_r3_2 + (s32)0xA) = (u16) (*(s32 *)((char *)temp_r3_2 + (s32)0xA) | 0x20);
                } else {
                    *(s32 *)((char *)temp_r3_2 + (s32)0x14) = NULL;
                    *(s32 *)((char *)temp_r3_2 + (s32)0xA) = (u16) ((*(s32 *)((char *)temp_r3_2 + (s32)0xA) & 0xFFFD) | 4);
                }
                fn_80009A44(0x10);
                temp_r3_6 = fn_80077BAC();
                *(s32 *)((char *)temp_r3_6 + (s32)0xC) = temp_r3_2;
                if (0) {
                    fn_8005D380(sp4C, temp_r3_2, temp_r3_6);
                }
                var_r22 += 1;
            } while (var_r22 < temp_r20);
        }
        if (var_r15 > 0) {
            var_ctr = var_r15;
            var_r8 = 0;
            do {
                *(s32 *)((s32 *)(*((s32 *)((char *)var_r19 + (*((s32 *)var_r8 + (s32)sp50) * 4)))) + 0x14) = (s32) *(s32 *)((s32 *)(*((s32 *)var_r19 + (*((s32 *)var_r8 + (s32)var_r16) * 4))) + 0x14);
                temp_r9_4 = *((s32 *)var_r8 + (s32)var_r16);
                var_r8 += 2;
                temp_r11_2 = *((s32 *)((char *)var_r19 + (temp_r9_4 * 4)));
                *(u16 *)((char *)temp_r11_2 + (s32)0xA) = (u16) (*(u16 *)((char *)temp_r11_2 + (s32)0xA) & 0xFFDF);
                var_ctr -= 1;
            } while (var_ctr != 0);
        }
        fn_80009AAC(var_r19);
        fn_80009AAC(sp50);
        fn_80009AAC(var_r16);
    }
    0;
}
