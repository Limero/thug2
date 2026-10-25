// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly
// family=m2c range=0x800DCE58-0x800DCEF4 size=156B
// FLAG: -fno-schedule-insns2
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// RE-MEASURED 2026-10-08: 14.9% -> **64.10%**, size-exact 156B.
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/score_wip.py \
//       0x800DCE58 src/wip/fn_800DCE58.c
//
// THE TYPE BUG (recipe §7k, the fn_800DBAE4 class, third confirmed case):
// want writes EIGHT `stfs` (0x20/0x24/0x28/0x2C and 0x30/0x34/0x38/0x3C).  The
// shared `Unk_C8FEE62D` declares 0x30/0x38 as `u64` (and 0x20..0x2F not at
// all), so the parked m2c body emitted int<->float round trips
// (`stw r0,4(r30)`-style field stores + `fctiwz`/`stfd`) for every float slot:
// the mnemonic delta was `{ stfs:+8 } | { stw:+7, fctiwz:+2, stfd:+2 }`.
// Fix = FILE-LOCAL f32 view: `F4 { f32 x4 }` at arg0+0x20 and arg0+0x30 (both
// blocks are 4 consecutive f32), plus a file-local header struct for the
// s32 slots.  Do not touch the shared header.
//
// 2026-10-12: 64.10% -> 79.49% (31/39). THREE levers:
//   1. `register F4 *temp_r9 __asm__("r9")` + `temp_r11 __asm__("r11")` fixes
//      the view<->register swap (got had +0x30-view in r11; want r9). Safe:
//      no calls cross the pointer lifetimes (fn_8009F53C is before both
//      births), so volatile-reg pins emit 0 extra instructions.
//   2. COUNTER-ROTATED store source order: sched2 emits each 3-store tail
//      with source-LAST first ([C,4,8]->[8,C,4], [C,8,4]->[4,C,8]), so write
//      tails rotated left by one ([4,8,C] and [4,8,C]) to land want's
//      [C,4,8] and [C,8,4]. r9-group confirmed first (64.1%->71.8%), then r11
//      (71.8%->74.4% partial, 79.5% full). If you touch store order, KEEP the
//      rotated form — want-order source REGRESSES to 64.1%.
// REMAINING 8 of 39 words — anchor rematerialization, NOT semantics:
//   * want interleaves `lis r9,lbl_80299F78` between the `lqr` of f0 and the
//     `stw r0,4(r30)` QB_SHADOW store, then emits `lfs f13` after the store;
//     got emits the store first and both lis/lfs as a unit.  Measured and
//     inert: moving the f13 load above the store in source (58.97%), moving it
//     below (v1 = 64.10%), pins on the two F4 pointers (byte-neutral).
//   * got gives the +0x30 view r11 and the +0x20 view r9; want is the other way
//     round; declaration-order swap of the two pointers is byte-neutral.
// Both are doc-15 scheduler/allocator coins on an otherwise correct body; the
// eight stores, their source order, and the literal set all match.
//
// 2026-10-15 (6 probes, still 79.49%): the 8-word residual decoded exactly —
// want (lis78, lisFA8, stw-QB) vs got (stw-QB, lis78, lisFA8), plus knock-on
// reg pairing (want 78->r9/FA8->r11, got reversed) and addi(+0x30)/lis(QB)
// order. Both sides emit all three `lis 0x802A` (no CSE either way); it is a
// pure order swap. Tried: address-locals born before the call (10.3%, frame
// -0x10->-0x18, live-across-call burst), after-call locals p78/pA8 (79.49%,
// same shape), birth-order swap (byte-neutral), QB-store-moved-last (79.49%,
// window shifts, no gain), -fno-schedule-insns (53.8%), -fno-schedule-insns2
// (79.49%). The lis-pair-above-stw order is not reachable from source: the
// lis's have the longer dataflow path (lis->lfs->stfs chain) yet got
// schedules the dead-end stw first. Wants's pairing (78->r9 then r9=+0x30
// view) vs got's (FA8->r9 then r9=+0x30) follows from the order. PARKED.
// ---------------------------------------------------------------------------
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80299F74[];
extern char lbl_80299F78[];
extern char lbl_80299FA8[];

/* want: eight stfs (0x20/0x24/0x28/0x2C and 0x30/0x34/0x38/0x3C).  The shared
   Unk_C8FEE62D declares those slots as u64 -> int<->float round trips. */
typedef struct F4 {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
} F4;

typedef struct Shad {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    s32 unk0x18;
    s32 unk0x1C;
    F4 v20;
    F4 v30;
    s32 unk0x40;
    char pad0x44[0x4];
    s32 unk0x48;
} Shad;

void fn_8009F53C(void);

void *fn_800DCE58(Shad *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    register F4 *temp_r9 __asm__("r9");
    register F4 *temp_r11 __asm__("r11");

    fn_8009F53C();
    temp_f0 = *(f32 *)lbl_80299F74;
    arg0->unk0x4 = QB_SHADOW;
    temp_f13 = *(f32 *)lbl_80299F78;
    arg0->unk0x18 = (s32)lbl_80299FA8;
    temp_r9 = (F4 *)((char *)arg0 + 0x30);
    arg0->unk0x1C = 0;
    temp_r9->unk0x0 = temp_f0;
    temp_r11 = (F4 *)((char *)arg0 + 0x20);
    temp_r9->unk0x4 = temp_f13;
    temp_r9->unk0x8 = temp_f0;
    temp_r9->unk0xC = temp_f13;
    arg0->unk0x40 = QB_NONE;
    temp_r11->unk0x0 = temp_f0;
    temp_r11->unk0x4 = temp_f0;
    temp_r11->unk0x8 = temp_f0;
    temp_r11->unk0xC = temp_f13;
    arg0->unk0x48 = 1;
    return arg0;
}
