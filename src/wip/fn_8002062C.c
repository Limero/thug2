// WIP DRAFT (non-matching) — hand-rebuilt from want disassembly
// family=m2c range=0x8002062C-0x80020834 size=520B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 52.3% -> 89.2% — SIZE-EXACT, all relocations
//   verified, 9 words left in ONE call window.
//   Official: `NEAR m2c 0x8002062C (520B) 89.2%`. Object .text 0x208 = 520B =
//   symbols.txt size:0x208 = the range= marker, and the object carries ONLY
//   .text + .rela.text (no private .rodata, so masked-EXACT would be
//   promote-clean, no doc-14 caveat). REL14 5/5 verified (addends +0x148,
//   +0x138 x2, +0x198, +0x1dc), REL24 4/4 (fn_8001E3CC x2, fn_8001E4E8 x2),
//   18 ADDR16_HA/LO pairs, every symbol a real symbols.txt entry.
//   INLINE ASM: 0 emitted instructions (0 __asm__, 0 .long).
//
// SEMANTIC FIXES THAT MATTERED (all four, in the order they paid):
//  1. M8.31 RETURN-TYPE FLIP, both callees `s32` -> `void`: 74.6% -> 89.2%.
//     15 of the 15 remaining words. Their results are discarded at all four
//     sites, and the non-void return made `expand_call` put arg0's `li r3`
//     LAST in the arg-setup window instead of first, in EVERY window. This is
//     the §7e rule-1 shape: an "arg-setup order" residual is a return-type
//     hypothesis first. Abmeasured: void/void 89.2%, fn_8001E3CC-only 88.5%,
//     fn_8001E4E8-only 75.4%, neither 74.6%.
//  2. THE FABRICATED SYMBOL. The draft read `extern s32 lbl_80362CAC;` — that
//     label does NOT exist in symbols.txt; 0x80362C90 is a size:0x20 object
//     and 0x80362CAC is index 7 of it. This is hazard 277's twin on the
//     DECLARE side: a masked score cannot see a wrong label. Fixed to
//     `lbl_80362C90` (which the draft also declared as `[]`).
//  3. THE TAIL LOOP'S BASE NEEDS TWO STATEMENTS (§6dq / the dead-old-value
//     split): `q = lbl_80362C90; q = (char *)q + 0x1C;` emits want's
//     `addi r9,r9,0x2c90` + `addi r9,r9,0x1c` as TWO words. The one-statement
//     `q = (char *)lbl_80362C90 + 0x1C` folds to a single `addi 0x1c` and was
//     the last missing word. 516B -> 520B (52.3% -> 63.6% together with #4).
//  4. THE FILL LOOP NEEDS ITS OWN CONSTANTS AND BIRTH ORDER. Want's preheader
//     is `li r7,0` (ctr) / `li r6,4` (four) / `li r8,0` (zero) / `li r10,0`
//     (byte off) — FOUR distinct `li`s, i.e. a FRESH zero web, not the
//     function's `li r31,0`. The draft reused the function-level `zero` and
//     `four` locals, so ngccc folded them onto r31/r30 and the loop came out
//     2 words short with a rotated base map. Split into `lzero`/`lfour`/`off`
//     and reordered the births to retail's `p1,p3,p4,i=0x10,p5,p2,p6,p7`.
//     Plus the store-run swap `p1,p5,p2,p3,p4,p6,p7` (74.6% at this point).
//  5. The trailing `lbl_80300364 = 0;` needs its OWN literal, not the `zero`
//     variable: want emits a fresh `li r0,0` there (63.6% on its own).
//  6. The 3rd call's four out-param stores go in ONE trailing comma-arg
//     chain (`fn(1,7,7,7,4,0,0, (a,b,c,d))`), which is what produces want's
//     `li x8` then `stw x4`. As separate statements they land before the
//     arg setup; as a per-arg comma chain they land after (74.6%).
//
// THE RESIDUAL — 9 words, all inside WINDOW 2 (the 2nd call, 0x800206D4..):
// the want stores r29 to 0xc(r1), loads immediate 0 into r3, stores r30 to
// 8(r1), loads immediate 0xf into r4, and then emits 8 immediate loads,
// while this build stores r29, loads r3, emits 7 immediate loads, and only
// then stores r30 to 8(r1).
//   Identical instruction multiset; arg1's `sp8[0] = one` store is emitted
//   at the END of the window instead of between arg0's and arg1's `li`.
//   Windows 1, 3 and 4 are BYTE-EXACT with the same comma-arg spelling, so
//   the shape is right and this is a per-site emission tie.
//   MEASURED INERT — do not re-run (8 structural variants, all 88.5-89.2%,
//   none better than the base):
//     - arg0's value via the `zero` VARIABLE instead of literal 0    89.2%
//     - arg0's value as `two - 2` (a 2-user, non-zero-looking expr) 89.2%
//     - the two stores merged into arg0's comma chain               89.2%
//     - arg1's 0xF via the `three` variable                         88.5%
//     - arg0 plain 0 + arg1 carrying both stores                    89.2%
//     - `sp8[1]=two` hoisted to its own statement, arg0 carries only
//       `sp8[0]=one`                                                  89.2%
//     - either store moved into the PREVIOUS call's last arg        30-33% (collapses)
//     - the 3rd call's stores as statements / a per-arg chain        61.7% / 88.5%
//   Nothing tried reaches 100%, so this parks on a genuine per-site
//   `expand_call` tie-break; the same 9 words are what a promoted twin's
//   source would settle (§6dc), but no promoted file calls both callees
//   (only src/fn_8001E4E8.c, the callee itself).
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 lbl_80300348;
extern s32 lbl_8030034C;
extern s32 lbl_80300350;
extern s32 lbl_80300354;
extern s32 lbl_80300358;
extern s32 lbl_8030035C;
extern s32 lbl_80300360;
extern bool lbl_80300364;
extern bool lbl_80362CB0;
extern s32 lbl_80362AD0[];
extern s32 lbl_80362B10[];
extern s32 lbl_80362B50[];
extern s32 lbl_80362B90[];
extern s32 lbl_80362BD0[];
extern s32 lbl_80362C10[];
extern s32 lbl_80362C50[];
extern s32 lbl_80362C90[];
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8002062C(s32 arg0) {
    s32 sp8[4];
    s32 zero;
    s32 one;
    s32 two;
    s32 three;
    s32 four;
    s32 flag;
    s32 i;
    s32 lzero;
    s32 lfour;
    s32 off;
    s32 *p1;
    s32 *p2;
    s32 *p3;
    s32 *p4;
    s32 *p5;
    s32 *p6;
    s32 *p7;
    s32 *q;
    flag = lbl_80300360;
    zero = 0;
    lbl_80300348 = zero;
    lbl_8030034C = zero;
    lbl_80300350 = zero;
    lbl_80300354 = zero;
    lbl_80300358 = zero;
    lbl_8030035C = zero;
    if (flag != 0) {
        if ((arg0 != 0) && (lbl_80362CB0 != 0)) {
            one = 1;
            two = 2;
            three = 3;
            fn_8001E3CC((sp8[0] = one, 0), (sp8[1] = two, 7), (sp8[2] = zero, 7),
                        (sp8[3] = zero, 7), 7, 0, 0, 0);
            fn_8001E4E8((sp8[1] = two, 0), (sp8[0] = one, 0xF), 0xF, 0xF, 8, 0, 0, 0);
            fn_8001E3CC(1, 7, 7, 7, 4, 0, 0,
                        (sp8[2] = zero, (sp8[0] = one, (sp8[1] = three, (sp8[3] = one, 0)))));
            fn_8001E4E8((sp8[0] = one, 1), (sp8[1] = three, 8), 0xF, 0xF, 4, 0, 0, 0);
        }
        lbl_80300348 = lbl_80300348 + 2;
    }
    p1 = lbl_80362BD0;
    p4 = lbl_80362C50;
    p3 = lbl_80362C10;
    i = 0x10;
    p5 = lbl_80362AD0;
    p2 = lbl_80362B10;
    p6 = lbl_80362B50;
    p7 = lbl_80362B90;
    lfour = 4;
    lzero = 0;
    off = 0;
    i = 0;
    for (;;) {
        p1[i] = lzero;
        p5[i] = i & 7;
        p2[i] = i & 7;
        p3[i] = lzero;
        p4[i] = lzero;
        p6[i] = lfour;
        p7[i] = lzero;
        i++;
        off += 4;
        if (i == 0x10) break;
    }
    q = lbl_80362C90;
    q = (s32 *)((char *)q + 0x1C);
    i = 8;
    do {
        *q = 0x3C;
        q = (s32 *)((char *)q - 4);
        i -= 1;
    } while (i != 0);
    lbl_80300364 = 0;
}
// 2026-10-22: 90.8% (was 89.2%): `p4` assigned before `p3`, `lfour` before `lzero`.
