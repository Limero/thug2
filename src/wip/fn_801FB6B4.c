// WIP DRAFT (non-matching) — PARKED at NEAR 61.3% (masked, -mps-float), 2026-08-24.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 56.4482% -> 57.0825% `volatile` keyword(s) removed from the body
// family=m2c range=0x801FB6B4-0x801FBE18 size=1892B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
//
// PARKING NOTES (read before retrying — this replaced a structurally-wrong m2c draft):
//
// Script-command hash dispatcher, 16-case u32 switch (case values span >=0x80000000
// -> switch index MUST be `u32 arg1`, recipe 84; m2c had s32 and rooted the compare
// tree at the signed median). Fully hand-rebuilt from disasm. Structure is verified
// correct: prologue/switch tree/case bodies/shared ret tails all match mnemonically;
// compiled size = want = 1892B exactly. Remaining 183 word diffs are register-color
// and micro-schedule artifacts, NOT structural.
//
// WHAT CRACKED IT (each verified by score delta here):
//  - frame-template struct `Fr` (§6q-86) for the whole locals region sp8..sp4C —
//    individual scalars got re-sorted into wrong slots;
//  - `register f32 *pv __asm__("r30")` scratch-web pin for the vec base pointer
//    (§6y-124 class) — fixes a global r29/r30 role rotation (doc-32 flavored);
//  - two-web pointer birth in case 0x5828E852: p58=&fr.v08; pv=p58;
//    __asm__("" : "+r"(p58)); stores/arg via p58, post-psq uses via pv (§6s-1);
//  - fn_801FB1C4 takes TWO args (its body reads r4: mr r3,r4; cmpw) — the entry
//    found by fn_801FB2A8 is passed as arg1, which is what produces want's
//    `or. r4,r3,r3` copy+test fusion at 0x801FBDA0 (recipe 56 shape);
//  - recipe-88 param-reassignment in case 0x8798E959: walk result assigned back
//    INTO arg0 so it homes in arg0's dead r29 (`mr r29,r3` like want);
//  - opaque asm-anchor block for the two lbl_802AE5CC float args of
//    fn_801F8430/fn_801F8768 (lis/lfs @ha/@l sandwich, §70-144) + pv-pin frees
//    the extra saved reg -> stmw span matches when combined (see variant note below).
//
// REMAINING DIFFS (structural map, ~183 words in 11 runs):
//  1. 0x801FB8D4 missing `li r3,0`: case D2C98192 wants [cmpwi][li r3,0][beq EPI]
//     (var_r3 kept IN r3); every C form either drops the li (goto-form, current)
//     or shifts the whole stream (-23%; var-form interacts badly with tail layout).
//  2. 0x801FB914..92C (~9w): case-5828 vec-init store schedule. want emits
//     [v08(r1-disp)][v10][v14][v0c] via a birth-reg R5 that doubles as the call
//     arg, with `mr r30,r5` home-copy after store #1; got births in r9 and emits
//     [v14][v0c][v08][v10]. Source-order permutations are scheduler-no-ops here.
//  3. 0x801FB9B4 missing `mr r0,r3` staging of fn_80230BEC's result before the
//     store to sp20 (want routes via r0; got stores r3 directly). 1 word.
//  4. 0x801FB9EC/FBA28 area: want materializes TWO page anchors early (r29 for
//     lbl_803A30E0 bss-label, r30 for the float) interleaved INSIDE the psq pair
//     copies; got defers both to just-before use. Position-only, masked-equal
//     immediates. The asm-anchor sandwich (§70-144) placed them but cost elsewhere.
//  5. 0x801FBA18..34 (~4w): stw r3,0x18(r31) / lfs f1 / addi r4 interleave order
//     around bl ContainsFlag -> bl fn_801F8430 (doc-15 expand_call emission order).
//  6. 0x801FBA58 extra `li r3,0`: GCC inlines the ret0 materialization into the
//     LA58-analog err-tail instead of branching backward to the shared L998 block
//     (+1 insn -> cascades the rest of the function). All label placements tried;
//     plain per-arm `return 0` is far worse (-25%).
//  7. 0x801FBC18 extra `mr r3,r31`: case-8798E959 entry web (fn_801FB2A8 result)
//     homed to r31 + copy-back; want keeps it in r3 across the guard
//     (`or. r3,r3,r3`, chained into fn_801F9B64 with zero setup). Resists
//     assignment-in-condition, s32/void* proto flips, old-style protos. THE main
//     remaining whale: killing this one insn resyncs ~100 words downstream.
//
// RETRY HINTS:
//  - Re-test items 1/6/7 after ANY new anti-homing or branch-tail-sharing recipe
//    lands (docs/parkings/15-call-arg-setup-scheduling.md,
//    docs/parkings/32-walker-role-rotation.md, doc-33 inlined-iterator webs —
//    this dispatcher walks fn_801FB2A8 lists and shows doc-32-style role rotation).
//  - Item 7 smells like §6ag-3's "=r"/"0"-matched init wedge: try creating the
//    entry web inside r3 explicitly IF a future cc1 accepts local pins on r3
//    safely (current attempt over-constrained globally).
//  - The stmw span flip-flops between r26/r27 with anchor strategy: pinning pv to
//    r30 + keeping the natural (non-asm) float loads gave 60.0% with stmw r26;
//    adding the asm-anchor sandwich gave perfect stmw r27 but 58.6%. Current file
//    keeps the higher-scored 61.3% form (pin, no asm-anchor). Both variants are
//    one experiment from EXACT if items above crack.
//  - Callee arities audited from prologues (zone ground truth): fn_801FAFD4 is a
//    frameless void 4-arg leaf (reads obj->0x20 vector, writes *r4/*r5/*r6 only);
//    fn_801FB1C4 is 2-arg (obj, node) despite most call sites passing garbage r4;
//    fn_802337CC is (ptr, f32-in-f1); fn_801F8C14 returns f32 in f1;
//    fn_8012788C 5-arg (s32,u32,f32,f32,f32); fn_8012772C 3-arg (s32,u32,f32);
//    Script_RunScript 5-arg; AddChecksum 3-arg at ALL three sites here (one site is
//    the chained alloc idiom AddChecksum(temp=CStruct_ctor(CStruct_new(8)),h1,h2),
//    §70-127 assignment-expression chain); fn_801FBE18 ignores its arg but callers
//    pass arg0 (§6y-132); everything else matched the AGENTS.md zone truths.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_8029FBE8[];
extern f32 lbl_802AE5CC;
extern f32 lbl_802AE5D0;
extern f32 lbl_802AE5D4;
extern f32 lbl_802AE5D8;
extern f32 lbl_802AE5DC;
extern char lbl_803A30E0[];
extern s32 lbl_80305F7C;

