// WIP DRAFT (non-matching) — HAND-REBUILT from the DOL disassembly 2026-10-05.
// FLAG: -fno-branch-count-reg
// family=m2c range=0x80019E50-0x8001A788 size=2360B
//
// PARKED 2026-10-05 (7.39% DIFF; was 6.41% DIFF / 2308 B before this round):
//   body is now structurally correct — frame is EXACT (stwu -0x5b0 / stmw
//   r14,0x568 / LR 0x5b4 / CR 0x564, struct @sp+8 size 0x558, every sp offset
//   identical) and the call sequence is EXACT (72 `bl` in the want, 72 in the
//   got, same callee order).  Object is 2328 B vs the want's 2360 B (8 words
//   short), which is why the index-aligned percentage stays low.
//   Residual is (a) 8 words of length, (b) CR-word encoding, (c) CR hoisting
//   in the two row loops, (d) small register/statement-order choices.  All four
//   measured and ruled out — see the four numbered items at the bottom.
//
// ---- WHAT THIS FUNCTION IS (fully recovered; do not re-derive) ----------
// fn_80019E50 = the "DVD boot / error screen" driver.  One scratch object
// (struct unk_19e50) at sp+0x08 is (a) a tagged struct (tag @+0x04, an
// fn_8000B618 result @+0x08), (b) a 0x500-byte u16 row buffer at +0x20
// (GX_PeekZ build loop) and (c) the struct BASE is used directly as the same
// 0x500-byte buffer by the GX_PokeZ upload loop (selfPtr = &fr).
//
//   outer loop (repeats while arg0 < 0):
//     drive = DVDGetDriveStatus();  fn_800181A4(0,0);
//     if (drive in {0,0xA})            -> leave loop
//     errSeen = 1; cArg0 = (arg0 < 0)
//     if (drive in {1,8,2})            -> goto L444
//     errSeen = 0;  lbl_80300170 = drive;
//     if (fn_80019E0C() && fn_80125814(lbl_80290E1C,0)) {
//         cdResult = fn_8001E17C(0);   fn_80261860();
//         if (cInit == 0) { inited=1; init globals/builders;
//                            2x (fn_80017DA4/fn_8001B8D0/fn_8001B9C8/
//                                fn_80017E20(0))
//                            build 0x1C0 rows (build loop)
//                            cInit = (inited == 0); }
//         *(f32 *)(lbl_8037B5E8+0x184) = lbl_80290E30;
//         ... 0x14x DVD-error switch (fn_80131008) ... }
//     if (cInited2 == 0) inited2 = 1;
//   L444: if (cArg0) loop;
//   after the loop, if (cInit): second (upload) loop 0x1C0 rows:
//     copy lbl_80300368[i*0x500] -> &fr;  fn_8001D668 x4 banks;
//     GX_PokeZ over 0x280 u16 of &fr
//     then a 2x "restore 0x184 + fn_80018064 + fn_80017E20" block,
//     fn_8000B618/fn_8000BD04/fn_8000B680.
//   tail: lbl_80300170 = 0; if (cdResult == -1) { fn_8001E17C(cdResult!=0);
//   fn_80261860(); } if (lbl_8030016C) fn_8001E17C(1); return errSeen;
//
//   Both row loops share ONE shape (verified against 0x8001A0A0-0x8001A22C
//   and 0x8001A4E0-0x8001A65C):
//     base = fn_800240F4()/1280;  b1..b4 = base+{0x19,0x32,0x4B,0x64}
//     for (i=0; i<=0x1BF; i++) {   /* per-row scratch work  */
//       if (i < base)  copy 0x500B;
//       else if (i < b1) fn_8001D4FC(bank0+(i-base)*0x500, row, 0x500);
//       else if (i < b2) fn_8001D4FC(bank1+(i-b1)   *0x500, row, 0x500);
//       else if (i < b3) fn_8001D4FC(bank2+(i-b2)   *0x500, row, 0x500);
//       else if (i < b4) fn_8001D4FC(bank3+(i-b3)   *0x500, row, 0x500); }
//   i.e. it is an if/else-if CHAIN (measured from the branch shape: the arm
//   bodies all fall into the *next* guard's `bge`/`blt`, so exactly one arm
//   runs per row), the guard set is {base, +0x19, +0x32, +0x4B, +0x64} and the
//   offsets are {base, base+0x19, base+0x32, base+0x4B}.  banks are the four
//   pointers at lbl_8037B5E8+0x198/0x19C/0x1A0/0x1A4.  Row packing:
//     build  : ((x>>3)&0x1F) | ((x>>5)&0x7E0) | ((x>>8)&0xF800)  -> sth
//     scan   : 0xFF000000 | ((v<<8)&0xF80000) | ((v<<5)&0xFC00) | ((v<<3)&0xF8)
//
//   The five guards are all hoisted to the loop header; CR4/CR3/CR2 survive
//   the calls so only CR0 needs the `mfcr`/`mtcrf 0x80` dance (4th guard) and
//   the 5th is re-compared at the tail of the body.
//
// ---- FRAME (measured) ---------------------------------------------------
// The frame adjusts the stack by 0x5b0 and saves r14 at 0x568, with the link
// register at 0x5b4 and the condition register at 0x564. The scratch struct
// sits at sp+0x08 with size 0x558 (ending at sp+0x560); cInit lives at
// struct offset 0x558 (sp 0x550 plus 8) and cInited2 at 0x554.
//
// ---- CALLEE SIGNATURES (audited from call sites + callee prologues) -----
//   DVDGetDriveStatus (0x80247CEC stub) 0-arg s32; fn_80261860 0-arg void;
//   fn_80019E0C/80019E18/800240F4 0-arg s32 getters; fn_800181A4 (s32,s32);
//   fn_80125814 (char*,s32)->s32; fn_8001E17C (s32)->s32; fn_8000B618 (s32)->s32;
//   fn_80119510 (s32)->s32; fn_80119AF8 (s32)->void; fn_80119578 0-arg;
//   fn_80017E20/80120A00 (s32,s32); fn_8001D424 (void*);
//   Camera_orthographic (ptr,4x s32); fn_80016A88 (ptr,s32); fn_80018064 (s32*);
//   fn_8001D4FC/fn_8001D668 (dst,src,len); GX_PokeZ (s32,s32,s32) void;
//   GX_PeekZ (s32,s32,s32*) void; fn_80131008/Script_RunScript (5x s32).
//
// ---- REMAINING BLOCKERS (all measured this round; none is a semantics bug)
// 1. doc-28 CR-word encoding (4 sites).  The want materialises SEVEN
//    comparisons as saved CR words — `cmpwi` + `mfcr` + `stw` at the def and
//    `lwz` + `mtcrf 0x80` + `b<cond>` at the use — for cDvdErr@sp548
//    (dvdErr==0, set 0x80019E80, used 0x80019FE0), cInit@sp558 (0x80019EB4 /
//    0x80019F60 / 0x8001A454), cArg0@sp554 (the cr7 `cmpwi cr7,r9,0` +
//    `mfcr` + `slwi r9,r9,0x1c` + `stw` at 0x80019EE4..F0, used 0x8001A444),
//    cInited2@sp55c (0x80019F20 / 0x8001A430) and cDvdErr2 in r16 (0x8001A484).
//    Every plain-C spelling measured here emits `subfic`+`adde` (0/1 integer)
//    instead, or re-loads+re-compares at each use.  Probe harness
// (<scratch> over sh/{a..l}.c) shows GCC only
//    caches a comparison in a NONVOLATILE CR field (cr2/cr3/cr4) when the
//    compared value is live in a callee-saved GPR; it spills the CR word to
//    memory only when no nonvolatile CR field is free — and here the two row
//    loops already take cr4/cr3/cr2/cr7, so the allocation is circular.
//    This is the catalogued doc-28 wall (recipes: fn_801808C8 is "a confirmed
//    new member ... unreproduced across all versions/-O levels").
// 2. CR hoisting in the row loops.  The want puts all FIVE guard compares at
//    the loop head (0x8001A0A0..0x8001A0BC uses cr4/cr3/cr2 + CR0; 0x8001A4E0
//    ..0x8001A4F4 uses cr7/cr4/cr3/cr2) and then branches on the cached CR
//    fields across the calls.  Plain C here re-compares each guard at its own
//    use site (`cmpw r28,r21; bge cr3` per arm).  Same doc-28 family.
// 3. Loop shape.  `for(;;) {...}` made ngccc rotate the loop header out of
//    line (preheader `b` to a header at the function's end, 5.15%).  Changing
//    the outer loop to `do {...} while (fr.cArg0);` with `goto done` for the two
//    `break`s puts the header back at 0x80019EA0 (= the want's first
//    instruction) — 5.15% -> 7.39%.  Keep the do-while.
// 4. 8 words of length (2328 B vs 2360 B), spread over the init block (~10
//    words short before fn_800240F4) and the upload-loop copy region.  A
//    literal page base (`char *page = (char *)0x80300000;`) was measured and
//    is WORSE (2276 B, 3.87%): GCC then CSEs one anchor instead of
//    rematerialising `lis` the way the want does (`lis r9,-0x7fd0` recomputed
//    per site, plus one long-lived `lis r17,-0x7fd0`).  Direct literal
//    addresses `*(s32 *)0x8030xxxx` for ALL nine 0x8030-page globals give an
//    exact 2384 B but only 6.10% and add `ori`+`lwz 0(r9)` pairs.
//    `-fno-branch-count-reg` re-measured and still load-bearing (dropping it
//    re-introduces `mtctr`/`bdnz` in one of the two copy loops).
//
// Retry hints: (a) items 1+2 are one problem — if any spelling makes ngccc
// allocate a nonvolatile CR field here the whole CR/hoist block should fall
// out; the two row loops' CR pressure is the thing to perturb (e.g. by making
// `base`/`b1..b4` loop-invariant in a form GCC does not re-derive).
// (b) The `if/else if` chain and the `bge`/`blt` reuse pattern are reproduced
// exactly — do not disturb them.
#include "types.h"
#include "qb_constants.h"

