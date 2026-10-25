// WIP DRAFT — hand-rebuilt from the want (m2c body was a placeholder).
// family=m2c range=0x8001CA68-0x8001CB60 size=248B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-04: DIFF, 140 B / 29 of 62 words = 17.1%
//   (up from the m2c husk's 100 B / 22 diffs = 12.0%). NOT promotable.
//   Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//         tools/want_got.py 0x8001CA68        # word-level want|got
// The m2c body this replaces was `fill_wip_drafts.py` filler: a bogus
// 4-term `&&` chain built from constant `0`s and an EMPTY `if` body, which
// compiled to 100 B of a 248 B function — i.e. most of the function was simply
// absent, so this was a DECODE job, not a scheduling one. The real function is
// fully decoded below and this body is the reconstruction; the three residual
// causes and every variant measured are at the bottom of this header.
//
// WHAT IT IS (decoded with tools/vdis-style capstone dump, because the
// bundled disassembler stalls nowhere here - this function is integer-only,
// no PS words):
//   frame -0x40, stmw r29/0x34, LR 0x44  =>  10 callee-saved-ish slots,
//   locals 0x8..0x33.  Stack slots actually used:
//     sp+0x08  s32   (arg1 AND arg5 of call 3 - the SAME slot, see below)
//     sp+0x09  u8    (call 3 arg3)
//     sp+0x0a  u8    (call 3 arg4)
//     sp+0x0c  s32   sp+0x10 s32  sp+0x14 s32  sp+0x18 s32   (call 1 out-params)
//     sp+0x1c  s32   sp+0x20 s32  sp+0x24 s32  sp+0x28 s32   (call 2 out-params)
//   Three calls, all GX SDK wrappers:
//     GX_ReadXfRasMetric(&sp0C, &sp10, &sp14, &sp18)
//     r30 = 1
//     GX_ReadXfRasMetric(&sp1C, &sp20, &sp24, &sp28)
//   Three booleans, each the `xor/subfic/adde` != idiom:
//     r29 = (sp10 != sp20)
//     r31 = (sp0C != sp1C)
//     r30 = (sp18 != sp28)      [r30 starts at 1, cleared when equal]
//   GX_GetGPStatus(sp+8, sp+8, sp+9, sp+0xa, sp+8)
//     <- NOTE r4 AND r7 are BOTH sp+8 (`mr r4,r3 ; mr r7,r3`).  The m2c draft
//        wrote `&sp8` three times which is right, but it also passed sp9/spA
//        (u8) into s32* params, which is what forced the `lbz` at the wrong
//        place.  sp+9/sp+0a must be u8 LOCALS and the params stay s32*.
//   Then the whole tail is one short-circuit chain whose "then" arm is EMPTY;
//   every branch targets either the next group or the epilogue 0x8001cb4c.
//   The LAST executed thing is `cmpwi r9,0` at 0x8001cb48, whose result is
//   never used - a dead compare that GCC 2.95 nonetheless keeps (the
//   "want keeps dead insns" family, recipes 6x-89).
//
// DERIVED BRANCH MAP (the shape to reproduce; cr6 = (r29==0),
// cr7 = (r31==0) are GCC's cr4-cache reloads of the two earlier compares):
// The chain first tests r31 with the nonzero arm going to L3 (0x8001cb1c),
// then tests r30 with the nonzero arm going straight to the epilogue. At L2
// it tests r29 and then r31 == 0, both targeting L3, and tests r30 again for
// the epilogue. At L3 it loads sp0a into r9, then tests spA, r29 == 0 and
// r31 == 0, all three targeting L4 (0x8001cb3c), and tests r30 once more for
// the epilogue. At L4 it tests sp9 == 0 for the epilogue, and the last
// executed compare of r9 against 0 is dead and falls through to the EPI label.
// i.e. "skip to the epilogue" is true iff
//     (r31==0 && r30) || (r29==0 && r31 && r30)
//   || (spA==0 && r29 && r31 && r30) || (sp9==0)
// which is the negation of the condition written below.
#include "types.h"

