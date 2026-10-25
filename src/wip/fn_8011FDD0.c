// WIP DRAFT (non-matching) — hand reconstruction from the DOL disassembly .
// family=m2c range=0x8011FDD0-0x80120464 size=1684B
//
// === PARKED 2026-10-08 — best draft so far, does NOT match yet ===
// MEASURED: 405 insns of want's 421, 3.3% of the index-aligned masked words
// (test_wip_drafts verdict: DIFF), register+const-normalised LCS 34.0% of want.
// Ranked blockers with the numbers behind them are in "WHAT STILL BLOCKS
// EXACTNESS" below; the first one (the lookup loop's CTR/peeled/rotated shape)
// is a GCC 2.95 loop-optimizer decision, not a statement-order tweak, and 8
// source variants were compiled and measured against it.
//
// BREAKTHROUGH (why this file changed shape): the promoted sibling
// src/fn_801210C4.c (matched, byte-identical) contains the *same* stop-voice
// block this function has, and it shows the original's real idiom:
//
//     char *base;  char *p1;  char *p2;  char *p3;  s32 temp;  s32 irq;
//     base = lbl_8038F0C0;
//     temp = arg0 * 0x21C;
//     p1 = base + 0x20C;
//     p2 = base + 0x218;
//     *(s32 *)(p2 + temp) = 0;
//     if (*(s32 *)(p1 + temp) != 0) { ... }
//     p3 = base + 0x28;
//     *(s32 *)(p3 + temp) = (*(s32 *)(p3 + temp) + 1) & 7;
//
// i.e. the addresses are EXPLICIT POINTER LOCALS (base + fixed displacement)
// with a separate `s32 temp` byte offset, and every field is `*(T *)(pX + temp)`.
// The previous round spelled the same accesses with `lbl_8038F0C0 + (o) + K`
// offset macros; both parse to the same expression tree, but the pointer-local
// form is what the original compiler saw: it is the difference between want's
// `addi r28, r31, 0x20c` + `lwzx r3, r28, r30` and a form where ngccc folds a
// *different* constant into the base (got kept base+0x20C and derived the other
// addresses from it with `addi rN, r30, -0x1e4`, want derives them from `base`).
// Use this style for every block from here on; do not go back to the macros.
//
// SCORE so far: want 421 insns; the macro draft compiled to 402.  Re-measure
// with  LEAF_TMPDIR=<your dir> tools/venv/bin/python tools/ps_diff.py 0x8011FDD0 1684 --all
// NOTE: tools/want_got.py is NOT PS-aware (its want column dies at the first
// opcode-4 word, here 0x8011FFB8-ish); use ps_diff.py --all for this function.
// Also: `test_wip_drafts.py` scores index-aligned masked words, which is near 0
// as soon as one block is off by one insn — compare structure with ps_diff.py
// and SequenceMatcher instead of trusting the percentage.
//
// What is settled (verified against the want disassembly):
//  * semantics: 3-voice PCM feeder.  arg1 is a ring-slot pointer (searched over
//    j=0..7 slots x i=0..2 voices, matching the voice whose ringIdx == j),
//    arg0 < 0 stops the voice (AXFreeVoice + ring bump + 0x2000/0x200 mask
//    clear), else the stream is (re)started: AXSetVoiceType/SrcType/Ve/Addr/
//    Adpcm + memset/DCFlushRange + ARQPostRequest(RAM->ARAM, 0x4000) and the
//    play offset wraps in a 0x8000 ring.  f32 rate = (f32)(u32)buf[8] * 100 =
//    / 32000 = lbl_8029D75C.
//  * callees (from symbols.txt): 0x80264768/0x80264790 = OSDisableInterrupts/
//    OSRestoreInterrupts, 0x802776E4 = AXFreeVoice, 0x80279D2C = AXSetVoiceType
//    (r4 = 0), 0x80279C0C = AXSetVoiceSrcType (r4 = 1), 0x80279FCC =
//    AXSetVoiceVe(&ve {0x7FFF,0}), 0x8027A024 = AXSetVoiceAddr(&addr),
//    0x8027A134 = AXSetVoiceAdpcm(&adpcm), 0x8027691C = ARQPostRequest,
//    0x8026AFB8 = memset, 0x802632AC = DCFlushRange, 0x8011FB4C = ARQ callback,
//    0x8011F3A8 = slot post-processor whose last arg is THIS function's own
//    address (ARQ callback).  NB: the first-start ARQ passes fn_8011FB4C, the
//    restart ARQ passes 0.
//  * stack layout (drives the 0x78 frame + stmw r22): AXPBAddr addr @ r1+8
//    (0x10), AXPBAdpcm adpcm @ r1+0x18 (0x28: 0x20-byte struct copy from
//    buf+0x1C — GCC movstr: one 0x18-byte loop pass + 8 tail bytes — then 4
//    halfwords from buf+0x3C/0x3E/0x40/0x42), AXPBVE ve @ r1+0x40 (0x7FFF,0),
//    and the (f32)(u32) conversion's own 8-byte temp @ r1+0x48.
//  * the lookup loop addresses the symbol lbl_8038F0EC (= &lbl_8038F0C0[0].slot[0]
//    = base+0x2C) DIRECTLY, re-materialised inside the loop (`lis r5` hoisted,
//    `addi r9, r5, -0xf14` in the loop body); ring reads are `lbl_8038F0EC - 4`
//    (+ i*0x21C) so the whole loop is writable with symbol arithmetic and needs
//    no pointer locals.  The loop's inner variable is UNSIGNED (`cmplwi r10,2`)
//    and the i=0 slot is tested before the `for (i = 1; i < 3; i++)` body
//    (GCC 2.x pre-increment loop form: `li r10, 0` then `addi r10, r10, 1`).
//  * the body blocks ALL use `base = lbl_8038F0C0` + pointer locals p1(base+0x20C,
//    the AXVPB slot), p2(base+0x218), p3(base+0x28, ring idx), p5(base+0x210, the
//    live flag), p6(base+0xC, the play offset, u32 in a 0x8000 ring); `temp` is
//    idx*0x21C.  p6+0x04 == base+4+temp is the voice's "already started" counter.
//  * the compare that guards the 0x4060 memset is hoisted by the scheduler
//    ABOVE the five AXSetVoice* calls and its CR is saved/restored
//    (`mfcr r29` ... `mtcrf 0x80,r29` ... `bgt`) — see
//    docs/parkings/28-cr-save-condition-liveness-across-calls.md; writing the
//    plain `if (arg0 < 0x4060)` puts the cmp+branch after the calls.
//
// MEASURED RESULTS OF ROUND r3 (all with ps_diff.py 0x8011FDD0 1684 --all +
// a register/const-normalised SequenceMatcher pass):
// macro-offset draft : 402 insns, LCS-norm 28.2% of want
//   this pointer-local draft      : 405 insns, LCS-norm 34.0% of want (best so far)
//   want                          : 421 insns
// The pointer-local form is a real improvement (+6 pts) but is NOT the blocker.
//
// WHAT STILL BLOCKS EXACTNESS, in measured order of impact:
//  1. THE LOOKUP LOOP (first ~45 insns) IS A DIFFERENT LOOP SHAPE.  want runs
//     the outer j loop as a CTR loop (`li r0, 8 / mtctr r0 ... bdnz`), with the
//     i==0 slot tested as a PEELED iteration using strength-reduced pointers
//     (`cmpw r4, r6` / `lwz r0, 0(r3)` with r6 += 0x3C, r3 = lbl_8038F0EC-4)
//     and the i>=1 cases in a ROTATED inner loop (`li r10, 0` at the loop top,
//     `addi r10,r10,1 / cmplwi r10,2 / bgt` at the bottom).  This draft gets a
//     plain nested loop with `cmpwi r8,7 / bgt` and `li r10,1`.  EIGHT source
//     variants were compiled and measured (nested i=1..2 with the i==0 test
//     first [best, 34.0%], single `for i=0..2` with break, same with
//     `idx != -1`, `i <= 2`, `while` outer, `for (j < 8 && idx < 0)`,
//     `for (j < 8 && idx == -1)`, single loop + separate `if (idx >= 0) break`):
//     every one produced 387-405 insns and 33.0-35.9% LCS, none reproduced the
//     CTR/peeled/rotated shape.  This is a loop-optimizer decision, not a
//     statement-order tweak — attack it with GCC 2.95 loop.c knowledge
//     (doloop + rotation preconditions), not with more source permutations.
//  2. SAVED-REGISTER COUNT / FRAME.  want `stmw r22, 0x50(r1)` + frame 0x78
//     (10 saved GPRs); this draft `stmw r18, 0x50(r1)` + frame 0x88 (14).  The
//     four extra are the hoisted pointer locals that stay live ACROSS the AX/
//     memset/DCFlush calls (measured: base in r19, p5/base+0x210 in r23,
//     p6/base+0xC in r20).  In want those same fields are re-materialised in
//     volatile registers just before each use instead (p5 appears as r7, r10,
//     r9 all inside the first-start block).  NOTE: simply moving the
//     `p5/p6 = base + ...` assignments into the two branches did NOT drop the
//     count (still stmw r18) and cost 3 pts (34.0 -> 30.9), so the fix is to
//     stop keeping them live at all — e.g. spell those two fields as
//     single-use expressions while keeping base/p1/... as locals.  The frame
//     and every stack offset follow from the saved-register count: see
//     docs/parkings/76 ("hoisted operand forces a saved reg") for the lever
//     and the measurement recipe.
//  3. block-A (unk04 == 0, first start) store ordering: want emits the halfword
//     stores of AXPBAddr in the order h02 / h0E / h0C, then the n<=0x8000 arm as
//     h08 / h0A / h04 / h06 / h00 — i.e. NOT ascending and NOT a clean reverse,
//     so the C statement order there has to be recovered, not guessed.
//  4. the B2 restart test (`a <= 0x3FFF ? flag = (x == 0) : (x == 0 ? flag = 1
//     : flag)`) is written as two different spellings in want (setcc via
//     xori/subfic/adde in one arm, cmpwi/bne/li in the other); one spelling in
//     both arms will not match.
// NO inline __asm__ anywhere in this draft; no pins; no barrier.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

