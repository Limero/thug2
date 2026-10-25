// PARKED 2026-10-03 (b54): NEAR 51.3% (baseline was DIFF 8.8%).
// Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8007EFE0
// (`tools/want_vs_got.py 0x8007EFE0` for the word diff.)
//
// WHAT CHANGED / WHY IT IS NOW NEAR
// The m2c draft was pure filler (8.8%). The body below is a hand
// reconstruction from `tools/ps_disasm.py` + `tools/ps_diff.py` (plain
// capstone 5.0.7 cannot decode Gekko opcodes 56/60 or opcode-4 A-forms and
// prints them as `.word` / bogus VMX mnemonics — see docs/parkings/06).
// Three changes did essentially all of the work:
//   1. Obj field offsets fixed: m2c's `unk0x38/0x3C/0x40` sat 4 bytes low
//      (it modelled the 0x38 f32 triple as s32 and lost the 4-byte pad at
//      0x34). Correct pad chain makes `this` in r30 -> r31 and the three
//      `lfs/stfs` land on 0x38/0x3C/0x40.
//   2. `Mem_Alloc` is 1-arg (see src/fn_80009A78.c); m2c's 3-arg proto was
//      phantom. Same for the vtable: each slot is {s16 adjustor, s32 fn} at
//      +0x128/+0x12C, +0x130/+0x134, +0x140/+0x144 -> `lha`+`lwz`+`add`+
//      `mtlr`+`blrl` with the calls written INLINE (`arg0->vt->fn0(...)`)
//      so `lwz r9,0x14(r31)` is re-materialised before each call, as retail does.
//   3. The two delta values MUST be a 2-element `__ps_t d[2]` array, not two
//      separate `__ps_t` scalars. As scalars ngccc homes them in callee-saved
//      f30/f31, saves them with `stfd` in the prologue, and the frame grows
//      0x28 -> 0x38 with an extra saved GPR (328B/336B output). As an array
//      the delta spills are `psq_st` to 8(r1)/16(r1), no FPR save at all,
//      and .text size becomes EXACTLY 304B == the symbol size.
// Result: prologue, epilogue, all 12 words of the prologue/return, the PS
// block, the three vcall sequences and the PS loop are instruction-for-
// instruction correct; only colouring/loop-shape differences remain.
//
// CONCRETE REMAINING DIFF (51.3%, .text 304B == want 304B)
//  (a) GPR colouring swap, worth ~12 words: retail keeps `this` in **r31**
//      and the count in **r30**; this draft gets **r30**/**r31** swapped.
//      Every `mr/add/lwz ... r30` vs `r31` mismatch in the diff is this one
//      cause. This is the generic ProDG callee-saved-GPR colouring tie-break
//      (doc 06 "M5.0o/M5.0r class"), not a semantics bug.
//  (b) The dead count-down loop after `Mem_Alloc`. Retail compares the count
//      in r30 against zero, steps a copy in r9 down by one and exits to the
//      label L84, then in the self-targeting latch labelled L78 re-compares
//      r9 against zero, steps it down again and branches back to L78.
//      ngccc recognises this as a counted loop and emits
//        cmpwi r31,0 ; beq ; addi r0,r31,-1 ; mtctr r0 ; bdnz     (5 vs 6 words)
//      Tried and rejected: `while (i != 0) i--;` -> mtctr + a dead `beq`
//      after `bdnz` (308B); m2c's own `c = (i==0); i -= 1; while (!c);`
//      -> strength-reduced to `subfic/adde` (320B). The retail `cmpwi/addi/
//      bne` self-loop is a rotated do-while latch that ngccc will not
//      produce once it has matched the induction variable to CTR.
//      NOTE (b) and (a) are the same root cause: while the loop induction is
//      tied to the count register, the count keeps the higher saved reg.
//  (c) PS register choice inside the second loop. Retail reloads the deltas
//      into **f11/f12** and walks the array in **f0/f13**, loading both
//      deltas up front; this draft reloads into f0/f12 and loads the second
//      delta between the two `ps_add`s (`e0010008`, `ps_add f13,f13,f0`,
//      `psq_st f13,0(r9)`, `e0010010`, `ps_add f12,f12,f0`, ...).
//      Semantics are identical; it is an FPR-colouring/scheduling tie-break.
//
// RULED OUT (don't redo these)
//  * `-msdata=eabi` / SDA21 masking — irrelevant here; the residual is real.
//  * Declaring the deltas as separate `__ps_t` locals: forces callee-saved
//    f30/f31 homes -> `stfd` prologue -> 328B (documented above).
//  * `volatile double _dummy` frame padding: the frame is ALREADY correct
//    (0x28, LR at 0x2c, stmw r29 at 0x1c) after the array change; the +8
//    issue-01 FPR quirk is not in play because retail saves no FPR here.
//  * Reordering the PS block or the lfs/stfs run: it is already
//    instruction-for-instruction identical to retail in that region.
//  * The op4 words at 0x8007F024/0x8007F030 are **ps_sub** (xo5=20) and the
//    two at 0x8007F0C0/0x8007F0C4 are **ps_add** (xo5=21) -- not merges,
//    not VMX. `ps_sub`/`ps_add` on `__ps_t` reproduce them exactly.
//
// MOST PROMISING NEXT IDEA
// Attack (b) first: it is the only *structural* (not colouring) diff and it
// appears to be coupled to (a). Any source shape that stops ngccc from
// matching the countdown to CTR (e.g. making the induction variable a value
// ProDG cannot prove constant-trip, or naming the loop through a pointer the
// optimiser does not trace) should simultaneously drop the loop to the
// retail `cmpwi/addi/bne` form and free the higher saved register for `this`.
//
// family=m2c range=0x8007EFE0-0x8007F110 size=304B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// Retail shape (tools/ps_disasm.py + tools/ps_diff.py decode; capstone 5.0.7
// mislabels the Gekko psq_* opcodes 56/60 and opcode-4 A-forms as ".word"):
//   if (this->unk30) { fn_80024FDC(this->unk30 + 0x38, arg1); return; }
//   d0 = arg1[0] - this[0x38]      (psq_l/psq_l/ps_sub, spill to 8(r1))
//   d1 = arg1[1] - this[0x40]      (psq_l/psq_l/ps_sub, spill to 16(r1))
//   this[0x38] = arg1[0..1]; this[0x40] = arg1[2]     (lfs/stfs run)
//   n = vt->fn0(this + vt->adj0)
//   buf = Mem_Alloc(n * 16)
//   if (n) { empty count-down loop }
//   vt->fn1(this + vt->adj1, buf)
//   if (n > 0) for (i=0;i<n;i++) { p[0] += d0; p[1] += d1; p += 2; }   (mtctr/bdnz)
//   vt->fn2(this + vt->adj2, buf)
//   Mem_Free(buf)
#include "types.h"
#include "mem.h"

