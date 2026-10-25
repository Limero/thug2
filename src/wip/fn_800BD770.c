// RE-TRIAGE 2026-10-20: confirmed 60.6% size-exact on random-batch pass;
// prologue through alloc-spin exact, residual is int scheduling window
// (li/cmpwi/addi/xori order) past the FPR saves. No asm-free lever tried
// this round; kept as best match.
// PARKED 2026-10-30: 60.6% -> 60.63% (no improvement; baseline
// re-measured independently, unchanged).  All r4 levers measured neutral or
// worse - see the ROUND r4 block below.  10 new levers, 0 wins.
// WIP DRAFT (non-matching) - hand-rebuilt from the retail disassembly
// family=m2c range=0x800BD770-0x800BD96C size=508B
// FLAG: -fno-sched-interblock
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// VERDICT 2026-09-30: NEAR 60.6% masked (was DIFF 35.4%), SIZE-EXACT 127 insns
// / 508 B (= retail size 0x1FC), frame 0xb0 EXACT, FPR set f25-f31 EXACT,
// 7 saved GPRs r24-r31 EXACT with the EXACT roles (r24 next_tog, r25 off,
// r26 the 0x43300000 constant, r27 arg1, r28 arg0, r29 slot pointer, r30 cur,
// r31 ctr), cr4-save/mtcrf 8 EXACT, both call sequences, the alloc spin and the
// whole int->double dance EXACT.  50 of 127 words still differ.
// `// FLAG: -fno-sched-interblock` is LOAD-BEARING: without it 47.24%.
//
// SEMANTICS RECOVERED (all verified against the retail bytes):
//   2-pass (tog ^= 1) builder of a 16-byte-per-entry point array; ctr runs
//   arg1-1 .. 0; scale = (f32)(u32)arg1, c58 = pi/2 (lbl_80298E58), c5c = 1.0f:
//     f[0] = (tog ? farg0 : farg1) * cosf(2*ctr*c58/scale)
//     f[1] = tog ? farg2 : -farg2
//     f[2] = (tog ? farg0 : farg1) * sinf(2*ctr*c58/(f32)(u32)arg1)  <- the
//             divisor is a SECOND conversion of arg1, NOT the cached scale,
//             and BOTH trig args are the same 2*ctr expression (the fadds at
//             0x800BD8DC is fadds f0,f0,f0, i.e. a doubling, not a sum)
//     f[3] = c5c
//   the base is re-read from arg0+0x64 once per store (4x in retail - the same
//   no-CSE pattern the byte-identical sibling src/fn_800BD354.c reproduces);
//   the int->double conversion is the UNSIGNED one ((u32)v ^ 0x80000000 against
//   the real rodata2 double lbl_80298E50 = 0x4330000080000000 = 2^52+2^31), so
//   the operands are u32 - the m2c draft's `(f32)arg1` (signed) picks the 2^52
//   magic and a private module .rodata pool (doc-14), so the conversion is
//   written as a manual union dance; `fr.pad0x40` is a frame-template pad that
//   puts the cvt pair at r1+0x48/0x4c.
//
// WHAT WAS FIXED THIS ROUND (35.43% -> 60.63%), each step measured:
//  1. `__asm__("" : "+r"(ctr))` before the SIN half's ctr conversion, 35.43 ->
//     32.03 on its own but it is the ONLY thing that stopped ngccc CSE-ing
//     `(u32)ctr ^ 0x80000000` across the two cvt sites; that CSE made the xor
//     live across both trig calls, which cost a NINTH callee-saved GPR and
//     shifted the entire save area (CR slot 0x50 vs 0x54, stmw 0x54 vs 0x58)
//     and every colour by one.  With the barrier the prologue matches word for
//     word and 46.5% is reachable; on its own (no pf change) it was 512 B.
//  2. make the slot pointer ONE reused variable (`register s32 pf __asm__("r29")`
//     assigned base+cur, then base+cur+8) instead of a fresh expression per
//     store: 46.46%, and back to 508 B.  The +8 must be inside the pointer
//     (retail: `add r9,r30,r9; addi r29,r9,8; stfs f1,0(r29)`), not folded
//     into a store displacement.
//  3. array declarations for the three rodata constants + the sibling's
//     `__asm__ __volatile__("" : : "r"(temp_r30));` after the alloc spin,
//     48.03% (that barrier alone is worth the 2-word `addi r9,r30,-1` /
//     `cmpwi r30,0` order of the spin latch).
//  4. compute ctr and next_tog BEFORE the `arg1 == 0` test (retail emits both
//     before the `beq`; the delay slot of that `beq` is the arg1 xor):
//     49.61%.  Three-branch shape only exists with a goto, not a `while`.
//  5. hoist the f[2] pointer computation above the `sinf` call: 53.54%.
//  6. offset-first addressing `(char *)(cur + (s32)arg0->unk0x64)` (so the
//     offset lands in `add`'s rA slot, retail's `add r9,r30,r9`): 55.12%.
//  7. make the COS half one temp end to end (`vc = cosf(vc); vc = farg0*vc;
//     *(f32 *)pf = vc;`) so the multiply happens in place in f1 and the
//     `fmr f0,f1` after the call disappears: 58.27%.
//  8. pin the slot pointer to r29 via an s32 alias: 60.63% (also fixes the
//     ctr/pf register swap, because a pointer-typed pin is dropped by cc1 and
//     the unpinned `f32 *pf` let the indexed `stfsx` form win).
//
// DISCLOSED scaffolding: 12 declaration-level `register ... __asm__("...")` pins
// (no asm templates) + 3 ZERO-CODE empty-template barriers (`"+r"` on ctr and
// arg1, one input-only volatile on temp_r30).  ZERO instructions are emitted by
// inline asm.
//   Ablation: deleting ALL 12 pins at once costs only 1 word (60.63 -> 59.84),
//   so the pin set is worth almost nothing - but the two `+r` barriers are
//   essential (deleting the ctr one: 34.13%).  Do not delete the barriers.
//   Deleting the fr26/fr27/fr28 float-param pins: 55.91% (load-bearing).
//
// REJECTED / NEUTRAL levers (all measured, all score-neutral or worse):
//   - `// FLAG:` removal 47.24% (worse); +`-fno-sched-spec` /
//     `-fno-expensive-optimizations` neutral; `-fno-schedule-insns` 56.69,
//     `-fno-schedule-insns2` 57.48, `-fno-gcse` 37.50 (all worse).
//   - source-order swap of the two cvt words (`w[1]` before `w[0]`): neutral -
//     the two `stw`s are scheduled, not order-preserved.
//   - `volatile` on the cvt union / on `f64 d` / on `w[2]`: 45.31% (worse).
//   - a named `p1` pointer for the f[1] slot to kill the duplicate `lwz` in
//     the negate arm: 36.80% and 500 B (worse).
//   - `*(f32 *)(pf + 4)` for the f[1] slot: 32.52% and 492 B (much worse).
//   - `pf` assigned at the top of the loop body instead of after the cvt: neutral.
//   - `hi = 0x43300000` as an assignment instead of a declaration initialiser:
//     neutral.
//   - the f[3] store before `off += 0x10` in the latch: neutral.
//   - swapping the C operand order of the trig multiply (`farg0*v` vs
//     `v*farg0`): IDENTICAL output - GCC 2.95 canonicalizes MULT_EXPR operand
//     order, so retail's `fmuls f1,f26,f1` is not reachable by any source
//     spelling of the same product.  Treat that word pair as a wall.
//   - splitting the SIN half into a separate ctr-conv temp (`vw`) so the
//     product can live in the divisor's register: 41.41% and 512 B, both with
//     the direct-to-store and the store-then-assign multiply form (worse).
//   - pinning `ctr` to r31 directly: 46.46% - it pushes arg0 into r29 instead.
//   - pinning the loop-carried `tog` to r7: 7.20% and a BROKEN body (508 ->
//     500 B, epilogue collapsed).  A hard-reg pin on a value whose source
//     live range does not cross a call can still break the function - cc1
//     reserves r7 as an argument register.  Never pin an arg register.
//
// ROUND r4 (2026-10-30) - re-measured the inherited 60.63% with the authority
// tool (60.6%, size-exact 508 B) and ran 10 new levers.  ZERO improvements.
// All scores are `tools/want_got.py 0x800BD770 --file <variant>` with
// LEAF_TMPDIR=<scratch> and the draft's own FLAG honoured.
//
//   SEMANTIC AUDITS (all clean, nothing to fix):
//     * callee arity (§6bf) - Mem_Alloc(s32)->ptr 0x80009A78, Mem_Free2(void*)
//       0x80009AD8, cosf(f32)->f32 0x80271070, sinf(f32)->f32 0x80271170: all
//       1-arg with the retail prologues; verified against src/cosf.c,
//       src/fn_80009AD8.c and ~12 promoted sibling declarations.  Redeclaring
//       Mem_Alloc as `s32 Mem_Alloc(s32)` (§6di per-call-site return type) is
//       byte-identical (60.63%).  Nothing to fix here.
//     * promoted sibling §6dc/§6fn: src/fn_800BD354.c (228 B, byte-identical)
//       is the SAME builder but only the no-trig prologue + a plain 4-store
//       loop, so it carries no trig idiom.  Its two transferable items -
//       `volatile` read of unk0x94 and offset-first stores
//       `(f32 *)(off + arg0->unk0x64)` - are ALREADY in this draft.
//     * stale scaffolding (§6bf/§6bg/§6bx): `// FLAG: -fno-sched-interblock` is
//       still load-bearing (47.24% without it) - keep.  `// family=m2c` intact.
//       The 12 declaration pins ablate to 59.84% (1 word) and the fr26/27/28
//       float pins to 55.91%, both as recorded; no stale pin/barrier found.
//
//   NEW LEVERS, ALL MEASURED (do NOT re-run):
//     * SIN half made "one temp end to end" like the COS half
//       (`v = sinf(v); v = farg0 * v; *(f32 *)pf = v;`)  -> 44.88%, WORSE.
//       Same 44.88% with the product in a `register f32 __asm__("fr1")` or
//       `"fr0"` local, i.e. the drop is the SOURCE SHAPE, not the colour: it
//       costs the direct `stfs` form.  The residual `fmr f0,f1` after
//       `bl sinf` is therefore NOT reachable by re-shaping the multiply.
//     * shared f[1] address web (`p1 = base+cur+4` used by both the store and
//       the negate)  -> 36.80% and the object drops to 500 B (2 words short).
//       This kills retail's re-use of r9, i.e. the negate arm DOES re-derive the
//       address in ngccc and cannot share it.  (Confirms the old note's 36.80%.)
//     * the length-balancing pair implied by that: shared f[1] web (-2 words)
//       PLUS f[2] address as two statements (`p2 = base+cur; pf = p2 + 8;`)
//       PLUS an opaque `__asm__("mr %0,%1" : "=r"(tcopy) : "r"(base0))` birth
//       for retail's dead `mr r10,r11`  -> still 500 B / 36.80%.  Neither the
//       3-instruction f[2] address nor the dead `mr` survives cc1's coalescing
//       and its empty-copy elimination, so the +2 words cannot be bought back.
//     * `p2 = base + cur; pf = p2 + 8` alone (no p1)  -> 60.63%, BYTE-IDENTICAL.
//     * named `base0` for the f[0] address instead of inline
//       `cur + (s32)arg0->unk0x64`  -> 60.63%, byte-identical (cc1 re-coalesces
//       the base into r29 and emits the same `add r29,r30,r29`; retail's
//       `add r29,r30,r11` with a separate scratch base is a 2-use-web shape,
//       and there is no honest 2nd use of the base in the source).
//     * f[2] pointer statement moved ABOVE `vb = (f32)(fr.cvt.d - magic)`
//       (i.e. between the arg1 `xoris` and its `stw`, which is where retail
//       has `addi r29,r9,8`)  -> 60.63%, byte-identical.
//     * `volatile s32 vpf` re-read for the slot pointer (§6al-180) -> 25.98%.
//     * `Mem_Alloc` return as `s32` (§6di)              -> 60.63% byte-identical.
//     * `-fno-rerun-cse-after-loop` alone 47.24%; PAIRED with the load-bearing
//       `-fno-sched-interblock` 60.63% (neutral).  Also neutral paired:
//       `-fno-thread-jumps`, `-fno-cse-follow-jumps`.  The flag axis is closed.
//
//   WHERE THE RESIDUAL ACTUALLY IS (corrected analysis).  GOT is +1 word from
//   the f[1] negate arm onward, because ngccc re-derives the f[1] address
//   (`lwz`+`add` twice) where retail re-uses r9, and 2 words LATER it
//   collapses retail's 3-instruction f[2] address (`lwz`/`add`/`addi`) into
//   `lwz`/`add` and drops retail's dead `mr r10,r11` - so the net length is
//   already correct (508 B) and the index-aligned 50-word diff is dominated by
//   the resulting SLIDE inside the sin half, not by 50 independent facts.  Two
//   consequences worth stating: (1) the `mr r10,r11` is provably dead in retail
//   (r10 is never read again) yet r11 - the base - is live across `bl cosf`
//   without being saved, which is only possible if retail's source had a real
//   second use of the base value; (2) closing the window therefore needs a
//   source that emits BOTH the shared f[1] address AND a 3-word f[2] address,
//   and neither is reachable (measured above) - the cos/sin halves' address
//   shapes are what allocate, and ngccc's CSE owns them.
//
//   NEW UNTRYD LEAD (for the next round, not tested here): retail's f[2] address
//   is 3 words because the base is loaded into its own register (r11) and the
//   `+8` is folded into a SEPARATE `addi` on the sum.  §6dq-2's "reassign the
//   pointer so the old value is dead" is the documented route for getting a
//   `lwzu`-style dead-old-value web - try it on `p2` (reassign `p2` from itself
//   rather than naming a second `p3`).
//