/* ---- data ------------------------------------------------------------- */
extern s32 lbl_80300120;
extern s32 lbl_80300125;
extern bool lbl_8030016C;
extern s32 lbl_80300170;
extern s32 lbl_80300368;
extern bool lbl_80301750;
extern bool lbl_80301754;
extern bool lbl_8030175C;
extern s32 lbl_80302F20;
extern char lbl_80290E1C[];
extern f32 lbl_80290E30;
extern char lbl_80290E38[];
extern char lbl_80290E50[];
extern char lbl_8037B5E8[];

/* ---- callees: arities read off the call sites + callee prologues ------- */
extern s32  DVDGetDriveStatus(void);      /* 0x80247CEC stub, reads no arg */
extern void VIFlush(void);
extern s32  fn_80019E0C(void);             /* returns lbl_80300170 */
extern s32  fn_80019E18(void);             /* returns lbl_803017F8 */
extern s32  fn_800240F4(void);             /* returns lbl_80300370 */
extern void fn_800181A4(s32, s32);
extern s32  fn_80125814(char *, s32);
extern s32  fn_8001E17C(s32);
extern s32  fn_8000B618(s32);
extern void fn_8000BC4C(void);
extern void fn_8000BD04(void);
extern void fn_8000B680(void);
extern s32  fn_80119510(s32);
extern void fn_80119578(void);
extern void fn_80119AF8(s32);
extern void fn_80120A00(s32, s32);
extern void fn_80017DA4(void);
extern void fn_80017E20(s32);
extern void fn_8001B8D0(void);
extern void fn_8001B8B0(void);
extern void fn_8001B8C0(void);
extern void fn_8001B9C8(void);
extern void fn_8001737C(void *);
extern void fn_800173CC(void *);
extern void Camera_orthographic(void *, s32, s32, s32, s32);
extern void fn_80016A88(void *, s32);
extern void fn_80016C70(void);
extern void fn_8001D424(void *);
extern void GX_SetZMode(s32, s32, s32);
extern void set_blend_mode(s32, s32, s32);
extern void fn_80018064(s32 *);
extern void GX_DrawDone(void);
extern void fn_80018E2C(void);
extern void fn_8001D4FC(void *, void *, s32);
extern void fn_8001D668(void *, void *, s32);
extern void GX_PokeZ(s32, s32, s32);
extern void GX_PeekZ(s32, s32, s32 *);
extern s32  Script_RunScript(s32, s32, s32, s32, s32);

