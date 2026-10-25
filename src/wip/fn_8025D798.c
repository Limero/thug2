// WIP DRAFT (non-matching) — hand decode from disasm 2026-10-11.
// family=hand range=0x8025D798-0x8025D8D0 size=312B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-11 at ~33% (51 diffs, got 304B vs want 312B).
// STRUCTURE SOLVED: C78++ (B5C+0x11C), CD04 snapshot (CEE8-0x1E4, r3),
// MMIO CC006828=0x88, C70 gate (BAC+0xC4) to end, CD08 (ADEE0-0x11D8, r11)
// countdown with CD04 += 0x200/0x400 by C70==4 then (Td)--, shared `docall:`
// join for CCFV(cd04, arg) (r3/r4 setup), CD0C (gap-0x3D4) swap arm
// (arg=CD0C reload into r4, CD0C=cd08), MMIO=CD0C via CSE reuse (hopeful),
// CD10 (DF94-0x1284) state arm, CD14 (gap-0x3CC, r31) zero/nonzero, cb via
// C74 (B5C+0x118, r30 saved across blrl) + D18 slot (DF94-0x127C), C70=1/5.
// Six bss base terms (gap+DF94 shared across non-overlapping spans).
// WALLS: (1) head coloring — want anchors r10/r7/r8 + values r9/r3/r11,
// every spelling gives a rotation (r11/r7/r10 + r9/r3/r0); decl order and
// head statement orders (all 4) tried, no movement. (2) got 8B short (2
// insns) — unlocated; branch counts want-vs-got to compare. (3) C70 MUST be
// BAC+0xC4 (own label gives full-address lis+0 form, wrong).
// CCFV=0x8025CCFC needs `lbl_8025CCFC = .text:0x8025CCFC; // type:label`
// for promotion (verify prologue); CCFV(cd04, arg) 2-arg per r3/r4.
#include "types.h"

extern u8 lbl_803ACEE8[];
extern u8 lbl_803ADEE0[];
extern u8 gap_05_803AD0E0_bss[];
extern u8 lbl_803ADF94[];
extern u8 lbl_80308B5C[];
extern u8 lbl_80308BAC[];
void fn_8025CCFC(s32, s32);
typedef void (*cb_t)(s32);
typedef struct { u8 pad[2]; u16 f2; u8 pad2[4]; s32 f8; } Dev;

void fn_8025D798(void) {
    s32 cd04;
    s32 cd08;
    s32 cd14;
    s32 arg;
    cb_t cb;

    *(s32 *)(lbl_80308B5C + 0x11C) += 1;
    cd04 = *(s32 *)(lbl_803ACEE8 - 0x1E4);
    *(volatile u32 *)0xCC006828 = 0x88;
    if (*(s32 *)(lbl_80308BAC + 0xC4) == 0) {
        goto end;
    }
    cd08 = *(s32 *)(lbl_803ADEE0 - 0x11D8);
    if (cd08 != 0) {
        if (*(s32 *)(lbl_80308BAC + 0xC4) == 4) {
            *(s32 *)(lbl_803ACEE8 - 0x1E4) = cd04 + 0x200;
            arg = 0x200;
        } else {
            *(s32 *)(lbl_803ACEE8 - 0x1E4) = cd04 + 0x400;
            arg = 0x400;
        }
        (*(s32 *)(lbl_803ADEE0 - 0x11D8))--;
        goto docall;
    }
    if (*(s32 *)(gap_05_803AD0E0_bss - 0x3D4) != 0) {
        arg = *(s32 *)(gap_05_803AD0E0_bss - 0x3D4);
        *(s32 *)(gap_05_803AD0E0_bss - 0x3D4) = cd08;
        goto docall;
    }
    *(volatile u32 *)0xCC006828 = *(s32 *)(gap_05_803AD0E0_bss - 0x3D4);
    if (*(s32 *)(lbl_803ADF94 - 0x1284) != 0) {
        if (*(s32 *)(lbl_80308BAC + 0xC4) == 4) {
            goto end;
        }
        *(s32 *)(lbl_80308BAC + 0xC4) = 1;
        goto end;
    }
    cd14 = *(s32 *)(gap_05_803AD0E0_bss - 0x3CC);
    if (cd14 != 0) {
        *(s32 *)(lbl_80308BAC + 0xC4) = 5;
        goto end;
    }
    cb = *(cb_t *)(lbl_80308B5C + 0x118);
    *(s32 *)(lbl_80308BAC + 0xC4) = cd14;
    *(s32 *)(lbl_803ADF94 - 0x127C) = cd14;
    if (cb != 0) {
        cb(0);
        *(cb_t *)(lbl_80308B5C + 0x118) = cd14;
    }
    goto end;
docall:
    fn_8025CCFC(cd04, arg);
end:;
}
