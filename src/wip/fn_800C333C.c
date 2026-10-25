// WIP DRAFT (non-matching) — fully hand-rebuilt from the DOL disasm; the m2c
// body (1.69%, 944B) has been replaced.
// family=m2c range=0x800C333C-0x800C37DC size=1184B
// extra_cflags: -Os
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// VERDICT 2026-10-04 — DIFF, masked **16.89% (50/296 words)**,
//   **OBJECT SIZE-EXACT: got 1184B / want 1184B**.  test_wip_drafts.py: DIFF.
//
// WHAT FOUND — two REAL decompilation bugs (the previous body was only
// size-exact because they cancelled out), plus the homed zero:
//
//  1. **`lbl_80305FF8` is a POINTER, and the old spelling read the WRONG
//     global.**  want is
//         lis r11,0x8030 ; lwz r10,0x5ff8(r11) ; ori r9,.. ; lwz r0,0x44(r10)
//     i.e. it loads the *value* of lbl_80305FF8 and reads +0x44 of the pointee.
//     The old `extern s32 lbl_80305FF8;` + `*(s32 *)((char *)&lbl_80305FF8 +
//     0x44)` let GCC fold the whole chain into ONE address and it emitted
//     `lis r9,0x8030 ; lwz r9,0x44(r9)` — a read of 0x8030603C, an unrelated
//     .data word.  Same instruction count, wrong memory.  Fixed by typing the
//     symbol `QbMgr *lbl_80305FF8` and using `lbl_80305FF8->qb`.
//     PROOF this is the right spelling: **promoted, byte-identical
//     src/fn_800EDF3C.c** uses exactly this idiom and its want is the *same*
//     10-word block (0x800EDF3C: `lis r11,-0x7fd0 / lwz r10,0x5ff8(r11) /
//     ... / lwz r0,0x44(r10) / cmpw / bne / li r11,0`).  The
//     `lis`+`lwz` pair is emitted @ha/@lo relocated (mask ffff0000 on both the
//     lis immediate and the lwz displacement) — that is what makes it compare
//     equal, so the old "unrelocated lis" mystery in (1) is a non-issue.
//  2. **`comp.v[4] = ps_merge00(t12,t12)` — want has THREE `ps_merge00` where
//     this body had two** (instruction census: want 3 / got 2).  want's
//     0x800C3754-0x800C3758 is `ps_merge00 f0,f12,f12 ; psq_st f0,232(r1)`,
//     i.e. v[4] gets the *splatted low half* of t12, not t12 itself.  It is
//     semantically neutral (the high half is overwritten two instructions
//     later by `stfs f0,0xec(r1)` = `comp.v[4].e[1] = lbl_80299074`) but it is
//     what the original emitted, and it is worth +1 word toward the count.
//  3. **The homed zero is reproducible from C.**  want materialises ONE zero in
//     the loop preheader (`li r26,0` at 0x800C3398) and reuses it at BOTH
//     zero-stores inside the function (`stw r26,4(r31)` = node->i04=0 in the
//     blend and `stw r26,0xb0(r1)` = *head=0 in the `done` cleanup), while the
//     preheader's `self->c120=0` and the pass-2 `comp.hA8=0` get their own
//     `li`.  A single `s32 z = 0;` shared by the three in-loop/late stores
//     reproduces exactly that: `li r22,0` in the preheader, `stw r22,4(r31)`
//     in the blend, `stw r22,0x...` in both cleanups.  It costs -2 words
//     (the two `li r0,0` disappear) and takes the allocation from 6 to 7
//     callee-saved registers (want has 10).
//  4. Store order (last-resort lever, deliberate): `comp.p[3]` before
//     `comp.p[2]`, and `*(__ps_t *)&node->f20 = ...` before
//     `t11 = *(__ps_t *)&comp.v[0]`.  +6 words matched.
//
// SIZE ACCOUNTING (296 words = want exactly):
//     previous body (2 bugs) 296 -> +fix(1) 297 -> +fix(2) 298 -> +fix(3) 296.
// i.e. the previous 1184B was reached by two cancelling errors, and the two
// real fixes are paid for by the shared zero.
//
// HOW FAR THE SHAPE ACTUALLY MATCHES (measured, regs-masked diff):
//     mnemonic-only equal  256/296      (86%)
//     register-masked     231/296      (78%)
//     byte-exact           50/296      (16.9%)
// => the entire remaining gap is REGISTER ALLOCATION, plus 3 unemittable
//    `ps_mr` words.  109 of the 231 shape-equal words differ only in which
//    register number is used.
//
// WHY IT IS STILL PARKED (blockers, in address order):
//  A. **Register allocation — 7 callee-saved pseudos vs want's 10.**
//     want: `stmw r21,0xf4(r1)` / `lmw r21,0xf4(r1)` = r21..r30, holding
//     r30=self, r29=counter, r28=&comp.hA8, r27=&comp, r26=the homed zero,
//     r25=byte offset, r24=a SECOND &comp copy, r23/r22/r21 = three
//     loop-invariant address HI-parts (all 0x802A0000).
//     got: `stmw r24,0x100(r1)` = r24..r30 = self, counter, &comp, sub(=node+
//     0x120), zero, offset, &comp.hA8.  The mapping that would be needed is
//     want r27->got r28 (&comp), want r28->got r24 (&head), want r25->got r26
//     (offset), want r24->got r28 (2nd &comp, folded away by GCC),
//     want r10->got r29 / r8->got r26 / r9->got r31 (pass-2 counter/offset/
//     node) — a full scramble, not a few swaps.  Nothing in C reaches GCC 2.95
//     local_alloc's choice; a second named pointer (`Comp *cq`) measured
//     byte-identical, and reordering `cp`/`head`/`self->c120` assignments only
//     permutes it.
//  B. **The three address HI-parts come from loop.c `move_loop_constants`**
//     (address split: `lis rN,hi` hoisted into the preheader, `addi r4,rN,lo`
//     at each use).  MEASURED NEGATIVES: `-Os` disables it (all five
//     fn_800DF004 sites then emit `lis r4,0`+`addi r4,r4,0` inline — that is
//     the -2 lis / +5 addi census gap); `-O2` hoists only 2 of the 3 symbols;
//     `-fmove-all-movables`, `-fforce-addr`, `-fsched-spec*`,
//     `-fsched-interblock`, `-fgcse`, `-fregmove`, `-fno-thread-jumps` do NOT
//     enable it at -Os; explicit `char *aBC/aC8/aD4` locals assigned before the
//     loop give 3x(lis+addi) = 6 preheader words instead of 3 (1188B, 7.4%).
//     So -2 words are unreachable here, and that is exactly the residual size
//     gap of the -O2 variant below.
//  C. **Three op-4 words are unemittable.**  want's 0x800C3724 / 0x800C372C /
//     0x800C3788 are `ps_mr` (op 4, XO5=8, selector field==2) used as
//     reg->reg paired-single copies of comp.v[2] / comp.v[1] / comp.v[4].
//     LENS VERIFIED BY PROBE (`register __ps_t __asm__("frN")` pins land in
//     bits 25-21 = the FPR number).  tools/ps_diff.py's dec() for op 4 is
//     wrong (it reads D@6-10 and xo5@26-30); the correct A-form layout is
//     opcode@31-26, D@25-21, A@20-16, B@15-11, C@10-6, XO5@5-1.  Probed
//     selector map: 1=ps_neg, 4=ps_nabs, 8=ps_abs, 0/2=ps_mr.  NO cc1.exe
//     `__builtin_ps_*` (all 24 probed) emits selector 2, and `gen_move` of a
//     __ps_t emits `fmr` (op 63), not op 4.  Here GCC instead re-loads the two
//     values from the frame (`psq_l f0,224(r1)` / `psq_l f7,208(r1)`), which
//     is why the census shows psq_l 21 vs want 19 and ps_mr 3 vs 0.
//  D. Loop latches.  want's loop-1 latch is `cmpwi i,0 ; addi off,-0x1e0 ;
//     addi i,-1 ; bne` (4 words, the `cmpwi` dead) where GCC always folds to
//     `addi off,-0x1e0 ; addic. i,-1 ; bne` (3).  Writing the test as
//     `while (i-- != 0)` does produce `cmpwi`+`addi`, but GCC also inserts an
//     `mr r0,i` (1208B); writing `i--; } while (i != 0);` is CSE'd straight
//     back to `addic.`.  Loop 2 is rotated in both, so that is not the issue.
//  E. Block placement of the `done` cleanup.  want's tail-5 `beq` jumps
//     FORWARD over the `done` cleanup, which therefore needs no extra branch;
//     flow.c always lays `done` out after the loop, so this body pays one extra
//     `b` (+1 word; census: b 3 vs 5).  Moving `done` in the source either
//     merges the two cleanup copies (1156B) or costs 8 words (1164B).
//  F. `sub` lives in a callee-saved register here (r27) but in a volatile (r5)
//     in want, which is why want emits `addi r5,r31,0x120` once and reuses r5
//     while this body needs `mr r5,r27` at the first report site.  Same root
//     cause as (A).
//
// MEASURED ALTERNATIVES (all on the earlier body, both bugs fixed):
//   -Os  (DELIVERED, pad0xE8[12])           1184B (296w)  50/296  16.89%
//   -O2 -fno-schedule-insns (pad0xE8[4])     1196B (299w)  84/296  28.38%
//   -O2 -fno-schedule-insns (pad0xE8[12])    1196B (299w)  82/296  27.70%
//   -O2 (pad0xE8[4]) / (pad0xE8[12])         1180B (295w) 32/296  10.81% /
//                                              30/296  10.14%
//   -Os -fforce-addr / -fmove-all-movables / -fno-branch-count-reg /
//   -fgcse / -fregmove / -fsched-spec* / -fsched-interblock   1184B 50/296
//     (all byte-identical to -Os)
//   -fno-schedule-insns2                      1176B       11/296   3.72%
//   -O2 -fno-schedule-insns -fno-expensive-optimizations
//                                              1188B       16/296   5.41%
//   -O1 -fno-schedule-insns                   1188B       25/296   8.45%
//
// **The -O2 -fno-schedule-insns variant is the most interesting negative
// result here.**  With the instruction scheduler off, all FIVE SELFCHK tails
// (the 11/13-word `li r11,0 / cmpwi / bne / lwz / lwz / andi. / beq / li r11,1`
// blocks at 0x800C341C..0x800C35F8) come out BYTE-EXACT, because the volatile
// allocation then coincides with want's; the whole region 0x800C3404-0x800C35B8
// lines up 1:1.  It is NOT delivered only because the object is 12 B long:
// +1 word because the THIRD address (lbl_802992D4, used once) is not hoisted,
// +1 for the extra `b done` (blocker E), and +1 net because GCC strength-reduces
// the loop induction variable into CTR (`mtctr r28 ; addi r28,-1 ; mfctr r0 ;
// cmpwi r0,0`, +2 words per loop, partly offset by blocker D's shorter latch).
// NONE of `-fno-strength-reduce`, `-fno-reduce-all-givs`, `-fno-branch-count-reg`,
// `-fno-peephole`, `-fno-thread-jumps`, `-frerun-loop-opt`, `-funroll-loops`
// removes the CTR form, and no loop-shape rewrite (`while` instead of
// `do/while`, `i--` test, `off = i*15*32`, `off = i*0x1E0`) helps.  If a future
// round can kill the CTR usage the recipes suggest a hard-register pin
// (`"+"r"` volatile asm copy — banned here), that variant is the one to keep.
//