/* AXVPB fields this function touches */
typedef struct {
    char pad00[0x1C];
    u32 unk0x1C;           /* +0x1C */
    char pad20[0x186];
    u16 unk0x1A6;          /* +0x1A6 */
    char pad1A8[0x02];
    u16 unk0x1AA;          /* +0x1AA */
    u16 unk0x1AC;          /* +0x1AC */
    char pad1AE[0x04];
    u16 unk0x1B2;          /* +0x1B2 */
    u16 unk0x1B4;          /* +0x1B4 */
} Vpb;

/* AXPBADDR: the original writes hi/lo halfword pairs explicitly */
typedef struct {
    u16 h00;               /* +0x00 */
    u16 h02;               /* +0x02 */
    u16 h04;               /* +0x04 */
    u16 h06;               /* +0x06 */
    u16 h08;               /* +0x08 */
    u16 h0A;               /* +0x0A */
    u16 h0C;               /* +0x0C */
    u16 h0E;               /* +0x0E */
} AXPBAddr;

/* the 0x20-byte part of AXPBADPCM that GCC block-copies (movstr) */
typedef struct {
    u32 w[8];
} AdpcmW;

typedef struct {
    AdpcmW words;          /* +0x00, copied as one 0x20 block */
    u16 h[4];              /* +0x20, copied halfword by halfword */
} AXPBAdpcm;

