// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025ABC4-0x8025ABEC (40B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
/*
VERIFIED 2026-09-25: the retail range is exactly 40 bytes:
  mflr r30; lbz r3,0x707(r31); lis/ori r4,0x704; lhbrx r4,r4,r31;
  lwz r5,0x708(r31); cmplwi r3,0xff; beq +4; mtlr r30; blr.
There is no stwu or LR-stack save, and the function never initializes r31.
The surrounding context-save/restore blob uses r31 as the live context base
(the nearby restore path reads and reloads the saved register frame from
0x8025AD88 onward), so r31 is a caller-carried input, not a local pointer.

This is a hand-written context-switch fragment rather than ordinary
compiler output. A bounded ProDG reconstruction uses a naked function and
file-scope r30/r31 register variables; C supplies the two normal loads and
argument staging. Inline asm is limited to the instructions with no ordinary
C lowering here: mflr/mtlr, lhbrx, and the one provably-dead beq-to-next.
The .long is the single-word encoding 0x41820004, not a whole-body
transcription. Standalone gen_leaves.compile_fn verification is byte-exact
for all 10 words. The remaining integration blocker is the dtk slice boundary:
this symbol is entered with caller-owned r31 from the hand-written context
blob, so the exact object is not evidence that it can be registered as an
ordinary standalone C function. Keep this draft inert; do not promote from
this worker.
*/
register s32 *ctx_r31 __asm__("r31");
register s32 lr_r30 __asm__("r30");

__attribute__((naked)) void Vtable0x80308A40_m17(void) {
    register s32 tag __asm__("r3");
    register s32 seq __asm__("r4");
    register s32 word __asm__("r5");

    __asm__ volatile("mflr %0" : "=r"(lr_r30));
    tag = *(u8 *)((char *)ctx_r31 + 0x707);
    __asm__ volatile("" : : "r"(tag));
    __asm__ volatile("lis %0,0\n\tori %0,%0,0x704\n\tlhbrx %0,%0,%1"
                     : "=&r"(seq) : "r"(ctx_r31));
    word = *(u32 *)((char *)ctx_r31 + 0x708);
    __asm__ volatile("" : : "r"(word));
    __asm__ volatile("cmplwi cr0,%0,0xff" : : "r"(tag) : "cr0");
    __asm__ volatile(".long 0x41820004");
    __asm__ volatile("mtlr %0" : : "r"(lr_r30));
}