extern void fn_801FAFD4(Unk_C7387A53 *, void *, f32 *, f32 *);
extern s32 fn_801FBE18(void *);
extern void fn_801FB248(Unk_C7387A53 *);
extern s32 fn_801F8250(void *, void *);
extern s32 fn_802337CC(CStruct *, f32);
extern s32 fn_80230BEC(s32);
extern s32 fn_80233404(void);
extern void fn_80230C54(void);
extern void *fn_801F9820(Unk_C7387A53 *);
extern f32 fn_801F8C14(void *);
extern s32 ContainsFlag(CStruct *, u32);
extern s32 GetVector(void *, u32, CStruct *, s32);
extern s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
extern s32 GetInteger(CStruct *, u32, s32 *, s32);
extern void fn_801F8430(Unk_C7387A53 *, void *, void *, f32);
extern void fn_801F8768(void *, void *, void *, f32);
extern void fn_801FB15C(Unk_C7387A53 *);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(void *);
extern void AddChecksum(CStruct *, u32, u32);
extern void Script_RunScript(u32, void *, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern void fn_801FB550(void *, void *);
extern void fn_801FB50C(Unk_C7387A53 *);
extern void *fn_801FB2A8(Unk_C7387A53 *, s32);
extern s32 fn_801F9C64(void *, s32, void *, s32);
extern void *fn_801F9B64(Unk_C7387A53 *, s32);
extern void fn_801F8DA8(void *, s32, s32);
extern s32 fn_801FA6FC(void *, Unk_C7387A53 *, void *);
extern void fn_801FB2D4(Unk_C7387A53 *);
extern void fn_801FA6B8(Unk_C7387A53 *);
extern s32 fn_801F9890(Unk_C7387A53 *);
extern void AddInteger(CStruct *, u32, s32);
extern void fn_801FB1C4(Unk_C7387A53 *, CStruct *);
extern void fn_801FA5E4(Unk_C7387A53 *);
extern void fn_801FA628(Unk_C7387A53 *);
extern void fn_8012772C(void *, u32, f32);
extern void fn_8012788C(void *, u32, f32, f32, f32);

typedef struct {
    f32 v08;
    f32 v0c;
    f32 v10;
    f32 v14;
    s32 v18;
    s32 v1c;
    s32 v20;
    s32 v24;
    f32 v28;
    f32 v2c;
    s32 v30;
    s32 v34;
    s32 v38;
    s32 v3c;
    s32 v40;
    s32 v44;
    s32 v48;
    s32 v4c;
} Fr;

s32 fn_801FB6B4(void *arg0, u32 arg1, CStruct *arg2, CScript *arg3) {
    Fr fr;
    register f32 *pv __asm__("r30");
    f32 *p58;
    f32 temp_f0;
    f32 temp_f13;
    s32 var_r3;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    Unk_C7387A53 *temp_r3_2;
    Unk_C4654E77 *temp_r3_3;

    switch (arg1) {
    case QB_GETCURSORPOSITION:
        temp_f0 = *(f32 *)&lbl_802AE5CC;
        temp_f13 = lbl_802AE5D0;
        pv = &fr.v08;
        pv[0] = temp_f0;
        pv[3] = temp_f13;
        pv[1] = temp_f0;
        pv[2] = temp_f0;
        fr.v28 = temp_f0;
        fr.v2c = temp_f0;
        fn_801FAFD4(arg0, pv, &fr.v28, &fr.v2c);
        fr.v0c = fr.v0c + fr.v28;
        fn_8012788C(arg3->unk0x18, QB_POS, pv[0], fr.v0c, pv[2]);
        fn_8012772C(arg3->unk0x18, QB_ANGLE,
                    (*(f32 *)(((Unk_C7387A53 *)arg0)->unk0x20 + 0x7C) * lbl_802AE5D4) / lbl_802AE5D8);
        goto block_71;
    case QB_NEWRAIL:
        if (fn_801FBE18(arg0) == 0) { return 0; }
        fn_801FB248(arg0);
        return 1;
    case QB_MAXRAILSREACHED:
        temp_r3 = fn_801FBE18(arg0);
        return temp_r3 == 0;
    case QB_ADDNEWPOSITION:
        temp_f13 = lbl_802AE5D0;
        temp_f0 = lbl_802AE5CC;
        p58 = &fr.v08;
        pv = p58;
        __asm__("" : "+r"(p58));
        fr.v08 = temp_f0;
        p58[0] = temp_f0;
        p58[3] = temp_f13;
        p58[1] = temp_f0;
        p58[2] = temp_f0;
        GetVector(arg2, QB_POS, p58, 0);
        temp_r3_2 = *((void * *)&((Unk_C7387A53 *)arg0)->unk0x28);
        if (temp_r3_2 == NULL) {
            goto block_40;
        }
        temp_r31 = temp_r3_2->unk0xC;
        if (temp_r31 == NULL) {
            goto lbl_964;
        }
        if (fn_801F8250((char *)temp_r31 + 8, pv) == 0) {
            goto block_71;
        }
        __asm__("" : "+r"(temp_r31));
    lbl_964:
        *(__ps_t *)&fr.v18 = *(__ps_t *)&fr.v08;
        *(__ps_t *)&fr.v20 = *(__ps_t *)(pv + 2);
        if (fn_802337CC(&fr.v18, lbl_802AE5DC) != 1) {
            return (temp_r31 != 0) ? 1 : 0;
        }
        fr.v24 = (s32)lbl_8029FBE8;
        fr.v20 = fn_80230BEC(0);
        if (fn_80233404() != 0) {
            __asm__ __volatile__("");
            fr.v24 = (s32)lbl_8029FBE8;
            fn_80230C54();
            goto block_40;
        }
        temp_r3_3 = fn_801F9820(*((void * *)&((Unk_C7387A53 *)arg0)->unk0x28));
        if (temp_r3_3 == NULL) {
            goto lbl_err2;
        }
        temp_r3_3->unk0x8 = *(__ps_t *)&fr.v08;
        temp_r3_3->unk0x10 = *(__ps_t *)(pv + 2);
        temp_f0 = fn_801F8C14(temp_r3_3);
        temp_r3_3->unk0x20 = fr.v0c - temp_f0;
        temp_r3_3->unk0x18 = ContainsFlag(arg2, QB_ADDPOST);
        fn_801F8430(temp_r3_3, lbl_803A30E0, lbl_803A30E0, *(f32 *)&lbl_802AE5CC);
        fn_801F8768(temp_r3_3, lbl_803A30E0, lbl_803A30E0, *(f32 *)&lbl_802AE5CC);
        fr.v24 = (s32)lbl_8029FBE8;
        fn_80230C54();
        goto block_71;
    lbl_err2:
        fr.v24 = (s32)lbl_8029FBE8;
        fn_80230C54();
        /* fall through */
    block_40:
        return 0;
    case QB_CLEARRAILEDITOR:
        fn_801FB15C(arg0);
        goto block_71;
    case QB_SETEDITINGMODE:
        GetChecksum_2(arg2, QB_MODE, (char *)arg0 + 0x2C, 0);
        AddChecksum((void *)(temp_r31 = CStruct_ctor((void *)CStruct_new(8))), QB_MODE, QB_RAIL_PLACEMENT);
        Script_RunScript(QB_PARKED_SET_HELPER_TEXT_MODE, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete((void *)temp_r31, 3);
        }
        goto block_71;
    case QB_GETEDITINGMODE:
        AddChecksum(*((void * *)&arg3->unk0x18), QB_MODE, ((Unk_C7387A53 *)arg0)->unk0x2C);
        goto block_71;
    case QB_DRAWDOTTEDLINE:
        GetVector(arg2, QB_POS, &fr.v08, 0);
        fn_801FB550(arg0, &fr.v08);
        goto block_71;
    case QB_DELETEDOTTEDLINE:
        fn_801FB50C(arg0);
        goto block_71;
    case QB_UPDATERAILPOINTPOSITION:
        fr.v30 = 0;
        GetChecksum_2(arg2, QB_RAIL_ID, &fr.v30, 0);
        fr.v34 = 0;
        GetInteger(arg2, 0xAB3C14U, &fr.v34, 0);
        GetVector(arg2, QB_POS, &fr.v08, 0);
        temp_r3_3 = fn_801FB2A8(arg0, fr.v30);
        if (temp_r3_3 == NULL) {
            break;
        }
        if (fn_801F9C64(temp_r3_3, fr.v34, &fr.v08, ContainsFlag(arg2, QB_UPDATESUPERSECTORS)) != 0) {
            goto block_71;
        }
        goto block_40;
    case QB_HIGHLIGHTRAILPOINT:
        fr.v38 = 0;
        GetChecksum_2(arg2, QB_RAIL_ID, &fr.v38, 0);
        fr.v3c = 0;
        GetInteger(arg2, 0xAB3C14U, &fr.v3c, 0);
        temp_r3_3 = fn_801FB2A8(arg0, fr.v38);
        arg0 = fn_801F9B64(temp_r3_3, fr.v3c);
        if (arg0 == NULL) {
            break;
        }
        temp_r30 = ContainsFlag(arg2, QB_FLASH);
        fn_801F8DA8((void *)arg0, temp_r30, ContainsFlag(arg2, QB_INCLUDEENDPOSTS));
        goto block_71;
    case QB_DELETERAILPOINT:
        fr.v40 = 0;
        GetChecksum_2(arg2, QB_RAIL_ID, &fr.v40, 0);
        temp_r3_3 = fn_801FB2A8(arg0, fr.v40);
        if (temp_r3_3 == NULL) {
            goto block_40;
        }
        fr.v44 = 0;
        GetInteger(arg2, 0xAB3C14U, &fr.v44, 0);
        temp_r3 = (s32)fn_801F9B64(temp_r3_3, fr.v44);
        var_r3 = 0;
        if (temp_r3 == 0) {
            return var_r3;
        }
        fn_801FA6FC(arg0, temp_r3_3, (void *)temp_r3);
        fn_801FB2D4(arg0);
        goto block_71;
    case QB_UNHIGHLIGHTALLRAILS:
        fn_801FA6B8(arg0);
        goto block_71;
    case QB_GETEDITEDRAILINFO:
        fr.v48 = 0;
        GetChecksum_2(arg2, QB_RAIL_ID, &fr.v48, 0);
        temp_r3_3 = fn_801FB2A8(arg0, fr.v48);
        if (ContainsFlag(arg2, QB_CURRENTRAIL) != 0) {
            temp_r3_3 = *((void * *)&((Unk_C7387A53 *)arg0)->unk0x28);
        }
        if (temp_r3_3 == NULL) {
            goto block_40;
        }
        AddChecksum(*((void * *)&arg3->unk0x18), QB_RAIL_ID, *((s32 *)&temp_r3_3->unk0x10));
        temp_r30 = arg3->unk0x18;
        AddInteger((void *)temp_r30, QB_NUM_POINTS, fn_801F9890(temp_r3_3));
        goto block_71;
    case QB_DELETERAIL:
        fr.v4c = 0;
        GetChecksum_2(arg2, QB_RAIL_ID, &fr.v4c, 0);
        temp_r3_2 = fn_801FB2A8(arg0, fr.v4c);
        if (temp_r3_2 == NULL) {
            goto block_71;
        }
        fn_801FB1C4(arg0, temp_r3_2);
        goto block_71;
    case QB_DESTROYEDITEDRAILSECTORS:
        lbl_80305F7C = 1;
        if (ContainsFlag(arg2, QB_DONOTUPDATESUPERSECTORS) != 0) {
            lbl_80305F7C = 0;
        }
        fn_801FA5E4(arg0);
        fn_801FA628(arg0);
        lbl_80305F7C = 1;
        goto block_71;
    default:
        return 2;
    }
block_71:
    return 1;
}
