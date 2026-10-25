// family=m2c range=0x8011FB4C-0x8011FDD0 size=644B
// PARKED 2026-10-05 (w_8011FB4C): DIFF 49.7% official
//   (test_wip_drafts / masked_pct; object 652B vs the 644B want = 8B LONG,
//   2 words).  On the OPCODE-ALIGNED stream 122/161 want words (75.8%) are
//   byte-identical under the reloc masks; prologue AND epilogue are exact and
//   both (u32) float->int fixup blocks match want verbatim.  The index-aligned
//   verdict is still capped by the length: index alignment holds perfectly to
//   word 83 (0x8011FC98) and breaks there.
//   This is NO LONGER the m2c husk - it is a full hand-decode.
// SEMANTICS FIXED vs m2c (each was worth real bytes):
//   * the 0x21C-stride record at 0x8038F0C0 is a real struct - f32 at
//     +0x10/+0x14/+0x18/+0x1C, s32 at +0x20/+0x24, void* at +0x20C, s32 at
//     +0x218 - indexed as `lbl_8038F0C0[i].f`.  THAT is what makes ngccc emit
//     retail's `addi rX,base,off` + `lwzx/lfsx rX,rY,idx` pair (same idiom as
//     matched fn_80120A00 / fn_801210C4).  m2c's `(char*)off + 0x8038F0D0`
//     literals folded the constant into the lwz displacement instead
//     (`add r10,r29,r30; lwz r0,0x20c(r10)`).
//   * both float->int casts are (u32), not (s32) (recipes 6gj(2)): only the
//     unsigned form emits `fcmpu f13,f10(2^31); cror cr0un,cr0eq,cr0gt; bso`
//     plus the `fsub 2^31; fctiwz; lwz; xoris 0x8000` slow arm.  Both arms
//     now match want word for word.
//   * int->float is (f32)(f64)(u32): `lis 0x4330; stw; lfd; fsub 2^52; frsp`
//     (0x8011FCC8..0x8011FD04).
//   * fn_8011A8FC returns f32 (matched src/fn_8011A8FC.c); fn_8011F590 takes
//     (void*,void*,f32,f32,f32,s32,s32) - ground truth is matched
//     src/fn_80120A00.c - so the args land in r3,r4,f1,f2,f3,r5,r6.
//   * the two stack locals are class objects: 0x80290E38 is a VTABLE (see
//     matched src/fn_8001B56C.c `arg0->unk0xC = (s32)lbl_80290E38`), so
//     sp+0x14 is the vptr slot of a local instance - assigned twice, want
//     does the same - and sp+0x10 is fn_80119510(0)'s s32, stored once and
//     reloaded (0x8011FD1C / 0x8011FD50).
//   * frame: locals 0x8..0x30, stmw r24, stfd f30/f31, stw lr 0x64 -> 0x60.
//     The 8th callee-saved GPR needs the vptr slot's address in a register,
//     hence the brief-sanctioned `register ... __asm__("r24")` pin.
//   * `first_arg = rec[i].unk20C + 0x138` is computed right after the
//     interrupt disable (want 0x8011FCAC/0x8011FCBC); left inline in the call
//     it lands late and costs 2 extra words.
//   * the voice pointer is re-read for the second fn_8011F590 argument
//     (want reloads at 0x8011FD00); a single shared variable gets a
//     callee-saved register instead and costs 3 words.
// RESIDUAL: want materialises base + offset pointers for BOTH stack locals and
//   keeps a copy of each across the calls; this body keeps one (r24) and uses
//   direct frame displacements 0x14(r1)/0x1c(r1) for the other. The missing
//   words all sit in the 0x8011FC94..0x8011FCBC block and after. At 0x8011FC94
//   the original rematerialises the array base at the join with a high-half
//   load into r30, followed at 0x8011FC9C by adding the low part. At
//   0x8011FCA4 it derives base plus 0x20C into r29, and at 0x8011FCAC it
//   reloads the voice pointer with an indexed load. At 0x8011FCB8 it copies
//   the vptr-slot address into r24. At 0x8011FCF8 it builds the spC base off
//   the stack pointer, copied onward at 0x8011FD18. At 0x8011FCE8 it emits a
//   second high-half load into r8 for the 2-to-the-31 pool double, where this
//   body reuses r9 instead.
//   and it emits 2 words want does not (an extra @ha/addi pair for the
//   base+0x20C reload late in the block, plus a `mr` in the arg shuffle).
// RULED OUT (each compiled + scored; LEAF_TMPDIR=<scratch>):
//   * `register Sp8 *q8 __asm__("r10"/"r11")` and `asm("" : "+r"(w))` pins:
//     GCC 2.95 silently overrides a pin on a caller-saved reg or on a MEM
//     reload pseudo - all such variants collapse back to the same code.
//   * the house `base = lbl_8038F0C0; p = base + 0x20C; *(s32*)(p + idx)`
//     idiom (tried for the early accesses and for the late reload): it DOES
//     keep `base` in a callee-saved reg and reproduces retail's
//     `addi r7,r30,0x1c`/`addi r30,r30,0x18`, but the address then folds
//     into the lwz again: 604-640B and 41-46%.
//   * asm emission-point pins on both local addresses: right SHAPE
//     (`stw r9,0xc(r27)` + `stw r3,4(r26)`) but the bases land at the top of
//     the function instead of the 0x8011FC98 join and the colours shuffle
//     (65% official, 632B).
//   * `volatile` pointer to the local struct: reaches exactly 644B but the
//     extra reloads land in the wrong slots (17% / 3%).
//   * nested `struct {s32; struct{s32;}; void*;}` and interior pointers
//     `(s32*)((char*)&obj+4)`: GCC constant-folds them away.
//   * two overlapping locals at sp+8 and sp+0xc (what want's two `addi` bases
//     imply) is not expressible: ngccc's allocator never overlaps two live
//     locals, and one 16B object folds every field store to `off(r1)`.
//   * inverted `!= 0`, separate-variable, inline and nested-`if` forms of the
//     AXSetVoiceState block, and splitting the 0x2F04 update in two: all
//     byte-identical to each other, so those choices are settled.
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    void *unkC;
} Sp8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    void *unkC;
} SpC;

