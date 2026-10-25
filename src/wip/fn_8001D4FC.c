// family=m2c range=0x8001D4FC-0x8001D668 size=364B
// PARKED: 96.7%, size-exact 364B, 3 differing words (both residuals below).
// No instructions are emitted from inline asm: the five
// `register ... __asm__("rN")` lines are register-VARIABLE declarations that
// only constrain allocation; there is no asm template in this file.
//
// WHAT THE FUNCTION IS: CPU->ARQ texture/DMA copy (0x8001D4FC..0x8001D668,
// 91 insns).  Fast path (dst/src/size all 32B-aligned): DCFlushRange(src),
// one big ARQPostRequest(src,dst,size), spin on the completion flag
// lbl_803627E0, DCFlushRange(src), return.  Slow path: stage through a
// 0x403C bounce buffer at (u32)&req+0x3F & ~0x1F in <=0x4000 chunks,
// src advances by len, d (=dst&~0x1F) advances by len (precomputed into r26
// before the memcpy, copied into r27 at the latch), rem=(size+0x1F)&~0x1F.
//
// -----------------------------------------------------------------------
// THIS ROUND'S WIN (94.5% -> 96.7%, 2 of the 5 old residual words killed)
// -----------------------------------------------------------------------
// The old note said the slow-path entry needed "the rem expression
// materialised without the r30 pin (or a non-coalescing source form)".  The
// non-coalescing source form is a SECOND register-variable pin on the
// `(size + 0x1F)` intermediate:
//         register s32 t9 __asm__("r9");
//         t9 = size_r + 0x1F;
//         rem_r = t9 & ~0x1F;
// Without t9, `rem_r = (size_r + 0x1F) & ~0x1F` COALESCES the addi into the
// pinned r30 (want `addi r9,r31,0x1f` + `rlwinm. r30,r9`; got
// `addi r30,r31,0x1f` + `rlwinm. r30,r30`) - that was residual #1 and #1b of
// the previous note, now both fixed.  A plain `__asm__("" : "+r"(t9))` barrier
// on an UNPINNED t9 is worth 0.0% (still 94.5%): the barrier blocks the
// optimisation but does not pick the register, so the addi still folds into
// r30.  The pin is what buys r9.
//
// -----------------------------------------------------------------------
// REMAINING RESIDUAL (3 words / 91)
// -----------------------------------------------------------------------
// (1) 0x8001D5CC/0x8001D5D0 - memcpy arg-setup order, 2 words: the want moves
//     r31 into r5, r28 into r4 and r29 into r3 before clearing cr1 and
//     calling memcpy, while this build moves r28 into r4 first and r31 into
//     r5 second with the r3 move, cr1 clear and call identical.
//     Want is pure reverse-arg emission (arg2,arg1,arg0); ngccc always emits
//     (arg1,arg2,arg0) here.  INVARIANT under every lever tried this round:
//     all 6 arg-type spellings (s32 / void* / u8* / (u32) casts), 5 memcpy
//     prototypes (`s32 memcpy();`, `void *memcpy();`, `void memcpy();`,
//     `s32 memcpy(void*,void*,s32);` - all four fixed-arity forms DELETE the
//     crclr cr1eq that want keeps, so the K&R form is required), staging both
//     args into named temps, comma/assignment in the last arg, arg-slot
//     register pins (r4/r5) placed both before the call and after the len
//     computation, volatile and non-volatile `"+r"` barriers on len / src_r /
//     buf, a `"memory"`-clobber fence before the call, a pre-computed
//     `dn = d + len` temp, and -fno-schedule-insns2 / -fno-sched-spec /
//     -fno-sched-interblock / -Os.  Freezing the window in a volatile
//     `__asm__("mr %0,%1...")` block does NOT work either: this cc1 does not
//     honour a register-variable pin used as an `asm` OUTPUT (it picks its own
//     register), so the copies land in the wrong regs.
//     => Genuine doc-15 expand_call/sched member.  Do not re-run the ladder.
//
// (2) 0x8001D64C - loop latch, 1 word: the want tests r30 with a record-form
//     OR of r30 with itself and branches on nonzero, while this build
//     compares r30 against immediate 0 and branches on nonzero.
//     The `or.`-with-identical-operands form is emitted by this cc1 ONLY for a
//     POINTER-typed (Pmode) test; an SImode `x != 0` is always `cmpwi x,0`.
//     Confirmed against the promoted exemplar src/fn_800CC268.c, whose latch
//     is `mr. r9,r9` (= `or. r9,r9,r9`) on a `Node *` web.
//     To use it here `rem` would have to be a Pmode web in r30, but the r30
//     home is only obtainable through an s32 register-variable pin - pointer
//     pins are SILENTLY DROPPED by this cc1 (§74-161a / §6an-245), and with
//     the pin removed GCC moves rem to r31 and len to r30 (the swap the pins
//     exist to prevent).  20+ spellings tried: `rem` as char*/void*/u8* unpinned
//     (lands r31), `(char *)rem_r != 0` / `(u32)rem_r != 0` casts on the
//     pinned s32 (front end folds the cast back to SImode), `while (rem_r)`,
//     `rem_r ? 1 : 0`, `rem_r && 1`, `1 && rem_r`, `rem_r < 0 || rem_r > 0`,
//     unsigned/long types, volatile rem (needs a stack slot, frame shifts),
//     explicit entry guard + do-while (unrotated, so the latch value would be
//     a Pmode PHI), a separate pointer-typed copy of rem for the test (lands
//     its own register), and (in standalone probes) 25+ further shapes.
//     => Unreachable in plain C while rem must live in r30.  Park.
//
// TOOLING NOTE worth remembering: `objdump` prints `or. rD,rS,rS` as
// `mr. rD,rS` when the two source operands are the same register.  Grepping a
// probe disassembly for the string "or." therefore MISSES every real instance
// of this idiom - that is why the first ~20 probe rounds of this round found
// "no or. anywhere" before the promoted fn_800CC268 was compiled as a control.
//
// LOADS ON THE EXISTING PINS: the four original pins are load-bearing, so
// "delete all stale scaffolding" (the earlier lever) does NOT apply here.
// Measured against the 94.5% four-pin body:
//   remove rem_r pin only          85.7%   (rem->r31 / len->r30 swap)
//   remove all four pins            6.5%
//   add t9 pin (this round)        96.7%   <- the 2 words recovered
// (dst_r / src_r / size_r were not removed individually; ag23b established
// them as load-bearing and nothing here disturbs them.)
// No `// FLAG:` line; the best body is also the flagless body.
//
// KEY FIX FROM 2026-09-27 (ag23b, 73.6% -> 94.5%): the dst/src saved-register
// swap (want dst->r27, src->r28; natural allocation gives src->r27, dst->r28
// because the fast path uses src first) and the rem/len swap (want rem->r30,
// len->r31; natural gives the reverse) are a doc-15 allocation tie-break,
// cracked with register-variable pin-a-copy after ~20 non-asm structural
// variants.  The prologue copy order, both DMA paths, the frame layout
// (stwu -0x4090, stmw r23), the store order and both completion spin loops
// match word-for-word.
//
// NOT PROMOTED (WIP, inert - src/wip is not in the build).
extern volatile s32 lbl_803627E0;
void DCFlushRange(s32, s32);
void ARQPostRequest(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001D4EC(void);
s32 memcpy();

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} ARQReq;