// SIGNATURES (read off the callee prologues, recipes §4p-4 / M8.31):
//   fn_80107A80(void*,s16,s16) void   `sth r5,0x56(r3); sth r4,0x54(r3)`
//   fn_80107B20(void*,s32,s32) ->s32  (cmpwi r3,0 at every call site)
//   fn_8010794C(void*) void / fn_800C9350(void*,void*) void
//   fn_800DF004(void*,char*,void*) — 3 args at ALL FIVE call sites; at
//       0x800C341C r5 already holds node+0x120 from the preceding compare,
//       so the source arg is that same pointer and GCC elides the reload.
//   CObject_RemoveRefLink(void*,void*) (0x8009DFC0 reads r4).
//   m2c's 2-arg `fn_800DF004(mgr, 0x802992BC)` was the arity bug; so was its
//       second arg being a string — 0x802992BC/C8/D4 are {1,4,0}/{1,3,0}/{9,0,0}
//       s32 tables (they only need to be extern'd, so the name does not matter).
//   The three tables are ADJACENT (0x2BC/0x2C8/0x2D4, 0xC bytes each) and all
//       in page 0x802A0000 — which is why want hoists three *separate* HI-parts
//       (r22/r23/r21) rather than one base (blocker B).
//
// CONSTANT FIX (recipes §6bb-287 / §6aq-223): m2c read the qb hash as
//   0x2BBC5D44.  want is `lis r9,-0x2bbd; ori r9,r9,0xa2bc` = 0xD445A2BC.
//   Kept as a bare literal (§6ae-174: hash literals stay bare).
//
// STRUCTURE (want 0x800C333C..0x800C37DC = 296 insns / 1184B):
//   One local aggregate `Comp` at r1+8 (0xF4 B) holds EVERY stack temp: the
//   fn_8010794C composite (p[4]@0x00 / i5C@0x5C / f80@0x80 / q[4]@0x88), the
//   3-word list head at 0xA8 (hA8 is the slot whose address goes to
//   CObject_RemoveRefLink), the iBC self-pointer, and the 0xC0..0xE7 scratch.
//   Declaring them as separate locals gives a different frame; as one aggregate
//   it lands exactly on want's 0x120 frame + stmw@0xF4.
//   v[] is a `f32 e[2]` overlay: the game writes its halves with stfs and
//   then reads the same 8 bytes with psq_l.  `f32[2]` + `*(__ps_t *)&` is the
//   only plain-C form that emits both — an `__ps_t` MEMBER copy emits psq_l
//   (see src/fn_801B7A48.c) but a 16-byte struct copy collapses to lwz/stw.
//   Pass 1: gather 4 PS pairs per node, drive fn_80107A80 / fn_80107B20,
//           report via fn_800DF004, blend node->f00, count hits.
//   Pass 2: scalar re-lerp of f1C, then the PS 4-vector block.
//   (want's own PS hash constant `lbl_80299074` lives at 0x80299074 — it is
//   loaded at 0x800C3760 as `lfs f0,-0x6f8c(r7)`, i.e. off a HOISTED page
//   anchor r7 = 0x802A0000, which is the 4th hoisted HI-part.)
//
// TOOLS GOTCHAS that cost real time on this one:
//   - `tools/ps_diff.py` does NOT read the draft's `// extra_cflags:` line; it
//     only ever appends `-mps-float`.  Pass the flags explicitly and as ONE
//     argv token: `tools/ps_diff.py 0x800C333C "-Os"`.  With two tokens
//     ("-Os" "-fforce-addr") only the last one survives.
//   - `tools/want_got.py` prints `?` for every opcode-4 word; use ps_diff/ps_disasm
//     for a PS body.
//   - The primary opcode of a Gekko word is its TOP 6 bits (`w >> 26`), not
//     `w & 0x3F` — lwz is 0xE0030148 and psq_l is 0xE00100D8 and both read 56
//     that way.  Do not filter opcode-4 words with `& 0x3F`.
//   - A draft whose compile emits any ngccc *warning* comes back from
//     compile_fn() as a bare FAIL (ngccc returns non-zero); the `(void *)&sym`
//     deref spelling needs the double cast `(*(void * *)&sym)`.
//
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* File-local layouts.  The shared Unk_* classes in structs.h are merged
   corpus-wide and mis-type nearly every slot this function touches (Comp
   0x00..0x1F and 0x88..0xA7 are __ps_t; Node 0x18..0x27 and 0xC0..0xCF are
   f32), so the real layouts are declared here rather than fought over in the
   shared header. */