void GX_ReadXfRasMetric(s32, s32, s32, s32);
void GX_GetGPStatus(s32, s32, s32, s32, s32);

void fn_8001CA68(void) {
    s32 sp0C;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp8;
    u8 sp9;
    u8 spA;
    s32 r29;
    s32 r30;
    s32 r31;

    GX_ReadXfRasMetric(&sp0C, &sp10, &sp14, &sp18);
    r30 = 1;
    GX_ReadXfRasMetric(&sp1C, &sp20, &sp24, &sp28);
    r29 = (sp10 != sp20);
    r31 = (sp0C != sp1C);
    if (sp28 == sp18) {
        r30 = 0;
    }
    GX_GetGPStatus(&sp8, &sp8, &sp9, &spA, &sp8);
    if ((r31 != 0 || r30 == 0) &&
        (r29 != 0 || r31 == 0 || r30 == 0) &&
        ((s32)spA != 0 || r29 == 0 || r31 == 0 || r30 == 0) &&
        ((s32)sp9 != 0)) {
    }
}
// ---------------------------------------------------------------------------
// MEASURED 2026-10-04 — body above is the best of 6 variants:
//   base reconstruction          140 B, 29/62 diffs, 17.1%   <- kept
//   + byte-pointers into the s32 slot (`(u8*)&sp8 + 1 / + 2` to reach sp+9/sp+a)
//                               140 B, 33 diffs,  5.7%   (worse)
//   + the same plus a 0x10 frame pad to force 0x40
//                               140 B, 33 diffs,  5.7%   (pad had NO effect)
//   + `(r31 | 0) != 0` to pin the bool as a value
//                               140 B, 33 diffs,  5.7%   (worse)
// The m2c husk this replaces was 100 B / 22 diffs / 12.0%, i.e. **100 B of a
// 248 B function** — the frame, both bool-materialisations, the r30 compare
// and the entire condition chain were missing. So this is a real step, not a
// rewrite of the same wrong idea.
//
// RESIDUAL, three independent causes, all still open:
//  1. FRAME 0x38 vs 0x40. Want saves THREE callee-saved GPRs (r29,r30,r31 at
//     0x34..0x3f) and needs 11 four-byte locals (0x8..0x33); got saves two
//     (r30,r31) with 10 slots. A `char x[0x10]` pad changes nothing because the
//     shortage is a *saved-register* shortfall, not a local-count one — ngccc
//     sizes the frame from the locals it has, so the pad only helps if the
//     extra local actually forces the third callee-saved register, which it
//     does not on its own.
//  2. BOOL MATERIALISATION. Want computes each comparison ONCE, before the
//     third call, into a callee-saved register with the
//     `xor / subfic / adde` != idiom (`r29`, `r31`), and `r30` by
//     `li r30,1 ; cmpw ; bne`. ngccc instead re-derives the operands AFTER the
//     call (`lwz ; cmpw ; bne`) because that needs no callee-saved register — a
//     strictly cheaper choice that loses 6 words. Pinning the bools (arith or
//     `volatile`) was tried and costs more than it saves; the lever has to be
//     "make the bool genuinely needed across the call", and no source-level
//     spelling of that was found.
//  3. THE sp+9 / sp+0a ARGUMENT ADDRESSES. Want passes r4 AND r7 as `sp+8` and
//     then reads BYTES at sp+9 and sp+0a — i.e. the two `u8` results alias
//     *inside* the 4-byte slot at sp+8. ngccc gives distinct automatics
//     distinct slots, so `&sp9` can only be sp+0xc. The cast form
//     `(s32 *)((u8 *)&sp8 + 1)` reproduces the addresses but scored WORSE
//     (33 diffs), so the addressing is right and something else about the cast
//     is not. Unresolved: what source makes ngccc both pack them and keep the
//     plain `addi r3,r1,8 / mr r4,r3 / mr r7,r3` shape.
//  4. `li r30,1` must land immediately after the FIRST call (0x8001ca8c),
//     before call 2's argument setup. In this body ngccc sinks it past call 2.
// ---------------------------------------------------------------------------
