// PARKED 2026-10-30 — base 0.7% (masked) -> final 0.18% (masked, LENGTH-MISMATCHED so both are meaningless: 6cs-1 / 6es)
// Object .text = 0x8c8 (2248B) vs want 0xB2C (2860B): 612B / 153 words SHORT. .rodata 8B persists. .bss eliminated (was 0x24). Inline asm: 0 instructions emitted (1 zero-code "m" pin + 0 "=r" births).
// Base note: WIP.md records 0.4% for the m2c body; the 2026-09-11 store-order search header recorded 0.7%. Both were measured against a body that was 584 words short, so neither is a meaningful baseline either.
//
// ============ WHY (measured, not hypothesised) ============
// 1. FRAME — now correct, was not. want: stwu -0x1180, stmw r14,0x1118, stw r0,0x1184 (locals region 0x1110 per the
//    CORRECTED 6db closed form frame = Gsave + 4*n, L = Gsave - 8, no 8-byte rounding). m2c had 9 file-scope
//    `static s32` -> .bss 0x24 and a 0x160 frame. They are now function locals; a `char gap[0x10E0]` kept alive by
//    a zero-code "m" pin (6ap-5 / 6dt) reproduces Gsave = 0x1118 EXACTLY. Frame is 0x11D0 vs 0x1180 because this
//    body still saves 14 FPRs (f18-f31) where the want saves 4 (f28-f31) — m2c has too many live f32 temps, i.e.
//    the float webs have not been de-merged yet.
// 2. LENGTH — 153 words missing. 38 of them are m2c's `0;` stubs, which are NOT dead code: they are the want's
//    paired-single blocks (84 of 715 instructions are primary opcodes 4/56/59). Decoded so far:
//      a) 0x8007147C-0x800714AC: 4 psq_l + 2 ps_muls0 + 2 ps_add + 4 psq_st into r1+0x28/0x30/0x38/0x40
//         (quaternion/matrix rows at arg0+0x88/0x90/0x98/0xA0, scaled by the pair at arg0+0xA8).
//      b) 0x8007181C-0x80071A3C: three 4-term cross products over eight pairs at arg0+0x28..0x67, then three
//         16-byte pair copies of arg0+0x28/0x38/0x48 into the out-param at arg0+0x1058/0x1068/0x1078.
//    Both are blocked on the same thing (see 3), so they were left as `0;` rather than half-written.
// 3. PAIRED-SINGLE WALL (measured with isolated per-builtin probes, 17 forms) — the want uses a THREE-operand
//    ps_muls0: `ps_muls0 f13,f13,f0,f10` has A=f13, B=f0, C=f10, D=f13 (all three source fields live, result
//    in-place on arg1). No `__builtin_ps_*` in cc1 3.9.3 can emit that:
//      - 2-arg mul-family (muls0=12 / muls1=13 / mul=25) -> A=arg1, C=arg2, D=reg(arg2), **B=0**;
//      - 2-arg add/sub/div (21/20/18)                    -> A=arg1, B=arg2, D=reg(arg2), C=0;
//      - 3-arg madd/madds0/madds1/msub/nmadd/nmsub/sel/sum0/sum1 -> A=arg1, C=arg2, B=arg3=**D**; none
//        emits xo5=12 at all;
//      - madds0/madds1(a,b,0.0f) is a dead end: the whole TU DCEs to an EMPTY object (6ax-228 trap).
//    So the muls0 seed of every dot product is only reachable by inline asm. Reproducing the rest of the
//    function would mean ~10 asm ps_muls0 words plus 38 restored `0;` sites; that is a fresh full rebuild,
//    not a repair of this draft.
// 4. STRUCT LAYOUT — m2c's local model is wrong in detail and this cannot be fixed locally. The want's touched
//    slots are 0x08-0x2B (fn_8000723C's out-quad, 36B) + 0x28-0x47 (fn_8000728C's min/euler array, 32B) +
//    0x48-0x57 (box) + 0x58-0x67 (0x8000:0x8008) + 0x1058/0x1068/0x1078 (out floats) + 0x10A8/0x10B0 (returned
//    16B pair) + 0x10F0/0x10F4 — and 0x5C..0x1057 is never read or written, i.e. ~0xFFC of genuinely unused
//    local. m2c's `sp10F0` alone is a 1-float slot that the want uses as a 2-float PAIR (`psq_l f10,0(r9)`),
//    and its `sp2C..sp54` block does not match either array. Correcting it means re-deriving every stack
//    offset from the want, which is the full rebuild again.
// 5. NOT the cause: callees. Every call now matches want's arg registers (see the promoted-oracle prototypes
//    below), the Mem_Alloc2->fn_8009636C chain is a single expression (recipe 23 / 4t), fn_8006BC80 really
//    is 1-arg, fn_8008741C really is 6xf32 at THIS call site despite its promoted `void` stub (6di), and the
//    game sinf/cosf are fn_80271170 / fn_80271070. 12 m2c `crclr cr1eq` removed, 0 added.
//
// ============ LEVERS MEASURED THIS ROUND ============
//  - no prototype/arity lever is left: all 16 call sites audited against want's arg registers (6dc / 6di / 6bf).
//  - -mps-float: forced on by the `__ps_t` in the fn_8000723C prototype; DIFF either way. All 17 sched/GCSE
//    flags and -O1/-O3/-Os are no-ops or worse on this body (6bx: re-measure flags AFTER the semantic round —
//    they were, and none is load-bearing).
//  - store-order / permutation search: NOT re-run. 6es + 280 are meaningless while the object is 153 words
//    short; the 2026-09-11 search in the old header was measuring a mis-aligned stream.
//  - frame-size sweep: `char gap[N]` for N = 0xF00..0x1100; 0x10E0 is the unique value giving Gsave = 0x1118
//    (0x10D0 -> 0x1108, 0x10F0 -> 0x1128). Linear, as 6db predicts.
//  - register pins: none added. Per 6cs-3 / 6ds-2 the float-web de-merge has to come first; pinning on top of
//    14 live FPRs would move the pool, not the count.
//
// ============ WHAT THE NEXT ATTEMPT SHOULD DO ============
// Full rebuild of the body from the want's disassembly with `__ps_t` locals, in this order:
//   (a) re-derive the locals layout from the want's stack offsets and build it as ONE frame-template struct
//       (6q-86) with explicit `char pad[]` for 0x5C..0x1057 — the gap filler alone already matches Gsave, so
//       this is the cheap half;
//   (b) de-merge the float webs: give each loop/cross-product phase its OWN named f32/__ps_t temps (6an-3 / 6bu /
//       6cw) to get from 14 saved FPRs down to retail's 4;
//   (c) with the FPR pressure gone, re-run the want_got diff — only then is a store-order / arg-setup pass
//       meaningful;
//   (d) the ps_muls0 seeds are the one thing that will still need inline asm; decide there whether the ~10
//       words fit the 4g / 6af-180 budget (they would, at ~1.4%, but the rest of the body must be real C first).
//
// Original: tools/fill_wip_drafts.py m2c body, inert (not in splits.txt / configure.py), never linked.
// family=m2c range=0x8007141C-0x80071F48 size=2860B
// INERT: not registered in splits.txt/configure.py — never compiled into the DOL,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern char lbl_80295308[];
extern char lbl_802FFE98[];
extern char lbl_80366DDC[];

