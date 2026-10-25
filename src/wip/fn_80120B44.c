// PARKED 2026-10-30: 76.60% -> 77.66%
// family=m2c range=0x80120B44-0x80120CBC size=376B
//
// fn_80120B44: 3-iteration sweep over an AXVoice table (lbl_8038F0C0, stride
// 0x21C, 3 entries) releasing stale voices, then DVDCheckAsync if anything
// changed. Retires a manager-side flag per bit (lbl_80302F04, bits 0x200<<i)
// and force-clears bit 0x100 on entry; fires a 7-arg fn_80120D14 command
// with the voices three floats when the manager reports a change.
// 7-arg fn_80120D14 shape confirmed byte-proven by promoted src/fn_801211B8.c;
// lbl_80302F04 flag semantics confirmed by promoted src/fn_80121448.c.
//
// RESIDUAL: 21/94 words, object .text 0x178 = want 376B = symbols.txt (exact).
// 17 of the 21 are ONE root cause; 2 are a preheader transposition; 2 are the
// 0x18/0x1C arg-addi order. Everything else (11 saved GPRs r21..r31, stwu
// -0x38, frame/stmw/LR offsets, all 7 call targets, the 0x200/0x2000 flag
// masks, the (v+1)&7 counter, the -0x1e4/-0x1fc p-relative loads) is exact.
//
// 1. ANCHOR (17 diffs) - the loop-invariant address-web leader. WANT builds
//    ONE register for the BARE table base and adds a plain per-access K:
//      preheader: the page high half goes into r9 and the low part (minus
//                 0xf40) into r26 as the base, then r29 derives the pointer
//                 by adding 0x20c
//      in-loop:   each access adds its own plain constant off r26 into a
//                 scratch (0x24, 0x20 and 0x218 into r9, r9 and r24) with an
//                 indexed word load through the r28 offset register
//    GOT instead mints a separate ADDR16_HA/LO pair PER CONSTANT (verified in
//    the .o: `R_PPC_ADDR16_LO lbl_8038F0C0+0x24`), picks the FIRST
//    program-order constant (0x24) as the leader, and folds the rest off it
//    (+0x1F4, -4, -8, -0xC). Both forms cost the same 16 words, so this is a
//    reload/`equate_symbolic_operands` anchor-choice tie-break.
//    It is NOT reachable from C in this cc1: the leaders value is always
//    `sym + <first constant used>`, never `sym + 0`, because a C-level base
//    variable is either (a) constant-folded straight back into the symbol
//    (measured byte-identical to the bare-symbol body) or (b) strength-reduced
//    into a running pointer, losing every lwzx/lfsx (see EXHAUSTED).
// 2. PREHEADER (2 diffs): WANT [lis r25][li r22,0x200][rlwinm][li r28,0];
//    GOT [li r28,0][li r22,0x200][rlwinm][lis r25]. A pure 2-insn
//    transposition of the loop-index `li` against the 2nd HI16 reload.
// 3. 0x18/0x1C (2 diffs): WANT emits `addi r9,r26,0x18` then
//    `addi r11,r26,0x1c`; GOT emits them in the opposite order (arg4 before
//    arg5 in the source). Staging both floats into named temps: no-op.
// 4. MASKED-HIDDEN BUG (not in the 21): the object is one word SHIFTED from
//    0x80120B8C, so the loop latch `ble` has REL14 addend 0x48 -> 0x80120B8C
//    (the preheaders `addi r29,r9,0x20c`) instead of the WANT 0x80120B90
//    (the loop head `lwz r9,0(r29)`). A consequence of (1); the masked
//    compare cannot see it (REL14 mask keeps BO/BI/AA, hides the target).
//    REL14 audit on the final body: 9 entries, 8/9 land on a real want branch
//    target (0x114 x5 -> 0x80120C58, 0x128 x2 -> 0x80120C6C, 0x154 ->
//    0x80120C98, 0x160 -> 0x80120CA4), 1 wrong (0x48, item 4).
//    REL24: 7/7 match wants bl (fn_80120664, OSDisableInterrupts,
//    AXFreeVoice, OSRestoreInterrupts, fn_8011BC88, fn_80120D14,
//    DVDCheckAsync). Address pairs: lbl_80302F04 (0x80300000+0x2f04),
//    lbl_8038F0C0 (0x80390000-0xf40), lbl_8038A820 (0x80390000-0x57e0) -
//    all three hand-decoded from wants lis/addi and all real symbols.txt
//    entries, so hazard 277 does not apply. No QB hash literals in this
//    function (the only `lis` fields are 0x8030/0x8039 address pages).
//    Sections: .text + .rela.text only - no private .rodata, so no doc-14
//    pool caveat. 0 emitted inline instructions.
//
// THIS ROUND WIN (+1.1): preheader statement order. WANT puts the loop
// indexs `li r28,0` AFTER the `rlwinm`; the inherited order put it before.
// Enumerating all 6 permutations of the three independent preheader
// statements (i=0 / mask=0x200 / off=0) and taking (i, off, mask) fixes one
// diff. All 6: 76.60 / 77.66 / 75.53 / 75.53 / 76.60 / 75.53. RE-MEASURE the
// flags on the new body, not the old one (AGENTS sec.6bx): all 11 are no-ops
// here (-fno-gcse, -fno-schedule-insns, -fno-schedule-insns2, -fno-sched-spec,
// -fno-sched-interblock, -fno-thread-jumps, -fno-expensive-optimizations,
// -fno-rerun-cse-after-loop, -fno-strength-reduce, -O3, -Os) - all 77.66%.
//
// EXHAUSTED (measured this round, all on the ADOPTED body unless noted):
//  * named base, MEM form `*(s32*)((char*)base + K + off)`, base = char* or
//    s32: 7.9% / 7.45%, object 20B SHORT - strength reduction collapses the
//    5 lwzx/lfsx into lwz/lfs displacements.
//  * C89 subscript `((s32 *)((char *)base + K))[off]` (the array-index `ai`
//    shape): identical strength reduction, 7.45%; on the BARE symbol (no
//    base) 75.53%.
//  * `s32 base` + pure integer arithmetic `*(s32 *)((s32)(base + K + off))`
//    and `*(s32 *)((char *)(base + K + off))`: both 20B short. So the fold
//    fires for PLUS_EXPR as well as POINTER_PLUS_EXPR.
//  * `char *base` used only for `p`, conditions keep the bare symbol: 11.7%.
//  * hard `register s32 base __asm__("r26")` + MEM form: 16B short.
//  * `register s32 off __asm__("r28")` on the bare-symbol body: 76.60%, no-op.
//  * `register s32 base __asm__("r26")` + `register s32 off __asm__("r28")`
//    together: still strength-reduced.
//  * `__asm__("" : "+r"(off))` at the loop top to make the index opaque and
//    defeat the IV machinery: COMPILE FAIL - ProDG cc1 rejects a block-start
//    declaration that follows a statement (sec.6cq: "parse error before `*`").
//    Put the barrier after `AXVoice *n = ...` and it no longer blocks the fold.
//  * goto state-machine loop (`goto test; body: ... test: if (i<=2) goto
//    body;`) to deny loop.c its strength-reduction pass: 26.6%.
//  * index/constant operand order, 3 spellings (`lbl + 0x24 + off`,
//    `lbl + off + 0x24`, `(char*)(off + (s32)lbl) + 0x24`): all 76.60%. The
//    apparent lwzx/lfsx slot "flip" is illusory - it only renumbers r26/r28
//    (off and the leader swap registers); the slot order [index, addr] is
//    fixed by `expand_ldux` and not source-reachable. NOTE: this axis also
//    costs a latch diff (`addi r26,r26,0x21c` vs `addi r28,r28,0x21c`).
//  * char-array subscript `*(s32 *)&lbl_8038F0C0[off + 0x24]`, both index
//    orders: 76.60%.
//  * staging the 0x18/0x1C float args into named temps, in both orders:
//    77.66%, no-op.
//  * the previous sessions list still stands: p-relative spellings for the
//    other three accesses (74.5 / 71.3 / 46.2 / 18.3%), named p218 base
//    (55.3%), off pinned r28, goto block split, address operand-order perms,
//    4 store/const orders, all flags. -fno-cse does not exist in this cc1.
//
// CONTRIBUTION (0 emitted instructions, both still valid):
//  1. UNNAMED extern array base vs NAMED local base. Referencing
//     `lbl_8038F0C0` inline in every `char *` address keeps one HI16 anchor
//     and the indexed `lwzx rX,scratch,off_reg` form; assigning it to a
//     `char *` local first hands the loop to GCCs IV machinery, which
//     strength-reduces the walk. AGENTS L1 / sec.6dz2 are the mirror rule: a
//     SYMBOL used at several sites must be re-written at each site.
//  2. An unused scalar local DOES reserve a frame slot in ProDG cc1 2.95:
//     `s32 sp8;` (declared, never read) is the whole 4-byte locals region
//     that produces `stwu -0x38` / `stmw r21,0xc` / `stw r0,0x3c` with
//     11 saved GPRs. `volatile double _dummy` is NOT needed and costs 8.
//  3. A hard `register s32 i __asm__("r27")` on the loop counter pins the
//     colour of the preheader birth (+7.4 points, 0 emitted). Pointer-typed
//     pins are dropped by this cc1; the s32 alias is the safe form.
#include "types.h"
#include "qb_constants.h"

