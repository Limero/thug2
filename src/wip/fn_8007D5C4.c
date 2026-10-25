// PARKED 2026-10-03 (a72): DIFF 24.8% (was DIFF 18.4% before this pass).
// family=m2c range=0x8007D5C4-0x8007DC58 size=1684B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8007D5C4
//
// WHAT WAS FIXED THIS PASS (all semantics, no flags/scaffolding):
//  * Frame is now right: three 256-byte char buffers + u16,u16 + 8x u32 gives
//    `stwu r1,-0x378` / `stmw r14,0x330(r1)` / `stw r0,0x37c(r1)` exactly.
//    m2c's `s32 sp108; s32 sp208; Unk_59AB5482 sp8;` (0x44-byte struct) gave a
//    wrong frame.  WANT slots: sp8@0x8, sp108@0x108, sp208@0x208 (all 0x100),
//    sp308@0x308 (u16), sp30A@0x30A (u16), sp30C..sp328 (u32 x8).
//  * The m2c `||`-monster at the "file not found" retry chain is really a
//    plain 2-deep nest: try -> if 0 { report; retry; if 0 { report; retry; if 0
//    goto tail; } }.  Third failure jumps to 0x8007DBF4 (the shared tail).
//  * 0x80269F4C is varargs sprintf (NOT vsprintf): calls are
//    `sprintf(sp208, lbl_80295F90, sp8)` and `sprintf(sp208, lbl_80295FC8, sp8)`.
//    sp8 is char[0x100], so sp8 decays to &sp8 == r1+8 == the r5 arg.  Left
//    unprototyped on purpose -> emits WANT's `crclr cr1eq`.
//  * Block order: `if (arg1 != 0) goto setflag; if (arg2 == 0) goto main; loop;
//    setflag: ...; main: <body>` reproduces WANT's physical layout exactly
//    (loop, flag-store, main-body, tail, epilogue) — 24.8% vs 8.7% for the
//    if/else-with-goto shape.  The `lbl_8030175C = 1` store must NOT be
//    merged into the tail's identical store: use `goto`-to-label, not a
//    trailing statement.
//  * Mode branch: `if (mode != 3) { if (mode == 5) {...} } else {...}` gives
//    WANT's `cmpwi r3,3; beq <mode3>; cmpwi r3,5; bne <end>` (mode5 inline,
//    mode3 out of line).  `if (mode == 3) {...} else if (mode == 5)` gives
//    `bne` and the mirrored layout.
//  * fn_8000DC80 / fn_8000DBFC / fn_800147E8 / strcpy / strcat all need real
//    prototypes (m2c had none for strcpy, fn_80017DA4, fn_8001B8D0,
//    fn_8001B9C8, fn_80017E20, fn_80014898 -> spurious `crclr cr1eq`).
//    fn_80017E20 takes ONE arg (`li r3,1` / `li r3,0`), not two.
//  * fn_80014904(ptr, elemSize, count, handle) x10 then x10 again.
//    GX_PokeZ is (u16 x, u16 y, u32 z) at 0x8001FE60; GX_PokeColorUpdate =
//    0x80020474, GX_PokeAlphaUpdate = 0x80020454.
//
// REMAINING DIFF (2nd pass, positional masked compare):
//  * GOT is 3 words SHORT in 0x8007D618-0x8007D670.  WANT materialises FOUR
//    `lis` there: 0x80290000 (sp8 base), 0x80300000 (lbl_802FFE48 -> r11),
//    0x80380000 (lbl_8037B5E8 -> r10) and 0x80300000 (lbl_802FFE8C -> r9),
//    and loads `lwz r21, lbl_802FFE8C` right after the first sp8 store.
//    GOT only builds 3 and reloads lbl_802FFE8C inside each branch.  Because
//    the mode branches are then 3 words early, words 0xB0-0x38C (both mode
//    bodies, the strcpy/strcat address forms, the sprintf/OSVReport retry
//    chain) all misalign.  That single 3-word offset is most of the score.
//  * r29/r11/r21 register assignment in that same preamble differs (WANT keeps
//    r21 = lbl_802FFE8C for the whole function).
//  * The mode-3/mode-5 bodies otherwise match instruction-for-instruction,
//    including `addi r30,r1,0x108` for the second buffer.
//  * The EFB->ARGB pixel loops and both GX_PokeZ loops are close (words
//    0x400-0x46C match almost continuously); remaining diff there is the
//    `char *` vs `s32 *` base for lbl_80300368 and the store-index expression.
//
// RULED OUT (do not retry):
//  * Splitting the 20-byte copy at 0x80295F34 into 5 individual field
//    assignments, with field0 via `lbl_80295F34` and fields1-4 via a literal
//    `(s32 *)0x80290000 + 0x5F34` base (m2c's exact shape): GCC materialises
//    the literal with `lis`+`ori` and emits SIX stores at 0x0,4,8,C,10,14 —
//    8.7% positional, far worse than the single struct copy.
//  * Hoisting `lbl_802FFE8C` into a `char *dir` local to get the single `lis`
//    + `lwz r21`: 16.6% — GCC re-allocates and loses more than it gains.  The
//    load has to come from the ORIGINAL source's own reference pattern, not a
//    new local.
//  * `if (mode == 3) {...} else if (mode == 5) {...}` (the natural m2c order).
//
// MOST PROMISING NEXT IDEA: reproduce WANT's *4-`lis` preamble by giving the
// preamble three separate address expressions instead of one — i.e. keep the
// struct copy for sp8, but read the 20-byte source with `nm = lbl_80295F34`
// where the first word comes from a bare `*(s32*)&lbl_80295F34` deref (so the
// `lwz` picks up the ADDR16_LO displacement form that WANT shows) and force
// `lbl_802FFE8C`/`lbl_802FFE48` to be *used* before the mode branch so GCC
// hoists their `lis` into the same preamble.  The 3-word deficit is worth
// ~+25 points by itself because everything downstream realigns.
#include "types.h"


typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
} Unk_Name20;

extern void *lbl_80300368;
extern s32 lbl_8037B5E8[];
extern s32 lbl_802FFE48;
extern char *lbl_802FFE8C;
extern char lbl_80295F34[];
extern char lbl_80295F48[];
extern char lbl_80295F50[];
extern char lbl_80295F64[];
extern char lbl_80295F6C[];
extern char lbl_80295F80[];
extern char lbl_80295F8C[];
extern char lbl_80295F90[];
extern char lbl_80295FC8[];
extern char lbl_80295FFC[];
extern bool lbl_80301750;
extern bool lbl_80301754;
extern bool lbl_8030175C;

void fn_8000DBFC(void *, char *, s32, s32, void *);
void fn_8000DC80(void *, char *, s32);
s32 fn_800147E8(char *, char *);
void fn_80014898(s32);
void fn_80014904(void *, s32, s32, s32);
void fn_80017DA4(void);
void fn_80017E20(s32);
void fn_8001B8D0(void);
void fn_8001B9C8(void);
void GX_PokeZ(u16, u16, u32);
void GX_PokeAlphaUpdate(s32);
void GX_PokeColorUpdate(s32);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void OSVReport(char *, s32);

void fn_8007D5C4(void *arg0, s32 arg1, s32 arg2) {
    char sp8[0x100];
    char sp108[0x100];
    char sp208[0x100];
    u16 sp308;
    u16 sp30A;
    u32 sp30C;
    u32 sp310;
    u32 sp314;
    u32 sp318;
    u32 sp31C;
    u32 sp320;
    u32 sp324;
    u32 sp328;
    void *r24;
    char *r25;
    s32 r26;
    s32 mode;
    s32 retry;

    if (arg1 != 0) {
        goto setflag;
    }
    if (arg2 == 0) {
        goto main;
    }
    retry = 2;
    do {
        fn_80017DA4();
        fn_8001B8D0();
        fn_8001B9C8();
        fn_80017E20(1);
        retry -= 1;
    } while (retry != 0);
setflag:
    lbl_8030175C = 1;
    return;
main:
    {
        *(Unk_Name20 *)sp8 = *(Unk_Name20 *)lbl_80295F34;
        lbl_8037B5E8[0x63] = 1;
        mode = lbl_802FFE48;
        if (mode != 3) {
            if (mode == 5) {
                strcpy(sp108, arg0);
                strcat(sp108, lbl_80295F48);
                fn_8000DBFC(lbl_802FFE8C, sp108, 0, 0, 0);
                strcat(sp8, lbl_80295F50);
            }
        } else {
            strcpy(sp108, arg0);
            strcat(sp108, lbl_80295F64);
            fn_8000DBFC(lbl_802FFE8C, sp108, 0, 0, 0);
            strcat(sp8, lbl_80295F6C);
        }
        strcat(sp8, arg0);
        strcat(sp8, lbl_80295F80);
        lbl_80301754 = 1;
        r26 = fn_800147E8(sp8, lbl_80295F8C);
        if (r26 == 0) {
            sprintf(sp208, lbl_80295F90, sp8);
            OSVReport(sp208, 0);
            *(Unk_Name20 *)sp8 = *(Unk_Name20 *)lbl_80295F34;
            strcat(sp8, arg0);
            strcat(sp8, lbl_80295F80);
            r26 = fn_800147E8(sp8, lbl_80295F8C);
            if (r26 == 0) {
                sprintf(sp208, lbl_80295FC8, sp8);
                OSVReport(sp208, 0);
                *(Unk_Name20 *)sp8 = *(Unk_Name20 *)lbl_80295F34;
                strcat(sp8, lbl_80295FFC);
                strcat(sp8, lbl_80295F80);
                r26 = fn_800147E8(sp8, lbl_80295F8C);
                if (r26 == 0) {
                    goto tail;
                }
            }
        }
        fn_80014904(&sp30C, 4, 1, r26);
        {
            u32 row = 0;
            u32 rows;
            s32 j;
            s32 k;
            s32 m;
            fn_80014904(&sp310, 4, 1, r26);
            fn_80014904(&sp314, 4, 1, r26);
            fn_80014904(&sp318, 4, 1, r26);
            fn_80014904(&sp31C, 4, 1, r26);
            fn_80014904(&sp320, 4, 1, r26);
            fn_80014904(&sp324, 4, 1, r26);
            fn_80014904(&sp328, 4, 1, r26);
            fn_80014904(&sp308, 2, 1, r26);
            fn_80014904(&sp30A, 2, 1, r26);
            r24 = lbl_80300368;
            r25 = (char *)r24 + (sp314 << 6);
            fn_80017DA4();
            fn_8001B8D0();
            GX_PokeColorUpdate(1);
            GX_PokeAlphaUpdate(0);
            while (row < sp318) {
                rows = sp318 - row;
                if (rows > 0x10) {
                    rows = 0x10;
                }
                fn_80014904(r24, sp314 * (rows * 4), 1, r26);
                if (lbl_80301750 != 0) {
                    s32 handle;
                    lbl_80301750 = 0;
                    row = 0;
                    fn_80014898(r26);
                    handle = fn_800147E8(sp8, lbl_80295F8C);
                    fn_80014904(&sp30C, 4, 1, handle);
                    fn_80014904(&sp310, 4, 1, handle);
                    fn_80014904(&sp314, 4, 1, handle);
                    fn_80014904(&sp318, 4, 1, handle);
                    fn_80014904(&sp31C, 4, 1, handle);
                    fn_80014904(&sp320, 4, 1, handle);
                    fn_80014904(&sp324, 4, 1, handle);
                    fn_80014904(&sp328, 4, 1, handle);
                    fn_80014904(&sp308, 2, 1, handle);
                    fn_80014904(&sp30A, 2, 1, handle);
                    fn_80017DA4();
                    fn_8001B8D0();
                } else {
                    rows = row + rows;
                    for (j = 0; j < (s32)rows - (s32)row; j += 4) {
                        for (k = 0; k < (s32)sp314; k += 4) {
                            char *p = (char *)r24 + (k * 0x10) + ((j * (s32)sp314) * 4);
                            for (m = 0; m < 0x10; m++) {
                                u32 a = *(u16 *)p;
                                u32 q = *(u16 *)(p + 0x20);
                                *(u32 *)(r25 + (((m & 3) + (sp314 * (m >> 2)) + k + (j * (s32)sp314)) * 4)) =
                                    (a << 16) | ((q << 16) & 0xFFFF0000) | (q & 0xFF);
                                p += 2;
                            }
                        }
                    }
                    for (j = 0; j < (s32)rows - (s32)row; j++) {
                        for (k = 0; k < (s32)sp314; k++) {
                            GX_PokeZ((u16)k, (u16)(sp318 - (row + j + 1)),
                                     *(u32 *)(r25 + (((sp314 * j) + k) * 4)));
                        }
                    }
                    row = rows;
                }
            }
            fn_8001B9C8();
            fn_80017E20(0);
            fn_80014898(r26);
        }
    }
tail:
    mode = lbl_802FFE48;
    lbl_80301754 = 0;
    if ((mode == 3) || (mode == 5)) {
        fn_8000DC80(lbl_802FFE8C, sp108, 0);
    }
    lbl_8037B5E8[0x63] = 0;
    lbl_8030175C = 1;
}