/* ---- the scratch object at sp+0x08 --------------------------------------
 *  offsets are struct-relative; sp = offset + 8
 *  0x000 pad, 0x004 tag, 0x008 f10, 0x018 f18, 0x01C f1C, 0x020 row[0x280],
 *  0x520 out18064, 0x524 outFE80, then the scalars.  The upload loop uses the
 *  struct BASE (&fr / fr.selfPtr) as the 0x500-byte working buffer. */
struct unk_19e50 {
    s32   pad00;        /* 0x000 */
    void *tag;           /* 0x004 */
    s32   f10;           /* 0x008  fn_8000B618() result */
    s32   pad0C;         /* 0x00C */
    s32   pad10;         /* 0x010 */
    s32   pad14;         /* 0x014 */
    s32   f18;           /* 0x018  fn_80119510() result */
    s32   f1C;           /* 0x01C  lbl_80290E38 */
    u16   row[0x280];    /* 0x020 .. 0x51F */
    s32   out18064;      /* 0x520 */
    s32   outFE80;       /* 0x524 */
    s32   arg0;          /* 0x528 */
    s32   errSeen;       /* 0x52C */
    s32   inited;        /* 0x530 */
    s32   inited2;       /* 0x534 */
    s32   cdResult;      /* 0x538 */
    s32   dvdErr;        /* 0x53C */
    s32   cDvdErr;       /* 0x540  CR-valued */
    s32   bank0;         /* 0x544  spilled in the build loop */
    s32   selfPtr;       /* 0x548 */
    s32   cArg0;         /* 0x54C  CR-valued */
    s32   cInit;         /* 0x550  CR-valued */
    s32   cInited2;      /* 0x554  CR-valued */
};                          /* size 0x558 */


