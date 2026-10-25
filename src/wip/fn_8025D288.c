// WIP DRAFT (non-matching) — hand decode from disasm 2026-10-11.
// family=hand range=0x8025D288-0x8025D32C size=164B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// DECODE: 6 args saved to r26-r31; andi./bne alignment pre-checks on a1/a2
// (return -1); D6D0 call; two stores ([CD14]=a5 via 0x803B/r9,
// [8B74]=a3 via 0x8031/r11); D114(a0,a1,a2,a4) 4-arg call (r7/r8 unset);
// post-call: r9/r11/r10/r9(0x8031) remats, [CD10]=a2, [CD00]=a0,
// [CD04]=a1, [8C70]=1 with li-r3-0 interleaved; return 0.
// PARKED 2026-10-11 at 75.6% NEAR (31/41, SIZE-EXACT 0xA4; started 10%).
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python
// <scratch> src/wip/fn_8025D288.c 0x8025D288 0xA4
// Prologue + checks + pre-call nearly exact (1-word mr-r3/r6 swap remains:
// want hoists mr-r3 before the a3-store, got hoists mr-r6).
// LOAD-BEARING (ablation-verified): six arg pins b0/b1/b2/b3/b4/b5 to
// r26/r30/r31/r27/r28/r29 in want-mr order (unpinnned spreads args to
// r24-r31 + 0x28 frame; pins force 0x20 frame AND force store bases into
// caller-saved r9-r11); six DISTINCT base symbols ([CD14]=CCC0+0x54,
// [8B74]=B5C+0x18, [CD10]=CDEE0-0x1D0, [CD00]=CDA0-0xA0, [CD04]=CEE8-0x1E4,
// [8C70]=C70 direct — lbl_80308C70 is itself link-defined!) so no anchor
// base is kept (any shared symbol collapses 2-4 stores onto one kept base
// reg with small disps: CDA0-triple -> r9-anchor, CCC0-pair across the D114
// call -> r25 kept (callee-saved survives!)).
// RESIDUAL (~10 words): post-call scheduler bunches the 4 lis's then
// stores in a different order (want interleaves lis/lis/stw/lis/lis/li/
// stw/li/stw/stw with b2 stored FIRST); pointer-var interleaving texture
// tried, neutral (75.6%). Next: statement orders that pin lis's below the
// first stw, or a second tb-style temp pin to steer the store regs.
// 2026-10-15: full want decode (no new score). Post-call is 10 words with
// NO addi's (all sym+off folded into lis+disp): lis r9 / lis r11 /
// stw r31(CD10) / lis r10 / lis r9(0x8031) / li r0,1 / stw r26(CD00) /
// li r3,0 (= return 0, scheduled UP mid-sequence!) / stw r30(CD04) /
// stw r0(8C70). Pre-call residual confirmed as pure scheduler placement:
// want (lis-r9, stw-CD14, lis-r11, mr-r3, stw-8B74, mr-r6, mr-r4, mr-r5, bl)
// vs got with mr-r6 and mr-r3 swapped — same births, only placement differs
// (all 6 pin copies stay at top in both: moving any pin late would break the
// prologue). Both residuals are scheduler-placement coins with no source
// lever: stw has no dependents to pull it early, mr's have no reason to
// prefer either slot. PARKED unless a schedule flag is found that flips both.
#include "types.h"

extern u8 lbl_803ACCC0[];
extern u8 lbl_80308BAC[];
extern u8 lbl_80308B5C[];
extern u8 lbl_80308C70[];
extern u8 lbl_803ACDA0[];
extern u8 lbl_803ACEE8[];
extern u8 lbl_803ADEE0[];

void fn_8025D6D0(void);
s32 fn_8025D114(s32, s32, s32, s32);

s32 fn_8025D288(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    register s32 b1 __asm__("r30") = a1;
    register s32 b0 __asm__("r26") = a0;
    register s32 b2 __asm__("r31") = a2;
    register s32 b3 __asm__("r27") = a3;
    register s32 b4 __asm__("r28") = a4;
    register s32 b5 __asm__("r29") = a5;
    if ((b1 & 0x1F) != 0) {
        return -1;
    }
    if ((b2 & 0x1F) != 0) {
        return -1;
    }
    fn_8025D6D0();
    *(s32 *)(lbl_803ACCC0 + 0x54) = b5;
    *(s32 *)(lbl_80308B5C + 0x18) = b3;
    fn_8025D114(b0, b1, b2, b4);
    *(s32 *)(lbl_803ADEE0 - 0x1D0) = b2;
    *(s32 *)(lbl_803ACDA0 - 0xA0) = b0;
    *(s32 *)(lbl_803ACEE8 - 0x1E4) = b1;
    *(s32 *)lbl_80308C70 = 1;
    return 0;
}
