// WIP DRAFT (non-matching) — hand-rebuilt from disasm
// family=m2c range=0x801B17E4-0x801B19DC size=504B
// FLAG: -fno-gcse
// PARKED: 86.5% (109/126 words). Everything matches except the register home
// of the bool/ptr web var_r31: WANT recycles arg1's r31 after its death
// (`li r31,0/1`, `or. r31,r3,r3` common tail), while every C shape tried gets
// var_r31 colored onto p's register (r30) instead.
// Shapes exhausted (~12): natural if/else and goto-form (GCC hoists the
// default `li` above cmpwi + flips to bne-skip layout); inverted polarity
// (correct block layout, mirrored branch); -fno-sched-spec/-interblock
// (hoist persists AND they shrink the frame to 0x28); "+r"/memory-clobber/
// dead-sink asm barriers in the zero arm (barrier IS needed to kill the
// hoist); assign-in-condition; p decl-init at top (flips roles perfectly --
// arg1->r31, p->r30 -- but drags the `addi r30,r1,8` birth up to function
// top and swaps f13/f0 const roles); p copy-init (=arg0, DCE'd, no-op);
// register pins: p@r30 works (+2 words), var@r31 blocks arg1's home,
// double-pin r31 or a1-copy-pin collapse the frame (cf. parking doc 33 /
// recipe §73-151 local-pin corruption).
// -fno-gcse is REQUIRED: without it GCSE unifies all four `&sp8[0]` sites
// into one function-wide callee-saved web (want computes fresh addis in the
// case04/case2 shared tail and keeps p arm-local).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802ABEC0;
extern f32 lbl_802ABEC4;
extern f32 lbl_802ABEC8;
extern f32 lbl_802ABECC;

s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800CC138(Unk_C7387A53 *, s32, void *, s32, s32);
void fn_800CBDA0(void *, s32, f32);
f32 fn_800CBE30(void *, s32);

void fn_801B17E4(Unk_31DE137E *arg0, CStruct *arg1, f32 farg0) {
    s32 sp8[2];
    s32 var_r31;
    register void *p __asm__("r30");
    f32 var_f1;
    s32 temp_r3;

    var_f1 = farg0 + lbl_802ABEC0;
    if (var_f1 < lbl_802ABEC4) {
        var_f1 += lbl_802ABEC8;
    }
    switch ((s32)(var_f1 / lbl_802ABECC)) {
    case 0:
    case 4:
        fn_80128E34(arg1, QB_JUMPFORWARD, &sp8[0], 1);
        break;
    case 1:
        p = &sp8[0];
        if (fn_80128E34(arg1, QB_JUMPLEFT, p, 0) != 0) {
            var_r31 = 0;
            __asm__("" : "+r"(var_r31));
        } else {
            var_r31 = 1;
            fn_80128E34(arg1, QB_JUMPRIGHT, p, 1);
        }
        if ((temp_r3 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER)) != 0) {
            fn_800CC138(temp_r3, *(s32 *)(arg0->unk0xC + 0x18), var_r31, 0, 1);
        }
        break;
    case 2:
        fn_80128E34(arg1, QB_JUMPBACK, &sp8[0], 1);
        break;
    case 3:
        p = &sp8[0];
        if (fn_80128E34(arg1, QB_JUMPRIGHT, p, 0) != 0) {
            var_r31 = 0;
            __asm__("" : "+r"(var_r31));
        } else {
            var_r31 = 1;
            fn_80128E34(arg1, QB_JUMPLEFT, p, 1);
        }
        if ((temp_r3 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER)) != 0) {
            fn_800CC138(temp_r3, *(s32 *)(arg0->unk0xC + 0x18), var_r31, 0, 1);
        }
        break;
    }
    var_r31 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
    if (var_r31 != 0) {
        fn_800CBDA0(var_r31, sp8[0], lbl_802ABEC4);
        *((f32 *)&arg0->unk0x1C) = fn_800CBE30(var_r31, sp8[0]);
    }
}