typedef struct { f32 e[2]; } V2;      /* 8B: scalar halves / punned __ps_t */

typedef struct {
    __ps_t p[4];                      /* 0x00 */
    char pad0x20[0x3C];
    s32 i5C;                          /* 0x5C */
    char pad0x60[0x20];
    f32 f80;                          /* 0x80 */
    char pad0x84[4];
    __ps_t q[4];                      /* 0x88 */
    s32 hA8, hAC, hB0;                /* 0xA8 3-word list head */
    char pad0xB4[0x8];
    s32 iBC;                          /* 0xBC = &self[0x338] */
    V2 v[5];                          /* 0xC0..0xE7 scratch */
    char pad0xE8[12];                  /* frame tail */
} Comp;

typedef struct { char pad0x0[0x5C]; s32 i5C; } Sub;   /* node + 0x120 */

typedef struct Node {
    f32 f00;                          /* 0x00 */
    s32 i04;                          /* 0x04 */
    char pad0x08[0x10];
    f32 f18, f1C, f20, f24;           /* 0x18..0x27 (== pairs m18 / m20) */
    __ps_t m28, m30;                  /* 0x28, 0x30 */
    char pad0x38[0x30];
    __ps_t m68, m70;                  /* 0x68, 0x70 */
    char pad0x78[0x8];
    __ps_t m80, m88, m90, m98;        /* 0x80..0x9F */
    __ps_t mA0, mA8;                  /* 0xA0, 0xA8 */
    __ps_t mB0, mB8;                  /* 0xB0, 0xB8 */
    f32 fC0, fC4, fC8, fCC;           /* 0xC0..0xCF */
    char pad0xD0[0x50];
    Sub sub;                          /* 0x120 */
} Node;

