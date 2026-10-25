// PARKED 2026-10-03 — m2c best guess retained.
//
// UPDATED 2026-10-04 (bf): the global addresses ARE now recovered, and the
// remaining blocker is the SCORER, not codegen. Decoding the address formation:
//   page anchor plus offsets 0x140 / 0x16c -> 0x80300140, 0x8030016C;
//   anchored base 0x8037B5E8 with field offsets 0x1BC = 0x8037B7A4,
//   0x1C0 = 0x8037B7A8, store slot 0x1AC = 0x8037B794;
//   a second spelling reaches the same 0x8037B7A4 cell.
// 0x8037B794/0x8037B7A8 already appear in the promoted src/fn_80019B90.c and
// src/fn_80018178.c; 0x8037B7A4 is new (see src/wip/fn_80120824.c).
//
// WHY THIS FUNCTION CANNOT BE SCORED RIGHT NOW: want accesses these globals
// as SYMBOL references (page anchor plus low part). Measured all three
// spellings with tools/gen_leaves.compile_fn:
//   (a) `extern s32 lbl_80300140;`      -> zero-page anchor load   12.0%
//   (b) `*(s32 *)0x80300140` (literal)  -> constant-setup then load  6.9%
//       (this is the documented fn_8006A8C0 constant-setup split)
//   (c) tentative DEFINITION of the globals in the TU -> still address 0,
//       zero-page anchor — the object has no other sections   18.6%
// In every case the HIGH half IS masked (ADDR16_HA -> 0xFFFF0000 at the
// operation) but the load DISPLACEMENT is not, because the ADDR16_LO mask is
// applied to the same word with the same 0xFFFF0000 — it keeps the
// displacement and masks the opcode, the wrong way round for a load. So any
// body that touches a .sdata/.bss global is capped well below 100% by the
// harness regardless of how correct it is. m2c's 35.1% body is left in place
// because it beats the 18.6% transliteration ON THE SCORER; it is not better
// code, it just fails to trip the same masked comparisons.
// Control-flow shape is also still wrong: retail branches through
// `fn_80018178` three times and the tail is
// `if (b) OSResetSystem(1,0,c?1:0); else OSResetSystem(1,0,0);` (the
// condition-register handling is cc1 keeping two condition tests live).
//
// family=m2c range=0x800181A4-0x8001836C size=456B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80300140;
extern bool lbl_8030016C;
extern bool lbl_8037B7A4;
void OSResetSystem(s32, s32, s32);
void fn_8001E17C(s32);
void fn_80120924(s32);
void PADRecalibrate(s32);
void fn_800181A4(s32 arg0, s32 arg1) {
    s32 var_r5;
    s32 temp_r11;
    s32 temp_r3;
    s32 var_r30;

    temp_r11 = lbl_80300140;
    if (temp_r11 <= 3) {
        if ((s32) *(s32 *)((char *)0x8037B5E8 + (s32)0x1BC) == 0) {
            lbl_80300140 = (s32) (temp_r11 + 1);
            goto block_3;
        }
        goto block_4;
    }
block_3:
    if (lbl_8037B7A4 != 0) {
block_4:
        lbl_80300140 = 0;
    }
    if ((fn_80018178() != 0) && ((s32) *(s32 *)((char *)0x8037B5E8 + (s32)0x1BC) == 0) && (lbl_80300140 == 4)) {
        var_r30 = 0;
        if ((fn_80018178() != 0) && ((s32) *(s32 *)((char *)0x8037B5E8 + (s32)0x1BC) == 0)) {
            temp_r3 = fn_80019E0C();
            if ((temp_r3 <= 6) && (temp_r3 >= 4)) {
                var_r30 = 1;
                if (fn_80019E18() != 0) {
                    lbl_8030016C = 1;
                }
            } else {
                var_r30 = 1;
            }
        }
        if ((s32) *(s32 *)((char *)0x8037B5E8 + (s32)0x1C0) != 0) {
            var_r30 = 1;
        }
        if (var_r30 != 0) {
            PADRecalibrate(QB_UNKNOWN_0xF0000000);
            0;
            0;
            0;
            fn_80120924(1);
            fn_8001E17C(1);
            ((void (*)(void))0x80261860)();
            ((void (*)(void))0x80260B70)();
            *(s32 *)((char *)0x8037B5E8 + (s32)0x1AC) = 0;
            ARQFlushQueue();
            do {

            } while (ARGetDMAStatus() != 0);
            AXQuit();
            AIReset();
            ARQReset();
            ARReset();
            0;
            if (0 || (0, 0)) {
                var_r5 = 0;
                0;
                if (0) {
                    var_r5 = 1;
                }
                OSResetSystem(1, 0, var_r5);
                return;
            }
            OSResetSystem(0, 0, 0);
        }
    }
}
