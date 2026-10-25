// WIP DRAFT — hand-written from disassembly (PARKED)
// family=hand range=0x8025AEEC-0x8025AF18 size=44B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
/*
UPDATED 2026-09-25 — boundary/ABI verification; semantic C retained below.
PARK ANALYSIS (fragment of one hand-written system asm routine):
WANT is exactly 11 words (0x8025AEEC..0x8025AF18):
  lbz r5,0x6D8(r31); cmpwi r5,0; beq skip
  addi r4,r31,0x6D9
  bl 0x8025AF3C
  li r5,0; stb r5,0x6D8(r31)
  skip:
  lwz r3,0x370(r31); addi r3,r3,4; stw r3,0x370(r31)
  b 0x8025AD64

Verified boundary facts:
  * the first word is a load through r31; there is no stwu, mflr, LR save,
    or any other prologue, so r31 is an incoming/context register here;
  * a .text branch/call scan found no direct b/bl to 0x8025AEEC. The symbol
    is an entry fragment of the surrounding hand-written context blob, not a
    normal standalone call target;
  * 0x8025AF3C is exactly 0x8025AF18 + 0x24, an interior label of
    fn_8025AF18, not its callable entry. There is no lbl_8025AF3C in
    symbols.txt; the C call below is only a semantic placeholder;
  * the final b targets the beginning of Vtable0x80308A40_m5 (0x8025AD64),
    and is a non-returning raw branch, not a C return/blr.

Technical blockers for a correct standalone C function:
  1. An ordinary C call to fn_8025AF18 would execute its strlen prefix;
     a call to lbl_8025AF3C has no linkable symbol and cannot express the
     interior entry. The interior target actually consumes str in r4 and
     len in r5 (r3 is overwritten), so the placeholder prototype below uses
     an ignored leading arg to model that entry ABI;
  2. a normal return/ tail call cannot emit the required raw branch to
     Vtable0x80308A40_m5, and normal C containing a bl grows a frame plus
     mflr/stw/mtlr/blr, shifting every word;
  3. a file-scope r31 register variable makes the context loads frameless
     (the same technique works in fn_8025AF7C), but it does not change
     either the interior call entry or the external branch.

Bounded attempts (not retained): plain semantic C compiled to 72B and
scored 0.0% because its 8-byte frame shifts the 44B target; a diagnostic
naked C form with a 3-argument placeholder call and an asm tail edge
reached only 30.8%, and the unprototyped-call form reached 27.3%. A
second diagnostic form using only one-asm `bl` and one asm `b` reproduced
the first 11 masked words (91.7% of a 48B object), but still appended a
compiler `blr` and left the undefined lbl_8025AF3C relocation. That is
partial asm transcription, not a valid C solution.
Root cause is the hand-written context/console blob sliced by dtk
boundaries; park until a new representation for the interior entry and
non-returning branch is available. Do not grind store/register permutations.
*/
register s32 *ctx_r31 __asm__("r31");

extern void lbl_8025AF3C(s32 unused, s32 str, s32 len);

void fn_8025AEEC(void) {
    register s32 n __asm__("r5");
    register s32 arg __asm__("r4");
    register s32 w __asm__("r3");

    n = *(u8 *)((s32)ctx_r31 + 0x6D8);
    if (n != 0) {
        arg = (s32)ctx_r31 + 0x6D9;
        lbl_8025AF3C(0, arg, n);     /* interior entry: r4=str, r5=len */
        n = 0;
        *(u8 *)((s32)ctx_r31 + 0x6D8) = (u8)n;
    }
    w = *(u32 *)((s32)ctx_r31 + 0x370);
    w += 4;
    *(u32 *)((s32)ctx_r31 + 0x370) = w;
    /* WANT: b 0x8025AD64 — raw external branch, falls through here */
}