//  A. `tog` lives in r8, retail uses r7 - 4 words (`li`, `xori`, `cmpwi cr4`,
//     `or.`).  Every C spelling and the direct pin both fail; a volatile-reg
//     choice this is not reachable from source.
//  B. the two rodata page anchors are r9/r11, retail uses r11/r8 - 2 words.
//     (Only the REGISTER is compared: ADDR16_HA/LO and HI/LO are both masked to
//     0xFFFF0000, so `extern f32 x;` vs `extern f32 x[];` is invisible here -
//     the array declarations are kept only to match the sibling's spelling.)
//  C. the loop-head 6-word window: retail interleaves
//     `xoris / stw lo / lwz base / stw hi / add / lfd f1` while ngccc emits
//     `xoris / stw hi / stw lo / lfd f0 / lwz base / fsub / frsp f1,f0 / add`,
//     i.e. it schedules the HI store of the loop-invariant 0x43300000 constant
//     early and the ctr double load into f0 (retail keeps it in f1, giving
//     `frsp f1,f1` instead of `frsp f1,f0`).
//  D. the trig multiply operand order at both sites - 4 words, see the
//     "not reachable" note above.
//  E. one extra base reload in the f[1] negate arm - 1 word, plus the
//     sin-half 15-word interleave: retail's `lwz/add/addi` for f[2] (3 insns)
//     against ngccc's `lwz/add` + `stfs 8(r29)` (2), the ctr/arg1 hi store
//     positions, and the `mr r10,r11` that retail keeps as a provably dead
//     copy (doc-33 / §6x-89 family).
//  F. `cmpwi r31,0` and `addi r25,0x10` are in the right order but the latch's
//     `lwz r9,0x64(r28)` is one slot early - 2 words.
//
// BEST THEORY OF THE BLOCKER: nothing semantic is left - every callee
// signature is right (Mem_Alloc/Mem_Free2/cosf/sinf all audited against
// symbols.txt and the prologues), every constant decodes right, the struct
// members are right, the register roles are right and the frame/save areas are
// right.  The whole residual is (a) one volatile-register choice for `tog`,
// (b) the operand order of a commutative MULT_EXPR, and (c) a 20-instruction
// store/load scheduling window inside the sin half in which ngccc schedules
// the loop-invariant `0x43300000` half of the cvt pair earlier than retail
// and collapses retail's 3-instruction f[2] address.  NEXT TO TRY:
//   * force the f[2] address to be 3 instructions (a `+r` barrier on the slot
//     pointer, or an explicit `pf = pf0 + 8;` from a second named base) - the
//     extra instruction it costs has to be paid back by killing the `fmr f0,f1`
//     after `sinf`, which needs the sin product to share the divisor's
//     register; the two together are the only untried pairing.
//   * `volatile s32` on a slot pointer (recipe §6al-180) to make ngccc
//     rematerialize `arg0->unk0x64` per store, in case that is what splits
//     retail's 4 base reloads from ngccc's 5.
//   * a per-object `-fno-rerun-cse-after-loop` (never tried here; this function
//     has a loop and two CSE-able cvt pairs, and it is the pass that could own
//     residual C).
//
// AUDIT of the current 60.63% body (so a future round does not re-verify it):
//   object .text = 508 B = 127 insns = retail size 0x1FC exactly; the header
//   marker `range=0x800BD770-0x800BD96C size=508B` agrees with symbols.txt
//   (`fn_800BD770 = .text:0x800BD770; size:0x1FC`).  REL24 targets are
//   Mem_Free2 / Mem_Alloc / cosf / sinf - all four match the retail `bl`s.
//   REL14: 9 relocations, 8 land on retail's branch target; the 9th is
//   `bne cr4` at 0x800BD89C, which wants 0x800BD8A8 and gets 0x800BD8B0 - the
//   1-instruction shift of residual E, not a structural error.  The body is
//   semantically sound: the inner latch decrements `ctr` (r31), the outer latch
//   tests `next_tog` (r24), and there is NO trace of the "latch decrements the
//   base pointer" corruption the inherited header warned about.
//   Inline asm: 3 empty-template barriers, ZERO emitted instructions.
#include "types.h"
#include "structs.h"

