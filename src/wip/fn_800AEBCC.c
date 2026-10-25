// WIP DRAFT (non-matching) — m2c body, hand-audited (2026-10-08). STILL PARKED.
// family=m2c range=0x800AEBCC-0x800AF6F8 size=2860B
//
// === PARKED 2026-10-08 — read this before touching the body ===
// This is the biggest remaining function here: 2860 B / 715 instructions,
// frame 0x1e0, 18 saved FPRs (f14-f31) + stmw r20. The m2c body is NOT a
// near-match: measured LCS-norm is ~19% and the *shape* is wrong (the original
// does paired-single matrix math where the draft does scalar float math), so it
// is a rewrite, not a tuning job. What IS established and should not be
// re-derived:
//
//  * ARTIFACT IDENTITY (from the want disasm): a per-model world/local matrix
//    update. It is NOT the same object as the matched twin src/fn_800AF6F8.c
//    (that one reads arg0->unk0x20 / arg0->unk0x10; this one reads
//    arg0->unk0x24 / arg0->unk0x18 and also arg0->unk0x2054, which the twin
//    never touches) — do not copy the twin's struct. The float pair
//    +0x3484/+0x348C is shared with the twin, which is what ties them together.
//  * CONTROL FLOW (want, with the block roles):
//      0x800AEBCC  prologue; `if (arg0->unk0x18 == 0) return;`  (0x800AEC2C)
//      0x800AEC34  fn_80026D34(arg0->unk0x24, &lbl_8037BD08, &lbl_8037C508,
//                              &lbl_8037CE08, arg0->unk0x18,
//                              arg0->unk0x3484 - arg0->unk0x348C)   <- note r4/r5/r6
//                              are the THREE SYMBOLS lbl_8037BD08 / lbl_8037C508 /
//                              lbl_8037CE08, and r7 (arg0->unk0x18) is the same
//                              load the early-out test used (CSE'd across it).
//      0x800AEC60  outer loop, count = `arg0->unk0x24->unk0x8` (lwz r0, 8(r9)),
//                  body calls fn_8002AE6C(arg0->unk0x24, i)  (0x800AEC9C)
//      0x800AECA0  inner scan over `arg0->unk0x2054` entries, stride 0x20,
//                  field at +0x54 (slwi r9,r11,5 / addi r9,r9,0x54 / add r9,r9,r27)
//      0x800AECE0  fn_8009F498() gate, then a LARGE PS/matrix block
//                  (0x800AECF8-0x800AF39C) that builds a 4x4 in the frame and
//                  psq_st's it to the destination object (+0x78 .. +0x100), and
//                  ends by calling fn_800AEA14 (the PROMOTED sibling, same TU)
//      0x800AEEE8  second phase: `li r29,0` over `arg0->unk0x2054` again,
//                  calls fn_8009FDD8 / fn_800C9780 / fn_8003951C, another
//                  fn_800AEA14 call at 0x800AF610
//      0x800AF620  fn_801257B8, then fn_8003F354 at 0x800AF688
//      0x800AF698  loop back (`blt 0x800aef14`) -> the phase above repeats
//    So the whole body is a two-level loop with a matrix rebuild in the middle;
//    recover the loop bounds from `arg0->unk0x2054` and `arg0->unk0x24->unk0x8`
//    first, then transcribe the matrix block.
//  * STATIC SP* FIXED in r3: the 19 `static s32 sp*` were m2c artefacts (stack
//    temps) and were read as f32 inside the body, so they emitted global
//    accesses AND inserted f32<->s32 conversions at every use. They are now
//    f32 locals. Object size went 2876 B -> 2064 B (want 2860 B), i.e. the
//    original draft's size was coincidentally right for the wrong reason.
//  * TOOLING (important): `tools/disasm.py` and `tools/want_got.py` STALL at
//    the first opcode-4 (paired-single) word — in this function that is
//    0x800AED1C (`psq_lx`), so their want column is `?` for the remaining 500+
//    instructions and any percentage they print is meaningless. Use
//      tools/venv/bin/python tools/ps_diff.py 0x800AEBCC 2860 "-Os" --all
//    (PS-aware; keeps the draft's own `-Os`), or tools/ps_disasm.py for a raw
//    listing. The full decoded want stream is cheap to regenerate.
//  * `-Os` is this draft's FLAG line and was inherited from the m2c fill; the
//    original is -O2 like everything else in the TU (siblings AEA14/AF6F8 use
//    the default), so re-test without it once the body is real.
//
// === WHAT r3 ACTUALLY FIXED (measured, keep these) ===
//  1. PROLOGUE IS NOW BYTE-EXACT: 0x800AEBCC-0x800AEC20 (insns 0-21)
//     `stwu -0x1e0 / mflr / stfd f14..f31 / stmw r20,0x120 / stw r0,0x1e4`.
//     The m2c draft was 8 B short (frame 0x1d8, stfd f14 at 0x148, stmw r14) —
//     i.e. the wrong saved-GPR count AND an 8-byte-short locals area. One
//     `volatile double _dummy;` as the first local fixes the 8 bytes and the
//     `static s32 sp*` -> f32 locals fix (with the typed pointer below) the
//     register set. See AGENTS-recipes §4c / docs/parkings/76.
//  2. FIRST CALL BLOCK 0x800AEC24-0x800AEC60 now matches want instruction for
//     instruction up to the arg0 register number (want r27, got r31) and the
//     masked `lis` immediates. The remaining difference is one register colour.
//  3. ONE TYPED VIEW OF arg0. m2c's `var_r3` + `void *temp_r27` + a cast per
//     access produced THREE copies of arg0 (`mr r30,r3` + `mr r31,r3` + r3
//     itself) where want has ONE (`mr r27,r3`). They are now a single
//     `AebccObj *p` — the body's byte arithmetic just casts it.
//  4. Overall score after r3: ps_diff masked 0.8% -> 1.8%, index-norm 3.0 -> 4.0%,
//     LCS-norm ~19%. Still DIFF — the ~680-insn body is a rewrite (item below),
//     but the function's head, frame, register count and stack layout are now
//     pinned, which is what a rewrite has to build on.

// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 0.4% ([23]rev->0.4%).
// FLAG: -Os
// UPDATED 2026-09-15 (e): 5.2% -> 5.7%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address. tools/raw_sym_scan.py automated the A/B; keep the best body.
#include "types.h"
extern char lbl_8037BD08[];
extern char lbl_8037C508[];
extern char lbl_8037CE08[];
// float view of the +0x3484/+0x348C pair (see src/fn_800AF6F8.c, matched twin)
typedef struct { char _p[0x3484]; f32 f3484; f32 f3488; f32 f348C; } AebccF32;
/* ONE typed view of arg0 covering every field the want touches. Using this
   instead of raw byte arithmetic / several casts keeps all of arg0's accesses on
   the SAME pseudo: want homes arg0 in r27 once (`mr r27, r3`) and reads every
   field through it, while a multi-cast draft creates one copy per cast
   (`mr r30, r3` + `mr r31, r3` in the got).  Fields: +0x18 (the early-out test
   and the 5th arg of fn_80026D34), +0x24 (its 1st arg), +0x2054 (the phase
   count), +0x3484/+0x348C (the float pair). */
typedef struct {
    char pad0x00[0x18];
    s32 unk0x18;
    char pad0x1C[0x8];
    void *unk0x24;
    char pad0x28[0x202C];
    s32 unk0x2054;
    char pad0x2058[0x142C];
    f32 unk0x3484;
    char pad0x3488[0x4];
    f32 unk0x348C;
} AebccObj;
extern char lbl_80298658[];
extern char lbl_8029865C[];
extern s32 lbl_80298660;
extern f32 lbl_80298664;
#include "qb_constants.h"
#include "structs.h"
s32 fn_80026D34(s32, s32, s32, s32, s32, f32);
void * fn_8002AE6C(Unk_31DE137E *o, s32 i);
// 2026-10-08 (r3): the 19 `static s32 sp*` above were m2c's artefact for stack
// temps it could not attribute. They are read/written as f32 inside the body,
// so as file-scope statics they (a) emit a global access instead of a stack
// slot and (b) silently convert f32 <-> s32 at every use. Moved into the body
// as plain f32 locals (declared with the other sp* locals below).