typedef struct { s32 pad0[3]; s32 i0C; } Mgr;

/* lbl_80305FF8 is a POINTER to the global script/qb manager, not a base
   address: want loads it (`lwz r10,0x5ff8(r11)`) and then reads +0x44 of
   the pointee.  Spelling it as `extern s32 lbl_80305FF8` + `((char *)&lbl_
   80305FF8 + 0x44)` made GCC fold the whole chain into one `lis`/`lwz`
   against the WRONG address (0x8030603C) — same instruction count, wrong
   memory. */
typedef struct QbMgr { char pad0x00[0x44]; s32 qb; } QbMgr;   /* 0x44 hash */

typedef struct Self {
    char pad0x00[0x0C];
    Mgr *pmgr;                        /* 0x0C */
    char pad0x10[0x60];
    f32 r0x, r0y, r0z;                /* 0x70 */
    char pad0x7C[4];
    f32 r1x, r1y, r1z;                /* 0x80 */
    char pad0x8C[4];
    f32 r2x, r2y, r2z;                /* 0x90 */
    char pad0x9C[0x14];
    __ps_t mB0, mB8, mC0, mC8;        /* 0xB0..0xCF */
    char pad0xD0[0x50];
    s32 c120;                         /* 0x120 */
    char pad0x124[4];
    s32 flg128;                       /* 0x128 */
    char pad0x12C[0x80];
    s32 cnt1AC;                       /* 0x1AC */
    char pad0x1B0[0x140];
    Node *arr2F0;                     /* 0x2F0 */
    char pad0x2F4[0x1070];
    void *pmgr1364;                   /* 0x1364 */
} Self;

