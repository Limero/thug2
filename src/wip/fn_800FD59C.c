// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-fno-schedule-insns` -> 25.40% to 33.33%.
// family=m2c range=0x800FD59C-0x800FD698 size=252B
// WIP draft - PARKED. See notes below.
// range=0x800FD59C-0x800FD698 size=252 B
// PARKED: 16/63 words (25%). Structure/statement order follows the m2c draft
// exactly (t0/t1/t2 divisions + product temps in want emission order) and size
// matches (252B), but FP register allocation differs from instruction one:
// WANT: C=f5, t rotating in f2, products in f11/f12/f10/f9/f13, o14=f4,
// o18=f3, negs f8/f7/f6, product temp f0. GOT assigns C=f8 etc. Tried: named
// temps vs inline divisions, aligned/non-aligned char[16] out-param, s32 vs
// void* first call arg, -mps-float always on (needed for final psq copies).
// Next idea: find what makes ngccc start FR allocation at f5 (maybe source had
// extra live float or different decl block).
// FLAG: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C180;
void fn_8008757C(void *out, Unk_DB0E2BAB * a, CStruct * b);
void fn_800FD59C(Unk_16447AB3 *arg0) {
    __attribute__((aligned(16))) char sp8[16];
    Unk_C4D756ED *temp_r11;
    f32 temp_f5;
    f32 temp_f4;
    f32 temp_f3;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f10;
    f32 temp_f9;
    f32 neg8;
    f32 neg7;
    f32 neg6;

    temp_f5 = lbl_8029C180;
    temp_r11 = (char *)arg0 + 0x20;
    temp_f2 = temp_f5 / arg0->unk0x10;
    temp_f4 = arg0->unk0x14;
    temp_f3 = arg0->unk0x18;
    temp_f11 = arg0->unk0x20 * temp_f2;
    arg0->unk0x80 = arg0->unk0x28 * temp_f2;
    temp_f12 = arg0->unk0x24 * temp_f2;
    arg0->unk0x60 = temp_f11;
    temp_f2_2 = temp_f5 / temp_f4;
    arg0->unk0x70 = temp_f12;
    temp_f10 = arg0->unk0x30 * temp_f2_2;
    arg0->unk0x84 = arg0->unk0x38 * temp_f2_2;
    temp_f9 = arg0->unk0x34 * temp_f2_2;
    arg0->unk0x64 = temp_f10;
    temp_f2_3 = temp_f5 / temp_f3;
    arg0->unk0x74 = temp_f9;
    arg0->unk0x68 = temp_r11->unk0x20 * temp_f2_3;
    neg8 = -arg0->unk0x50;
    neg7 = -arg0->unk0x54;
    neg6 = -arg0->unk0x58;
    arg0->unk0x78 = ((Unk_1D62F22E_2 *)temp_r11)->unk0x24 * temp_f2_3;
    ((Unk_32DC67FE *)arg0)->unk0x90 = neg8;
    arg0->unk0x88 = ((Unk_1D62F22E_2 *)temp_r11)->unk0x28 * temp_f2_3;
    arg0->unk0x94 = neg7;
    ((Unk_32DC67FE *)arg0)->unk0x98 = neg6;
    fn_8008757C(sp8, (char *)arg0 + 0x60, (char *)arg0 + 0x90);
    *((__ps_t *)&((Unk_32DC67FE *)arg0)->unk0x98) = ((__ps_t *)sp8)[1];
    *((__ps_t *)&((Unk_32DC67FE *)arg0)->unk0x90) = ((__ps_t *)sp8)[0];
}