typedef struct {
    char pad0[0x10];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s32 unk20;
    s32 unk24;
    char pad28[0x1E4];
    void *unk20C;
    s32 unk210;
    s32 unk214;
    s32 unk218;
} Rec;

extern char lbl_8039B860[];
extern Rec lbl_8038F0C0[3];
extern s32 lbl_80302F2C;
extern s32 lbl_80302F04;
extern f32 lbl_8029D734;
extern f32 lbl_8029D738;
extern f32 lbl_80302F0C;
extern char lbl_80290E38[];
s32 fn_80119510(s32);
void fn_80119578(void);
f32 fn_8011A8FC(s32);
void fn_8011F590(void *, void *, f32, f32, f32, s32, s32);
void AXSetVoiceState(s32, s32);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);

void fn_8011FB4C(s32 arg0) {
    Sp8 sp8;
    SpC spC;
    register Sp8 *q8 __asm__("r24");
    SpC *qC;
    s32 var_r11;
    s32 var_r27;
    void *first_arg;
    s32 g;
    s32 irq;
    f32 a;
    f32 b;
    u32 i1;
    u32 i2;

    var_r27 = -1;
    var_r11 = 0;
    if (arg0 == (s32)lbl_8039B860) {
        var_r27 = 0;
    } else {
    loop_2:
        var_r11 += 1;
        if (var_r11 <= 2) {
            if (arg0 == (s32)(lbl_8039B860 + (var_r11 << 5))) {
                var_r27 = var_r11;
            } else {
                goto loop_2;
            }
        }
    }
    if (var_r27 == -1) {
        return;
    }
    if (lbl_8038F0C0[var_r27].unk20C == 0) {
        return;
    }
    lbl_8038F0C0[var_r27].unk24 = 1;
    g = lbl_80302F2C;
    lbl_8038F0C0[var_r27].unk20 = g;
    if (g == 0 && lbl_8038F0C0[var_r27].unk218 == 0) {
        if (lbl_8038F0C0[var_r27].unk20C == 0) {
            return;
        }
        AXSetVoiceState(lbl_8038F0C0[var_r27].unk20C, 1);
    }
    a = lbl_8038F0C0[var_r27].unk10 * lbl_8038F0C0[var_r27].unk14 * lbl_8029D734 *
        lbl_8029D738 * lbl_8029D734;
    i1 = (u32)a;
    irq = OSDisableInterrupts();
    first_arg = (void *)(lbl_8038F0C0[var_r27].unk20C + 0x138);
    q8 = &sp8;
    q8->unkC = lbl_80290E38;
    qC = &spC;
    __asm__("" : "+r"(qC));
    qC->unk4 = fn_80119510(0);
    b = (f32)(f64)i1 * lbl_80302F0C;
    i2 = (u32)b;
    fn_8011F590(first_arg, (void *)lbl_8038F0C0[var_r27].unk20C,
                lbl_8038F0C0[var_r27].unk18, lbl_8038F0C0[var_r27].unk1C,
                fn_8011A8FC(qC->unk4), i2, 1);
    OSRestoreInterrupts(irq);
    lbl_80302F04 = (lbl_80302F04 | (0x200 << var_r27)) & ~(0x2000 << var_r27);
    q8->unkC = lbl_80290E38;
    fn_80119578();
}
