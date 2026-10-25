// PARKED 2026-09-30: 96.8% -> 96.8%
// family=m2c range=0x8009B3B4-0x8009B4B0 size=252B
// FLAG: -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py - never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
//
// RESIDUAL: 2 words of 63. Everything else - prologue, 3 calls, both log2
// loops, all 12 tail stores, the whole epilogue - is byte-identical.
// The want materialises 0 into r9 and 0 into r11 and 6 into r10 and 0x127
// into r8 and 0 into r0, stores the r26 word to 0x10 of r31, copies r31 to
// the return register, then stores the r0 word to 0x14 of r31 before the r6
// byte store. The current output materialises those same five immediates in
// those same registers and stores r26 to 0x10 of r31 the same way, but then
// stores r0 to 0x14 of r31 before copying r31 to the return register, ahead
// of that same byte store.
// The return-value copy sits exactly ONE slot late: want has ONE store before
// it and ELEVEN after, we emit two before and ten after.
//
// UNMEASURED VARIANT IN THIS BODY: the return value is held in a named local
// `rv` born right after the last call (before the store run) and the tail
// returns `rv`, so the copy's pseudo exists before the store block instead of
// being created by expand_return at the end. If the object grows past 252B the
// local did not coalesce and the previous body must be restored.
//
// WHY IT IS STUCK - sched2 owns this, and the documented "2 users" cure is
// closed here. (Verified with cc1 -v pass trace, -dr post-reload RTL and -dj
// post-sched2 RTL on a 1-function probe that reproduces GOT byte-for-byte.)
//   1. `reorder_basic_block` is NOT the culprit: in the post-reload RTL the
//      return copy is already the LAST insn of the function (insn 192).
//      -fno-schedule-insns2 leaves it there; -fno-schedule-insns (the flag this
//      object carries) keeps sched2 enabled and produces the 96.8% diff.
//   2. sched2 schedules only TARGET_INSNs - in the tail block those are
//      `movmem` (the 12 stores) and the return copy's `movsi3`; the five `li`s
//      are non-TARGET insns and keep their relative order. The copy is emitted
//      in the FIRST gap after the leading frozen insns, because its cost (52)
//      is strictly below every store's (512). Measured gap index: 1 = want,
//      2 = what we get, 3 with a `__asm__` barrier. It is a cost tie, not an
//      ordering choice, so no source reordering can move it.
//   3. The AGENTS remedy for a 1-user-position residual ("give the insn 2
//      users, i.e. raise its reorder priority") CANNOT be applied: the residual
//      is `mr r3,r31`, and its result register r3 has exactly one user - the
//      fixed `(use (reg/i:SI 3 r3))` in the epilogue. No C construct can add a
//      second user to the return register. Giving the 2 users to the f_14
//      CONSTANT instead just re-orders the const group (measured: `li r0,0`
//      moves to slot 2, copy slot unchanged, no score change).
//
// IDENTITY: 0x1C-byte grid/buffer object factory. Promoted (byte-identical)
// caller src/fn_8007A230.c:
//   temp_r3 = Mem_Alloc2(0x1C);
//   temp_r3 = fn_8009B3B4(temp_r3, arg1, arg2, arg3, arg4, arg5, arg6);
//   arg0->unk0xC = temp_r3;  return temp_r3 != 0;
// Only r3-r6 of the 7 args are used:
//   +0x00 arg1 | +0x06 log2(arg2) | +0x07 log2(arg3) | +0x0c arg2*arg3*4
//   +0x10 buffer | +0x04/+0x05/+0x08/+0x14/+0x18 zero | +0x09 6 | +0x0a 0x127
// Both `1 << l2` loops must use s32 counters (m2c's s8 adds extsb), and
// fn_80010E78 is a 0-arg BODY whose call site still loads r3, so it needs a
// 1-arg prototype or GCC drops the setup.
//
// WHAT IS LOAD-BEARING (do not undo - each was measured):
//  1. Callee arities re-verified from each callee's own first insns
//     (fn_80010D94 reads r4 = 2-arg; Mem_Alloc 0x80009A78 does `mr r4,r3` =
//     1-arg; memset 0x8026AFB8 = 3-arg; fn_80010E78 reads no arg reg = 0-arg
//     body / 1-arg prototype). THIS FUNCTION IS 7-ARG.
//  2. `register s32 l2 __asm__("r6"); l3 __asm__("r7");` reproduce both log2
//     loop blocks exactly. Dropping the pins entirely -> compile FAIL / 47.6%.
//  3. The four tail constants are hard-reg-pinned AND assigned INLINE at first
//     use (`z9 = 0; t->f_05 = z9;`), which is what fixes r9/r11/r10/r8.
//     The re-births `z9 = 0;` / `z11 = 0;` before f_04 / f_18 are ALSO
//     load-bearing: dropping them gives 50/63 (88.9%).
//  4. Store order in source == emission order here: f_10, f_14, f_06, f_07,
//     f_05, f_0c, f_08, f_00, f_09, f_0a, f_04, f_18.
//  5. The memset LENGTH must be staged through `register s32 nbytes __asm__("r5")`
//     so `mr r5,r27` lands before `li r4,0`.
//  6. `arg0` is s32 and the function ends `return (void *)arg0;`.
//  7. `-fno-schedule-insns` per object; the same body WITHOUT it scores
//     55/63 = 87.3%. The flag is honoured by test_wip_drafts.py and by
//     promote_wip.py - keep the line.
//  8. The `k6 = 6;` and `k127 = 0x127;` CONSTANT BIRTHS must be hoisted to sit
//     between `t->f_10 = blk;` and `t->f_14 = 0;` - the STORES stay in want's
//     order, only the two `= const` assignments move up. Moving just k6 ->
//     93.7%; just k127 -> 92.1%; both (or both above f_10) -> 96.8%.
//
// ROUND r2 - WHAT WAS ADDED TO THE DEAD-END LIST (all measured on a probe
// that reproduces GOT exactly; probe tail = 18 insns, best = 16/18, and
// 16/18 in the probe IS 61/63 in the real function):
//  * 13x13 grid over the source position of the `k6`/`k127` constant births
//    (item 8 generalised from hand orderings to every gap): 0 combinations
//    reach want's tail. The copy only lands in want's slot (b=1) when one of
//    the two constants is late-defined, and that always costs the `li r10,6`
//    / `li r8,0x127` order or the f_14 store position.
//  * 13x13 grid over the source position of the two load-bearing `z9`/`z11`
//    RE-BIRTHS (a lever this file had never repositioned, only dropped):
//    0 hits, all 169 variants the same shape. Dropping them is still 88.9%.
//  * 20 further flags on top of the ones item 7 lists: `-fno-strict-aliasing`,
//    `-fstrict-aliasing`, `-ffloat-store`, `-fomit-frame-pointer`,
//    `-fno-builtin`, `-fno-asynchronous-unwind-tables`(FAIL), `-ffixed-r13`,
//    `-ffixed-r2`, `-fshort-enums`, `-mno-multiple`, `-msdata=eabi`,
//    `-mhard-float`, `-fno-if-conversion`(FAIL), `-falign-functions`(FAIL),
//    `-G8`(FAIL), `-fno-merge-constants`(FAIL), `-fno-signaling-nans`(FAIL),
//    `-fno-trapping-math`(FAIL), `-fno-omit-frame-pointer`(FAIL): every
//    compiling one is 16/18, i.e. no change at all.
//  * The one construct that DOES reach want's copy slot is making the f_14
//    STORE blocked on a late value definition (`t->f_14 = z0;` with
//    `z0 = 0;` after `t->f_18 = z11;`) - it emits the exact
//    `stw r26,0x10 | mr r3,r31 | stw rX,0x14` order. It cannot be used:
//      - unpinned, the long live range (def at block end, use 2nd) makes the
//        allocator pick a callee-saved reg: r24 (+7th save slot, `lmw r24`) or
//        r25 (which then steals arg1's r25). 68.3-73.4%, never r0.
//      - `register s32 z0 __asm__("r0")` gives r0 AND the right slots, but
//        gcc DELETES the `li r0,0` as dead and - confirmed on the REAL
//        function this round, 60.3% - reserves r0 for the whole function, so
//        both log2 loops re-colour to `li r11,1 / slw r9,r11,r6`. Opening the
//        pin in a NESTED block after the two loops does NOT rescue it (also
//        60.3%): cc1 still reserves r0 function-wide. So AGENTS' "a nested
//        pin avoids the birth poisoning" does not apply to r0.
//      - volatile-asm `li` birth 73.0-73.4% (r25); `z0 = size - size`,
//        `z0 = l2 & 0`, u32 z0: 68.3%.
//    The blocking route is therefore dead: at that point in the store run the
//    only registers already holding a zero are r9 and r11, and want spends
//    both on its two 2-user stores (`stb r9,5 / stb r9,4` and
//    `stb r11,8 / stw r11,0x18`). r0 is the only register left, and r0 is
//    exactly what both log2 loops need.
//  * Return-SPELLING variants, all byte-identical 96.8%: `return (void *)t`,
//    `return t`, an `s32` return type, a `void *rv` local assigned between
//    f_10 and f_14, a hard `register s32 rv __asm__("r3")` (pins to r3
//    collapse the frame: 52.4%), an explicit `__asm__("mr %0,%1")` copy.
//    `-fno-regmove` shows the copy is not a regmove artifact, so it is
//    `expand_return`'s own copy.
//
// ALSO DEAD (do not re-run):
//   - all pins removed 47.6% / no-flag 50.8%; k6+k127 pins only 64.1%;
//     nbytes pin removed 88.9%; z9/z11 re-births removed 88.9%.
//   - every `__asm__` barrier placement around the tail stores: 76-87%.
//   - `volatile s32 *` lvalue for the f_10/f_14 stores: 90.5-96.8% (no help).
//   - a separate `char *tb` base for the first two stores: 96.8% (no change).
//   - swapping the f_10/f_14 store STATEMENTS: 96.8% (identical diff - the
//     two are interchangeable in the schedule, so the copy does not move).
//   - putting the f_14 store last in the store run: 66.7%.
//
// AUDIT OF THE 96.8% BODY (re-run 2026-09-30, all clean):
//   object .text = 0xFC = 252B = symbols.txt `size:0xFC` = this range marker;
//   object carries only .text + .rela.text (no .rodata/.data, so no doc-14
//   pool caveat); 0 emitted inline instructions; compiles warning-free.
//   4/4 R_PPC_REL14 (type 11, section-relative, readelf prints addends in
//   HEX): .text+0x80 -> 0x8009B434, +0x70 -> 0x8009B424, +0xA0 -> 0x8009B454,
//   +0x90 -> 0x8009B444 = want's four `beq/ble/blt` targets.
//   4/4 R_PPC_REL24 (type 10): fn_80010D94, Mem_Alloc, memset, fn_80010E78,
//   matching want's four `bl`s in order.
//   1x R_PPC_ADDR16_HA + 2x R_PPC_ADDR16_LO all against lbl_802FFE98, which
//   hand-decodes from want's `lis r30,-0x7fd0` + `lwz r9,-0x168(r30)`
//   (0x80300000 - 0x168 = 0x802FFE98) and is a real symbols.txt entry
//   (`.data:0x802FFE98, size:0x8`), so the masked-100%-wrong-label hazard
//   cannot apply. Every external symbol in the object was checked against
//   config/G2TE52/symbols.txt at the exact relocation address.
//   No opcode-4 words in the want, so the PS/VMX mislabel trap never applied.
#include "types.h"
extern s32 lbl_802FFE98;
extern void fn_80010D94(s32, s32);
extern void *Mem_Alloc(s32);
extern void *memset(void *, int, unsigned int);
extern void fn_80010E78(s32);
typedef struct {
    s32 f_00;
    s8 f_04;
    s8 f_05;
    s8 f_06;
    s8 f_07;
    s8 f_08;
    s8 f_09;
    u16 f_0a;
    s32 f_0c;
    s32 f_10;
    s32 f_14;
    s32 f_18;
} T;
void *fn_8009B3B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    T *t = (T *)arg0;
    void *rv;
    s32 size;
    s32 *blk;
    register s32 l2 __asm__("r6");
    register s32 l3 __asm__("r7");
    register s32 z9 __asm__("r9");
    register s32 z11 __asm__("r11");
    register s32 k6 __asm__("r10");
    register s32 k127 __asm__("r8");
    register s32 nbytes __asm__("r5");
    size = arg2 * arg3 * 4;
    fn_80010D94(*(s32 *)((char *)lbl_802FFE98 + 0x11C), 0x20);
    blk = (s32 *)Mem_Alloc(size);
    nbytes = size;
    memset(blk, 0, nbytes);
    fn_80010E78(*(s32 *)((char *)lbl_802FFE98 + 0x11C));
    rv = (void *)arg0;
    l2 = 3;
    if (arg2 > 8) {
        do {
            l2++;
        } while ((1 << l2) < arg2);
    }
    l3 = 3;
    if (arg3 > 8) {
        do {
            l3++;
        } while ((1 << l3) < arg3);
    }
    t->f_10 = (s32)blk;
    k6 = 6;
    k127 = 0x127;
    t->f_14 = 0;
    t->f_06 = l2;
    t->f_07 = l3;
    z9 = 0;
    t->f_05 = z9;
    t->f_0c = size;
    z11 = 0;
    t->f_08 = z11;
    t->f_00 = arg1;
    t->f_09 = k6;
    t->f_0a = k127;
    z9 = 0;
    t->f_04 = z9;
    z11 = 0;
    t->f_18 = z11;
    return rv;
}