typedef struct AXVoice {
    char _000[0x146];
    u16 f146;
} AXVoice;

extern char lbl_8038F0C0[];
extern s32 lbl_80302F04;
extern char lbl_8038A820[];

extern void fn_80120664(void);
extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern void AXFreeVoice(void *);
extern s32 fn_8011BC88(void *);
extern s32 fn_80120D14(s32, s32, s32, f32, f32, f32, s32);
extern void DVDCheckAsync(void);

s32 fn_80120B44(void) {
    s32 flag;
    s32 g;
    register s32 i __asm__("r27");
    s32 mask;
    s32 off;
    char *p;
    char *mgr;
    s32 sp8;
    void *next;
    s32 ret;

    flag = 0;
    g = lbl_80302F04;
    i = 0;
    off = 0;
    mask = 0x200;
    g &= QB_UNKNOWN_0xFFFFFEFF;
    lbl_80302F04 = g;
    fn_80120664();
    for (p = lbl_8038F0C0 + 0x20C, mgr = lbl_8038A820; i <= 2;
         i++, p += 0x21C, mgr += 0x74, off += 0x21C) {
        AXVoice *n = *(AXVoice **)p;
        if (n != NULL) {
            if (n->f146 == 0
                && *(s32 *)(lbl_8038F0C0 + 0x24 + off) != 0
                && *(s32 *)((char *)p - 0x1EC + off) == 0
                && (next = *(void **)(lbl_8038F0C0 + 0x218 + off)) == NULL) {
                u32 irq = OSDisableInterrupts();
                AXFreeVoice(*(void **)p);
                *(void **)p = next;
                *(s32 *)(p - 0x1E4) = (*(s32 *)(p - 0x1E4) + 1) & 7;
                OSRestoreInterrupts(irq);
                lbl_80302F04 = lbl_80302F04 & ~(0x2000 << i) & ~(mask << i);
                ret = fn_8011BC88(mgr);
                if (ret != 0) {
                    fn_80120D14(ret, i, 1, *(f32 *)(lbl_8038F0C0 + 0x18 + off),
                                *(f32 *)(lbl_8038F0C0 + 0x1C + off),
                                *(f32 *)(p - 0x1FC),
                                (s32)*(void **)(lbl_8038F0C0 + 0x218 + off));
                }
            } else {
                flag = 1;
                lbl_80302F04 |= mask << i;
            }
        }
    }
    if (lbl_80302F04 & 0x100) {
        flag = 1;
    }
    if (flag != 0) {
        DVDCheckAsync();
    }
    return 0;
}
