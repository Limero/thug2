// PARKED 2026-10-03: DIFF, masked 2/76 words (2.6%), object .text 280B
// vs want 304B (6 words short). Baseline was DIFF 7.7% with the m2c draft —
// the pct went DOWN because the body is now instruction-for-instruction
// correct but the positional scorer can no longer reward coincidence: every
// register number differs and the tail is 6 words short, so almost no word
// lands on its want position. The body below is the honest best.
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80076778
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_vs_got.py 0x80076778
//
// WHAT IS NOW EXACT (do not undo):
//  * Stride/limit struct: fields are u16 at +0x10/+0x12/+0x18/+0x1A and s32 at
//    +0x0C. The m2c draft typed them s32 and emitted lwz for all four; the want
//    is lhz on all four. (m2c's Unk_5D1D68CC does not even cover +0x12/+0x1A.)
//  * The `clrlwi rX, rY, 0x10` idiom needs NO cast: a plain `u16` FIELD read
//    into an `s32` LOCAL reproduces it exactly. `(u16)x`, `(u16)(s32)x`,
//    `(s32)(s16)x` and a u16/u32 intermediate ALL fold the mask away (12 probe
//    spellings compiled; see below). The m2c `(s32)x` reads were the reason
//    both clrlwi's were missing.
//  * `clrlwi ...,0x10` here is a genuine `& 0xFFFF` of the widened field, not a
//    sign-extension: loop 3's test against it is `cmplw` (unsigned).
//  * ONE variable must carry both the accumulator and the walking pointer
//    (want keeps it in r3 from the entry block through the final `subf`). Using
//    a separate `p` costs an extra `mr` + a branch-to-copy block (268B vs 272B
//    region diffs) — this was worth 4 bytes and one basic block.
//  * Empty countdown loop over the u16 at +0x1A:
//        if (n1 != 0) { cnt = n1; do { cnt -= 1; } while (cnt != 0); }
//    gives `[clrlwi][add][cmpwi][beq][mtctr][bdnz]` — byte-for-byte want's
//    sequence (only register numbers differ).
//  * `acc = acc + 0x40 + *(s32 *)((char *)acc + 4);` and `acc += t + 0x40;`
//    reproduce want's `addi rX,r3,0x40 / add` and `addi r0,r9,0x40 / add` pairs.
//  * The 0x20 alignment tail
//    `((tot + 0x1F) & 0xFFFFFFE0) - tot` gives want's
//    `addi/rlwinm/subf` triple (rlwinm needs the 0xFFFFFFE0 to be unsigned).
//
// THE PIN IS LOAD-BEARING, KEEP IT: `register s32 n3 __asm__("r28")` is what
// buys `stwu r1,-0x18(r1)` + `stmw r28,8(r1)` / `lmw r28,8(r1)` +
// `addi r1,0x18(r1)`. Want's stmw covers r28..r31 although only r28 is ever
// READ, so the allocator had to touch r28 AND r29; without a callee-saved
// assignment ngccc emits no frame at all (268B, no prologue/epilogue) and the
// whole body shifts by 2 words. Adding the pin costs nothing extra (no entry
// copy is inserted) and moved 268B -> 280B.
//
// REMAINING DIFF (all regalloc / block placement, no semantic content):
//  1. 4 loop-preheader regmoves want has and got does not, one per loop:
//     loop1 `mr r11,r10` (bound), loop2 `mr r10,r0` + `mr r9,r5`,
//     loop3 `mr r8,r0` (bound). Want ALWAYS copies the loop bound into a
//     loop-local register (pre-test uses the entry reg, latch uses the copy);
//     got CSEs the bound into the entry register in every loop and only keeps
//     the POINTER copy (loop1 `mr r7,r0`). This is a preedge-CSE/PRE threaded
//     pre-test signature (recipes: CSE-PRE threading), NOT a loop spelling
//     problem: `while`, `for`, and `if (c) { do{}while(c); }` all compile
//     byte-identically here (measured).
//  2. One extra `b` to a trailing copy block in got: the outer loop-3 latch
//     (`cmplw r10,r8; blt`) is emitted AFTER the function tail, so the tail is
//     only reachable via an unconditional branch. Linear block order.
//  3. Every register number differs (arg0: want r7 vs got r4; counters want
//     r8/r11/r10 vs got r10/r10/r10; acc+pointer want r3 vs got r11). Want's
//     allocator had r4/r5/r6 already taken when it allocated arg0 (it picked
//     r7); got allocates arg0 first and picks r4. Pure pseudo-numbering
//     difference (recipes: "matching instruction counts => pure home-assignment
//     park", cf. fn_8017981C).
//
// RULED OUT (do not re-try):
//  * 12 spellings for `clrlwi rD,rS,0x10`: `(u16)field`, `(u16)(s32)field`,
//    `s32 m = field; s32 n = (u16)m;`, `u32 m = field; (u16)m`, `(s16)field`
//    (gives lha), `(s16)` of an s32 intermediate, u16-typed loop var, and
//    s32-typed-field + `(u16)`. Every one folds the mask away; ONLY the plain
//    `s32 n = u16_field;` keeps it. So the "carries two live names" clrlwi rule
//    (AGENTS recipes §6y-126 / the two-live-names item) does not apply here.
//  * `if (c) { body; do {} while (c); }` for all three loops: byte-identical
//    to `while` (280B, same diffs).
//  * `-Os` from the m2c header: not a flag this object wants (the want frame
//    has no spills at all); default `-O2 -G0 -mcpu=750 -fno-common` is right.
//
// MOST PROMISING NEXT IDEA: item 1 — get the loop bound to stop being CSE-able
// so the preheader regmove is forced. Cheapest experiment is a per-object flag
// aimed at preedge CSE (`-fno-cse-follow-jumps` / `-fno-gcse` are the knobs
// that control whether the pre-test is threaded into the loop; the direction
// is unknown because want may also have come from a differently-flagged object).
// Second: adding one genuinely-live value early (want must allocate r4/r5/r6
// before arg0) is the only route to the register-number class.
// family=m2c range=0x80076778-0x800768A8 size=304B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct {
    s32 unk0x00;
    s32 unk0x04;
    s32 unk0x08;
    s32 unk0x0C;
    u16 unk0x10;
    u16 unk0x12;
    s32 unk0x14;
    u16 unk0x18;
    u16 unk0x1A;
} Obj_76778;

