// PARKED 2026-09-30: 78.9% -> 84.2%
// family=m2c range=0x800A9200-0x800A9298 size=152B
// FLAG: -mps-float -fno-schedule-insns2
// INERT: not registered in splits.txt/configure.py - never compiled, not
// counted in objdiff progress.  activate via tools/wip.py.
//
// SIGNATURE: caller at 0x800A93E8 passes only the object pointer in r3.
// Semantics (hand-decoded from the op-4 words with tools/ps_diff.py's dec()):
//   d0 = v80-v08 ; d1 = v88-v10 ; out[4]=d0 ; out[5]=d1 ;
//   s = d0.d0^2 + d0.d1^2 + d1.d0^2 + d1.d1^2 ; if (s > lbl_80298214) {
//   out[4] = d0 * rsqrte(s) ; out[5] = d1 * {rsqrte(s), lbl_80298218} }
//   i.e. a 2D normalize.  obj .text = 152B == want == symbols.txt size:0x98.
//
// WHAT THIS ROUND CHANGED (78.9% -> 84.2%, 2 diffs):
//  The merge00 operand `lbl_802981C0` was an inline argument of
//  the pair-merge builtin, which let cc1 sink its constant pair load to the
//  very end of the window and transpose the store/copy pair. Giving the
//  operand its OWN named statement placed BEFORE the `a = v` copy and
//  before the out[5] store -
//      v = loc[1]; zc = lbl_802981C0; a = v; *(...*)&out[5] = v;
//      t = ps_mul(a,a); t = ps_merge00(t, zc);
//  - makes cc1 emit that window in exact source order, i.e. it cut the
//  mid-window diff from 4 words to 2. The register pin on zc is NOT
//  load-bearing (unpinned scores 84.2% too), so zc is left plain.
//
// RESIDUAL (6 of 38 words):
//  (A) HEAD, first four words - unchanged this round. Only one constant
//      address setup is misplaced (the high half of the page reference);
//      the low half already sits at the expected position. The setup is
//      hoisted to the block top and no C shape moves it.
//  (B) two middle words - a 3-element rotation around the pair copy:
//      the pair store, the pair copy and the constant reload come out in
//      source order here, while the original has the store first. Every
//      source order that would put the store first is re-sorted by cc1
//      (see dead ends).
//
// LEVERS MEASURED THIS ROUND (all on top of the 78.9% body unless noted):
//  Constant address setup as inline asm with an extern page symbol, a fixed
//  page register, and a paired-single view of the load:
//    setup both volatile, out-wedge in its original spot   65.8%
//    setup both volatile, out-wedge moved after the v10 load  76.3%
//    setup non-volatile (gets sunk back to block top)       84.2% (== best)
//    high half volatile + low half non-volatile             65.8%
//    high half non-volatile + low half volatile             65.8%
//    both volatile + float dependency inputs                65.8% / 60.5%
//    (the volatile asms lose the out-pointer pin and
//     re-block the whole head - confirms the old header's note)
//  Literal-page anchor: page base then subtract 0x7E40 -> folds to the wrong
//  constant encoding, so the address is wrong: 81.6%.
//  Source reorderings of the [store | copy | zc-load | mul] window, all
//  measured: zc after the copy 78.9% | zc after the mul 78.9% | zc before
//  the copy 84.2% | zc between copy and store 84.2% | zc inside the
//  out[5] store's comma RHS 78.9% | out[5] store nested in the copy's
//  comma RHS 84.2% | zc nested in a 3-term comma 84.2%.  The 84.2%
//  variants all emit a BYTE-IDENTICAL object.
//  Zero-code levers that were no-ops here: `volatile` on any/all of the
//  four head PS loads (84.2%, identical object), a `"memory"` fence as
//  the first statement (78.9%), `zc` as the first statement of the
//  function (DIFF - collapses the out-pointer base), `zc` as a
//  `*(volatile __ps_t *)&lbl` read (78.9%).
//
// KEEP (measured, do not undo):
//  the float flag set and the scheduler flag (scheduler flag alone scores low);
//  the two stack scratch pair slots as a volatile pair array with the
//  second-slot reload read through a named temp; out base = arg0+0x20 held
//  in a fixed register written as out[4]/out[5] (the real fields are +0x40/+0x48);
//  the tail union as a volatile pair/float view with the scalar in the low lane;
//  multiply plus its store BEFORE the spill; fixed float registers for the
//  input loads and temps, fixed register for the out base; and the ONE
//  zero-code output wedge that stops cc1 folding the base into the store
//  displacement (without it the schedule collapses to 10.5%).
//
// AUDIT of the 84.2% body: object text size matches the symbol size;
// object has ONLY text plus relocations (no private read-only data,
// so a masked-exact result would also be promote-clean); inline
// asm emits zero instructions (one zero-code output wedge plus register
// variable pins); the single branch relocation target matches the expected
// end-of-function branch, so the control-flow extent is verified; there
// are no call relocations (the original has no calls); the three constant
// address pairs all resolve to real symbol addresses, so the address
// hazard cannot apply.
#include "types.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU;

typedef struct {
    char pad0x00[0x08];
    __ps_t v08;
    __ps_t v10;
    char pad0x18[0x68];
    __ps_t v80;
    __ps_t v88;
} OBJ;

extern __ps_t lbl_802981C0;
extern f32 lbl_80298214;
extern f32 lbl_80298218;

void fn_800A9200(OBJ *arg0) {
    volatile OBJ *vo = arg0;
    register __ps_t a __asm__("fr11");
    register __ps_t b __asm__("fr12");
    register __ps_t c __asm__("fr13");
    __ps_t vv88;
    __ps_t d0;
    register __ps_t d1 __asm__("fr0");
    volatile __ps_t loc[2];
    volatile PSU rr;
    __ps_t t;
    register __ps_t v __asm__("fr0");
    __ps_t zc;
    PSU dot;
    register __ps_t *out __asm__("r10");

    a = vo->v10;
    b = vo->v80;
    c = vo->v08;
    vv88 = vo->v88;
    d0 = __builtin_ps_sub(b, c);
    d1 = __builtin_ps_sub(vv88, a);
    __asm__("" : "=r"(out) : "r"((char *)arg0 + 0x20));
    loc[0] = d0;
    loc[1] = d1;
    *(volatile __ps_t *)&out[4] = d0;
    v = loc[1];
    zc = lbl_802981C0;
    a = v;
    *(volatile __ps_t *)&out[5] = v;
    t = __builtin_ps_mul(a, a);
    t = __builtin_ps_merge00(t, zc);
    t = __builtin_ps_madd(d0, d0, t);
    dot.ps = __builtin_ps_sum0(t, t, t);
    if (dot.flt.hi > lbl_80298214) {
        __ps_t r = __builtin_ps_rsqrte(dot.ps);
        register __ps_t r13 __asm__("fr13");
        register __ps_t res __asm__("fr0");
        *(volatile __ps_t *)&out[4] = __builtin_ps_muls0(d0, r);
        rr.ps = r;
        rr.flt.lo = lbl_80298218;
        r13 = rr.ps;
        res = __builtin_ps_mul(a, r13);
        *(volatile __ps_t *)&out[5] = res;
    }
}