extern void Mem_Free2(void *);
extern void *Mem_Alloc(s32);
extern f32 cosf(f32);
extern f32 sinf(f32);
extern f64 lbl_80298E50[];
extern f32 lbl_80298E58[];
extern f32 lbl_80298E5C[];

void fn_800BD770(Unk_8A4B2B78 *arg0, s32 arg1, f32 farg0in, f32 farg1in,
                f32 farg2in) {
    register f32 farg0 __asm__("fr26") = farg0in;
    register f32 farg1 __asm__("fr27") = farg1in;
    register f32 farg2 __asm__("fr28") = farg2in;
    struct {
        char pad0x40[0x40];
        union {
            u32 w[2];
            f64 d;
        } cvt;
    } fr;
    register u32 var_r9 __asm__("r9");
    register f64 magic __asm__("fr31");
    f32 scale;
    register f32 c58 __asm__("fr30");
    register f32 c5c __asm__("fr25");
    f32 v;
    f32 vc;
    f32 vb;
    register s32 pf __asm__("r29");
    s32 temp_r3;
    s32 temp_r30;
    s32 tog;
    register s32 next_tog __asm__("r24");
    register s32 off __asm__("r25");
    register s32 cur __asm__("r30");
    u32 ctr;

    arg0->unk0x94 = (u16)(arg1 * 2);
    if (arg0->unk0x64 != 0) {
        Mem_Free2((void *)arg0->unk0x64);
    }
    temp_r30 = arg0->unk0x94;
    temp_r3 = (s32)Mem_Alloc(temp_r30 * 0x10);
    var_r9 = temp_r30 - 1;
    if ((s32)temp_r30 != 0) {
        while (var_r9-- != 0) {
        }
    }
    __asm__ __volatile__("" : : "r"(temp_r30));
    arg0->unk0x64 = temp_r3;
    tog = 0;
    off = 0;
outer_test:
    __asm__("" : "+r"(arg1));
    ctr = (u32)(arg1 - 1);
    next_tog = tog ^ 1;
    if (arg1 == 0) {
        goto outer_latch;
    }
    {
        s32 hi = 0x43300000;
        fr.cvt.w[0] = hi;
        fr.cvt.w[1] = (u32)arg1 ^ 0x80000000;
        magic = lbl_80298E50[0];
        scale = (f32)(fr.cvt.d - magic);
        c58 = lbl_80298E58[0];
        c5c = lbl_80298E5C[0];
        cur = off;
        do {
            fr.cvt.w[0] = hi;
            fr.cvt.w[1] = (u32)ctr ^ 0x80000000;
            vc = (f32)(fr.cvt.d - magic);
            vc = vc + vc;
            vc = vc * c58;
            vc = vc / scale;
            pf = (s32)(char *)(cur + (s32)arg0->unk0x64);
            vc = cosf(vc);
            if (tog != 0) {
                vc = farg0 * vc;
            } else {
                vc = farg1 * vc;
            }
            *(f32 *)pf = vc;
            *(f32 *)((char *)(cur + (s32)arg0->unk0x64) + (s32)0x4) = farg2;
            if (tog == 0) {
                *(f32 *)((char *)(cur + (s32)arg0->unk0x64) + (s32)0x4) = -farg2;
            }
            __asm__("" : "+r"(ctr));
            fr.cvt.w[0] = hi;
            fr.cvt.w[1] = (u32)ctr ^ 0x80000000;
            v = (f32)(fr.cvt.d - magic);
            v = v + v;
            __asm__("" : "+r"(arg1));
            fr.cvt.w[0] = hi;
            fr.cvt.w[1] = (u32)arg1 ^ 0x80000000;
            vb = (f32)(fr.cvt.d - magic);
            v = v * c58;
            v = v / vb;
            pf = (s32)(char *)(cur + (s32)arg0->unk0x64) + (s32)0x8;
            v = sinf(v);
            if (tog != 0) {
                *(f32 *)pf = farg0 * v;
            } else {
                *(f32 *)pf = farg1 * v;
            }
            off += 0x10;
            *(f32 *)((char *)(cur + (s32)arg0->unk0x64) + (s32)0xC) = c5c;
            cur += 0x10;
        } while (ctr-- != 0);
    }
outer_latch:
    tog = next_tog;
    if (tog) {
        goto outer_test;
    }
}