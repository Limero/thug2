// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800301A0-0x80030290 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802919C0;
extern f32 lbl_802919C4;
extern f32 lbl_802919C8;
extern f32 lbl_802919CC;
extern f32 lbl_802919D0;
extern f32 lbl_802919D4;
extern f32 lbl_802919D8;
extern f32 lbl_802919DC;
extern f32 lbl_802919E0;
extern f32 lbl_802919E4;
s32 fn_800301A0(s32 arg0, f32 farg0) {
    register f32 t __asm__("fr0");
    s32 r0;

    r0 = 0;
    switch (arg0) {
    case 0:
        if (farg0 == lbl_802919C0) {
            break;
        }
        if (farg0 == lbl_802919C4) {
            goto one;
        }
        if (farg0 != lbl_802919C8) {
            break;
        }
        r0 = 2;
        break;
    case 1:
        if (farg0 == lbl_802919CC) {
            break;
        }
        t = lbl_802919C8;
        goto cmp;
    case 2:
        if (farg0 == lbl_802919D0) {
            break;
        }
        t = lbl_802919D4;
        goto cmp;
    case 3:
        if (farg0 == lbl_802919D8) {
            break;
        }
        t = lbl_802919DC;
        goto cmp;
    case 4:
        if (farg0 == lbl_802919E0) {
            break;
        }
        t = lbl_802919E4;
    cmp:
        if (farg0 != t) {
            break;
        }
    one:
        r0 = 1;
        break;
    }
    return r0;
}
// ---- fix log (all measured) -------------------------------------
// baseline m2c body: 6.67% (56/60 words differ), 240B, 0 relocs wrong
//  (1) extern f32 lbl_XXXX for all ten .rodata2 data:float symbols.  The
//      draft's *(f32 *)0x8029xxxx literals emitted lis+ori+lfs 0(reg); the
//      symbol form emits lis@ha + lfs@l(r9) == want, and each load keeps its
//      OWN anchor (want has eight `lis r9,-0x7fd7`).
//  (2) case 0's third test was `if (farg0 == *(s32 *)0x802919C8)` — an
//      (s32) load of a float constant, which made cc1 synthesize a whole
//      int->double conversion (lis 0x4330 / xoris / stw pair / lfd / fsub /
//      frsp) and compare in f12.  With a real f32 symbol it is a plain lfs.
//  (3) m2c had `return var_r0;` plus a labelled early exit -> two identical
//      `mr r3,r0; blr` epilogues (+2 words).  Rewriting every early exit as
//      `break` out of the switch and keeping ONE `return r0;` merges them:
//      252B -> 244B.
//  (4) the shared tail is one `fcmpu` at 0x8003027C reached by `goto cmp`
//      from cases 1/2/3 and by fall-through from case 4; case 0's second test
//      branches straight to `one:`.  Restructured to match (m2c's label
//      placement put the compare in the wrong block).
//  (5) register f32 t __asm__("fr0")  — 244B -> 240B, 0% -> 100%.
//      FPR colour fix, ZERO emitted instructions.  Without the pin cc1's
//      global_alloc gave the short-lived `t` the incoming arg register f1 and
//      pushed the long-lived float param to f13, costing an `fmr f13,f1` at
//      offset 0 (which also mis-aligned all 60 words).  fr0 restores
//      (farg0=f1, t=f0) == want.  fr2 is 91.67% (5 words differ: the anchor
//      block and one branch).  Pinning the PARAMETER (`register f32 farg0
//      __asm__("fr1")`) is a hard COMPILE FAIL in cc1 2.95.2.