void fn_8001D4FC(void *dst, void *src, s32 size) {
    register s32 dst_r __asm__("r27");
    register s32 src_r __asm__("r28");
    register s32 size_r __asm__("r31");
    register s32 rem_r __asm__("r30");
    register s32 t9 __asm__("r9");
    ARQReq req;
    u8 buffer[0x403C];
    u8 *buf;
    s32 len;
    s32 d;
    dst_r = (s32)dst;
    src_r = (s32)src;
    size_r = size;

    if ((((u32)dst_r & 0x1F) == 0) && (((u32)src_r & 0x1F) == 0) && ((size_r & 0x1F) == 0)) {
        lbl_803627E0 = 0;
        DCFlushRange(src_r, size_r);
        ARQPostRequest((s32)&req, 0, 0, 1, src_r, dst_r, size_r, (s32)fn_8001D4EC);
        if (lbl_803627E0 == 0) {
            while (lbl_803627E0 == 0) {
            }
        }
        DCFlushRange(src_r, size_r);
        return;
    }
    t9 = size_r + 0x1F;
    rem_r = t9 & ~0x1F;
    buf = (u8 *)(((u32)&req + 0x3F) & ~0x1F);
    d = dst_r & ~0x1F;
    while (rem_r != 0) {
        len = 0x4000;
        if (rem_r <= 0x3FFF) {
            len = rem_r;
        }
        memcpy((s32)buf, src_r, len);
        rem_r -= len;
        lbl_803627E0 = 0;
        src_r += len;
        DCFlushRange((s32)buf, len);
        ARQPostRequest((s32)&req, 0, 0, 1, (s32)buf, d, len, (s32)fn_8001D4EC);
        if (lbl_803627E0 == 0) {
            while (lbl_803627E0 == 0) {
            }
        }
        DCFlushRange((s32)buf, len);
        d += len;
    }
}