extern char lbl_802992BC[];
extern char lbl_802992C8[];
extern char lbl_802992D4[];
extern f32 lbl_80299074;
extern QbMgr *lbl_80305FF8;

void fn_8010794C(void *);
void fn_80107A80(void *, s16, s16);
s32 fn_80107B20(void *, s32, s32);
void fn_800DF004(void *, char *, void *);
void fn_800C9350(void *, void *);
void CObject_RemoveRefLink(void *, void *);

#define SELFCHK   (self->flg128 != 0) || (self->pmgr->i0C & 1)

void fn_800C333C(Self *arg0) {
    Comp comp;
    Comp *cp;
    Self *self;
    Node *node;
    Sub *sub;
    __ps_t t7, t11, t12, u;
    s32 i;
    s32 off;
    s32 r11;
    s32 *head;
    s32 f1, f2, f3, f4, f5;
    s32 z;

    self = arg0;
    cp = &comp;
    head = &comp.hA8;
    fn_8010794C(cp);
    comp.iBC = (s32)((char *)arg0 + 0x338);
    self->c120 = 0;
    z = 0;

    i = self->cnt1AC;
    if (i-- != 0) {
        off = ((i << 4) - i) << 5;
        do {
            node = (Node *)((char *)self->arr2F0 + off);
            comp.p[0] = node->m80;
            comp.p[1] = node->m88;
            comp.p[2] = node->m90;
            comp.p[3] = node->m98;
            fn_80107A80(cp, 0x10, 0);
            if (fn_80107B20(cp, 0, 0) != 0) {
                sub = (Sub *)((char *)node + 0x120);
                if (node->i04 != 1) {
                    if (comp.i5C != sub->i5C) {
                        fn_800DF004(self->pmgr1364, lbl_802992BC, sub);
                        f1 = 0;
                        if (SELFCHK) { f1 = 1; }
                        if (f1 != 0) { goto done; }
                        fn_800DF004(self->pmgr1364, lbl_802992C8, cp);
                        f2 = 0;
                        if (SELFCHK) { f2 = 1; }
                        if (f2 == 0) { goto blend; }
                        goto done;
                    } else {
                        goto blend;
                    }
                } else {
                    fn_800DF004(self->pmgr1364, lbl_802992C8, cp);
                    f3 = 0;
                    if (SELFCHK) { f3 = 1; }
                    if (f3 != 0) { goto done; }
                }
blend:
                fn_800C9350(sub, cp);
                node->i04 = z;
                node->f00 = (f32)(comp.f80 * (node->fC0 - node->fC8) + node->fC8);
                node->m68 = comp.q[2];
                node->m70 = comp.q[3];
                comp.p[3] = comp.q[1];
                comp.p[2] = comp.q[0];
                self->c120 = self->c120 + 1;
            } else {
                if (node->i04 != 1) {
                    sub = (Sub *)((char *)node + 0x120);
                    fn_800DF004(self->pmgr1364, lbl_802992BC, sub);
                    f4 = 0;
                    if (SELFCHK) { f4 = 1; }
                    if (f4 != 0) { goto done; }
                    node->i04 = 1;
                    node->f00 = node->fC0;
                }
            }
            r11 = 1;
            if (lbl_80305FF8->qb == 0xD445A2BC) { r11 = 0; }
            if (r11 != 0) {
                fn_80107A80(cp, 0, 0x50);
                if (fn_80107B20(cp, 0, 0) != 0) {
                    fn_800DF004(self->pmgr1364, lbl_802992D4, cp);
                    f5 = 0;
                    if (SELFCHK) { f5 = 1; }
                    if (f5 == 0) { goto loopend; }
                    goto done;
                }
            }
            off -= 0x1E0;
            i--;
        } while (i != 0);
loopend:
    }
    goto pass2;

done:
    if (*head != 0) {
        CObject_RemoveRefLink(*head, head);
        *head = z;
    }
    return;

pass2:
    i = self->cnt1AC;
    if (i-- != 0) {
        off = ((i << 4) - i) << 5;
        do {
            node = (Node *)((char *)self->arr2F0 + off);
            *(__ps_t *)&node->f18 = node->mA8;
            *(__ps_t *)&node->f20 = node->mB0;
            node->f1C = node->f1C + (*(f32 *)((char *)self->arr2F0 + off) - node->fC8);
            off -= 0x1E0;
            comp.v[2].e[0] = (node->f20 * self->r2x) + ((node->f18 * self->r0x) + (node->f1C * self->r1x));
            comp.v[2].e[1] = (node->f20 * self->r2y) + ((node->f18 * self->r0y) + (node->f1C * self->r1y));
            comp.v[3].e[0] = (node->f20 * self->r2z) + ((node->f18 * self->r0z) + (node->f1C * self->r1z));
            comp.v[3].e[1] = node->f24;
            *(__ps_t *)&comp.v[0] = *(__ps_t *)&comp.v[2];
            *(__ps_t *)&comp.v[1] = *(__ps_t *)&comp.v[3];
            *(__ps_t *)&node->f18 = *(__ps_t *)&comp.v[2];
            *(__ps_t *)&node->f20 = *(__ps_t *)&comp.v[3];
            t11 = *(__ps_t *)&comp.v[0];
            t7 = *(__ps_t *)&comp.v[1];
            t12 = __builtin_ps_mul(self->mC0, __builtin_ps_merge10(t11, t7));
            t12 = __builtin_ps_sub(t12, __builtin_ps_mul(__builtin_ps_merge10(self->mC0, self->mC8), t11));
            *(__ps_t *)&comp.v[4] = __builtin_ps_merge00(t12, t12);
            u = __builtin_ps_mul(__builtin_ps_merge00(self->mC8, self->mC0),
                                 __builtin_ps_merge00(t11, t7));
            comp.v[4].e[1] = lbl_80299074;
            u = __builtin_ps_sub(u, __builtin_ps_merge10(u, u));
            t12 = __builtin_ps_merge10(t12, u);
            *(__ps_t *)&comp.v[2] = t12;
            u = *(__ps_t *)&comp.v[4];
            *(__ps_t *)&comp.v[0] = __builtin_ps_add(self->mB0, t12);
            *(__ps_t *)&comp.v[3] = u;
            *(__ps_t *)&comp.v[1] = __builtin_ps_add(self->mB8, u);
            node->m28 = *(__ps_t *)&comp.v[0];
            node->m30 = *(__ps_t *)&comp.v[1];
            i--;
        } while (i != 0);
    }
    if (comp.hA8 != 0) {
        CObject_RemoveRefLink((void *)comp.hA8, head);
        comp.hA8 = z;
    }
}
