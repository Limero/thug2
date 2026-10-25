// PARKED 2026-10-30 — base 93.0%, final 93.0% (40/43, size-exact 172B).
// WIP DRAFT (non-matching) — C body from tools/fill_wip_drafts.py, hand-corrected.
// family=m2c range=0x8009E004-0x8009E0B0 size=172B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// fn_8009E004 — node/sub-object constructor, 172 B (symbols.txt: size:0xAC;
// 0x8009E0B0-0x8009E004 = 0xAC, so the marker is self-consistent).
//
// RESIDUAL: exactly 3 words (one instruction transposition), 0x8009E058..0x8009E064.
// The A50 movlo (`addi r9,r9,@l(lbl_80297A50)`) is emitted TWO slots too early.
// The want forms the high halves for A50 then F18 then F1C in r9 then r11
// then r10, resolves the A50 low half into r9 fourth, and then runs the
// shared word-load, move, word-load and word-store tail. The current output
// forms the A50 high half in r9 first but resolves its low half second,
// before forming the F18 and F1C high halves in r11 and r10, and then runs
// that same tail.
// Everything from 0x8009E068 on is byte-identical, INCLUDING the whole tail
// [lwz r8 / mr r3,r30 / lwz r0 / stw r9,8(r28) / stw r30,0xc(r28) / stw r8,0x18 /
// stw r0,0x1C], the six-store zero tail, the frame, the prologue and the epilogue.
// So the tail's *relative* scheduling is already exact; only the frozen prefix is wrong.
//
// SEMANTICS (all five lbl_ symbols are present in config/G2TE52/symbols.txt at
// exactly those addresses, so the body is link-safe — audit (d) below):
//
//   CObject_ctor(arg0);                    // 0x8009DEDC: arg0+4 = 0, arg0+8 = lbl_802979B0
//                                          //   (src/fn_8009DEDC.c is PROMOTED and
//                                          //   byte-identical: `void *CObject_ctor(CStruct *)`)
//   arg0->unk0x8      = lbl_80297A00;     // +0x08
//   list = arg0 + 0x2C;                   // embedded dlist node
//   list->unk0x14     = lbl_802929C8;     // +0x40
//   list->unk0x4      = arg0;             // +0x30
//   list->unk0x8      = 0;                // +0x34
//   list->unk0xC      = list;             // +0x38
//   list->unk0x10     = list;             // +0x3C
//   CObject_ctor(arg0 + 0x48);            // second embedded object
//   sub->unk0x8       = lbl_80297A50;     // +0x50  (the A50 whose movlo is the residual)
//   sub->unk0xC       = arg0;             // +0x54
//   arg0->unk0x18     = lbl_80297F18;     // +0x18
//   arg0->unk0x1C     = lbl_80297F1C;     // +0x1C
//   arg0->{0x20,0x24,0x14,0x10,0x0C,0x44} = 0;
//   return arg0;
//
// LEVER THAT IS LOAD-BEARING (keep it; 0 emitted instructions, 0% of the function):
//  * `__asm__ __volatile__("" : "+r"(a50));` — a zero-code web-opacity barrier with
//    an EMPTY template; it emits NO instruction (AGENTS §6bv/§6du-2 "cheap 0-insn
//    cousin of the opaque birth"). It forces the A50 *reload* to be materialised at
//    the assignment instead of being deferred to its use, which in turn fixes the
//    two `lwz` destination registers (F18->r8, F1C->r0) and the `mr r3,r30` slot.
//    83.7% without it (the addi then sinks to slot 6 AND both lwz dests swap).
//    It is a conjunction with nothing else — see the measured matrix below.
//
// NOTE CORRECTED (measured this round, all with a private LEAF_TMPDIR):
//  1. "the barrier creates the addi at the barrier" is WRONG. The `+r` barrier
//     pins the reload *pair* (lis + addi) at the assignment's RTL position.
//     Moving the barrier later moves BOTH halves: barrier after 2 symbol
//     mentions = 86.0%, after 3 = 83.7%, no barrier = 83.7%. The pair is atomic
//     in RTL position, which is why "put the barrier after both lis" cannot work.
//  2. "the addi only ever lands in THREE slots (1, 2, 6)" is WRONG — there are
//     FOUR: slot 2 (volatile barrier), 3 (non-volatile barrier), 5 (asm-`lis` +
//     a free plain-C addi), 6 (no barrier / free reload). Slot 4 remains
//     unreachable, so the CONCLUSION (parked) stands but the enumeration did not.
//  3. "a volatile A50 STORE pulls the movlo to slot 3 (83.7%)" is WRONG — a
//     volatile A50 store measures 79.1% and does not move the movlo to slot 3.
//  4. "no flag moves it" CONFIRMED and extended: a 25-combo sweep on this exact
//     body (21 singles + 3 pairs, plus -O1/-O3/-Os/-mcpu=603/-mcpu=750) gives
//     NOTHING above 93.0%. The only flags that change the score all make it worse:
//     -fno-schedule-insns 37.2, -fno-schedule-insns2 72.1, -Os 69.8, -O1 27.9,
//     -mcpu=603 53.5, and the insns/pairs combinations 27.9-30.2. Twelve flags
//     (-fno-sched-spec, -fno-sched-interblock, -fno-gcse, -fno-thread-jumps,
//     -fno-expensive-optimizations, -fno-cse-follow-jumps, -fno-strength-reduce,
//     -fno-branch-count-reg, -fno-rerun-cse-after-loop, the sched-spec+interblock
//     and gcse+rerun pairs, -O3, -mcpu=750) are exact no-ops at 93.0%.
//     Five more (-fno-sched-round, -fno-peephole2, -fno-tree-pre, -fno-tree-ter,
//     -fno-delete-null-pointer-checks) are not in this cc1's option set at all.
//  5. The callee-prototype audit is CONFIRMED inert: `void CObject_ctor(CStruct *)`
//     = 93.0%, `void *CObject_ctor(void *)` = 93.0%. Ground truth from the
//     promoted src/fn_8009DEDC.c is `void *CObject_ctor(CStruct *)` — already
//     what the draft declares. (Chaining the ctor's return into a `void *` temp
//     is 48.9%.)
//
// NEW MEASURED FACTS THIS ROUND (scoped to this function; NOT claimed as a law):
//  A. The `lis`/ADDR16_LO pair DOES split in this cc1 without any barrier, and
//     with the CORRECT symbol order and colours. With the `+r` barrier removed the
//     object is [lis r9 | lis r11 | lis r10 | lwz r0,(r11) | lwz r8,(r10) |
//     addi r9 | stw r9 | mr r3,r30] — i.e. A50->r9, F18->r11, F1C->r10 exactly as
//     want, the addi merely sinking to slot 6 (just before its use) and the two
//     lwz destinations swapping. So the HI16 reload floats to the block top and
//     only the movlo is tied to the use. Confirmed independently by the promoted
//     address-adjacent sibling src/fn_8009E0B0.c (byte-identical), whose want
//     splits the lbl_802929C8 pair as [lis r11][lwz r0][addi r11][lwz r10] from a
//     SINGLE source statement — so "the pair can split" is real, not an artifact.
//  B. `volatile` inline-asm insns are SCHEDULABLE in this cc1, so a volatile asm
//     cannot be used to freeze a plain-C addi at a chosen slot. Measured:
//       `__asm__ volatile("addi %0,%0,31312" : "+r"(pg));` at the right source
//         position -> addi still lands at slot 6 (and the lwz dests swap): 5 diffs.
//       `__asm__ __volatile__("");` (empty, 0 insns) after the addi -> no effect.
//         The same empty volatile after a *reload*-derived addi (vbar, 93.0%) is
//         also a no-op (93.0% both ways).
//     This is a FUNCTION-LOCAL negative against reading §6br / §6bg-6 /
//     "volatile pins placement" as general: it holds for the `lis`/anchors those
//     notes use, and it does NOT hold for a C-computed addi here.
//  C. Making the movlo a *plain C addi* (emit only the `lis` as an opaque,
//     volatile, r9-pinned asm and add 0x7A50 in C) puts it in a different cost
//     class and moves it to slot 5 — one slot LATE — while rotating the tail
//     ([addi][lwz][lwz][stw][mr] instead of want's [addi][lwz][mr][lwz][stw]).
//     90.7% with the store-only variant, 88.4% with the empty-volatile variant.
//     So the plain-C addi and the reload addi are NOT interchangeable, and the
//     reload one is the only one that gets the tail exactly right.
//
// LEVERS TRIED THIS ROUND, all measured on the same body (base 93.0%):
//  statement/structure
//    F18/F1C reads moved before the A50 store (owner store last / owner store in
//      want's order / barrier after the A50 store / no barrier)  76.7 / 74.4 /
//      74.4 / 76.7  -- the STORE order survives but the `lis` ORDER inverts to
//      (F18, F1C, A50), so it can never reach 100.
//    `+r` barrier after 2 / after 3 symbol mentions               86.0 / 83.7
//    F18-only before the barrier, F1C after                       83.7
//    volatile on: the A50 store 79.1, the F18 load 76.7, the F18+F1C loads 74.4
//    `+r` barrier on a50 AND on t18 (74.4), on a50 after the A50 store (81.4),
//      on a50 at the very end (81.4), on a50 + on arg0 -- all <= 81.4
//    owner store before the A50 store                             93.0 (identical)
//    drop the `t18` temp (read the global at the store)           93.0 (identical)
//    A50 via a named `s32 *` field pointer at the top of the fn  79.1
//    `a50` typed `char *` / `void *` instead of `s32`            93.0 / 93.0
//    `&lbl_80297A50[0]` instead of `(s32)lbl_80297A50`           93.0 (identical)
//  declaration form
//    `extern s32 lbl_80297A50;` + `a50 = lbl_80297A50;`          81.4
//    `*(s32 *)&lbl_80297A50`                                      81.4
//    F18/F1C as `extern char[]` + `*(s32 *)&lbl`                  74.4
//    F18 read through a named `s32 *` / `f32 *` symbol pointer    76.7
//  barrier strength gradations (aiming at slot 4)
//    non-volatile `+r`                                            90.7
//    non-volatile `+r` + `"memory"` clobber                       81.4
//    volatile `+r` + `"memory"` clobber                           93.0 (identical)
//    two stacked non-volatile `+r`                                 79.1
//    non-volatile `+r` on a50 and on t18                          79.1
//    volatile `+r` on a50 and non-volatile `+r` on t18           83.7
//    non-volatile `=r` re-birth of a50 into a2, store a2         90.7
//    volatile `+r` then non-volatile `=r` re-birth                 88.4
//    two-name A50 web (a50 = sym; a2 = a50; barrier; store a2)    50.0
//  asm-anchor route (1-2 emitted insns, all measured, none better)
//    `lis %0,%1@ha` volatile into an r9-pinned var, add in C     90.7
//    same, non-volatile                                           83.7
//    same + `+r` barrier on the C addi                            93.0 (identical)
//    same + F18/F1C reads before the addi                         88.4 / 90.7 / 88.4
//    `addi` itself as a volatile asm (2 emitted insns)            5 diffs (addi still
//      not frozen; it lands at slot 6 and the lwz dests swap)
//  flags: 25-combo sweep, nothing above 93.0% (see correction 4).
//
// WHY IT IS STILL PARKED, in one line: the movlo must move DOWN past two other
// HI16 reloads, but every construct that makes it schedulable moves it DOWN to
// slot 5 or 6 instead of 4, and every construct that keeps it at slot 2 also
// freezes the two HI16s after it.  Slot 4 needs the movlo to be schedulable AND
// cheaper than the `lwz`; the reload movlo is not cheap enough and the plain-C one
// still loses the tie to the first `lwz` on LUID order. That is a
// reload-cost-class wall, not a source-shape problem -- do NOT re-run the
// statement-order, store-permutation, prototype or flag ladders.
//
// ORACLE USED (AGENTS §6fn): the address-ADJACENT function src/fn_8009E0B0.c is
// already PROMOTED and byte-identical. It uses the same two symbols, the same
// `CObject_dtor`/`CObject_delete` callee set, the same `char[0x2C]`-embedded-node
// idiom, and the same "symbol store first, node stores after" order as region 1
// of this function -- which is why region 1 (0x8009E024..0x8009E03C) already
// matches and region 2 does not. It also supplies the positive proof for fact A.
//
// VERIFY BEFORE BELIEVING THIS DRAFT (re-run all five):
//   a. object .text = 0xAC = 172 B = symbols.txt `size:0xAC` = header size=172B  OK
//   b. R_PPC_REL14: the object has ZERO. Want has no b/beq/bne/bgt/... either --
//      hand-decoded all 43 want words: only `bl` x2 (0x8009E020, 0x8009E054) and
//      `blr`. The branch audit is therefore vacuous, not skipped.             OK
//   c. R_PPC_REL24: 2 entries, both -> CObject_ctor, at .text+0x1c and +0x50;
//      symbols.txt: CObject_ctor = .text:0x8009DEDC, matching want's two
//      `bl 0x8009dedc`.  2/2 correct.                                      OK
//   d. 5 x ADDR16_HA + 5 x ADDR16_LO, hand-decoded (all page 0x8029, matching
//      want's five `lis r*, -0x7fd7`):
//        lbl_80297A00 -> HA 0x8029 LO 0x7A00  (want lis r11 / addi 0x7a00)   OK
//        lbl_802929C8 -> HA 0x8029 LO 0x29C8  (want lis r10 / addi 0x29c8)   OK
//        lbl_80297A50 -> HA 0x8029 LO 0x7A50  (want lis r9  / addi 0x7a50)   OK
//        lbl_80297F18 -> HA 0x8029 LO 0x7F18  (want lis r11 / lwz 0x7f18)    OK
//        lbl_80297F1C -> HA 0x8029 LO 0x7F1C  (want lis r10 / lwz 0x7f1c)    OK
//      All five are real config/G2TE52/symbols.txt entries at exactly those
//      addresses, so the masked-100%-wrong-label hazard (recipe 277) is clear.
//   e. object sections: .text + .rela.text ONLY -- no .rodata/.data/.bss, so no
//      doc-14 FP-pool promote caveat.                                       OK
//   inline asm: ONE `__asm__ __volatile__("" : "+r"(a50))` with an EMPTY
//      template -> ZERO emitted instructions, 0 of 43 (0.0%). Well under the
//      30% ASM_FUNC ban and the 20% guidance.
//
// tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8009E004
#include "types.h"
#include "structs.h"
extern s32 lbl_80297F18;
extern s32 lbl_80297F1C;
extern char lbl_802929C8[];
extern char lbl_80297A00[];
extern char lbl_80297A50[];
void *CObject_ctor(CStruct *);
void *fn_8009E004(Unk_DB0E2BAB *arg0) {
    CStruct *temp_r28;
    Unk_C8FEE62D *temp_r9;
    s32 t18;
    s32 a50;

    temp_r28 = (char *)arg0 + 0x48;
    CObject_ctor(arg0);
    temp_r9 = (char *)arg0 + 0x2C;
    arg0->unk0x8 = (s32)lbl_80297A00;
    temp_r9->unk0x14 = (s32)lbl_802929C8;
    temp_r9->unk0x4 = arg0;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    CObject_ctor(temp_r28);
    a50 = (s32)lbl_80297A50;
    __asm__ __volatile__("" : "+r"(a50));
    temp_r28->unk0x8 = a50;
    temp_r28->unk0xC = arg0;
    t18 = lbl_80297F18;
    arg0->unk0x18 = t18;
    arg0->unk0x1C = lbl_80297F1C;
    arg0->unk0x24 = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x10 = 0;
    arg0->unk0xC = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x20 = 0;
    return arg0;
}
