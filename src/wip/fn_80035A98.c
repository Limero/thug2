// PARKED 2026-10-30: 65.71% -> 88.57% (31/35 words).
// family=m2c range=0x80035A98-0x80035B24 size=140B
//
// WHY PARKED: 4 words left, in TWO coupled groups, both traced to GCC 2.95's
//   preheader `reorder_basic_block` priority (= number of users of the result,
//   AGENTS 6bg-8) plus the paired-single store scheduling it feeds.
//   (a) `lis r28,-0x7fd0` (the @ha anchor for lbl_80301A38) lands LAST in the
//       loop preheader instead of first. `cc1 -dr` proves why: the HI16 insn is
//       born INSIDE the loop body (LUID 28) while the preheader's own addis are
//       LUID 13/16, because `loop`/LICM runs BEFORE `reload` and only hoists
//       the address pseudo, not the HI16. A hoisted preheader statement is then
//       APPENDED and sorts last (6eq/6ew). Want has it FIRST, which requires
//       the HI16 to have been born in the preheader -- unreachable from C.
//       Adding/removing the `addi r30` users never reorders the block: 4
//       declaration/birth permutations all give byte-identical objects.
//   (b) the two `psq_st` to the sp8 temp use base r30 (`0(r30)`/`8(r30)`)
//       where want uses r1 (`8(r1)`/`16(r1)`), while the RELOAD correctly uses
//       `8(r30)`. That is a split-base, i.e. the address web has 3 uses in C but
//       only 1 in retail. Forcing the stores r1-relative (`sp8[0]=a; sp8[1]=b;`)
//       does give 8(r1)/16(r1) -- but it also drops &sp8 to 1 user, which (i)
//       swaps the GPR choice (r29 for &sp8, r30 for `end`; want is the reverse)
//       and (ii) re-breaks the ps_add/psq_st interleave (add,st,add,st instead of
//       add,add,st,st) and shuffles all four FPR colours. 60% vs 88.57%.
//       So (a) and (b) are the SAME fact seen twice, and neither is reachable.
//
// BIGGEST LEVER THIS ROUND: `// FLAG: -fno-sched-interblock` -> 68.57% ->
//   88.57% (+20.0) on its own. It is what reproduces want's FPR colouring
//   (psq_l f11/f0/f13/f12 + ps_add f0,f0,f13 / f11,f11,f12) AND want's
//   `lwz r3,<lbl>`-before-`lwz r4,0x20(r31)` call-arg order. The 2026-09-26
//   note recorded the schedule flags as "exact no-ops" -- that was measured on
//   the OLD body (reload of sp[0]); re-measure every inherited lever after the
//   semantic round (AGENTS 6bx/6dh/6aq-222: a flag can flip sign too).
// SECOND LEVER (semantic, +2.86 on top of the flag, and an AND with it):
//   the reload feeds node+0x58 from **sp8[1]**, not sp8[0].
//   want's `psq_l f0, 8(r30)` with r30 = r1+8 addresses r1+16 = sp8[1];
//   the old draft read sp8[0] and got a self-consistent `psq_l f0, 0(r30)`.
////   (a) and the flag alone: 68.57%. (b) sp[1] alone: 65.71%. (a)+(b): 88.57%.
//
// LEVERS TRIED (all measured, best body unless noted):
//   -fno-schedule-insns 68.57 | -fno-schedule-insns2 68.57 | -fno-sched-spec
//   68.57 | -fno-gcse 68.57 | -fno-expensive-optimizations 68.57 |
//   -fno-thread-jumps 68.57 | -O3 68.57 | -Os/-fno-sched-round/
//   -fno-rerun-cse-after-loop/-fno-crossjumping: not accepted by cc1.
//   -fno-schedule-insns ON TOP of -fno-sched-interblock: 68.57 (undoes it).
//   -fno-schedule-insns2 / -fno-sched-spec / -fno-gcse / -fno-expensive-opt /
//   -fno-thread-jumps / -fno-caller-saves ON TOP: all 88.57, i.e. inert.
//   staging the 4 PS operands into named `__ps_t` locals in 6 different birth
//     orders: 88.57% every time (byte-identical objects) -- the front end
//     canonicalises the operand graph, so birth order is NOT the FPR lever.
//   `volatile` on the p[]/node[] PS reads, on the sp8 store lvalues, on the
//     whole array, on the store pointer: 68.57 / 62.86 / 60 / 68.57.
//   r1-relative store forms (sp8[] stores, mixed sp/sp8, both reloads
//     volatile, 2-user mixed): 60 - 85.71%, none better.
//   explicit `lis %0,%1@ha` page-anchor asm (volatile and the 6ds2 non-volatile
//     + loop-variant-input form): 88.57%; it DOES make the `lwz` word
//     byte-exact (0x807c1a38, no reloc) but the lis still sorts last.
//   `while (node <= end)` loop form: 17.14% (wrong shape). `for(;;){...break;}`:
//     88.57% (same object). `do/while` is already rotated to want's shape.
//   call-arg staging / comma / `(s32)` cast on lbl_80301A38: 88.57% identical.
//   declaration & birth permutations of `end` / `sp8` / `sp = sp8`: 88.57% all.
//   `register __ps_t/sn_ps x __asm__("frN")` pins on any operand: DROPPED by
//     cc1 (verified with a standalone probe -- output byte-identical to unpinned).
//
// AUDIT (88.57% body): object .text = 0x8C = 140B = symbols.txt size:0x8C =
//   header `size=140B`; only .text + .rela.text in the object (no private
//   .rodata, so no doc-14 promote caveat); 0 inline-asm instructions;
//   4/4 intra-function R_PPC_REL14 (type 11, section-relative addends 6c, 6c,
//   20, 6c -> 0x80035B04, 0x80035B04, 0x80035AB8) match want's `bne`/`beq`/
//   `ble` targets, and the single R_PPC_REL24 (type 10) targets fn_800A398C;
//   the ADDR16_HA/LO pair hand-decodes from want's `lis -0x7fd0` +
//   `lwz 0x1a38(r28)` to 0x80301A38 = lbl_80301A38 (symbols.txt .data
//   size:0x4), so hazard 277 cannot apply.
//
// WHAT WAS DECODED (m2c emitted six `0;` statements here -- it cannot read
// paired-single at all, so the whole body had to be re-derived from want):
//   loop over 4 records of stride 0x78 starting at arg0, end = arg0+0x168
//   if (*(s32*)(node+0x84) == 0) {
//       p = fn_800A398C(lbl_80301A38, *(s32*)(node+0x20));
//       if (p) {
//           a = p[0x58..0x5F] + node[0x60..0x67];   // ps_add f0, f0, f13
//           b = p[0x60..0x67] + node[0x68..0x6F];   // ps_add f11,f11, f12
//           sp8[0] = a; sp8[1] = b;                 // 0x8(r1) / 0x10(r1)
//           *(ps*)(node+0x50) = a;                 // 0x50(r31)
//           *(ps*)(node+0x58) = sp8[1];            // reload, 0x58(r31)
//       }
//   }
//
// DECODING NOTES worth keeping (ps_add A-form field layout):
//   `__builtin_ps_add(a,b)` lowers to the template `ps_add %0,%1,%2` and the
//   2nd C operand lands in **VB** for add/sub but in **VC** for mul. Probed
//   directly: __builtin_ps_add(a,b) -> 0x1021102A = VD=a VA=a VB=b VC=0;
//   __builtin_ps_mul(a,b)        -> 0x102100B2 = VD=a VA=a VB=0 VC=b.
//   So a hand-decoded `ps_add fD,fA,fX,fC` word is __builtin_ps_add(A, X).
//   xo5 21=add 20=sub 25=mul 18=div 29=madd 10=sum0 12=muls0 23=sel 24=res.
//
// SHAPE CONSTRAINTS (all load-bearing, do not "tidy" them):
//  1. The list walker MUST be a `u32`, not `char *`. Want ends the loop with
//     `cmplw r31,r29` (no scratch reg); a `char *` walker plus the
//     `(u32)node <= (u32)end` cast emits `cmplw r0,r31,r29` and shifts the
//     whole tail by one instruction. +28 points on its own.
//  2. `__ps_t *sp = sp8;` as a decl-init -- the named base is what materialises
//     `addi r30,1,8` in the prologue and routes the reload through `8(r30)`.
//     Dropping it (using sp8[] everywhere) costs the r30 slot entirely -> 11.8%.
//  3. `volatile __ps_t sp8[2]` is required -- it is what keeps the reload of
//     sp8[1] before the 0x58 store (want really reloads; plain members get
//     hoisted into the FPR and the reload disappears).
//  4. Declared `void` (no return). m2c's `void *` return forces a second
//     `mr r30,r3` to keep arg0 alive, which is exactly the wrong prologue.
//  5. ProDG cc1 is C89 -- every local `__ps_t a; __ps_t b;` must be declared at
//     the TOP of the `if (p != 0)` block, before any statement. Declaring them
//     after the `__builtin_ps_add` calls is a hard parse error.
//
// UNTIED LEVER: the 4 residual words need a source form in which the &sp8
//   address pseudo has exactly ONE use (so the two psq_st fold to r1
//   displacements) while the preheader's `addi r30` still outranks the two
//   single-user statements -- i.e. retail's `reorder_basic_block` saw all three
//   preheader insns at EQUAL priority. Nothing tried moves either half
//   independently; the untried route is a small `__asm__` window that emits the
//   two `psq_st` as raw D-form words off r1 (2 insns, ~5.7% of the function)
//   while leaving everything else as honest C. Try that only if 88.57% -> 100%
//   is worth the 2 emitted instructions; the body is currently 0 asm.
//
// FLAG: -fno-sched-interblock
#include "types.h"
#include "dolphin/SN_PS.h"
extern s32 lbl_80301A38;
s32 fn_800A398C(s32, s32);
void fn_80035A98(void *arg0) {
    u32 node = (u32)arg0;
    u32 end = node + 0x168;
    volatile __ps_t sp8[2];
    __ps_t *sp = sp8;
    do {
        if (*(s32 *)(node + 0x84) == 0) {
            __ps_t *p = (__ps_t *)fn_800A398C(lbl_80301A38, *(s32 *)(node + 0x20));
            if (p != 0) {
                __ps_t a;
                __ps_t b;
                a = __builtin_ps_add(p[11], *(__ps_t *)(node + 0x60));
                b = __builtin_ps_add(p[12], *(__ps_t *)(node + 0x68));
                sp[0] = a;
                sp[1] = b;
                *(__ps_t *)(node + 0x50) = a;
                *(__ps_t *)(node + 0x58) = sp[1];
            }
        }
        node += 0x78;
    } while (node <= end);
}