typedef struct {
    u16 vol;               /* +0x00 */
    u16 delta;             /* +0x02 */
} AXPBVe;

extern char lbl_8038F0C0[];      /* 3-voice table (stride 0x21C) */
extern char lbl_8038F0EC[];      /* &lbl_8038F0C0[0].slot[0] = base + 0x2C */
extern s32 lbl_80302F04;         /* per-voice active mask */
extern char *lbl_80302F14[3];    /* per-voice sample buffer */
extern s32 lbl_8038F714[3];      /* per-voice ARAM base */
extern u32 lbl_8037B778;         /* sample/tick counter */
extern char lbl_8039B860[];      /* ARQRequest[3], stride 0x20 */
extern f32 lbl_8029D758;         /* 100.0f */
extern f32 lbl_8029D75C;         /* 32000.0f */

s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void AXFreeVoice(Vpb *);
void AXSetVoiceType(Vpb *, u16);
void AXSetVoiceSrcType(Vpb *, u32);
void AXSetVoiceVe(Vpb *, void *);
void AXSetVoiceAddr(Vpb *, void *);
void AXSetVoiceAdpcm(Vpb *, void *);
void ARQPostRequest(void *, u32, u32, u32, void *, void *, u32, void *);
void memset(void *, s32, u32);
void DCFlushRange(void *, u32);
void fn_8011FB4C(void *);
void fn_8011F3A8(void *, void *, s32, s32, void *);
void fn_8011FDD0(s32 arg0, char *arg1);