/* ---- promoted bodies in src/ are the arity/type oracle (6dc / 6di) ---- */
void fn_8000723C(__ps_t *arg1, __ps_t *arg2);
void fn_8000728C(f32 *arg0, f32 *arg1);
s32 fn_8010391C(void *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg4);
/* promoted as (void), but the want materialises f1..f6 before the bl: 6 f32 */
s32 fn_8008741C(f32, f32, f32, f32, f32, f32);
s32 fn_8007219C(s32 arg0);
void fn_8006BC80(void *o);
void fn_8006BC90(void *arg0, s32 arg1);
void fn_8000F2F8(void *arg0, s32 arg1);
void *Mem_Alloc(s32 arg0);
void fn_8000F320(void *self);
void *Mem_Alloc2(s32 arg0);
void *fn_8009636C(void *arg0);
void Mem_Free2(void *arg0);
s32 fn_8008279C(s32 *arg0, s32 arg1);
f32 fn_80271170(f32);   /* game sinf */
f32 fn_80271070(f32);   /* game cosf */

void fn_8007141C(Unk_C8FEE62D *arg0, void **arg2) {
    /* These nine were file-scope `static s32` in the m2c body: they reserved
       NO frame (the object carried a 0x24-byte .bss) and every store to them
       was DCE'd. All nine are address-taken (passed as &spN to fn_8008741C /
       fn_8008279C), so the want has them in the locals region. The want's
       prologue is `stwu r1,-0x1180 / mflr / stmw r14,0x1118 / stw r0,0x1184`
       -> by the corrected 6db closed form (frame = Gsave + 4*nSavedGPRs,
       L = Gsave - 8, NOT rounded up to 8) the locals region is 0x1110 bytes. */
    s32 sp105C;
    s32 sp106C;
    s32 sp107C;
    f32 sp2C;
    f32 sp30;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp10F0;
    s32 sp10EC;
    void *sp10E8;
    u8 sp10E4;
    u8 sp10E0;
    u8 sp10DC;
    u32 sp10D8;
    f32 sp10D4;
    f32 sp10D0;
    f32 sp10CC;
    f32 sp10C8;
    f32 sp10C4;
    f32 sp10C0;
    f32 sp10BC;
    f32 sp10B8;
    f32 sp10B4;
    f32 sp10B0;
    f32 sp10AC;
    f32 sp10A8;
    f32 sp10A4;
    f32 sp10A0;
    f32 sp109C;
    f32 sp1098;
    f32 sp1094;
    f32 sp1090;
    f32 sp108C;
    f32 sp1088;
    f32 sp1080;
    f32 sp1078;
    f32 sp1070;
    f32 sp1068;
    f32 sp1060;
    f32 sp1058;
    s32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp28;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f1;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f8;
    f32 temp_f9;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r10_4;
    s32 temp_r26;
    s32 temp_r29_2;
    s32 temp_r6;
    s32 temp_r9_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r11;
    s32 var_r11_2;
    s32 var_r11_3;
    s32 var_r26;
    s32 var_r28;
    s32 var_r9_3;
    u16 *var_r19;
    u16 temp_r0;
    u16 temp_r0_2;
    u16 temp_r11_2;
    u16 temp_r9_3;
    u16 temp_r9_4;
    u16 var_r0;
    u32 var_r14;
    u32 var_r24;
    u8 temp_r11_3;
    u8 temp_r4;
    u8 temp_r5;
    u8 temp_r8;
    u8 temp_r9;
    u8 var_r0_2;
    u8 var_r0_6;
    u8 var_r0_7;
    u8 var_r7;
    u8 var_r9;
    u8 var_r9_2;
    void **var_r17;
    void *temp_r0_5;
    Unk_C8FEE62D *temp_r10_3;
    Unk_C8FEE62D *temp_r11;
    Unk_C7387A53 *temp_r15;
    Unk_4A174A22 *temp_r27;
    Unk_C8FEE62D *temp_r28;
    CStruct *temp_r29;
    void *temp_r29_3;
    CStruct *temp_r30;
    CStruct *temp_r31;
    Unk_C8FEE62D *temp_r31_2;
    Unk_9994C3F5 *temp_r3;
    void *temp_r9_5;
    void *var_r18;
    void *var_r22;
    void *var_r30;
    Unk_9994C3F5 *var_r3;
    /* The want's frame is 0x1180 with Gsave 0x1118, so its locals region is
       exactly 0x1110 bytes, while the highest stack slot the want TOUCHES is
       0x10F0. The 0x5C..0x1057 range is never read or written by the want, so
       it is a real-but-unused local (most likely the 0x800 scratch buffer that
       fn_8010391C is called with; see the park block). Declared last and kept
       alive with a zero-code "m" pin (6ap-5 / 6dt) so it reserves the bytes
       without emitting anything. */
    char gap[0x10E0];
    __asm__("" : : "m"(gap));

    var_r17 = arg2;
    temp_r15 = arg0->unk0x1C;
    var_r18 = NULL;
    var_r22 = NULL;
    sp10EC = temp_r15->unk0xC;
    fn_8000723C(&sp8, (char *)arg0 + 0x98);
    sp10F0 = arg0->unk0xA8;
    0;
    0;
    0;
    0;
    0;
    fn_8000728C(&sp8, &sp28);
    0;
    0;
    temp_f11 = arg0->unk0x68 * *(f32 *)0x80295304;
    sp48 = sp28 - temp_f11;
    sp4C = sp2C - temp_f11;
    sp50 = sp30 - temp_f11;
    sp54 = *(f32 *)0x80295308;
    0;
    0;
    sp4C = sp3C + temp_f11;
    sp48 = sp38 + temp_f11;
    sp50 = sp40 + temp_f11;
    0;
    var_r3 = *((s32 *)var_r17);
    0;
loop_74:
    var_r17 += 4;
    if (var_r3 == NULL) {

    } else {
        temp_r27 = var_r3->unk0x8;
        var_r19 = fn_8010391C(temp_r27, &sp28, &sp10D8, &sp58, 0x800);
        var_ctr = 3;
        do {
            var_ctr -= 1;
        } while (var_ctr != 0);
        var_r14 = 0U;
        if (sp10D8 > 0U) {
            temp_f29 = *(f32 *)0x8029530C;
            temp_f28 = *(s32 *)lbl_80295308;
            temp_f30 = *(f32 *)0x80295314;
loop_5:
            temp_r0 = *((s32 *)var_r19);
            temp_r9 = *(s32 *)((char *)temp_r27 + (s32)0xA);
            if ((s32) temp_r9 != 0) {
                var_r0 = *((s32 *)((char *)temp_r27->unk0xC + (temp_r0 * 8)));
            } else {
                var_r0 = *((s32 *)((char *)temp_r27->unk0xC + (temp_r0 * 10)));
            }
            if (!(var_r0 & 0x1010)) {
                if ((s32) temp_r9 != 0) {
                    var_r0_2 = *(s32 *)((s32 *)((temp_r0 * 8) + temp_r27->unk0xC) + 0x4);
                } else {
                    var_r0_2 = (u8) *(s32 *)((s32 *)((temp_r0 * 0xA) + temp_r27->unk0xC) + 0x4);
                }
                temp_r9_2 = temp_r27->unk0x3C;
                if (temp_r9_2 != 0) {
                    var_r0_3 = temp_r27->unk0x3C;
                    sp108C = *(s32 *)((s32 *)(var_r11 + temp_r27->unk0x3C) + 0x4);
                    sp1088 = *((s32 *)var_r11 + (s32)temp_r9_2);
                    var_r11 = var_r0_2 * 0xC;
                } else {
                    var_r11 = var_r0_2 * 0xC;
                    sp1088 = *((s32 *)var_r11 + temp_r27->unk0x30);
                    sp108C = *(s32 *)((s32 *)(var_r11 + temp_r27->unk0x30) + 0x4);
                    var_r0_3 = temp_r27->unk0x30;
                }
                sp1094 = temp_f29;
                sp1090 = *(s32 *)((s32 *)(var_r11 + var_r0_3) + 0x8);
                0;
                0;
                temp_r9_3 = *((s32 *)var_r19);
                if ((s32) *(s32 *)((char *)temp_r27 + (s32)0xA) != 0) {
                    var_r9 = *(s32 *)((s32 *)((temp_r9_3 * 8) + temp_r27->unk0xC) + 0x5);
                } else {
                    var_r9 = (u8) *(s32 *)((s32 *)((temp_r9_3 * 0xA) + temp_r27->unk0xC) + 0x6);
                }
                temp_r10 = temp_r27->unk0x3C;
                if (temp_r10 != 0) {
                    var_r11_2 = var_r9 * 0xC;
                    sp1098 = *((s32 *)var_r11_2 + (s32)temp_r10);
                    sp109C = *(s32 *)((s32 *)(var_r11_2 + temp_r27->unk0x3C) + 0x4);
                    var_r0_4 = temp_r27->unk0x3C;
                } else {
                    var_r11_2 = var_r9 * 0xC;
                    sp1098 = *((s32 *)var_r11_2 + temp_r27->unk0x30);
                    sp109C = *(s32 *)((s32 *)(var_r11_2 + temp_r27->unk0x30) + 0x4);
                    var_r0_4 = temp_r27->unk0x30;
                }
                sp10A4 = temp_f29;
                sp10A0 = *(s32 *)((s32 *)(var_r11_2 + var_r0_4) + 0x8);
                0;
                0;
                temp_r9_4 = *((s32 *)var_r19);
                if ((s32) *(s32 *)((char *)temp_r27 + (s32)0xA) != 0) {
                    var_r9_2 = *(s32 *)((s32 *)((temp_r9_4 * 8) + temp_r27->unk0xC) + 0x6);
                } else {
                    var_r9_2 = (u8) *(s32 *)((s32 *)((temp_r9_4 * 0xA) + temp_r27->unk0xC) + 0x8);
                }
                temp_r10_2 = temp_r27->unk0x3C;
                if (temp_r10_2 != 0) {
                    var_r11_3 = var_r9_2 * 0xC;
                    sp10A8 = *((s32 *)var_r11_3 + (s32)temp_r10_2);
                    sp10AC = *(s32 *)((s32 *)(var_r11_3 + temp_r27->unk0x3C) + 0x4);
                    var_r0_5 = temp_r27->unk0x3C;
                } else {
                    var_r11_3 = var_r9_2 * 0xC;
                    sp10A8 = *((s32 *)var_r11_3 + temp_r27->unk0x30);
                    sp10AC = *(s32 *)((s32 *)(var_r11_3 + temp_r27->unk0x30) + 0x4);
                    var_r0_5 = temp_r27->unk0x30;
                }
                sp10B4 = temp_f29;
                sp10B0 = *(s32 *)((s32 *)(var_r11_3 + var_r0_5) + 0x8);
                0;
                0;
                sp54 = temp_f28;
                sp10A4 = temp_f28;
                sp1094 = temp_f28;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                0;
                temp_f13 = *(f32 *)0x80295310;
                0;
                0;
                0;
                if ((!(sp1060 < temp_f13) || !(sp1070 < temp_f13) || !(sp1080 < temp_f13)) && (fn_8008741C(sp1058, sp105C, sp1068, sp106C, sp1078, sp107C) != 0)) {
                    var_r9_3 = 0;
                    if (sp48 == sp1088) {
                        0;
                        var_r9_3 = ((u32) 0 >> 1U) & 1;
                    }
                    if ((sp4C == sp108C) && (sp108C == sp109C)) {
                        var_r9_3 += 1;
                    }
                    if ((sp50 == sp1090) && (sp1090 == sp10A0)) {
                        var_r9_3 += 1;
                    }
                    if (var_r9_3 <= 1) {
                        if (var_r22 == NULL) {
                            var_r18 = fn_8007219C(sp10EC);
                            if (var_r18 != NULL) {
                                var_r22 = var_r18 + 0x20;
                                goto block_43;
                            }
                            goto block_72;
                        }
block_43:
                        var_r26 = ((Unk_50DDB38B *)var_r18)->unk0x1C;
                        var_r28 = var_r26 * 3;
                        0;
                        temp_r9_5 = (var_r26 * 0x60) + var_r22;
                        temp_r11 = temp_r9_5 + 0x20;
                        temp_r10_3 = temp_r9_5 + 0x40;
                        0;
                        0;
                        0;
                        *((f32 *)&((Unk_C8FEE62D *)temp_r9_5)->unk0x14) = (f32) ((sp1058 * temp_f30) + temp_f30);
                        *((f32 *)&((Unk_C8FEE62D *)temp_r9_5)->unk0x18) = (f32) ((sp105C * temp_f30) + temp_f30);
                        *((f32 *)&temp_r11->unk0x14) = (f32) ((sp1068 * temp_f30) + temp_f30);
                        *((f32 *)&temp_r11->unk0x18) = (f32) ((sp106C * temp_f30) + temp_f30);
                        *((f32 *)&temp_r10_3->unk0x14) = (f32) ((sp1078 * temp_f30) + temp_f30);
                        *((f32 *)&temp_r10_3->unk0x18) = (f32) ((sp107C * temp_f30) + temp_f30);
                        temp_r11_2 = *((s32 *)var_r19);
                        if ((s32) *(s32 *)((char *)temp_r27 + (s32)0xA) != 0) {
                            var_r7 = *(s32 *)((s32 *)((temp_r11_2 * 8) + temp_r27->unk0xC) + 0x4);
                        } else {
                            var_r7 = (u8) *(s32 *)((s32 *)((temp_r11_2 * 0xA) + temp_r27->unk0xC) + 0x4);
                        }
                        temp_r10_4 = temp_r27->unk0x38;
                        temp_r0_2 = *((s32 *)var_r19);
                        temp_r11_3 = *(s32 *)((char *)temp_r27 + (s32)0xA);
                        temp_r4 = *((s32 *)temp_r10_4 + ((temp_r11_2 * 3) + var_r7));
                        if ((s32) temp_r11_3 != 0) {
                            var_r0_6 = *(s32 *)((s32 *)((temp_r0_2 * 8) + temp_r27->unk0xC) + 0x5);
                        } else {
                            var_r0_6 = (u8) *(s32 *)((s32 *)((temp_r0_2 * 0xA) + temp_r27->unk0xC) + 0x6);
                        }
                        temp_r5 = *((s32 *)temp_r10_4 + ((temp_r0_2 * 3) + var_r0_6));
                        if ((s32) temp_r11_3 != 0) {
                            var_r0_7 = *(s32 *)((s32 *)((temp_r0_2 * 8) + temp_r27->unk0xC) + 0x6);
                        } else {
                            var_r0_7 = (u8) *(s32 *)((s32 *)((temp_r0_2 * 0xA) + temp_r27->unk0xC) + 0x8);
                        }
                        temp_r6 = var_r26 * 0x60;
                        temp_r31 = temp_r6 + var_r22;
                        temp_r8 = *((s32 *)temp_r10_4 + ((temp_r0_2 * 3) + var_r0_7));
                        sp10DC = temp_r4;
                        *(s32 *)((char *)&sp10DC + 0x2) = temp_r4;
                        *(s32 *)((char *)&sp10DC + 0x3) = -0x80;
                        *(s32 *)((char *)&sp10DC + 0x1) = temp_r4;
                        temp_r31->unk0x10 = (s32) sp10DC;
                        sp10E0 = temp_r5;
                        *(s32 *)((char *)&sp10E0 + 0x2) = temp_r5;
                        *(s32 *)((char *)&sp10E0 + 0x3) = -0x80;
                        *(s32 *)((char *)&sp10E0 + 0x1) = temp_r5;
                        temp_r31->unk0x30 = (s32) sp10E0;
                        sp10E4 = temp_r8;
                        *(s32 *)((char *)&sp10E4 + 0x2) = temp_r8;
                        *(s32 *)((char *)&sp10E4 + 0x3) = -0x80;
                        *(s32 *)((char *)&sp10E4 + 0x1) = temp_r8;
                        temp_r31->unk0x50 = (s32) sp10E4;
                        sp10E8 = NULL;
                        if ((s32) arg0->unk0x74 != 0) {
                            temp_r0_3 = temp_r6 + 0x20;
                            temp_r29 = var_r22 + temp_r0_3;
                            temp_r0_4 = temp_r6 + 0x40;
                            temp_f9 = *((s32 *)var_r22 + (s32)temp_r0_3) - *((s32 *)temp_r6 + (s32)var_r22);
                            temp_r30 = var_r22 + temp_r0_4;
                            temp_f8 = temp_r29->unk0x4 - temp_r31->unk0x4;
                            sp10A8 = temp_f9;
                            temp_f10 = temp_r29->unk0x8 - temp_r31->unk0x8;
                            sp10AC = temp_f8;
                            sp10B0 = temp_f10;
                            sp10B4 = temp_f28;
                            temp_f12 = *((s32 *)var_r22 + (s32)temp_r0_4) - *((s32 *)temp_r6 + (s32)var_r22);
                            temp_f0 = temp_r30->unk0x4 - temp_r31->unk0x4;
                            sp10B8 = temp_f12;
                            temp_f13_2 = temp_r30->unk0x8 - temp_r31->unk0x8;
                            sp10BC = temp_f0;
                            sp10C0 = temp_f13_2;
                            sp10C4 = temp_f28;
                            sp10D0 = (temp_f9 * temp_f0) - (temp_f12 * temp_f8);
                            sp10CC = (temp_f10 * temp_f12) - (temp_f13_2 * temp_f9);
                            sp10C8 = (temp_f8 * temp_f13_2) - (temp_f0 * temp_f10);
                            sp10D4 = temp_f28;
                            fn_8006BC80((void *)lbl_80366DDC);
                            *(s32 *)(lbl_80366DDC + (s32)0x4) = 0x20;
                            fn_8006BC90((void *)lbl_80366DDC, (s32)temp_r31);
                            fn_8006BC90((void *)lbl_80366DDC, (s32)temp_r29);
                            fn_8006BC90((void *)lbl_80366DDC, (s32)temp_r30);
                            temp_r3 = *(void **)lbl_802FFE98;
                            fn_8000F2F8(temp_r3, temp_r3->unk0x118);
                            temp_r0_5 = (s32)Mem_Alloc(0xC80);
                            var_ctr_2 = 0x64;
                            do {
                                var_ctr_2 -= 1;
                            } while (var_ctr_2 != 0);
                            sp10E8 = (void *)temp_r0_5;
                            var_r30 = (void *)temp_r0_5;
                            fn_8000F320(*(void **)lbl_802FFE98);
                            /* CHAINED (recipe 23 / 4t): the want is
                               `li r3,0x1c; bl Mem_Alloc2; bl fn_8009636C`
                               with no `mr r3` in between. */
                            temp_r29_2 = (s32)fn_8009636C(Mem_Alloc2(0x1C));
                            do {

                            } while (fn_8008279C((s32 *)&sp10E8, temp_r29_2) != 0);
                            if (temp_r0_5 != (s32)sp10E8) {
                                var_r24 = (var_r26 * 3) + 2;
loop_62:
                                temp_r29_3 = (var_r28 << 5) + var_r22;
                                0;
                                temp_r31_2 = temp_r29_3 + 0x20;
                                temp_r28 = temp_r29_3 + 0x40;
                                0;
                                0;
                                0;
                                *((f32 *)&((Unk_C8FEE62D *)temp_r29_3)->unk0x14) = (f32) *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x14);
                                *((f32 *)&((Unk_C8FEE62D *)temp_r29_3)->unk0x18) = (f32) *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x18);
                                *((f32 *)&temp_r31_2->unk0x14) = (f32) *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x34);
                                *((f32 *)&temp_r31_2->unk0x18) = (f32) *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x38);
                                *((f32 *)&temp_r28->unk0x14) = (f32) *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x54);
                                *((f32 *)&temp_r28->unk0x18) = (f32) *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x58);
                                if (arg0->unk0xC0 != temp_f29) {
                                    temp_f31 = fn_80271170(arg0->unk0xC0);
                                    temp_f1 = fn_80271070(arg0->unk0xC0);
                                    *((f32 *)&((Unk_C8FEE62D *)temp_r29_3)->unk0x14) = (f32) ((temp_f1 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x14)) - (temp_f31 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x18)));
                                    *((f32 *)&((Unk_C8FEE62D *)temp_r29_3)->unk0x18) = (f32) ((temp_f31 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x14)) + (temp_f1 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x18)));
                                    *((f32 *)&temp_r31_2->unk0x14) = (f32) ((temp_f1 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x34)) - (temp_f31 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x38)));
                                    *((f32 *)&temp_r31_2->unk0x18) = (f32) ((temp_f31 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x34)) + (temp_f1 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x38)));
                                    *((f32 *)&temp_r28->unk0x14) = (f32) ((temp_f1 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x54)) - (temp_f31 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x58)));
                                    *((f32 *)&temp_r28->unk0x18) = (f32) ((temp_f31 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x54)) + (temp_f1 * *((f32 *)&((Unk_C8FEE62D *)var_r30)->unk0x58)));
                                }
                                var_r26 += 1;
                                var_r24 += 3;
                                ((Unk_C8FEE62D *)temp_r29_3)->unk0x10 = (s32) ((Unk_C8FEE62D *)var_r30)->unk0x10;
                                var_r28 = var_r26 * 3;
                                ((Unk_C8FEE62D *)temp_r29_3)->unk0x30 = (s32) ((Unk_C8FEE62D *)var_r30)->unk0x30;
                                ((Unk_C8FEE62D *)temp_r29_3)->unk0x50 = (s32) ((Unk_C8FEE62D *)var_r30)->unk0x50;
                                if (var_r24 > 0x5FFU) {
                                    if ((s32) arg0->unk0x74 != 0) {
                                        ((Unk_50DDB38B *)var_r18)->unk0x1C = var_r26;
                                        if (temp_r0_5 != NULL) {
                                            Mem_Free2(temp_r0_5);
                                        }
                                    }
                                } else {
                                    var_r30 += 0x60;
                                    if (var_r30 == sp10E8) {
                                        goto block_69;
                                    }
                                    goto loop_62;
                                }
                            } else {
block_69:
                                ((Unk_50DDB38B *)var_r18)->unk0x1C = var_r26;
                                ((Unk_50DDB38B *)var_r18)->unk0x18 = (s32) arg0->unk0x20;
                                ((Unk_50DDB38B *)var_r18)->unk0xC020 = (s32) temp_r15->unk0xC;
                                if (((s32) arg0->unk0x74 != 0) && (temp_r0_5 != NULL)) {
                                    Mem_Free2(temp_r0_5);
                                }
                                goto block_72;
                            }
                        } else {
                            temp_r26 = var_r26 + 1;
                            if ((u32) ((temp_r26 * 3) + 2) <= 0x5FFU) {
                                ((Unk_50DDB38B *)var_r18)->unk0x1C = temp_r26;
                                ((Unk_50DDB38B *)var_r18)->unk0x18 = (s32) arg0->unk0x20;
                                ((Unk_50DDB38B *)var_r18)->unk0xC020 = (s32) temp_r15->unk0xC;
                                goto block_72;
                            }
                        }
                    } else {
                        goto block_72;
                    }
                } else {
                    goto block_72;
                }
            } else {
block_72:
                var_r14 += 1;
                var_r19 += 2;
                if (var_r14 >= sp10D8) {
                    goto block_73;
                }
                goto loop_5;
            }
        } else {
block_73:
            var_r3 = *((s32 *)var_r17);
            goto loop_74;
        }
    }
}