void fn_80024FDC(__ps_t *, __ps_t *);
void *Mem_Alloc(s32);
void Mem_Free(void *);

typedef struct Vt_8007EFE0 {
    char pad0x0[0x128];
    s16 adj0;
    void *fn0;
    s16 adj1;
    void *fn1;
    char pad0x138[0x8];
    s16 adj2;
    void *fn2;
} Vt_8007EFE0;

typedef struct Obj_8007EFE0 {
    char pad0x0[0x14];
    Vt_8007EFE0 *vt;
    char pad0x18[0x18];
    void *unk30;
    char pad0x34[4];
    f32 v38;
    f32 v3c;
    f32 v40;
} Obj_8007EFE0;

void fn_8007EFE0(Obj_8007EFE0 *arg0, f32 *arg1) {
    s32 n;
    s32 i;
    void *buf;
    __ps_t d[2];
    __ps_t *p;
    f32 ax;

    if (arg0->unk30 != 0) {
        fn_80024FDC((__ps_t *)arg0->unk30 + 7, (__ps_t *)arg1);
        return;
    }
    ax = arg1[0];
    d[0] = *(__ps_t *)arg1 - *(__ps_t *)&arg0->v38;
    d[1] = *(__ps_t *)(arg1 + 2) - *(__ps_t *)&arg0->v40;
    arg0->v38 = ax;
    arg0->v3c = arg1[1];
    arg0->v40 = arg1[2];
    n = ((s32(*)(void *))arg0->vt->fn0)((char *)arg0 + arg0->vt->adj0);
    buf = Mem_Alloc(n * 16);
    if (n != 0) {
        i = n - 1;
        do {
            i = i - 1;
        } while (i != 0);
    }
    ((void (*)(void *, void *))arg0->vt->fn1)((char *)arg0 + arg0->vt->adj1, buf);
    p = (__ps_t *)buf;
    if (n > 0) {
        for (i = 0; i < n; i++) {
            p[0] = p[0] + d[0];
            p[1] = p[1] + d[1];
            p += 2;
        }
    }
    ((void (*)(void *, void *))arg0->vt->fn2)((char *)arg0 + arg0->vt->adj2, buf);
    Mem_Free(buf);
}