void *fn_800AEBCC(void *arg0) {
    // r3: want's locals area is 8 B larger than the m2c one (frame 0x1e0 vs
    // 0x1d8, every stmw/stfd/LR offset uniformly +8).  A `volatile double`
    // forces a real 8-byte stack slot, which shifts the register save area up
    // by 8 and reproduces want's prologue exactly.  See AGENTS-recipes §4c.
    volatile double _dummy;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp4C;
    f32 sp50;
    f32 sp54;
    f32 sp88;
    f32 sp8C;
    f32 sp90;
    f32 sp98;
    f32 sp9C;
    f32 spA0;
    f32 spA8;
    f32 spAC;
    f32 spB0;
    f32 spB8;
    f32 spBC;
    f32 spC0;
    f32 spC4;
    f32 sp118;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spB4;
    f32 spA4;
    f32 sp94;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp60;
    f32 sp5C;
    Unk_59AB5482 sp58;
    Unk_59AB5482 sp48;
    f32 sp44;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    Unk_59AB5482 sp18;
    f32 sp14;
    f32 spC;
    Unk_E266FB50 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f10_4;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f1;
    f32 temp_f25;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f7_3;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    f32 temp_r10;
    f32 temp_r10_2;
    f32 temp_r22;
    f32 temp_r9_2;
    f32 temp_r9_3;
    f32 temp_r9_5;
    s32 *var_r9;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r20;
    s32 temp_r28;
    s32 temp_r31;
    s32 temp_r4;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_r10;
    s32 var_r11;
    s32 var_r23;
    s32 var_r29;
    s32 var_r31;
    AebccObj *p;
    void *temp_r30;
    Unk_C8FEE62D *temp_r7;
    CStruct *temp_r9;
    CStruct *temp_r9_4;
    void *var_r3;

    p = (AebccObj *)arg0;
    if (p->unk0x18 != 0) {
        var_r3 = fn_80026D34((s32)p->unk0x24, (s32)lbl_8037BD08, (s32)lbl_8037C508, (s32)lbl_8037CE08, p->unk0x18, p->unk0x3484 - p->unk0x348C);
        var_r31 = 0;
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)((char *)p)) + 0x24) + 0x8) > 0) {
            temp_f31 = *(f32 *)&lbl_80298658;
            temp_f30 = *(f32 *)&lbl_8029865C;
            do {
                var_r3 = fn_8002AE6C(((Unk_0771A7B9 *)((char *)p))->unk0x24, var_r31);
                var_r10 = 0;
                var_r11 = ((Unk_0771A7B9 *)((char *)p))->unk0x2054 - 1;
                if (var_r11 >= 0) {
                    var_r9 = (var_r11 << 5) + 0x54 + ((char *)p);
                    do {
                        temp_r0 = *((s32 *)var_r9);
                        var_r9 -= 0x20;
                        if (temp_r0 == var_r3) {
                            var_r10 = 1;
                        }
                        var_r11 -= 1;
                    } while (var_r11 >= 0);
                }
                if (var_r10 == 0) {
                    var_r3 = fn_8009F498();
                    if (var_r3 != NULL) {
                        temp_r4 = var_r31 * 0x10;
                        var_ctr = 4;
                        do {
                            var_ctr -= 1;
                        } while (var_ctr != 0);
                        *((f32 *)&sp48) = temp_f31;
                        temp_r9 = temp_r4 +lbl_8037BD08;
                        sp48.unk0xC = temp_f30;
                        sp48.unk0x4 = temp_f31;
                        sp48.unk0x8 = temp_f31;
                        0;
                        0;
                        temp_f8 = temp_r9->unk0x4;
                        temp_f9 = -temp_r9->unk0x8;
                        temp_f7 = temp_r9->unk0xC;
                        temp_r9->unk0x8 = temp_f9;
                        temp_f13 = temp_f8 * temp_f8;
                        sp5C = temp_f13;
                        temp_f12 = temp_f9 * temp_f9;
                        temp_f11 = temp_f7 * temp_f9;
                        temp_f10 = *(s32 *)((char *)temp_r4 + (s32)0x8037BD08);
                        sp60 = temp_f12;
                        temp_f0 = temp_f10 * temp_f8;
                        sp80 = temp_f11;
                        sp70 = temp_f0;
                        temp_f12_2 = temp_f7 * temp_f8;
                        sp7C = temp_f12_2;
                        temp_f0_2 = temp_f9 * temp_f10;
                        sp6C = temp_f0_2;
                        sp78 = temp_f7 * temp_f10;
                        sp68 = temp_f8 * temp_f9;
                        *((f32 *)&sp8) = temp_f30 - (2.0f * (temp_f13 + temp_f12));
                        spC = 2.0f * (temp_f0 + temp_f11);
                        *((f32 *)&sp58) = temp_f10 * temp_f10;
                        sp8.unk0x8 = (f32) (2.0f * (temp_f0_2 - temp_f12_2));
                        sp14 = temp_f31;
                        sp1C = temp_f30 - (2.0f * (*((f32 *)&sp58) + sp60));
                        *((f32 *)&sp18) = 2.0f * (sp70 - sp80);
                        sp20 = 2.0f * (sp68 + sp78);
                        sp24 = temp_f31;
                        0;
                        0;
                        sp28 = 2.0f * (temp_f0_2 + sp7C);
                        sp2C = 2.0f * (sp68 - sp78);
                        sp34 = temp_f31;
                        sp44 = temp_f30;
                        sp30 = temp_f30 - (2.0f * (*((f32 *)&sp58) + sp5C));
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                    }
                }
                var_r31 += 1;
            } while (var_r31 < (s32) *(s32 *)(*(s32 *)((char *)((char *)((char *)p)) + 0x24) + 0x8));
        }
        var_r29 = 0;
        if ((s32) ((Unk_0771A7B9 *)((char *)p))->unk0x2054 > 0) {
            temp_r20 = lbl_80298660;
            temp_r22 = lbl_80298664;
            do {
                temp_r7 = ((char *)p) + ((var_r29 << 5) + 0x54);
                temp_r31 = temp_r7->unk0x18;
                temp_r30 = temp_r7->unk0x14;
                if (temp_r31 != 0) {
                    var_r23 = var_r29 + 1;
                    GetChecksum_3(temp_r31, QB_SKELETON);
                    temp_r28 = fn_800C9780(arg0);
                    fn_8003951C(QB_BONE_NECK, &sp8);
                    var_ctr_2 = 4;
                    0;
                    0;
                    0;
                    0;
                    0;
                    *((f32 *)&((Unk_31DE137E *)temp_r30)->unk0x64) = (f32) *(s32 *)&lbl_8029865C;
                    do {
                        var_ctr_2 -= 1;
                    } while (var_ctr_2 != 0);
                    fn_80038C04(temp_r28, QB_BONE_NECK, &sp18);
                    var_ctr_3 = 4;
                    do {
                        var_ctr_3 -= 1;
                    } while (var_ctr_3 != 0);
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    temp_r9_2 = *(s32 *)&lbl_80298658;
                    sp94 = temp_r9_2;
                    spC8 = (sp24 * spB8) + ((sp20 * spA8) + ((*((f32 *)&sp18) * sp88) + (sp1C * sp98)));
                    spA4 = temp_r9_2;
                    spB4 = temp_r9_2;
                    temp_f0_3 = *(s32 *)&lbl_80298658;
                    spCC = (sp24 * spBC) + ((sp20 * spAC) + ((*((f32 *)&sp18) * sp8C) + (sp1C * sp9C)));
                    0;
                    temp_f0_4 = *(s32 *)&lbl_80298658;
                    temp_f3 = sp3C * spA0;
                    temp_f4 = *(s32 *)&lbl_80298658;
                    sp118 = (sp38 * temp_f4) + (sp3C * temp_f0_4);
                    temp_f25 = *(s32 *)&lbl_80298658;
                    temp_f1 = (sp28 * sp90) + (sp2C * spA0);
                    temp_f2 = (sp24 * spC4) + ((sp20 * temp_f0_3) + ((*((f32 *)&sp18) * temp_f0_3) + (sp1C * temp_f0_3)));
                    sp104 = (sp54 * spC4) + ((sp50 * *(s32 *)&lbl_80298658) + ((*((f32 *)&sp48) * temp_f25) + (sp4C * temp_f0_4)));
                    temp_f5 = (sp44 * spC4) + ((sp40 * temp_f25) + sp118);
                    temp_f10_2 = (sp54 * spB8) + ((sp50 * spA8) + ((*((f32 *)&sp48) * sp88) + (sp4C * sp98)));
                    spD4 = temp_f2;
                    temp_f9_2 = (sp54 * spBC) + ((sp50 * spAC) + ((*((f32 *)&sp48) * sp8C) + (sp4C * sp9C)));
                    spF8 = temp_f10_2;
                    spFC = temp_f9_2;
                    sp100 = (sp54 * spC0) + ((sp50 * spB0) + ((*((f32 *)&sp48) * sp90) + (sp4C * spA0)));
                    spE4 = (sp34 * spC4) + ((sp30 * temp_f25) + ((sp28 * temp_f4) + (sp2C * temp_f0_4)));
                    spF4 = temp_f5;
                    temp_f7_2 = (sp34 * spBC) + ((sp30 * spAC) + ((sp28 * sp8C) + (sp2C * sp9C)));
                    spDC = temp_f7_2;
                    spD0 = (sp24 * spC0) + ((sp20 * spB0) + ((*((f32 *)&sp18) * sp90) + (sp1C * spA0)));
                    spE8 = (sp44 * spB8) + ((sp40 * spA8) + ((sp38 * sp88) + (sp3C * sp98)));
                    temp_f13_2 = (sp44 * spBC) + ((sp40 * spAC) + ((sp38 * sp8C) + (sp3C * sp9C)));
                    temp_f8_2 = (sp34 * spB8) + ((sp30 * spA8) + ((sp28 * sp88) + (sp2C * sp98)));
                    spEC = temp_f13_2;
                    spD8 = temp_f8_2;
                    spE0 = (sp34 * spC0) + ((sp30 * spB0) + temp_f1);
                    spF0 = (sp44 * spC0) + ((sp40 * spB0) + ((sp38 * sp90) + temp_f3));
                    0;
                    *((f32 *)&sp58) = *(s32 *)&lbl_80298658;
                    0;
                    0;
                    0;
                    0;
                    ((Unk_E266FB50 *)&sp58)->unk0xC = (f32) *(s32 *)&lbl_8029865C;
                    temp_r10 = *(s32 *)&lbl_80298658;
                    sp58.unk0x4 = temp_r10;
                    sp58.unk0x8 = temp_r10;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    fn_800AEA14(((char *)p), temp_r30, temp_f1, temp_f2, temp_f3, spBC, temp_f5, 0, temp_f7_2, temp_f8_2, temp_f9_2, temp_f10_2, 0, 0, temp_f13_2);
                } else {
                    var_r23 = var_r29 + 1;
                    if ((s32) temp_r7->unk0x1C != -1) {
                        var_ctr_4 = 4;
                        do {
                            var_ctr_4 -= 1;
                        } while (var_ctr_4 != 0);
                        *((f32 *)&sp48) = *(s32 *)&lbl_80298658;
                        sp48.unk0xC = (f32) *(s32 *)&lbl_8029865C;
                        temp_r9_3 = *(s32 *)&lbl_80298658;
                        sp48.unk0x4 = temp_r9_3;
                        sp48.unk0x8 = temp_r9_3;
                        temp_r0_2 = temp_r7->unk0x1C * 0x10;
                        0;
                        temp_r9_4 = temp_r0_2 + 0x8037BD08;
                        0;
                        temp_f8_3 = temp_r9_4->unk0x4;
                        temp_f9_3 = -temp_r9_4->unk0x8;
                        temp_f7_3 = temp_r9_4->unk0xC;
                        temp_r9_4->unk0x8 = temp_f9_3;
                        temp_f13_3 = temp_f8_3 * temp_f8_3;
                        sp5C = temp_f13_3;
                        temp_f12_3 = temp_f9_3 * temp_f9_3;
                        temp_f10_3 = *(s32 *)((char *)temp_r0_2 + (s32)0x8037BD08);
                        temp_f11_2 = temp_f7_3 * temp_f9_3;
                        sp60 = temp_f12_3;
                        sp80 = temp_f11_2;
                        temp_f0_5 = temp_f10_3 * temp_f8_3;
                        sp70 = temp_f0_5;
                        temp_f12_4 = temp_f7_3 * temp_f8_3;
                        sp7C = temp_f12_4;
                        temp_f0_6 = temp_f9_3 * temp_f10_3;
                        sp6C = temp_f0_6;
                        sp78 = temp_f7_3 * temp_f10_3;
                        *((f32 *)&sp8) = *(s32 *)&lbl_8029865C - (2.0f * (temp_f13_3 + temp_f12_3));
                        temp_f10_4 = temp_f10_3 * temp_f10_3;
                        spC = 2.0f * (temp_f0_5 + temp_f11_2);
                        *((f32 *)&sp58) = temp_f10_4;
                        sp68 = temp_f8_3 * temp_f9_3;
                        sp8.unk0x8 = (f32) (2.0f * (temp_f0_6 - temp_f12_4));
                        temp_r9_5 = *(s32 *)&lbl_80298658;
                        sp14 = temp_r9_5;
                        *((f32 *)&sp18) = 2.0f * (sp70 - sp80);
                        sp1C = *(s32 *)&lbl_8029865C - (2.0f * (temp_f10_4 + sp60));
                        sp20 = 2.0f * (sp68 + sp78);
                        sp24 = temp_r9_5;
                        sp34 = temp_r9_5;
                        sp2C = 2.0f * (sp68 - sp78);
                        0;
                        sp28 = 2.0f * (temp_f0_6 + sp7C);
                        0;
                        sp30 = *(s32 *)&lbl_8029865C - (2.0f * (temp_f10_4 + sp5C));
                        sp44 = *(s32 *)&lbl_8029865C;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                        fn_800AEA14(((char *)p), temp_r30);
                    }
                }
                var_r3 = Script_GetInteger(QB_DEBUG_CUTSCENES, 0);
                if (var_r3 != NULL) {
                    *((f32 *)&sp8) = *(s32 *)&lbl_8029865C;
                    ((Unk_59AB5482 *)&sp8)->unk0x4 = temp_r20;
                    temp_r10_2 = *(s32 *)&lbl_8029865C;
                    sp8.unk0x8 = temp_r10_2;
                    ((Unk_59AB5482 *)&sp8)->unk0xC = temp_r10_2;
                    *((f32 *)&sp18) = temp_r22;
                    var_r3 = fn_8003F354(temp_r30 + 0xD0, temp_r30 + 0x58, &sp8, 0, 1, 0, QB_UNKNOWN_0xC80000FF, temp_r10_2);
                    sp18.unk0x8 = temp_r22;
                    sp18.unk0x4 = temp_r22;
                    sp18.unk0xC = temp_r10_2;
                }
                var_r29 = var_r23;
            } while (var_r29 < (s32) ((Unk_0771A7B9 *)((char *)p))->unk0x2054);
        }
    }
    return var_r3;
}
