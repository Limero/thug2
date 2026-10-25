// WIP DRAFT (non-matching) — hand-rebuilt from the disasm (m2c draft was wrong)
// family=m2c range=0x8002C128-0x8002C388 size=608B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Semantics recovered from the want:
//   v = (f32)*(s32 *)&arg0->unk0x0   -- ngccc's int->float conversion idiom
//        (stw x^0x8000 / stw 0x43300000 to 8(r1), lfd, fsub of the pool double
//         0x802916D8 = 2^52+2^31, frsp)
//   if (arg1 != 0) { if (farg0 < farg1) {
//        if (arg0->unk0x30 != 0) { if (farg1 > v) goto TAIL; return 0; }
//        else                     { if (v < farg1 - 1.0f) return 0; }
//        TAIL: return 0 unless (v >= farg0-1.0f && v <= farg1)
//     } else     { return 0 unless (v <= farg0+1.0f && v >= farg1) } }
//   else          -- byte-identical body, except the SECOND tail test uses the
//                    plain `<`/`>` polarity (`bge`/`ble`) instead of the
//                    cror+bns NaN-strict `!(<=)`/`!(>=)` form of the first half.
// `!(a<=b)` / `!(a>=b)` (not `!(a<b)`/`!(a>b)`) is what reproduces want's
// fcmpu+cror eq,lt/eq,gt+bns; the first tail test in each block is a `goto` to a
// trailing label and the second a plain `return 0` — that pairing is what makes
// ngccc block-merge the 2nd ret0 into the tail block (the hoisted `li r3,0`).
#include "types.h"
#include "structs.h"

s32 fn_8002C128(CStruct *arg0, s32 arg1, f32 farg0, f32 farg1) {
    if (arg1 != 0) {
        if (farg0 < farg1) {
            if (arg0->unk0x30 != 0) {
                if (!(farg1 > (f32)arg0->unk0x0)) {
                    goto E1L;
                }
                return 0;
            } else {
                if ((f32)arg0->unk0x0 < farg1 - 1.0f) {
                    return 0;
                }
            }
E1L:
            if (!((f32)arg0->unk0x0 >= farg0 - 1.0f)) {
                goto E1;
            }
            if (!((f32)arg0->unk0x0 <= farg1)) {
                return 0;
            }
            return 1;
E1:
            return 0;
        } else {
            if (!((f32)arg0->unk0x0 <= farg0 + 1.0f)) {
                goto E12;
            }
            if (!((f32)arg0->unk0x0 >= farg1)) {
                return 0;
            }
            return 1;
E12:
            return 0;
        }
    } else {
        if (farg0 < farg1) {
            if (arg0->unk0x30 != 0) {
                if (!(farg1 > (f32)arg0->unk0x0)) {
                    goto E3L;
                }
                return 0;
            } else {
                if ((f32)arg0->unk0x0 < farg1 - 1.0f) {
                    return 0;
                }
            }
E3L:
            if (!((f32)arg0->unk0x0 >= farg0 - 1.0f)) {
                goto E3;
            }
            if (!((f32)arg0->unk0x0 < farg1)) {
                return 0;
            }
            return 1;
E3:
            return 0;
        } else {
            if (!((f32)arg0->unk0x0 <= farg0 + 1.0f)) {
                goto E34;
            }
            if (!((f32)arg0->unk0x0 > farg1)) {
                return 0;
            }
            return 1;
E34:
            return 0;
        }
    }
}

// PARKED 2026-10-03: 72.4% masked (110/152 words), object 608B ==
// symbol size EXACT, and every block (A / B / L_B / L_C, both halves) is
// byte-identical modulo reloc masks. The whole residual is ONE thing repeated in
// the 4 tail blocks: want materialises `li r3,0` as the 7th insn of the block
// (right after the cvt store pair) so that BOTH `bns` failure branches go
// straight to the epilogue; mine keeps `li r3,0` at the 2nd compare and sends
// the FIRST failure to the shared `li r3,0` block at 0x178 instead. Measured
// why: that requires ngccc to BLOCK-MERGE *both* trailing `return 0` blocks into
// the tail block (it CSEs the duplicate `li`). It only ever merges the one that
// is chain-adjacent to the tail — the `goto`-target label, sitting after
// `return 1`, is never merged. Proven with a minimal repro: the identical
// source shape with a 1-word tail body merges BOTH (goes to the epilogue), and
// adding one `fsubs f1,f13` to that tail body (block 16 -> 20 insns, no
// semantic change) makes ngccc stop merging the goto target and send that
// failure to the shared ret0 block — the same flip this function needs. Also
// ruled out: `-fno-gcse`/`-fno-thread-jumps` (accepted but do not restore it;
// -fno-gcse also flips the cvt store order), two-separate-label tails (both
// failures then go to the shared block and the layout collapses), and
// `!(a<b)`/`!(a>b)`/`&&`/`||`/ternary forms of the two tail tests (wrong cror
// polarity or a shared failure block).