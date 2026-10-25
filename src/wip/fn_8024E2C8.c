// WIP DRAFT (non-matching) — rebuilt from disasm (GX TEV stage config, 2 variants)
// family=m2c range=0x8024E2C8-0x8024EA14 size=1868B
// extra_cflags: -Ilibs/dolphin/include
//
// PARKED 79.5% NEAR (baseline m2c draft was 9.8%; body fully re-derived
// from disasm — all ~81 calls with correct callees/args/order incl. the
// arm2 col<<16 / (col<<8)|0x32 shift web and GXSetTevSwapMode 3-arg).
// Remaining 96 diffs are allocator/scheduler residue:
//  - want frame stwu -0x28 + stmw r29 (3 saved regs: p10-arm0->r30,
//    p10-arm2->r29, +r31); got stmw r30/0x20 with both &sp10 webs
//    coalesced into one home.
//  - want stack layout sp8[2]@8/spC@0xc pair + sp10@0x10; got only
//    reproduces it when the p10 assignments are LATE (after B47C);
//    early assignment (want's addi-at-arm-start) flips slots back.
//  - B47C/B4F0 arg staging interleave ([addi arg][addi lbl][li][lwz][lwz]
//    [stw][stw][bl] in want) vs got's interleaved order.
// Levers that worked here: switch() dispatch (beq/beq/b-ret0 shape),
// escaping s32 sp8[2] array for the pair (recipe 117), named lbl pointer
// `lp`, per-arm separate p10 webs, late p10 assignment.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 79.7% ([1]rev->79.7%).
// PERMUTED 2026-09-13 (<permute script> full-permutation statement search): score now 84.15% ([1]p8->84.2%).
#include "types.h"
#include "dolphin/gx/GXEnum.h"
#include "qb_constants.h"

void GXSetTevOrder(s32, s32, s32, s32);
void GXSetTevColorIn(s32, s32, s32, s32, s32);
void GXSetTevColorOp(s32, s32, s32, s32, s32, s32);
void GXSetTevAlphaIn(s32, s32, s32, s32, s32);
void GXSetTevAlphaOp(s32, s32, s32, s32, s32, s32);
void GXSetTevKColorSel(s32, s32);
void GXSetTevKAlphaSel(s32, s32);
void GXSetTevSwapMode(s32, s32, s32);
void fn_8028B47C(s32, s32 *);
void fn_8028B408(s32, s32 *);
void fn_8028B4F0(s32, s32 *);
extern s32 lbl_802B1B54[];
extern s32 lbl_802B1B5C[];

s32 fn_8024E2C8(s32 arg0) {
    s32 sp10;
    s32 sp8[2] __attribute__((aligned(8)));
    u32 col;
    s32 *p10;
    s32 *p10b;
    s32 *lp;

    switch (arg0) {
    case 0:
        p10 = &sp10;
        __asm__("" : "+r"(p10));
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K1_A);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K2);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
        GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_K2_A);
        GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_CPREV, GX_CC_APREV, GX_CC_KONST, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE3, GX_TEV_KCSEL_K3);
        GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        lp = lbl_802B1B54;
        sp8[0] = lp[0];
        sp8[1] = lp[1];
        fn_8028B47C(1, sp8);
        sp10 = 0xff32;
        fn_8028B4F0(0, p10);
        sp10 = QB_UNKNOWN_0xCD000068;
        fn_8028B4F0(1, p10);
        sp10 = QB_UNKNOWN_0x95009595;
        fn_8028B4F0(2, p10);
        sp10 = 0xff0000;
        fn_8028B4F0(3, p10);
        return 4;
    case 1:
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
            col = 0xFF;
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG1);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG1);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_KONST, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K0);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A1, GX_CA_KONST, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K0_A);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K1);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_K1_A);
        GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE3, GX_TEV_KCSEL_K2);
        GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
        GXSetTevKAlphaSel(GX_TEVSTAGE3, GX_TEV_KASEL_K2_A);
        GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevSwapMode(GX_TEVSTAGE4, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE4, GX_CC_ZERO, GX_CC_C1, GX_CC_KONST, GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE4, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE4, GX_TEV_KCSEL_K3);
        GXSetTevAlphaIn(GX_TEVSTAGE4, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE4, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevSwapMode(GX_TEVSTAGE5, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE5, GX_CC_CPREV, GX_CC_APREV, GX_CC_C2, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE5, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE5, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE5, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        sp8[0] = lp[0];
        lp = lbl_802B1B5C;
        sp8[1] = lp[1];
        p10b = &sp10;
        __asm__("" : "+r"(p10b));
        fn_8028B47C(1, sp8);
        sp10 = (col << 16);
        fn_8028B408(3, p10b);
        sp10 = ((col << 8) | 50);
        fn_8028B4F0(0, p10b);
        sp10 = QB_UNKNOWN_0xCD000068;
        fn_8028B4F0(1, p10b);
        sp10 = QB_UNKNOWN_0x95009595;
        fn_8028B4F0(2, p10b);
        sp10 = 768;
        fn_8028B4F0(3, p10b);
        return 6;
    }
    return 0;
}
