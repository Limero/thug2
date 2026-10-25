// family=m2c range=0x80003FF8-0x80004104 size=268B
// WIP DRAFT — 4x4 matrix rotation builder (axis-frame init).
// Builds a 4x4 rotation matrix for rotation about the axis FIXED by `arg1`:
// the two perpendicular axes are m1 = (arg1+1)%3 and m2 = (arg1+2)%3; the
// matrix is first filled with 1.0f everywhere and 0.0f on the diagonal, then
// the 2x2 block spanned by (m1,m2) is overwritten with cos/sin:
//   [m1][m1]=cos  [m1][m2]= sin
//   [m2][m1]=-sin [m2][m2]=cos
// lbl_8028FC78 = 0.0f (diagonal), lbl_8028FC7C = 1.0f (off-diagonal).
// sinf (0x80271170) is called FIRST, then cosf (0x80271070); returns arg0.
// The only caller (src/fn_801C39EC.c, byte-proven) passes `f32 v[16]` and
// ignores the return value.
//
// STATUS: NEAR 80.6% (54/67 words) — 13 diffs, all a sched2 tie inside the
// 14-instruction window 0x80004078-0x800040AC. See PARKED block at the end.
//
// m2c CORRUPTION REPAIRED (earlier revisions of this draft):
//  * Unk_DB0E2BAB's first 0x40 bytes are f32 (want has stfs, not stw), so a
//    file-local typedef with `volatile f32 m[16]` is used. The s32 members
//    made GCC emit an fctiwz/stfd dance plus frame spills (23.9% -> 40.3%).
//  * m2c wrote the four indexed stores as `*((s32 *)row + byteoff)` — a
//    double-scaled index. Correct spelling is `(f32*)row[idx]` / byte cast.
//  * The single `volatile double _dummy` of the previous revision was wrong:
//    want's frame is 0x38 = native + 16, so TWO pads are needed (+8 each).
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct Unk_DB0E2BAB_local {
    volatile f32 m[16];
} Unk_DB0E2BAB_local;

extern f32 lbl_8028FC78;
extern f32 lbl_8028FC7C;
f32 sinf(f32);
f32 cosf(f32);

void *fn_80003FF8(Unk_DB0E2BAB_local *arg0, s32 arg1, f32 farg0) {
    s32 temp_r29;
    s32 temp_r31;
    f32 temp_f30;
    f32 temp_f1;
    f32 temp_f13;
    f32 temp_f0;
    register f32 *temp_r11 __asm__("r11");
    register f32 *temp_r9 __asm__("r9");
    register s32 temp_o1 __asm__("r7");
    register s32 temp_o2 __asm__("r8");
    volatile double _d1;
    volatile double _d2;

    temp_r31 = (arg1 + 1) % 3;
    temp_r29 = (arg1 + 2) % 3;
    temp_f30 = sinf(farg0);
    temp_f1 = cosf(farg0);
    temp_f13 = lbl_8028FC78;
    temp_f0 = lbl_8028FC7C;
    temp_o1 = temp_r31 * 4;
    temp_o2 = temp_r29 * 4;
    temp_r11 = arg0->m + temp_r31 * 4;
    temp_r9 = arg0->m + temp_r29 * 4;
    arg0->m[0] = temp_f13;
    arg0->m[15] = temp_f13;
    arg0->m[14] = temp_f0;
    arg0->m[1] = temp_f0;
    arg0->m[2] = temp_f0;
    arg0->m[3] = temp_f0;
    arg0->m[4] = temp_f0;
    arg0->m[5] = temp_f13;
    arg0->m[6] = temp_f0;
    arg0->m[7] = temp_f0;
    arg0->m[8] = temp_f0;
    arg0->m[9] = temp_f0;
    arg0->m[10] = temp_f13;
    arg0->m[11] = temp_f0;
    arg0->m[12] = temp_f0;
    arg0->m[13] = temp_f0;
    *(f32 *)((char *)temp_r11 + temp_o1) = temp_f1;
    *(f32 *)((char *)temp_r11 + temp_o2) = temp_f30;
    *(f32 *)((char *)temp_r9 + temp_o1) = -temp_f30;
    *(f32 *)((char *)temp_r9 + temp_o2) = temp_f1;
    return arg0;
}

// === PARKED (2026-10-01) — 80.6% / 54 of 67 words ===
// SCORE: NEAR 80.60% (was 23.88%). Object .text = 268 B = symbols.txt size
// 0x10C = the `range=` marker. 13 diffs, all inside one window.
//
// WHAT IS ALREADY EXACT: whole prologue/epilogue (frame 0x38, stmw/stfd/LR
// slot), the whole `(%3)` block (both mulhw chains, interleaved, r29/r31
// choice), both calls and their f1 save/restore, all four stfsx stores with
// want's register numbers (r11/r7, r11/r8, r9/r7, r9/r8), and the complete
// store run in want's exact order (0x0, 0x3c, 0x38, 0x04..0x34).
//
// WHAT IS LEFT: 0x80004078-0x800040AC (14 instructions, same multiset, same
// registers, pure order). The want bunches the seven address/ALU computations
// first and then runs the stores: an slwi into r11, an add into r11, an slwi
// into r7, a store to 0x0, an slwi into r8, an slwi into r9, an fneg, an f0
// load, an add into r9, a store to 0x3c, a move into r3, a store to 0x38,
// then the store to 4 and onward. ngccc/sched2 instead alternates one ALU op
// with one store: an slwi into r11, the f0 load, the add into r11, the store
// to 0x0, the slwi into r7, the store to 0x3c, the slwi into r8, the store to
// 0x38, the slwi into r9, the store to 4, the add into r9, the store to 8,
// the fneg, the store to 0xc, and the move into r3.
//
// WHY IT IS STUCK: it is a post-regalloc scheduler tie, not a semantic or
// types error. Evidence: `cc1 -dr -dj` dumps show the PRE-sched2 RTL is
// identical in shape (the 16 stores carry SEQNOs 109,112,...,154 = ascending,
// i.e. the source order) and `.sched2`'s file order is exactly the emitted
// order — so sched2 is the pass that picks the interleaving. Flags cannot be
// the fix: the original was built with the game's own flag set
// (-O2 -G0 -mcpu=750 -fno-common, AGENTS §4b), so any -fno-schedule* would
// change the whole function, not reproduce it.
//
// MEASURED AND REJECTED (all at or below this body):
//  * statement order of the fill/row/const/offset/negation/return statements
//    (7 variants): bit-identical output every time — sched2 normalises it.
//  * fill as a loop (`for (i=0;i<16;i++) m[i]=(i%5==0)?z:o;` and the nested
//    `m[i][j]=(i==j)?z:o`): neither unrolls, 34% / 39%.
//  * writing want's literal store order WITHOUT volatile: 58% — worse,
//    because sched2 then hoists the last store of each value class.
//  * `volatile f32 m[16]` (stores pinned, order reproduced) = 80.6%: the one
//    thing that works; volatile is what keeps sched2 from re-hoisting.
//  * barrier probes `"+r"` on the offsets / on the two %3 results (no change),
//    `"+f"` on the second constant load (76%, worse).
//  * pin subsets: rows only 73%, offsets only = same as no pins 70%.
//  * frame pads: one pad 40%, two pads 55% (of the pre-pin body).
//
// NOT TRIED (the one thing I would do next): re-derive the pre-sched2 RTL that
// makes sched2 bunch the ALU ops, i.e. find a source whose fill statements are
// interleaved with the address computations in want's *output* order rather
// than grouped — tried one such grouping (identical output) but not a
// systematic search of the 4 address statements' positions relative to the
// 16 stores.