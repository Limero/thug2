// PARKED 2026-10-03 (a42): NEAR 73.6% (baseline DIFF 24.5%).
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x80119B24
//
// WHAT THIS IS (from the disasm, not from m2c): the function returns a POINTER
// to the matching 0x24-byte table entry, or NULL. Two tables (lbl_80385A44 with
// count lbl_80302C48, then lbl_80383644 with count lbl_80302C44), each indexed
// by a local s32, entry stride 0x24, compared s32 at offset 0 against arg1.
// Gated on fn_80119470() returning 0.
//
// REMAINING DIFF: 14 words, and they are ALL the same thing — GCC's local-alloc
// hands r10/r11 to the two loop induction variables in the opposite order.
// The original keeps the loop index in r10 (zeroed at entry, incremented by
// one each pass, and word-compared against r8) and the walking base pointer
// in r11 (copied from r9, dereferenced at offset 0, and advanced by the 0x24
// entry stride each pass). This draft assigns them the other way round, with
// the base pointer in r10 and the index in r11.
// Affected sites (offsets from 0x80119B24): 0x30,0x38,0x50,0x54,0x58,0x5c,
// 0x64,0x6c,0x70 and the same set again in loop 2 (0x9c,0xa4,0xa8,0xac,0xb0,
// 0xb4,0xb8,0xbc). Everything else — prologue, frame, the `lis/addi` address
// forms, `cmpwi r3,0` gate, the hoisted-count guard `cmpw i,n; bge`, the
// `add r3,r3,r9` + shared `b epilogue` tail-merge of both "found" paths, and
// all 8 epilogue insns — is byte-identical.
//
// RULED OUT (all measured, all worse):
//  - `while (i < n) { ...; i++; }` instead of `for`: 73.6%, identical output.
//  - `if (lbl[..][i].f0 == arg1)` (operand order): 69.8% — flips the compare to
//    `cmpw r0,r31`; register assignment is unchanged, so it is not the lever.
//  - Explicit walk pointer `for (i=0, p=arr; i<n; i++, p++)` with
//    `return &arr[i]`: 18.9% — GCC stops strength-reducing `&arr[i]` and emits
//    `mulli r0,r10,0x24` in the found path.
//  - Explicit `off += 0x24` accumulator plus `p++`: DIFF — GCC CSEs them away
//    and pre-computes `lis/addi/add` pairs in both found paths.
//  - Hoisting the array into a local `ListEnt *base`: DIFF — CSE merges
//    `base[i]` and `&base[i]`, losing the separate r3 byte-offset accumulator
//    that the original clearly has (`addi r3,r3,0x24` / `add r3,r3,r9`).
//  - `return lbl_..[i]` + `i` instead of `&lbl_..[i]`: 73.6%, identical.
//
// NEXT IDEA: this is a pseudo-numbering tie-break inside GCC's local-alloc
// (higher `allocno` number is allocated first -> lower hard reg; `i` is a
// front-end pseudo, the strength-reduced base pointer is a loop.c pseudo and so
// has the higher number). Source-shape changes that reorder expand do not move
// it. Worth trying next: a shape where the index itself is derived rather than
// declared (e.g. a byte-stride pointer walk with the count compared against a
// pre-scaled end), so both induction variables are loop.c pseudos, or an
//    explicitly pinned allocno via a `register`-qualified index.
// TRIED 2026-10-12: `register s32 i __asm__("r10")` => DIFF
// (worse than the 73.6% baseline — the pin breaks the strength-reduced
// base/index shape, not just the colour). Do not retry index pins.
// TRIED 2026-10-12: explicit walk pointer `for (i=0,p=arr;..;i++,p++)`
// with `return p` (instead of the note's `return &arr[i]`) => DIFF. Returning
// the walked pointer collapses the two-induction shape entirely rather than
// recolouring it. Do not retry walk-pointer forms.
// family=m2c range=0x80119B24-0x80119BF8 size=212B
#include "types.h"

typedef struct {
    s32 f0;
    char pad[0x20];
} ListEnt;

extern s32 lbl_80302C44;
extern bool lbl_80302C48;
extern ListEnt lbl_80383644[];
extern ListEnt lbl_80385A44[];

void *fn_80119B24(void *arg0, s32 arg1) {
    s32 i;

    if (fn_80119470() != 0) {
        return 0;
    }

    for (i = 0; i < lbl_80302C48; i++) {
        if (arg1 == lbl_80385A44[i].f0) {
            return &lbl_80385A44[i];
        }
    }

    for (i = 0; i < lbl_80302C44; i++) {
        if (arg1 == lbl_80383644[i].f0) {
            return &lbl_80383644[i];
        }
    }

    return 0;
}