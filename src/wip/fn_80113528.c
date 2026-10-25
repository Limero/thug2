// PARKED 2026-10-10: DIFF ~35% (ps_diff 25/71, got 284B vs want 300B, 16B short).
// Tail call sequence is semantically right (195DC/1976C ctors, 1A708, 19640,
// return 1) but the object is 4 insns short and the mid-body call arg setups
// differ throughout. Suspect: the empty-body `if (GetFloat==0 && t31==0) {}`
// folds differently than want's surviving `cmpwi/bne/cmpwi` (note-6 shape),
// and/or the ctor-call address materialisation. Needs a want-vs-got walk
// from the top, not flag permutations.
// candidate — fn_80113528. Rewritten from the want
// disassembly. Changes vs the parked m2c draft:
//  1. REAL 4-ARG PROTOTYPES for GetFloat / GetChecksum_2 and prototypes for
//     fn_801195DC / fn_8011976C / fn_80119640 -> removes the four spurious
//     `crclr cr1eq` before each `bl` (want has none).
//  2. `lbl_8029D0F0` is a real .rodata2 f32 (100.0f, src/r2d_8029D0E8.c) and is
//     read symbolically; the draft used the raw literal 0x8029D0F0, which
//     cannot produce want's `lis r9,-0x7fd6 ; lfs f0,-0x2f10(r9)` HA/LO form.
//  3. The 24-byte stack buffer at r1+8 is a FLOAT struct. The draft's
//     `((Unk_59AB5482 *)&sp8)->unk0x4 = sp28;` stored through an s32 member,
//     i.e. a float->int conversion: G has `fctiwz f13,f0` + `stfd f13,0x20(r1)`
//     where want has a plain `stfs f0,4(r30)`. That conversion is also what
//     grew the frame to 0x40 and shifted every slot.
//  4. FRAME LAYOUT: want's locals are buf@0x08 (24B), sp20@0x20, sp24@0x24,
//     sp28@0x28, sp2C@0x2C, sp30@0x30 (frame 0x40, stmw r30,0x38). ngccc
//     hands the FIRST-declared local the HIGHEST slot, so the declaration
//     order below is sp30..sp20 then the buffer.
//  5. The materialised `addi r30,r1,8` that want keeps live across the last
//     two calls (used as `4(r30)`, `mr r5,r30`, `mr r3,r30`) is a POINTER
//     LOCAL to that buffer, while the two constructor calls still use `&sp8`.
//  6. The `cmpwi r3,0 / bne L / cmpwi r31,0` pair with no second branch is an
//     `A == 0 && B == 0` test whose (empty) body is the fall-through, so the
//     second branch is a jump-to-next and was deleted. The draft's one-condition
//     `if (...) { }` cannot produce the leftover `cmpwi r31,0`.
//  7. Store order is want's emission order via the corpus rotation rule: source
//     ascending (sp24, sp28, sp30) emits (sp30, sp24, sp28); source
//     (sp24, sp28) emits (sp28, sp24).
// family=m2c range=0x80113528-0x80113654 size=300B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_8011976C(void *);
void fn_801195DC(void *);
void fn_80119640(void *, s32);
s32 fn_8011A708(s32, s32, void *, f32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern f32 lbl_8029D0F0;
extern char lbl_80302C34[];

typedef struct {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
} B13528;

bool ScriptSetSoundParams(CStruct *arg0) {
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 sp20;
    B13528 sp8;
    f32 temp_f0;
    s32 temp_r31;
    B13528 *p;

    sp20 = 0;
    if (GetChecksum_2(arg0, 0, &sp20, 0) != 0) {
        temp_f0 = lbl_8029D0F0;
        sp24 = temp_f0;
        sp28 = temp_f0;
        sp30 = temp_f0;
        temp_r31 = GetFloat(arg0, QB_VOLL, &sp24, 0);
        if (GetFloat(arg0, QB_VOLR, &sp28, 0) == 0 && temp_r31 == 0) {
        }
        if (GetFloat(arg0, QB_VOL, &sp2C, 0) != 0) {
            sp28 = sp2C;
            sp24 = sp2C;
        }
        GetFloat(arg0, QB_PITCH, &sp30, 0);
        fn_801195DC(&sp8);
        fn_8011976C(&sp8);
        p = &sp8;
        sp8.unk0x0 = sp24;
        p->unk0x4 = sp28;
        fn_8011A708(*(s32 *)lbl_80302C34, sp20, p, sp30);
        fn_80119640(p, 2);
    }
    return true;
}
