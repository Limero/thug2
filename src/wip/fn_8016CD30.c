// PARKED 2026-10-30: 91.1% -> 91.1% (no improvement; ~90 new variants)
// UPDATE 2026-10-09: `extern const f32` on all four float externs -> 94.1%.
// Draft body now carries const.
// family=m2c range=0x8016CD30-0x8016CEC4 size=404B
// WIP DRAFT (non-matching) — hand-rebuilt from the DOL; NOT promoted.
// INERT: not registered in splits.txt/configure.py — never compiled into the DOL,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BEST: NEAR 91.09% (9 of 101 words).  m2c baseline was 34.91%.
// SIZE: exact — object .text 0x194 = 404 B = symbols.txt size:0x194 = header size.
//        object carries .text + .rela.text ONLY (no .rodata/.data/.bss => if it
//        ever reaches masked-EXACT it is also promote-clean; no doc-14 pool).
// ASM:   0 emitted instructions.  Two `register ... __asm__("rN")` variable pins
//        (tmpa->r30, tmpb->r29) plus one `__asm__("" : "+r"(tmpa))` EMPTY
//        identity barrier; all three emit nothing (0/101 = 0% density).
// RELOC AUDIT (tools/readelf -r, all 43 entries checked by hand):
//        1/1 R_PPC_REL14 (type 11, section-relative addend 0x78) -> 0x8016CDA8,
//          which is exactly want's `bne 0x8016CDA8`.  (readelf prints addends
//          in HEX — 0x78 = 120.)
//        12/12 R_PPC_REL24 call targets match want's `bl`s: fn_8009C838,
//          fn_80137724, fn_80136FA0, fn_80125A3C, Mem_NewZero x4, fn_80009B04 x4.
//        15/15 ADDR16_HA/LO pairs resolve to real symbols.txt entries and their
//          hand-decoded want addresses all agree: lbl_802FFE58 (0x803D-0x1a8),
//          lbl_802A8B40 (0x802B-0x74c0), lbl_80303448 (0x803D+0x3448),
//          lbl_802A8B08 (0x802B-0x74f8), fn_8016AEC4 (0x8021-0x513c),
//          lbl_802A8B90 (0x802B-0x7470), fn_8016AB1C (0x8021-0x54e4),
//          lbl_802A8B68 (0x802B-0x7498), lbl_802A8B18 (0x802B-0x74e8),
//          lbl_802A8B1C (0x802B-0x74e4), lbl_803CAF74 (0x803D-0x508c),
//          lbl_803CAF78 (0x803D-0x5088), fn_8016C4B0 (0x8021-0x3b50),
//          fn_8016AAA0 (0x8021-0x5560), lbl_80305E9C (0x803D+0x5e9c).
//        QB hash 0x702247A5 == QB_VIEWER_CONTROLLER, emitted lis+ori (a VALUE
//          constant, not a symbol) so the 91.1% already byte-verifies it.
//
// WHAT IT IS: the QB "viewer_controller" constructor — 4 script nodes (two
// 0x24 + two 0x30) wired into `arg0`, a one-shot setup of the two global fog
// params (lbl_803CAF74/78, which promoted src/fn_8016CFF0.c / fn_8016CFFC.c are
// the promoted setters for), and a global self-pointer store.  `return arg0;`
// is what produces the `mr r31,r3` / `void *` head.
//
// IDIOM IS PROVEN, NOT GUESSED: promoted sibling src/fn_8021B830.c (byte-
// identical) contains this exact shape —
//     task = Mem_NewZero(0x24);
//     cb   = (s32)fn_X;               /* named local live across the call */
//     fn_80009B04(task, 0);
//     task->unk0x1C = cb;
// with the same callee proto `void fn_80009B04(Unk_5EF41E38 *, void *)`.
// The 34.91% -> 68.32% step (the single biggest win, previous round) was
// applying that template; the rest is pins + the residual below.
//
// RESIDUAL — ONE 13-instruction window (text 0x0D0..0x0FC); same instruction
// multiset, pure permutation, everything from `li r3,0x24` on is byte-exact:
//   Concretely, the want's pre-call run is the r30 page anchor, the r30 low
//   half, the zeroing of the fourth call argument, and the call to the
//   0x80009B04 routine; the got instead opens with the r30 and r27 page
//   anchors, zeroes the argument, then emits the r27 low half and only
//   afterwards the r30 low half before the call. After the call the want
//   runs the r27 page anchor, two float page anchors, the r27 low half, the
//   node store to 0x28(r29), a third float page anchor, the first float
//   load, a fourth float page anchor, the second float load, and the 0x24
//   size argument; the got instead runs two float page anchors, the first
//   float load, a third anchor, the second load, a fourth anchor, and sinks
//   the node store to just ahead of the size argument.
// Three independent sub-permutations:
//   (1) `addi r30` (the lo half of tmpa's address) must be IMMEDIATELY after
//       its `lis`, before `li r4,0`; got defers it past `addi r27`.
//   (2) s68's lis+addi pair must be entirely AFTER the call (want's `lis r27`
//       is the call's delay slot); got has both in the PRE-call region.
//   (3) `stw r30,0x28(r29)` must precede the two `lfs`; got has it after them.
//
// ROOT CAUSE (established with `cc1 -dall`, see ROUND r2 below): `high:`(lis)
// and `lo_sum:`(addi) are SEPARATE RTL insns, so sched2 may split any symbol
// pair, and the post-reload RTL is ALREADY in want's source order — the
// permutation is produced entirely by sched/sched2 inside one basic block.
// want's pre-call region is only [hi tmpa][lo tmpa][li r4,0], which requires
// (a) no `+r` barrier and (b) s68's address BORN AFTER the call; every shape
// that achieves (a)+(b) breaks the post-call order instead (the three float
// `hi`s then jump ahead of s68's `hi`).  Measured 20 (position x barrier x pin)
// combinations; the two requirements are mutually exclusive from C.
//
// ROUND r2 (2026-10-30) — ~90 new variants, NONE beat 91.09%.  Findings, in
// the order they were worth:
//  1. The `+r` empty barrier on `tmpa` is load-bearing (removing it = 90.10)
//     and it is precisely a `+r` ON tmpa: `+r` on s68 = 84.16, on temp_r29_2 =
//     51.0, input-only `"r"` on tmpa = 49.0, two barriers = 87.13.  MECHANISM
//     found: the barrier adds a SECOND definition of r30, so the `lo_sum`
//     becomes its own web and splits from its `lis` — that is why the barrier
//     trades (1) for (2).  It cannot give both.
//  2. The anchor lever the previous round left as THEORY is MEASURED AND
//     DEAD.  A 2-instruction opaque `lis`+`addi` asm for lbl_802A8B68 was tried
//     in four forms (volatile / non-volatile; "=r" / "=&r"; with and without
//     the tmpa barrier; register-var output and plain-local output):
//       volatile 2-insn  -> 50.5% and a 392 B object (12 B SHORT, 47 diffs):
//                           a volatile asm is a full scheduling barrier and the
//                           whole post-call block collapses.
//       non-volatile    -> 35.6% / 52.0%, same collapse.
//       register-var out -> 71.3%, and the pair is re-birthed right after
//                           `bl fn_80125A3C` because a register variable is
//                           live-from-entry (AGENTS §73-151 / §6bg-153).
//     Do not re-attempt an asm anchor here; the honest residual is a
//     post-front-end sched2 tie, not a reachable-source-shape problem.
//  3. s68 assigned AFTER the call fixes requirement (2) — the pre-call region
//     then matches want exactly — but the post-call order breaks: the two
//     float-load `hi`s (lbl_802A8B18 / lbl_802A8B1C) are scheduled BEFORE
//     s68's `hi` even though they are born later in the RTL.  Best variant of
//     this family = 89.11% (s68 assigned after the 0x2C store + pins
//     s68->r27 / s90->r28); s68 at the top of the group = 86.14%.
//     Full sweep: pos0..pos4 x {barrier, no barrier} x {pin, no pin} —
//     83.2 / 88.1 / 81.2 / 86.1 (pos0-2) and 83.2 / 89.1 / 81.2 / 87.1
//     (pos3-4).  Nothing reaches 91.1.
//  4. `volatile` on the node-2 0x28 store DOES move it earlier (AGENTS §6ek's
//     "pin the store to the head of its block" — directionally confirmed) but
//     it also duplicates the store and costs 4 more words: 87.13%.
//  5. Full 17-flag sweep on the CURRENT body (§6bx: re-measure after changes):
//     -fno-sched-interblock / -fno-sched-spec / -fno-thread-jumps /
//     -fno-expensive-optimizations / -fno-gcse / -fno-rerun-cse-after-loop /
//     -fno-strength-reduce / -fno-branch-count-reg / -fno-caller-saves /
//     -fconserve-space / -O3 are all 91.09% (no-ops).
//     -fno-schedule-insns2 83.2, -Os 86.1, -fno-schedule-insns 44.6.
//     (-fno-crossjumping / -falign-labels / -fno-ipa-ra do not exist in ProDG
//     cc1; -fno-sched-round likewise.)
//  6. Byte-for-byte NEUTRAL (same 9-diff window, 91.09%): s68/s90 as `u32` or
//     as `char *`; pins added for s68->r27 / s90->r28 / temp_r26->r26; the two
//     float stores as one comma statement, swapped, or staged through named
//     f32 temps; the float stores comma-folded into the 0x18 store;
//     s68 assigned inside the fn_80009B04 arg as a comma; s68 assigned inside
//     its own store; the tmpa barrier moved after the call or after s68.
//  7. WORSE (measured): s68 written INLINE at both use sites 83.2 (this also
//     swaps s90/s68's registers, needing pins to recover 88.1); s68 before tmpa
//     89.1; node-2 0x18 store first 89.1, 0x28 last 87.1; float stores before
//     the node-2 group 84.2; float stores after the node-3 alloc 88.1;
//     volatile reads of the two float constants 82.2; volatile on the
//     arg0->0x18 store 82.2; barrier on tmpb as well 89.1; two barriers on
//     tmpa 87.1; s68 before the barrier 89.1.
//  8. Two harness traps hit and confirmed for the record: (a) `score_body.py`
//     and `want_got.py` share `$LEAF_TMPDIR` per address, so a private dir is
//     mandatory (AGENTS §6fj / §6bc-278) — `want_got.py --file` additionally
//     overrides LEAF_TMPDIR with its own mkdtemp, so disassembling
//     `$LEAF_TMPDIR/*.o` afterwards reads a stale sweep artifact;
//     (b) ProDG cc1 2.95 REJECTS a declaration after a statement, so every
//     "stage it into a named local" experiment must be declared at the top
//     (two variants that placed a decl mid-body FAILed rather than scoring).
//
// NEXT IF SOMEONE REVISITS: the only untried shape is making the two float
// LOAD anchors cheaper (or the two float `lfs` dearer) so sched2 cannot let
// them jump `stw r30,0x28`.  A `-fsched-cost`-style knob does not exist in
// cc1, and a `volatile` lvalue is the only available "frozen insn" lever and it
// measures worse.  Do NOT re-run the statement-order, pin-set, flag or
// asm-anchor ladders — they are all measured above.
//
// VERIFY BEFORE YOU CLAIM 100% (this draft would pass all five if it did):
//   a. object .text 0x194 == symbols.txt size:0x194 == header size=404B  [OK]
//   b. 1/1 REL14 addend 0x78 -> 0x8016CDA8 == want's bne target            [OK]
//   c. 12/12 REL24 call targets == want's bls                              [OK]
//   d. 15/15 lis+addi/lo pairs decode to real symbols.txt addresses       [OK]
//   e. object has .text + .rela.text only, no .rodata/.data               [OK]
#include "qb_constants.h"
#include "structs.h"
void *Mem_NewZero(s32 size);
void fn_80009B04(void *, s32);
s32 fn_80125A3C(s32, s32);
s32 fn_80137724(s32);
void *fn_80136FA0(void *, s32, char *, s32, s32, s32, s32);
void fn_8016AEC4(void);
void fn_8016AB1C(void);
void fn_8016C4B0(void);
void fn_8016AAA0(void);
extern char lbl_802A8B08[];
extern char lbl_80305E9C[];
extern const f32 lbl_802A8B18;
extern const f32 lbl_802A8B1C;
extern bool lbl_802FFE58;
extern char lbl_80303448[];
extern const f32 lbl_803CAF74;
extern const f32 lbl_803CAF78;
extern char lbl_802A8B40[];
extern char lbl_802A8B68[];
extern char lbl_802A8B90[];
void *fn_8016CD30(Unk_9AA07378 *arg0) {
    s32 temp_r26;
    s32 temp_r30;
    register s32 tmpa __asm__("r30");
    register s32 tmpb __asm__("r29");
    s32 s90;
    s32 s68;
    CScript *temp_r29;
    CScript *temp_r29_2;
    CScript *temp_r30_2;
    CScript *temp_r30_3;
    fn_8009C838();
    arg0->unk0x14 = (s32)lbl_802A8B40;
    arg0->unk0x48 = 0;
    arg0->unk0x4C = 0;
    if (lbl_802FFE58 == 0) {
        temp_r30 = *(s32 *)&lbl_80303448;
        fn_80137724(temp_r30);
        arg0->unk0x54 = fn_80136FA0(temp_r30, 0, (s32)lbl_802A8B08, 4, 0x2710, 0, 0x10);
    }
    temp_r26 = fn_80125A3C(QB_VIEWER_CONTROLLER, 0);
    temp_r29 = Mem_NewZero(0x24);
    tmpa = (s32)fn_8016AEC4;
    fn_80009B04(temp_r29, 0);
    temp_r29->unk0x1C = tmpa;
    temp_r29->unk0x20 = arg0;
    s90 = (s32)lbl_802A8B90;
    temp_r29->unk0x18 = s90;
    arg0->unk0x20 = temp_r29;
    temp_r29_2 = Mem_NewZero(0x30);
    tmpa = (s32)fn_8016AB1C;
    s68 = (s32)lbl_802A8B68;
    __asm__("" : "+r"(tmpa));
    fn_80009B04(temp_r29_2, 0);
    temp_r29_2->unk0x28 = tmpa;
    temp_r29_2->unk0x24 = temp_r26;
    temp_r29_2->unk0x18 = s68;
    temp_r29_2->unk0x2C = arg0;
    arg0->unk0x18 = temp_r29_2;
    lbl_803CAF74 = lbl_802A8B18;
    lbl_803CAF78 = lbl_802A8B1C;
    temp_r30_2 = Mem_NewZero(0x24);
    tmpb = (s32)fn_8016C4B0;
    fn_80009B04(temp_r30_2, 0);
    temp_r30_2->unk0x1C = tmpb;
    temp_r30_2->unk0x20 = arg0;
    temp_r30_2->unk0x18 = s90;
    arg0->unk0x24 = temp_r30_2;
    temp_r30_3 = Mem_NewZero(0x30);
    tmpb = (s32)fn_8016AAA0;
    fn_80009B04(temp_r30_3, 0x3E8);
    temp_r30_3->unk0x24 = temp_r26;
    temp_r30_3->unk0x18 = s68;
    temp_r30_3->unk0x28 = tmpb;
    temp_r30_3->unk0x2C = arg0;
    arg0->unk0x1C = temp_r30_3;
    *(void **)lbl_80305E9C = arg0;
    return arg0;
}