void fn_8011FDD0(s32 arg0, char *arg1) {
    AXPBAddr addr;
    AXPBAdpcm adpcm;
    AXPBVe ve;
    char *base;
    char *p1;
    char *p2;
    char *p3;
    char *p5;
    char *p6;
    char *buf;
    Vpb *vpb;
    s32 idx;
    s32 temp;
    s32 unk04;
    s32 irq;
    s32 idx4;
    s32 n;
    s32 v;
    s32 q;
    s32 len;
    s32 flag;
    s32 cur;
    s32 j;
    u32 i;

    /* find the voice + ring slot that owns arg1 */
    idx = -1;
    for (j = 0; j < 8; j++) {
        if (arg1 == (void *)(lbl_8038F0EC + j * 0x3C) &&
            j == *(s32 *)(lbl_8038F0EC - 4)) {
            idx = 0;
            break;
        }
        for (i = 1; i < 3; i++) {
            if (arg1 == (void *)(lbl_8038F0EC + i * 0x21C + j * 0x3C) &&
                j == *(s32 *)(lbl_8038F0EC + i * 0x21C - 4)) {
                idx = i;
                break;
            }
        }
        if (idx >= 0) {
            break;
        }
    }
    if (idx == -1) {
        return;
    }

    if (arg0 < 0) {
        /* stop: free the voice, bump the ring, clear the mask bits */
        irq = OSDisableInterrupts();
        temp = idx * 0x21C;
        base = lbl_8038F0C0;
        p1 = base + 0x20C;
        if (*(s32 *)(p1 + temp) != 0) {
            AXFreeVoice(*(s32 *)(p1 + temp));
        }
        p3 = base + 0x28;
        p2 = base + 0x218;
        *(s32 *)(p2 + temp) = 0;
        *(s32 *)(p1 + temp) = 0;
        *(s32 *)(p3 + temp) = (*(s32 *)(p3 + temp) + 1) & 7;
        OSRestoreInterrupts(irq);
        lbl_80302F04 = lbl_80302F04 & ~(0x2000 << idx);
        lbl_80302F04 = lbl_80302F04 & ~(0x200 << idx);
        return;
    }

    temp = idx * 0x21C;
    base = lbl_8038F0C0;
    p1 = base + 0x20C;
    vpb = *(Vpb **)(p1 + temp);
    if (vpb == NULL) {
        return;
    }
    unk04 = *(s32 *)(base + 4 + temp);
    p5 = base + 0x210;
    p6 = base + 0xC;

    if (unk04 == 0) {
        /* first start */
        irq = OSDisableInterrupts();
        idx4 = idx * 4;
        buf = lbl_80302F14[idx];
        v = lbl_8038F714[idx] * 2;
        addr.h02 = (u16)unk04;
        n = (u32)*(s32 *)(buf + 4) >> 1;
        addr.h0E = (u16)(v + 2);
        addr.h0C = (u16)((u32)(v + 2) >> 16);
        if (n > 0x8000) {
            q = n >> 14;
            if ((n & 0x3FFF) > 0) {
                q++;
            }
            addr.h04 = (u16)((u32)(v + 2) >> 16);
            addr.h06 = (u16)(v + 2);
            if (q & 1) {
                *(s32 *)(p6 + temp) = *(s32 *)(p6 + temp) + 0x4000;
                *(s32 *)(p5 + temp) = unk04;
                addr.h0C = (u16)((u32)(v + 0x8002) >> 16);
                addr.h0E = (u16)(v + 0x8002);
            } else {
                *(s32 *)(p6 + temp) = n & 0x3FFF;
                *(s32 *)(p5 + temp) = 1;
            }
            addr.h00 = 1;
            addr.h08 = (u16)((u32)(v - 1) >> 16);
            addr.h0A = (u16)(v - 1);
        } else {
            *(s32 *)(p5 + temp) = 1;
            addr.h08 = (u16)((u32)(v + *(s32 *)(buf + 4) - 1) >> 16);
            addr.h0A = (u16)(v + *(s32 *)(buf + 4) - 1);
            addr.h04 = (u16)((u32)(lbl_8037B778 * 2) >> 16);
            addr.h06 = (u16)(lbl_8037B778 * 2);
            addr.h00 = (u16)unk04;
        }

        adpcm.words = *(AdpcmW *)(buf + 0x1C);
        adpcm.h[0] = *(u16 *)(buf + 0x3C);
        adpcm.h[1] = *(u16 *)(buf + 0x3E);
        adpcm.h[2] = *(u16 *)(buf + 0x40);
        adpcm.h[3] = *(u16 *)(buf + 0x42);
        ve.vol = 0x7FFF;
        ve.delta = 0;

        AXSetVoiceType(vpb, 0);
        AXSetVoiceSrcType(vpb, 1);
        AXSetVoiceVe(vpb, &ve);
        AXSetVoiceAddr(vpb, &addr);
        AXSetVoiceAdpcm(vpb, &adpcm);

        if (arg0 < 0x4060) {
            len = 0x4060 - arg0;
            memset(buf + arg0, 0, len);
            DCFlushRange(buf + arg0, len);
        }
        OSRestoreInterrupts(irq);

        ARQPostRequest(&lbl_8039B860[idx * 0x20], 0, 0, 1, buf + 0x60,
                       (void *)(lbl_8038F714[idx] + *(s32 *)(p6 + temp)),
                       0x4000, fn_8011FB4C);

        cur = *(s32 *)(p6 + temp);
        *(s32 *)(p6 + temp) = cur + 0x4000;
        *(f32 *)(base + 0x14 + temp) =
            (f32)*(u32 *)(buf + 8) * lbl_8029D758 / lbl_8029D75C;
        if (cur + 0x4000 > 0x7FFF) {
            *(s32 *)(p6 + temp) = cur - 0x4000;
        }
        *(s32 *)(base + 4 + temp) = *(s32 *)(base + 4 + temp) + 0x4060;
    } else {
        /* keep an already running stream going */
        idx4 = idx * 4;
        buf = lbl_80302F14[idx];
        if (arg0 < 0x4000) {
            len = 0x4000 - arg0;
            memset(buf + arg0, 0, len);
            DCFlushRange(buf + arg0, len);
        }

        n = ((s32)(((u32)vpb->unk0x1B2 << 16) | vpb->unk0x1B4) -
             lbl_8038F714[idx] * 2) /
            2;
        flag = 0;
        if (n <= 0x3FFF) {
            flag = (*(s32 *)(p5 + temp) == 0);
        } else if (*(s32 *)(p5 + temp) == 0) {
            flag = 1;
        }
        if (flag) {
            ARQPostRequest(&lbl_8039B860[idx * 0x20], 0, 0, 1, buf,
                           (void *)(lbl_8038F714[idx] + *(s32 *)(p6 + temp)),
                           0x4000, NULL);
            cur = *(s32 *)(p6 + temp);
            *(s32 *)(p6 + temp) = cur + 0x4000;
            if (cur + 0x4000 > 0x7FFF) {
                *(s32 *)(p6 + temp) = cur - 0x4000;
            }
            *(s32 *)(p5 + temp) = (*(s32 *)(p5 + temp) != 0);
            *(s32 *)(base + 4 + temp) = *(s32 *)(base + 4 + temp) + 0x4000;
        }
    }

    n = *(s32 *)(base + 4 + temp) + 0x4000;
    if (n > *(s32 *)(base + temp)) {
        len = (0x4000 - (n - *(s32 *)(base + temp))) & ~0x3F;
    } else {
        len = 0x4000;
    }
    if (len > 0) {
        fn_8011F3A8(
            (void *)(lbl_8038F0EC + temp + *(s32 *)(lbl_8038F0EC - 4 + temp) * 0x3C),
            buf, len, *(s32 *)(base + 8 + temp) + *(s32 *)(base + 4 + temp),
            fn_8011FDD0);
    } else if (vpb->unk0x1A6 == 1) {
        vpb->unk0x1A6 = 0;
        vpb->unk0x1C |= 0x6000;
        vpb->unk0x1AA = (u16)((u32)(lbl_8037B778 * 2) >> 16);
        vpb->unk0x1AC = (u16)(lbl_8037B778 * 2);
    }
}
