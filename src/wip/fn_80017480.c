// PARKED 2026-09-30: 84.34% -> 86.60%; re-measured 86.75% (11/83 words).
// WIP DRAFT (non-matching) — hand-reconstructed 2026-09-26 (was an inert
// tools/fill_wip_drafts.py m2c body parked at 7.4% DIFF).
//
// SCORE: 86.60% (73/83 words), SIZE-EXACT 332B, flagless.
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80017480
//
// WHAT THIS IS (semantics, all verified against the DOL + object relocs):
// a viewport/projection setup for the camera object at arg0:
//   - C_MTXOrtho(self+0xC0, left, right, bottom, top, near, far) with
//     left=+224 (lbl_80290C6C), bottom=-320 (lbl_80290C68), near=1
//     (lbl_80290C70), far=100000 (lbl_80290C74); right=-left, top=-bottom.
//     When arg3 == 0x80 both horizontal pairs are pre-scaled by 0.5
//     (lbl_80290C78). Two call sites (one per arm), as the DOL has.
//   - self->unk0xBC = 1, then fn_800175CC(self, arg1, arg2, arg3, arg4)
//     (which stores arg1..arg4 at self+0x100..0x10C).
//   - 12 consecutive f32 fields self+0x00..0x2C initialised
//     (1,0,0,-320,0,-1,0,224,0,0,1,0).
//   - fn_800175E0(self, (f32)arg3, (f32)arg4) — stores them at +0xAC/+0xB0
//     and the reciprocals at +0xB4/+0xB8.
//
// FIXES APPLIED vs the old m2c draft (all three defects named in the 2026-09-11
// park note are now fixed):
//  1. 0x8025E810 is C_MTXOrtho (scope:global) — now a DIRECT prototyped call,
//     not an fn-ptr cast through a literal. (AGENTS.md §6av: the mtx library is
//     already wired as a Matching object, so the symbol resolves.)
//  2. The float fields are a file-local struct with real f32 members, so the
//     stores are plain stfs — no fctiwz/int-pun dance. The corpus-merged
//     Unk_72CEBC39 types 0x0/0x4/0x8/0x10/0x18/0x20/0x24/0x28/0x2C as s32
//     (majority vote across other files); per AGENTS.md M6.89d-note the
//     function's OWN file is the right place for the true layout.
//  3. The int->float conversion is the PLAIN `(f32)(f64)(u32)x` cast. That is
//     what the DOL shows: `lis r0,0x4330; stw x,0x14(r1); stw r0,0x10(r1);
//     lfd f1,0x10(r1); fsub f1,f1,f13; frsp f1,f1` — the single fsub IS
//     ngccc's own unsigned-int->double bias fixup, with its pool constant
//     resolving to the game's real rodata2 double lbl_80290C88 (2^52) and
//     loaded ONCE into f13 for both sites. Writing an explicit
//     `- lbl_80290C88` makes ngccc emit TWO fsubs (the fixup plus yours) and
//     is semantically wrong (arg - 2^52).
//
// NON-OBVIOUS LEVERS THAT WERE REQUIRED (kept, all load-bearing):
//  * The four ortho constants are loaded ONCE into shared locals BEFORE the
//    if/else. With raw per-site references in each arm, ngccc duplicates all
//    four loads into both arms: +28 bytes, 10.5%.
//  * DECLARATION ORDER of those four locals is an allocator lever: declared in
//    ASCENDING rodata2 address order (0xC68, 0xC6C, 0xC70, 0xC74) the four
//    address pseudos are born in that order and land in r10, r8, r9, r11 as
//    the DOL has. Any other order permutes them (84.3% -> 72-80%).
//  * `register f32 left __asm__("fr1")` / `bottom __asm__("fr3")`: these are
//    C_MTXOrtho's first/third float argument registers, so the pins put left
//    and bottom in f1/f3 and the whole ortho block (both arms, incl. the
//    fneg pair and the arg setup) matches. Unpinned: 15.5% and 20 extra bytes.
//  * Source store order is ASCENDING offset (0x00..0x2C) — the natural struct
//    init. want's own emission order as source scores only 74.7%.
//  * The 12 stores must stay RAW per-site symbol references; staging them into
//    named locals at function scope moves every load into the prologue
//    (8.1%). A nested block immediately before the stores is the only place
//    staging works, and only for the two frN-pinned constants.
//  * No -f flag changes anything: -fno-schedule-insns 31.7%, -fno-schedule-
//    insns2 56.6%, -fno-sched-spec / -fno-gcse / -fno-sched-interblock /
//    -fno-expensive-optimizations / -fno-thread-jumps all neutral; re-measured
//    on the current body, none of them moves residual (a) or (b).
//
// REMAINING BLOCKER (11 words, ONE 14-instruction window at 0x8001753C-0x80017590):
// Both conversions' bias stores and both lfd loads already land in want's slots.
// Two residuals remain inside the window:
//   (a) the pool 2^52 load (f13) and the 0.0f load (f0) are swapped: want loads
//       f13 first (it feeds the longer frsp chain), GOT loads f0 first and slips
//       f13 to the slot after the second `lis`. f13 is the compiler's own pool
//       constant for the (f64)u32 fixup, so its position is chosen by sched; the
//       four frN-pinned constants that follow (f9, f12, f10, f11) are in order.
//   (b) the four non-zero store run is rotated: want [0x14,0x28,0x0C,0x1C] vs
//       GOT [0x0C,0x14,0x1C,0x28] (source/ascending order). Knock-on of (a): the
//       0.0f load moving two slots later lets the first store leave early.
//
// OWNER PROVEN: `cc1 -dr` (post-reload RTL) is ALREADY in source order, so the
// permutation is introduced after `reload`, by sched's ready-list cost tie-break.
// Consistent with that, EVERY lever below is neutral-or-worse and the block is
// flag-invariant:
//   * 20-flag ladder re-measured on THIS body (AGENTS 6bx): -fno-sched-spec /
//     -fno-gcse / -fno-sched-interblock / -fno-expensive-optimizations /
//     -fno-thread-jumps / -fno-caller-saves / -fno-strength-reduce /
//     -fno-branch-count-reg / -O3 all 86.60%; -fno-schedule-insns2 57.8%,
//     -fno-rerun-cse-after-loop 34.9%, -fno-schedule-insns 30.1%, -O1 8.3%.
//   * frozen-ness (AGENTS 6bz/6ek): volatile on each of the four pinned constant
//     inits, on all four, on any pair -- 73.5% every time; a
//     `__asm__ volatile("" ::: "memory")` fence before the block 60.2%.
//   * the manual int->float dance against the game's real lbl_80290C88
//     (AGENTS 6j-1) to get a second, controllable 2^52 lfd: 53.0% plain,
//     34.9% with a volatile slot.
//   * store order: ascending is already correct; want's own emission order as
//     source 74.7% (and 85.5% or worse in all 24 declaration orders x 2 store
//     orders). Per AGENTS 6ex's store-class model GOT's head order IS the source
//     LUID order, so the 4-store run is a sched artefact, not a source order.
//   * M8.31 return-type flips: fn_800175CC -> s32 80.7%, fn_800175E0 -> s32 and
//     C_MTXOrtho -> s32 neutral, both flipped 80.7%.
//   * staging 1.0f/0.0f/224 into named locals without frN pins: 84.3%.
// BRANCH-AUDIT CAVEAT (the mask cannot see this, AGENTS 6bw/6bq/4aq): reading the
// object's own relocation addends, the `bne` is CORRECT (addend 0x70 => 0x800174F0,
// exactly want's else-arm target) but the then-arm's local `b` is NOT: its addend is
// 0x50 where want needs 0x80 (0x80017500, the merge point). So the residual is NOT
// purely a store permutation -- there is a genuine block-layout/branch-extent
// difference in that one arm, which is why a masked 86.6% must not be read as
// "structure only". The `b`'s in-field displacement is a placeholder the reloc
// overwrites, so the addend is the ground truth here.
// Honest park reason: a post-reload `sched` reorder of one basic block PLUS the
// then-arm merge-branch target -- not reachable by source order or flags.
// Audit: 1/1 R_PPC_REL14 + 5/5 R_PPC_REL24 present and named correctly
// (2x C_MTXOrtho, 1 local `b`, fn_800175CC, fn_800175E0); .text 0x14C == header
// `size=332B` == symbols.txt size:0x14C; all 7 tail anchors hand-decode to real
// .rodata2 lbl_80290C68/6C/70/74/78/7C/80/88 entries (no hazard-277 wrong label).
//
// NOT promote-clean even at 100%: the object carries a private 8-byte `.rodata`
// pool for the (f64)u32 2^52 bias (2x ADDR16_HA/LO against `.rodata`). The game's
// own copy is lbl_80290C88; tools/fix_fp_pool.py retargets it at build time.
//
// family=m2c range=0x80017480-0x800175CC size=332B

// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

// True field types for THIS function (see note 2 above). f00..f2C are the
// 12-float viewport block written by stfs in the DOL; iBC is the word flag.
typedef struct Unk_80017480 {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    char pad30[0x8C];
    s32 iBC;
    f32 proj[4][4];
} Unk_80017480;

extern f32 lbl_80290C68;
extern f32 lbl_80290C6C;
extern f32 lbl_80290C70;
extern f32 lbl_80290C74;
extern f32 lbl_80290C78;
extern f32 lbl_80290C7C;
extern f32 lbl_80290C80;

// Retail ABI order is (m, left, right, bottom, top, near, far) — recovered from
// C_MTXOrtho's own body at 0x8025E810, which computes m[0][*] from f1/f2 and
// m[1][*] from f3/f4. Parameter names are cosmetic; the types match the SDK
// prototype exactly, so including dolphin/mtx.h later cannot conflict.
void C_MTXOrtho(f32 m[4][4], f32 left, f32 right, f32 bottom, f32 top, f32 nearZ, f32 farZ);
void fn_800175CC(void *self, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_800175E0(void *self, f32 arg1, f32 arg2);

void Camera_orthographic(Unk_80017480 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    /* Declaration order == ascending rodata2 address (see header note 4). */
    register f32 bottom __asm__("fr3") = lbl_80290C68;
    register f32 left __asm__("fr1") = lbl_80290C6C;
    f32 nearZ = lbl_80290C70;
    f32 farZ = lbl_80290C74;
    f32 a;
    f32 b;

    if (arg3 == 0x80) {
        f32 s = lbl_80290C78;
        C_MTXOrtho(arg0->proj, left * s, -(left * s), bottom * s, -(bottom * s), nearZ, farZ);
    } else {
        C_MTXOrtho(arg0->proj, left, -left, bottom, -bottom, nearZ, farZ);
    }
    arg0->iBC = 1;
    fn_800175CC(arg0, arg1, arg2, arg3, arg4);
    a = (f32)(f64)(u32)arg3;
    b = (f32)(f64)(u32)arg4;
    {
        register f32 czero __asm__("fr0") = lbl_80290C7C;
        register f32 cone __asm__("fr9") = lbl_80290C70;
        register f32 cneg1 __asm__("fr12") = lbl_80290C80;
        register f32 cbot __asm__("fr10") = lbl_80290C68;

        arg0->f00 = cone;
        arg0->f04 = czero;
        arg0->f08 = czero;
        arg0->f0C = cbot;
        arg0->f10 = czero;
        arg0->f14 = cneg1;
        arg0->f18 = czero;
        arg0->f1C = lbl_80290C6C;
        arg0->f20 = czero;
        arg0->f24 = czero;
        arg0->f28 = cone;
        arg0->f2C = czero;
    }
    fn_800175E0(arg0, a, b);
}