s32 fn_80019E50(s32 arg0)
{
    struct unk_19e50 fr;
    s32 drive;
    s32 cnt;
    s32 cCd;
    s32 cDvdErr2;
    s32 base, b1, b2, b3, b4;
    s32 bank1, bank2, bank3;
    s32 i, j;
    u32 x;
    u16 bits;
    u16 *p;
    u16 *q;

    fr.errSeen  = 0;
    fr.dvdErr   = lbl_80302F20;
    fr.inited   = 0;
    fr.cDvdErr  = (fr.dvdErr == 0);
    fr.inited2  = 0;
    fr.arg0     = arg0;
    fr.cdResult = -1;

    do {
        drive = DVDGetDriveStatus();
        fr.cInit = (fr.inited == 0);
        fn_800181A4(0, 0);
        if (drive == 0) goto done;
        if (drive == 0xA) goto done;

        fr.errSeen = 1;
        fr.cArg0 = (fr.arg0 < 0);
        if (drive == 1) goto test_cArg0;
        if (drive == 8) goto test_cArg0;
        if (drive == 2) goto test_cArg0;

        fr.errSeen = 0;
        lbl_80300170 = drive;
        fr.cInited2 = (fr.inited2 == 0);
        if (fn_80019E0C() == 0) goto after;
        if (fn_80125814(lbl_80290E1C, 0) == 0) goto after;

        fr.cdResult = fn_8001E17C(0);
        VIFlush();

        if (fr.cInit == 0) {
            fr.inited = 1;
            *(s32 *)(lbl_8037B5E8 + 0x18C) = 1;
            if (lbl_80301754 != 0) lbl_80301750 = 1;
            fr.tag = lbl_80290E50;
            fr.selfPtr = (s32)&fr;
            fr.f10 = fn_8000B618(0);
            fn_8000BC4C();
            fr.f1C = (s32)lbl_80290E38;
            fr.f18 = fn_80119510(0);
            fn_80119AF8(fr.f18);
            if (fr.cDvdErr == 0) {
                fn_80120A00(1, 0);
                fn_80120A00(1, 1);
            }
            fr.cInit = (fr.inited == 0);

            if (lbl_8030175C != 0) {
                cnt = 2;
                do {
                    fn_80017DA4();
                    fn_8001B8D0();
                    fn_8001B9C8();
                    fn_80017E20(0);
                    cnt--;
                } while (cnt != 0);

                base  = fn_800240F4() / 1280;
                b1    = base + 0x19;
                b2    = base + 0x32;
                b3    = base + 0x4B;
                b4    = base + 0x64;
                fr.bank0 = *(s32 *)(lbl_8037B5E8 + 0x198);
                bank1 = *(s32 *)(lbl_8037B5E8 + 0x19C);
                bank2 = *(s32 *)(lbl_8037B5E8 + 0x1A0);
                bank3 = *(s32 *)(lbl_8037B5E8 + 0x1A4);
                for (i = 0; i <= 0x1BF; i++) {
                    p = fr.row;
                    for (j = 0; j <= 0x27F; j++) {
                        GX_PeekZ((u16)j, (u16)i, &fr.outFE80);
                        x = (u32)fr.outFE80;
                        *p = (u16)(((x >> 3) & 0x1F) |
                                    ((x >> 5) & 0x7E0) |
                                    ((x >> 8) & 0xF800));
                        p++;
                    }
                    if (i < base) {
                        s32 *d = (s32 *)((char *)lbl_80300368 + i * 0x500);
                        s32 *g = (s32 *)fr.row;
                        s32 n = 0x4F8;
                        do {
                            n -= 0x18;
                            d[0] = g[0]; d[1] = g[1]; d[2] = g[2];
                            d[3] = g[3]; d[4] = g[4];
                            { s32 t = g[5]; g += 6; d[5] = t; d += 6; }
                        } while (n != 0);
                        d[0] = g[0];
                        d[1] = g[1];
                    } else if (i < b1) {
                        fn_8001D4FC((void *)(fr.bank0 + (i - base) * 0x500), (void *)fr.row, 0x500);
                    } else if (i < b2) {
                        fn_8001D4FC((void *)(bank1 + (i - b1) * 0x500), (void *)fr.row, 0x500);
                    } else if (i < b3) {
                        fn_8001D4FC((void *)(bank2 + (i - b2) * 0x500), (void *)fr.row, 0x500);
                    } else if (i < b4) {
                        fn_8001D4FC((void *)(bank3 + (i - b3) * 0x500), (void *)fr.row, 0x500);
                    }
                }
            }
            fr.f1C = (s32)lbl_80290E38;
            fn_80119578();
            fr.tag = lbl_80290E50;
            fn_8000B680();
        }

        cnt = 0x14;
        *(f32 *)(lbl_8037B5E8 + 0x184) = lbl_80290E30;
        fn_80017DA4();
        fn_8001B8D0();
        fn_8001D424(&fr);
        Camera_orthographic(&fr, 0, 0, 0x280, 0x1C0);
        fn_80016C70();
        fn_8001B8B0();
        fn_8001737C(&fr);
        GX_SetZMode(0, 7, 1);
        set_blend_mode(0, 5, 0);
        do {
            fn_800181A4(0, 0);
            switch (fn_80019E0C()) {
            case -1:
                if (fn_80019E18() != 0) lbl_8030016C = 1;
                Script_RunScript(QB_NGC_DVD_FATAL, 0, 0, 0, 0);
                *(s32 *)(lbl_8037B5E8 + 0x1BC) = 1;
                break;
            case 11:
                if (fn_80019E18() != 0) lbl_8030016C = 1;
                Script_RunScript(QB_NGC_DVD_RETRY, 0, 0, 0, 0);
                break;
            case 5:
                if (fn_80019E18() != 0) lbl_8030016C = 1;
                Script_RunScript(QB_NGC_DVD_COVER_OPEN, 0, 0, 0, 0);
                *(s32 *)(lbl_8037B5E8 + 0x1BC) = 0;
                break;
            case 4:
                if (fn_80019E18() != 0) lbl_8030016C = 1;
                Script_RunScript(QB_NGC_DVD_NO_DISK, 0, 0, 0, 0);
                *(s32 *)(lbl_8037B5E8 + 0x1BC) = 0;
                break;
            case 6:
                if (fn_80019E18() != 0) lbl_8030016C = 1;
                Script_RunScript(QB_NGC_DVD_WRONG_DISK, 0, 0, 0, 0);
                *(s32 *)(lbl_8037B5E8 + 0x1BC) = 0;
                break;
            }
            cnt--;
        } while (cnt != 0);
        fr.out18064 = lbl_80300125;
        fn_80018064(&fr.out18064);
        fn_800173CC(&fr);
        fn_8001B8C0();
        fn_8001B9C8();
        GX_DrawDone();
        fn_80017E20(1);
        fn_80016A88(&fr, 2);
after:
        if (fr.cInited2 == 0) fr.inited2 = 1;
test_cArg0:
        ;
    } while (fr.cArg0);
done:

    cCd = (fr.cdResult == -1);
    if (fr.cInit != 0) {
        cDvdErr2 = (fr.dvdErr == 0);
        fr.selfPtr = (s32)&fr;
        if (lbl_8030175C != 0) {
            base  = fn_800240F4() / 1280;
            b1    = base + 0x19;
            b2    = base + 0x32;
            b3    = base + 0x4B;
            b4    = base + 0x64;
            fr.bank0 = *(s32 *)(lbl_8037B5E8 + 0x198);
            bank1 = *(s32 *)(lbl_8037B5E8 + 0x19C);
            bank2 = *(s32 *)(lbl_8037B5E8 + 0x1A0);
            bank3 = *(s32 *)(lbl_8037B5E8 + 0x1A4);
            for (i = 0; i <= 0x1BF; i++) {
                if (i < base) {
                    s32 *d = (s32 *)fr.selfPtr;
                    s32 *g = (s32 *)((char *)lbl_80300368 + i * 0x500);
                    s32 n = 0x4F8;
                    do {
                        n -= 0x18;
                        d[0] = g[0]; d[1] = g[1]; d[2] = g[2];
                        d[3] = g[3]; d[4] = g[4];
                        { s32 t = g[5]; g += 6; d[5] = t; d += 6; }
                    } while (n != 0);
                    d[0] = g[0];
                    d[1] = g[1];
                } else if (i < b1) {
                    fn_8001D668(&fr, (void *)(fr.bank0 + (i - base) * 0x500), 0x500);
                } else if (i < b2) {
                    fn_8001D668(&fr, (void *)(bank1 + (i - b1) * 0x500), 0x500);
                } else if (i < b3) {
                    fn_8001D668(&fr, (void *)(bank2 + (i - b2) * 0x500), 0x500);
                } else if (i < b4) {
                    fn_8001D668(&fr, (void *)(bank3 + (i - b3) * 0x500), 0x500);
                }
                q = (u16 *)fr.selfPtr;
                for (j = 0; j <= 0x27F; j++) {
                    bits = *q;
                    q++;
                    GX_PokeZ((u16)j, (u16)i,
                                (((bits << 8) & 0xF80000) |
                                 ((bits << 5) & 0xFC00) |
                                 0xFF000000 |
                                 ((bits << 3) & 0xF8)));
                }
            }
        }
        x = *(u32 *)&lbl_80290E30;
        cnt = 2;
        do {
            *(u32 *)(lbl_8037B5E8 + 0x184) = x;
            fn_80017DA4();
            fn_8001B8D0();
            fn_8001B8B0();
            fn_8001B8C0();
            fr.out18064 = 0;
            fn_80018064(&fr.out18064);
            fn_8001B9C8();
            fn_80017E20(lbl_8030175C == 0);
            cnt--;
        } while (cnt != 0);
        if (lbl_80300120 != 0) fn_80018E2C();
        if (cDvdErr2 == 0) {
            fn_80120A00(0, 1);
            fn_80120A00(0, 0);
        }
        fr.tag = lbl_80290E50;
        fr.f10 = fn_8000B618(0);
        fn_8000BD04();
        *(s32 *)(lbl_8037B5E8 + 0x18C) = cnt;
        fr.tag = lbl_80290E50;
        fn_8000B680();
    }

    lbl_80300170 = 0;
    if (cCd != 0) {
        fn_8001E17C(fr.cdResult != 0);
        VIFlush();
    }
    if (lbl_8030016C != 0) fn_8001E17C(1);
    return fr.errSeen;
}