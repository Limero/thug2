// family=m2c range=0x8005B11C-0x8005B258 size=316B
// PARKED 2026-10-03: NEAR 91.1% (was DIFF 21.0%). Reproduce:
//   LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8005B11C
//   LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/want_got.py 0x8005B11C
// Got 316B = want 316B; 7 word diffs, all in the last loop, in TWO groups:
//  (1) ONE register-allocation swap (5 diffs, 0x8005B1C0-0x8005B1EC). want keeps
//      r29 = node-pool base and r30 = address of lbl_8030089C; 3.9.3 recycles
//      r29 for lbl_8030089C and gives the pool base to r30: the want build
//      loads the 0x8030 page into r30, derives the pool base into r29 with a
//      0x4cc8 displacement, copies it to r31 and loads through r30 with an
//      0x89c displacement, while this build loads a zero page into r29,
//      derives a zero-displacement base into r30, copies it to r31 and loads
//      through r29 with a zero displacement.
//      Both pseudos are live at different times (lbl_80300898's base dies when
//      loop 1 ends), so this is pure register-recycling order, not semantics.
//  (2) ONE instruction placement (2 diffs, 0x8005B1F0). want materialises the
//      source pointer BEFORE the first pair copy: it scales the index by 0x28,
//      stores, adds the pool base to form the address and then performs a
//      direct pair load of the first element, while this build scales, stores,
//      performs the first element load in indexed form off the summed registers
//      and only then materialises the address.
//      i.e. 3.9.3's reload uses the indexed memory operand for the first
//      single-use access and only materialises it from the 2nd member on.
//      Hoisting `src = &lbl_80364CC8[last];` above `lbl_8030089C = last;` does
//      NOT change this (measured, still 91.1%).
// What is already RIGHT (do not re-derive):
//  - Globals MUST be `extern` declarations (lbl_80300498 / lbl_80300898 /
//    lbl_8030089C / lbl_80364CC8). Raw literals `(s32 *)0x80300898` make
//    ngccc fold the page: `ori r9,r9,0x898 ; lwz r0,0(r9)` — never matches.
//    extern gives want's `lis ; lwz rX,0x898(rX)` (reloc-masked).
//  - Loop 1 must be `i = 0; if (count > 0) { do {...; i++;} while (i < count); }`.
//    A plain `for (i=0; i<count; i++)` yields `cmpw r11,r0 ; bge` in the
//    preheader; want has the folded `cmpwi r0,0 ; ble`. Adding a redundant
//    outer `if` around a `for` is also WRONG (adds a second test, 8.9%).
//  - The pool element is 0x24 bytes with 8-byte alignment (2 __ps_t + 2 f32 +
//    3 s32) -> 0x28 array stride. Add a field at 0x24 and want stops copying.
//  - The copy MUST be written out per member; `nodes[i] = nodes[last]` makes
//    3.9.3 emit a 24-byte lwz/stw copy LOOP and no psq at all. Per-member
//    __ps_t copies need `-mps-float` and then match want's psq_l/psq_st,
//    lfs/stfs, lwz/stw run verbatim.
// Next idea: the only C-reachable lever left is perturbing pseudo-allocation
// order so the pool base lands in r29 and lbl_8030089C in r30 (e.g. give
// loop 2's counter a second, structurally different access shape, or swap the
// declaration order of the two counters). Every such attempt must be re-measured
// — 91.1% is only 5 words away but the residue is regalloc, not semantics.
#include "types.h"
#include "types.h"
#include "structs.h"

// 0x24-byte payload, 8-byte aligned -> 0x28 stride in the pool at 0x80364CC8.
typedef struct Unk_Node5B {
    __ps_t unk0x0;
    __ps_t unk0x8;
    f32 unk0x10;
    f32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
} Unk_Node5B;

extern Unk_C7387A53 *lbl_80300498[0x100];
extern s32 lbl_80300898;
extern s32 lbl_8030089C;
extern Unk_Node5B lbl_80364CC8[150];

void Mem_Free(void *);
void fn_8005A0B0(Unk_Node5B *);

void fn_8005B11C(s32 arg0) {
    Unk_Node5B *src;
    Unk_Node5B *dst;
    s32 i;
    s32 last;

    i = 0;
    if (lbl_80300898 > 0) {
        do {
            if (lbl_80300498[i]->unk0x2C == arg0) {
                Mem_Free(lbl_80300498[i]);
                last = lbl_80300898 - 1;
                lbl_80300898 = last;
                lbl_80300498[i] = lbl_80300498[last];
                lbl_80300498[last] = NULL;
                break;
            }
            i++;
        } while (i < lbl_80300898);
    }

    i = 0;
    while (i < lbl_8030089C) {
        if (lbl_80364CC8[i].unk0x18 == arg0) {
            fn_8005A0B0(&lbl_80364CC8[i]);
            last = lbl_8030089C - 1;
            lbl_8030089C = last;
            src = &lbl_80364CC8[last];
            dst = &lbl_80364CC8[i];
            dst->unk0x0 = src->unk0x0;
            dst->unk0x8 = src->unk0x8;
            dst->unk0x10 = src->unk0x10;
            dst->unk0x14 = src->unk0x14;
            dst->unk0x18 = src->unk0x18;
            dst->unk0x1C = src->unk0x1C;
            dst->unk0x20 = src->unk0x20;
            break;
        }
        i++;
    }
}