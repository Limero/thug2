// FPR-frame fix: volatile double dummy (issue 01, M4.92)
// WIP DRAFT (NEAR 72.0%) — stub rewritten from the want; whole body
// re-derived (real Slot struct, real prototypes, real frame template).
// family=m2c range=0x8011AACC-0x8011AC40 size=372B
// PARKED 2026-10-02 (w75/0x8011AACC): object is 372 B = symbols.txt size, and
// the whole body/control-flow/frame-tail matches want; the ONLY residual is that
// ngccc's loop-invariant motion hoists TWO loop-invariant address computations
// into the loop preheader that retail recomputes inside the loop body:
//   (1) `addi rX, rBase, 0x18`  -> want has it at 0x8011AB50, in-loop
//       (the base for the `lfsx f1, rX, r31` load of slot->f18; PPC lfsx has no
//        displacement, so base+0x18+IV must be materialised somewhere)
//   (2) `lis rY, 0x8029`        -> want has it at 0x8011AB54, in-loop
//       (the address of lbl_8029D520, whose f32 is loaded into f31 and compared
//        twice: fcmpu f1,f31 at 0x8011AB60 and fcmpu f13,f31 at 0x8011AB74)
// Hoisting (1) costs the 8th callee-saved GPR: got saves r24..r31 (stmw r24,0x20)
// where want saves r25..r31 (stmw r25,0x24), and the 2 extra preheader words
// shift the loop head by 8 bytes, which is what the 28% residual is made of.
// Tried: `c` local vs direct global read (needs the local, or GCC reloads the
// float twice into f0 and the FPR frame collapses to one stfd); `const`
// lbl_8029D520 (CSEs the two loads but flips GCC to a single pointer IV, losing
// retail's lwzx/lfsx + separate &next IV mix); `volatile` global/local; frame
// template tail pad 12/16/20/24/28 (16 and 20 both give the exact 0x50 frame);
// 1 vs 2 `volatile double _dummy`; -fno-gcse (hoists survive -> not GCSE);
// array bound [0x3B]; for/while/while; `continue` vs nested-if (the nested-if
// `if (id == arg1) { ... }` shape is what reproduces retail's loop rotation);
// u32 vs s32 index; swapped compare operands; i<0x3B. Best = 72.0%.
// Applies to: any ngccc loop with >=2 distinct constant field offsets off one
// array IV plus a loop-invariant global read inside the body.
#include "types.h"
#include "qb_constants.h"
typedef struct Slot Slot;
struct Slot {
    s32   id;
    s32   id2;
    Slot *next;
    s32   u0C;
    s32   u10;
    f32   f14;
    f32   f18;
    s32   u1C;
    f32   f20;
    char  rest[0x3C - 0x24];
};
extern Slot lbl_80387E44[];
extern s32 fn_80119470(void);
extern s32 fn_8011ED40(s32);
extern void fn_80119668(void *, f32);
extern s32 fn_8011970C(void *);
extern void fn_8011A450(s32, void *, f32 *, Slot *);
extern void fn_8011ED64(s32, void *, f32);
extern s32 Script_GetInteger(s32, s32);
extern f32 lbl_8029D520;
extern f32 lbl_8029D524;
extern bool lbl_802FFE58;
s32 fn_8011AACC(s32 arg0, s32 arg1, void *arg2, f32 farg0) {
    struct { f32 v; char pad[20]; } fr;
    f32 k;
    s32 i;
    Slot *n;
    f32 f0;

    fr.v = farg0;
    if (fn_80119470() != 0) {
        return 1;
    }
    k = lbl_8029D524;
    for (i = 0; i <= 0x3A; i++) {
        if (lbl_80387E44[i].id == arg1) {
            if (fn_8011ED40(i) != 0) {
                if (fn_8011970C(arg2) == 0) {
                    f32 c = lbl_8029D520;
                    if (lbl_80387E44[i].f18 != c) {
                        fn_80119668(arg2, lbl_80387E44[i].f18);
                    }
                    if (lbl_80387E44[i].f14 != c) {
                        fr.v = fr.v * lbl_80387E44[i].f14 * k;
                    }
                }
                n = lbl_80387E44[i].next;
                if (n == NULL) {
                    return 0;
                }
                if (fn_8011970C(arg2) == 0) {
                    fn_8011A450(arg0, arg2, &fr.v, n);
                }
                f0 = fr.v * n->f20 * k;
                fr.v = f0;
                fn_8011ED64(i, arg2, f0);
                return 1;
            }
            break;
        }
    }
    if (lbl_802FFE58 == 0) {
        Script_GetInteger(QB_UNKNOWN_0x6D2E270E, 0);
    }
    return 0;
}
