// PARKED 2026-09-30: 69.7% -> 70.2% (object SIZE-EXACT 1596B throughout)
// REVIEWED 2026-10-18 (random triage): residual unchanged (ctor mr-pair +
// 2-reg rotation + arg-setup perm + stb sink + mr r11,r9); each has a recorded
// dead-end list above. Needs the mr-r11 breakthrough first. Body untouched.
// NEAR 70.2% (118/399 words differ, SIZE-EXACT 1596B, only .text+.rela.text).
// Was 4.2% DIFF (m2c husk: frame -0x90 vs want -0xC0, no mfcr CR-save,
// register roles permuted body-wide).  Full HAND REBUILD from the disasm.
// family=m2c range=0x800914C4-0x80091B00 size=1596B
//
// ============================ ROUND r4 (r4-w08) ===========================
// Object .text was ALREADY 0x63C = 1596B at the recorded 69.7%, so the masked %
// was trustworthy (AGENTS 6cs-1/6es) and the work was NOT a length hunt.
// Contiguous-run map of the 121 residual words (want_got.py, masked-diff
// blocks):  ONE 64-word block at +0x11C..+0x218, then a 1-2 word scatter
// all the way to +0x594 (its tail).  Everything before +0x11C was clean.
// So the whole residual is the loop head + one register rotation.
//
// r4-1  M8.31 RETURN-TYPE FLIP on fn_80014904 -- THE ROUND'S ONE REAL WIN.
//   The draft declared `void fn_80014904(s32*,s32,s32,s32)`.  The PROMOTED,
//   BYTE-IDENTICAL callee source `src/fn_80014904.c` declares
//       s32 fn_80014904(void *arg0, s32 arg1, s32 arg2, s32 arg3)
//   and `src/fn_80016928.c` (also promoted) calls it as `s32`.  Flipping the
//   draft's proto void->s32 moved arg0's `mr r3, r24` from FIRST to LAST in
//   BOTH `fn_80014904(p50,4,1,h)` arg windows -- exactly want's
//   `li r4 / li r5 / mr r6 / mr r3 r24`.  69.7% -> 70.2%, still 1596B.
//   This is AGENTS 6fe's diagnostic verbatim ("the diff is the same 4-word
//   transposition inside every call's arg window -> run the M8.31 return-type
//   flip first, do NOT grind statement order or flags") and 6dc/6di's rule
//   that a promoted callee is the arity/type oracle.  `void*` vs `s32*` for
//   the first param is neutral (both 70.2%).  The same flip is load-bearing on
//   the ctor body below too (+2.0% there).
//
// r4-2  THE CTOR PROTOTYPE IS PROVABLY WRONG HERE -- but FIXING IT COSTS 4 BYTES.
//   `src/fn_80077428.c` (PROMOTED, byte-identical) has, verbatim:
//       void *fn_8009B5D8(void *arg0);
//       temp_r0 = fn_8009B5D8(Mem_Alloc2(0x1C));
//   and the ctor body is `mr r9,r3; li r0,0; sth/stw x3; blr` -- it never
//   writes r3, so it RETURNS `this` (the SN C++ ctor ABI).  So the correct
//   source is `item = fn_8009B5D8((I914C4 *)Mem_Alloc2(0x1C));`, not a void
//   call on a separate statement.  MEASURED, and it is NOT a net win yet:
//     * it makes GOT's loop head match want EXACTLY -- the spurious
//       `mr r29,r3` + `mr r3,r29` pair around the ctor disappears and the
//       shape becomes `bl ctor / slwi / mr rX,r3 / stwx rX` = want's;
//     * BUT the object goes 1596 -> 1592 (-1 word), so the masked score
//       collapses to ~29% PURELY from the 1-word index shift (the structural
//       hit count only goes 189 -> 139, and a +-1 re-align recovers 139).
//   The missing word is `mr r11, r9` at 0x800916DC -- want copies the masked
//   value into r11 and the switch's ROOT and LEFT subtree compare r11 while
//   the RIGHT subtree compares r9 (i.e. retail had two webs for the switch
//   operand and the stored value).  MEASURED DEAD ENDS for that one word
//   (all keep 1592B or overshoot, none produces the copy):
//     * `s32 sv = fr.a54 & 0xF;` + separate `fr.a54 = fr.a54 & 0xF;` + switch(sv)
//       -> 1592B, 2 webs but GCC still CSEs them (27.07%, inert);
//     * same + `__asm__("" : "+r"(sv));` -> 1592B, 26.57% (worse);
//     * `register s32 sv __asm__("r11"/"r9"/"r0")` -> 1592B, pin never binds
//       (the store's web wins; 26.8-28.8%);
//     * switch on `(s32)(u8)(fr.a54 & 0xF)` or a `u8 sv` -> 1600B (+1, wrong);
//     * `sv = *(volatile s32 *)&fr.a54;` before the mask -> 1596B and 77.7%!
//       ...but it is a FALSE FRIEND: it replaces want's `clrlwi r9,r0,0x1c`
//       with an `lwz r9,0x54(r1)` RELOAD of the UNMASKED value, so the
//       switch no longer sees the low nibble.  Semantically wrong -- do not
//       ship it; it only re-aligns the index.
//     * replacing the switch with an if/goto chain (6ag-1) -> 1584/1580B,
//       19.3%/30.1%.  The median-rooted 3-case switch tree is CORRECT.
//   NEXT ROUND: the ctor fix is the right semantics and the 64-word block is
//   solved by it; the whole remaining barrier is that single `mr r11, r9`,
//   after which the body is a 2-register rotation (below) and ~95%.
//
// r4-3  The residual after r4-1/r4-2 is a PURE 2-REGISTER ROTATION, and hard
//   pins do NOT reach it (all re-measured on the ctor body, 6bx/6bf-A):
//     want {item:r31, w1:r29, w2:r30, m5:r28}   GOT {item:r29, w1:r28, w2:r30, m5:r28}
//   w1 and m5 do NOT overlap (w1 dies at +0x194, m5 is born at +0x1E8), so the
//   r28 sharing is legal register reuse, not a collision.  Pins measured on
//   the ctor body: item->r31 INERT (76-178: pointer pins dropped; also 7a-137
//   because it is a call-result web), item as an `s32` carrier pinned r31
//   COSTS 8B, w1->r29 costs 8B, m5->r28 +1.0%, everything else inert.
//   This is a `local_alloc` decision (6es-2) -- 6fq-1's "pin the member that
//   must MOVE" does not apply because the member that must move (item) is
//   exactly the one whose pin is dropped.
//
// r4-4  Also measured, all inert or worse, do NOT re-try: `"+r"(p50)` barriers
//   (volatile or not) before/after the p50 calls -> 1580B (AGENTS 6bh-2/6eb:
//   a barrier on p50 is the wrong lever once M8.31 fixed the order);
//   passing `&fr.a50` inline at the p50 call; `+r`(m24) (perturbs m24 to r26
//   and does not split the switch web).
// =============================================================================
//
// WHAT WAS DONE (each was worth points; keep them if you continue):
//  1. Frame-template struct local (AGENTS 6q-86 / fn_8003F93C) reproduces the exact
//     slot map: a8[8]@0x08 a28[8]@0x28 a48..a5C@0x48..0x5C, then a60 + the two
//     SPILLED pointer slots p54@0x64 / p58@0x68 as separate locals, then 8 free
//     bytes, mfcr CR-save@0x74, stmw r14@0x78, frame -0xC0.  <-- the single biggest
//     win (17% -> 52%): a plain `volatile double`-less locals list makes ngccc
//     2.95 order the 4-byte out-params wrongly (sp50 lands after sp58).
//     NOTE: the struct is 22 words so it is 8-aligned and NOT padded; adding the
//     2 pointer members to the struct instead puts p54/p58 at 0x68/0x6c (wrong)
//     and also reorders the preheader, so keep them separate.
//  2. The three `p54=&fr.a54 / p58=&fr.a58 / p50=&fr.a50` assignments must be the
//     FIRST statements INSIDE the main loop so LICM hoists them into the loop
//     preheader (after the guard).  Written before the loop they get hoisted
//     above the three fn_8000F10C allocations (5-instruction shift).
//  3. PER-PHASE WEB SPLIT: the final `for (k = 0; k < np; k++)` needs its OWN
//     variable (k2).  Sharing `k` with the sub-item/refill/memcpy loops stops
//     ngccc converting the countdown to mtctr/bdnz (it emits addic./bne) and
//     costs 4 bytes.  61% -> 67.7%.
//  4. Path B was MISSING `item->unk0xA |= 2` and the whole
//     `node = fn_80077BAC(Mem_Alloc2(0x10)); node[3] = item;` pair (m2c dropped
//     both).  52.9% -> 61%.
//  5. The tail flag chain `if(m24==1)|=8; else if(m24<=1)|=4; else if(m24==2)|=0x10;
//     else |=4;` needs the GOTO form (labels lb4/lb8/lb10/ljoin) so all three test
//     arms land out-of-line and the `|=4` block is the fall-through.  The if/else-if
//     form inlines the FIRST arm and the whole chain shifts.  67.7% -> 69.7%.
//  6. m2c's decode of the byte extract was RIGHT and must not be "fixed":
//     `rlwinm r25,r0,0x18,0x18,0x1f` is `(x >> 8) & 0xFF`, i.e. m2c's
//     `(u8)((u32)sp54 >> 8U)` -- NOT `>> 24` (which emits plain `srwi`).  Only
//     m16 needs the explicit `(u32)` cast for `srwi` vs `srawi`.  Verified by probe.
//  7. L1 (pointer-valued global decl AND read, `extern Unk_9994C3F5 *lbl_802FFE98`
//     + bare `lbl_802FFE98->unk0x118/0x11C`) is applied throughout -- but on the
//     OLD m2c draft it was worth 0.0 (4.2% -> 4.2%): a 1-word lever cannot help a
//     400-instruction structural husk.  It is only load-bearing once the rebuild
//     below exists.  Do not spend a round re-testing L1 here.
//
// RESIDUAL (121 words, 4 opcode-level sites + one global register permutation):
//  A. 0x800915E0  GOT emits `mr r29,r3` (item) + `mr r3,r29` around the
//     `bl fn_8009B5D8` ctor; want passes the Mem_Alloc2 result in r3 straight
//     through and only copies to r31 at the `stwx`.  Costs 1 instruction, which
//     shifts every index through the rest of the loop body.  DEAD END: declaring
//     the ctor pointer-returning (`item = fn_8009B5D8((I914C4*)Mem_Alloc2(0x1C))`)
//     removes the extra `mr` but blows the tail up (27%) and loses 4 bytes.
//  B. Register permutation: want {p50:r24, m24:r25, m16:r20, m5:r28, w1:r29,
//     w2:r30, item:r31, h:r26, total:r27} ; GOT {p50:r24, m24:r25, m16:r20,
//     w1&m5 SHARED in r28, item:r29, w2:r30}.  want uses all 18 callee-saved regs,
//     GOT reuses r28 between w1 and m5.  59 of the 121 diffs are pure register
//     renames from this.  DEAD ENDS: hard-reg pins (item->r31, p50->r24) COLLAPSE
//     the allocation (21-23%); declaration-order steering is a no-op; the `s32`
//     alias form is required (pointer pins are silently dropped, AGENTS 76-178).
//  C. 0x80091600  arg-setup permutation: want `li r4 / li r5 / mr r6 / mr r3 r24`,
//     GOT `mr r3 r24` first.  DEAD ENDS: `void *` / `s32` first-param proto for
//     fn_80014904 (neutral), non-volatile and volatile `"+r"(p50)`` barriers
//     (16-17%, 12 bytes short).
//  D. 0x800916B4  the two `stb` of unk0x4/unk0x5 sink below the next call's
//     `lwz r3,0x64(r1)` arg setup.  DEAD ENDS: `(volatile s8 *)&item->unk0x4`
//     (neutral), `__asm__ volatile("" ::: "memory")` before the p54 call (neutral).
//  E. 0x800916DC  want has `mr r11,r9` (the switch value lives in a register copy);
//     GOT compares r9 in place.  A separate `s32 sw` for the switch operand is
//     NEUTRAL, not a fix.  1 word.
//  Also: `stwu/mflr/mfcr/stmw/stw` prologue, the doc-28 CR save (`mfcr r12` +
//     `mtcrf 0x18` for cr3/cr4 live across ~15 bls), the `for (i=0; i<sp4C; i++)`
//     loop ROTATION (`addi r15,r22,1` at the loop head), the `if (r25 < 1)` guard
//     that makes cr4 live across the refill loop, the switch tree on sp54&0xF and
//     the mtctr/bdnz tail loop all now come out of plain C -- no inline asm, no
//     flags, 0 bytes of rodata.  All callee arities were audited from prologues:
//     fn_80014904 4-arg, fn_8000F10C 4-arg, fn_80010D94 2, fn_80010E78 1,
//     fn_80014898 1, fn_800147E8 2, fn_8005D380 3, fn_80077BAC 1, strstr 2
//     (prototyped, no crclr), memcpy 3 LEFT UNPROTOTYPED (want has crclr cr1eq).
#include "types.h"
#include "mem.h"
#include "structs.h"

