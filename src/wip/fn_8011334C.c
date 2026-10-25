// PARKED: best 43.8%. DIFF — local stack-slot
// ORDER mismatch.  The frame (0x40), stwu/stmw, all 6 script-call arg lists
// (4-arg GetFloat/GetChecksum_2 with arg0 passthrough + flag), the
// QB_VOLL/QB_VOLR/QB_VOL/QB_PITCH/QB_ID hashes, the LocalSp8 struct (24B, f32
// fields at 0x0/0x4), and the fn_801195DC/fn_8011976C/fn_8011A56C/fn_80119640
// call sequence all match; the remaining ~45 diffs are the stack-slot ORDER:
// WANT sp20@0x20 sp24@0x24 sp28@0x28 sp2C@0x2C sp30@0x30 sp34@0x34 vs GOT
// sp34@0x20 sp28@0x24 sp30@0x28 sp24@0x2C sp2C@0x30 sp20@0x34.  Tried: 4
// declaration orders (identical — GCC 2.95 does not allocate stack slots in
// declaration order), a Locals-struct grouping (same), volatile on the global
// (worse).  The slot order is an assign_stack_local quirk not reachable from C
// source shape.  Known family: regalloc / stack-slot-order.
//
// WIP DRAFT (non-matching) — body hand-written to fix the m2c draft's structure.
// family=m2c range=0x8011334C-0x8011348C size=320B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 OSPanic(s32, s32, s32);
extern f32 lbl_8029D0EC;
extern s32 lbl_80302C34;
s32 GetFloat(s32, s32, f32 *, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 fn_801195DC(void *);
s32 fn_8011976C(void *);
s32 fn_8011A56C(s32, s32, void *, s32, s32, s32, f32);
s32 fn_80119640(void *, s32);
typedef struct {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
} LocalSp8;
bool ScriptPlaySound(s32 arg0) {
    LocalSp8 sp8;
    s32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 sp30;
    s32 sp34;
    f32 temp_f0;
    temp_f0 = lbl_8029D0EC;
    sp34 = 0;
    sp30 = temp_f0;
    sp20 = 0;
    sp24 = temp_f0;
    sp2C = temp_f0;
    sp28 = temp_f0;
    GetChecksum_2(arg0, 0, &sp20, 0);
    GetFloat(arg0, QB_VOLL, &sp24, 0);
    GetFloat(arg0, QB_VOLR, &sp28, 0);
    if (GetFloat(arg0, QB_VOL, &sp2C, 0) != 0) {
        sp28 = sp2C;
        sp24 = sp2C;
    }
    GetFloat(arg0, QB_PITCH, &sp30, 0);
    GetChecksum_2(arg0, QB_ID, &sp34, 0);
    fn_801195DC(&sp8);
    fn_8011976C(&sp8);
    sp8.unk0x0 = sp24;
    sp8.unk0x4 = sp28;
    fn_8011A56C(lbl_80302C34, sp20, &sp8, sp34, 0, 0, sp30);
    fn_80119640(&sp8, 2);
    return true;
}