s32 fn_80076778(Obj_76778 *arg0) {
    char *base;
    char *p1;
    char *p2;
    u32 i;
    u32 j;
    s32 na;
    s32 nb;
    s32 na8;
    s32 nb18;
    s32 tot;
    s32 acc;
    s32 n1;
    register s32 n3 __asm__("r28");
    s32 cnt;
    s32 m;
    s32 t;

    i = 0;
    nb = arg0->unk0x12;
    base = (char *)arg0 + 0x40;
    na = arg0->unk0x18;
    nb18 = nb * 0x18;
    na8 = na * 8;
    p2 = base + na8;
    tot = na8 + nb18;
    acc = (s32)p2 + nb18 + (((tot + 0x1F) & 0xFFFFFFE0) - tot);

    p1 = base;
    while (i < (u32)na) {
        acc += *(s32 *)p1;
        i++;
        p1 += 8;
    }

    nb = arg0->unk0x12;
    i = 0;
    while (i < (u32)nb) {
        acc += *(s32 *)p2;
        i++;
        p2 += 0x18;
    }

    n1 = arg0->unk0x1A;
    acc += arg0->unk0x0C;
    if (n1 != 0) {
        cnt = n1;
        do {
            cnt -= 1;
        } while (cnt != 0);
    }

    n3 = arg0->unk0x10;
    j = 0;
    while (j < (u32)n3) {
        m = *(u16 *)acc;
        acc = acc + 0x40 + *(s32 *)((char *)acc + 4);
        j++;
        if (m != 0) {
            cnt = m;
            do {
                t = *(s32 *)acc;
                if (t != 0) {
                    acc += t + 0x40;
                }
                cnt -= 1;
            } while (cnt != 0);
        }
    }

    return (acc + 4 + (*(s32 *)acc * 0x50)) - (s32)arg0;
}