typedef struct {
    s32 unk0x0;
    s8  unk0x4;
    s8  unk0x5;
    s8  unk0x6;
    s8  unk0x7;
    u8  unk0x8;
    u8  unk0x9;
    u16 unk0xA;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
} I914C4;

extern char lbl_802970D8[];
extern char lbl_802970E8[];
extern char lbl_802970FC[];
extern Unk_9994C3F5 *lbl_802FFE98;
extern s32 lbl_803018F8;

s32 fn_8000F10C(void *, s32, s32, s32);
void fn_80010D94(s32, s32);
void fn_80010E78(s32);
s32 fn_80014904(s32 *, s32, s32, s32);
s32 fn_800147E8(s32, s32);
void fn_80014898(s32);
void fn_8009B5D8(I914C4 *);
s32 fn_80077BAC(s32);
void fn_8005D380(s32, I914C4 *, s32);
char *strstr(char *, char *);

void fn_800914C4(char *arg0, s32 arg1) {
    struct {
        s32 a8[8];
        s32 a28[8];
        s32 a48;
        s32 a4C;
        s32 a50;
        s32 a54;
        s32 a58;
        s32 a5C;
    } fr;
    s32 a60;
    s32 *p50;
    s32 *p54;
    s32 *p58;
    s32 h;
    s32 np;
    s32 i;
    s32 k;
    s32 j;
    s32 k2;
    s32 v1;
    s32 v2;
    s32 total;
    s32 m24;
    u32 m16;
    s32 m5;
    s32 half;
    s32 dst;
    s32 w1;
    s32 w2;
    s32 sh1;
    s32 sh2;
    u8  b;
    I914C4 **items;
    u16 *arrA;
    u16 *arrB;
    I914C4 *item;
    s32 *node;

    if (strstr(arg0, lbl_802970D8) == 0) {
        strstr(arg0, lbl_802970E8);
    }
    h = fn_800147E8((s32)arg0, (s32)lbl_802970FC);
    if (h == 0) {
        return;
    }
    fn_80014904(&fr.a48, 4, 1, h);
    fn_80014904(&fr.a4C, 4, 1, h);
    np = 0;
    items = (I914C4 **)fn_8000F10C(lbl_802FFE98, fr.a4C * 4, 1, lbl_802FFE98->unk0x118);
    arrA = (u16 *)fn_8000F10C(lbl_802FFE98, fr.a4C * 2, 1, lbl_802FFE98->unk0x118);
    arrB = (u16 *)fn_8000F10C(lbl_802FFE98, fr.a4C * 2, 1, lbl_802FFE98->unk0x118);
    for (i = 0; i < fr.a4C; i++) {
        p54 = &fr.a54;
        p58 = &fr.a58;
        p50 = &fr.a50;
        item = (I914C4 *)Mem_Alloc2(0x1C);
        fn_8009B5D8(item);
        items[i] = item;
        fn_80014904(item, 4, 1, h);
        fn_80014904(p50, 4, 1, h);
        w1 = *(u16 *)((char *)p50 + 2);
        fn_80014904(p50, 4, 1, h);
        w2 = *(u16 *)((char *)p50 + 2);
        fn_80014904(p50, 4, 1, h);
        b = *(u8 *)((char *)p50 + 3);
        v1 = (w1 + 3) & 0xFFFFFFFC;
        item->unk0x8 = b;
        v2 = (w2 + 3) & 0xFFFFFFFC;
        sh1 = 3;
        if (v1 > 8) {
            do {
                sh1++;
            } while ((s32) (1 << sh1) < v1);
        }
        item->unk0x6 = (s8)sh1;
        sh2 = 3;
        if (v2 > 8) {
            do {
                sh2++;
            } while ((s32) (1 << sh2) < v2);
        }
        item->unk0x7 = (s8)sh2;
        item->unk0x4 = (s8) (v1 - w1);
        item->unk0x5 = (s8) (v2 - w2);
        fn_80014904(p54, 4, 1, h);
        m24 = (u8) ((u32)fr.a54 >> 8);
        m16 = (u32)fr.a54 >> 16;
        m5 = fr.a54 & 0x20;
        fr.a54 &= 0xF;
        switch (fr.a54) {
        case 0:
            item->unk0x9 = 0xE;
            break;
        case 1:
            item->unk0x9 = 0xE;
            break;
        case 2:
            item->unk0x9 = 6;
            break;
        }
        item->unk0xA = 0;
        fn_80014904(p58, 4, 1, h);
        item->unk0xA = item->unk0xA | (u16) (fr.a58 != 0);
        total = 0;
        for (k = 0; k < (u32)item->unk0x8; k++) {
            fn_80014904(&fr.a5C, 4, 1, h);
            fr.a8[k] = fn_8000F10C(lbl_802FFE98, fr.a5C, 1, lbl_802FFE98->unk0x118);
            fr.a28[k] = fr.a5C;
            total += fr.a5C;
            fn_80014904((s32 *)fr.a8[k], fr.a5C, 1, h);
        }
        if (lbl_803018F8 != 0 && m5 != 0) {
            total = total * 8;
            item->unk0xA = item->unk0xA | 0x100;
        }
        fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
        item->unk0x10 = Mem_Alloc(total);
        item->unk0xC = total;
        fn_80010E78(lbl_802FFE98->unk0x11C);
        dst = item->unk0x10;
        for (j = 0; j < (u32)item->unk0x8; j++) {
            memcpy(dst, (void *)fr.a8[j], fr.a28[j]);
            Mem_Free((void *)fr.a8[j]);
            dst += fr.a28[j];
        }
        if (fr.a54 == 1) {
            if (m24 == 0) {
                half = total >> 1;
                total = 0;
                if (m24 < 1) {
                    for (k = 0; k < (u32)item->unk0x8; k++) {
                        fn_80014904(&a60, 4, 1, h);
                        fr.a8[k] = fn_8000F10C(lbl_802FFE98, a60, 1, lbl_802FFE98->unk0x118);
                        fr.a28[k] = a60;
                        total += a60;
                        fn_80014904((s32 *)fr.a8[k], a60, 1, h);
                    }
                }
                if (item->unk0xA & 0x100) {
                    item->unk0x14 = (item->unk0x10 + half) & 0xFFFFFFE0;
                } else {
                    fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
                    item->unk0x14 = Mem_Alloc(total);
                    fn_80010E78(lbl_802FFE98->unk0x11C);
                }
                dst = item->unk0x14;
                for (j = 0; j < (u32)item->unk0x8; j++) {
                    memcpy(dst, (void *)fr.a8[j], fr.a28[j]);
                    Mem_Free((void *)fr.a8[j]);
                    dst += fr.a28[j];
                }
                item->unk0xA = item->unk0xA | 2;
            } else {
                item->unk0xA = item->unk0xA | 2;
                arrA[np] = (u16)i;
                arrB[np] = (u16)m16;
                np++;
            }
            if (m24 == 1) {
                goto lb8;
            }
            if (m24 <= 1) {
                goto lb4;
            }
            if (m24 == 2) {
                goto lb10;
            }
            goto lb4;
lb4:
            item->unk0xA = item->unk0xA | 4;
            goto ljoin;
lb8:
            item->unk0xA = item->unk0xA | 8;
            goto ljoin;
lb10:
            item->unk0xA = item->unk0xA | 0x10;
ljoin:;
            item->unk0xA = item->unk0xA | 0x20;
        } else {
            item->unk0x14 = 0;
            item->unk0xA = (u16) ((item->unk0xA & 0xFFFD) | 4);
        }
        node = (s32 *)fn_80077BAC(Mem_Alloc2(0x10));
        node[3] = (s32)item;
        if (arg1 != 0) {
            fn_8005D380(arg1, item, (s32)node);
        }
    }
    for (k2 = 0; k2 < np; k2++) {
        items[arrA[k2]]->unk0x14 = items[arrB[k2]]->unk0x14;
        items[arrB[k2]]->unk0xA = items[arrB[k2]]->unk0xA & 0xFFDF;
    }
    fn_80014898(h);
    Mem_Free((void *)items);
    Mem_Free((void *)arrA);
    Mem_Free((void *)arrB);
}
