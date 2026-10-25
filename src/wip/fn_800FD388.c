// family=m2c range=0x800FD388-0x800FD494 size=268B
// WIP draft - PARKED. See notes below.
// range=0x800FD388-0x800FD494 size=268 B
// PARKED: 63/67 words match (94%). Remaining 4-word diff is a scheduler
// interleave in the constant-setup block: WANT emits lis r11(A-ha); lis r9(ptr-ha);
// lfs A; lis r10(B-ha); addi r9; lfs B -- GOT always emits B's lis before the
// ptr's lis regardless of source order ([A,B,P], [A,P,B], direct-store variants,
// ctr placement, decl order, -fno-sched-spec/-interblock/-insns/-insns2 all tried).
// Registers + everything else (both empty bdnz countdown loops, all 34 tail
// stores incl. rotated 0x98/0x9C emission) are exact.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C178;
extern f32 lbl_8029C17C;
extern char lbl_8029C600[];
void *fn_800FD264(Unk_C7387A53 * arg);
void *fn_800FD388(Unk_132A52FF *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f13;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 ptr;
    Unk_C4D756ED *temp_r10;
    Unk_5EF41E38 *temp_r11;

    fn_800FD264(arg0);
    temp_f0 = lbl_8029C178;
    temp_f13 = lbl_8029C17C;
    ptr = (s32)lbl_8029C600;
    var_ctr = 4;
    arg0->unk0xC = ptr;
    temp_r11 = (char *)arg0 + 0x10;
    arg0->unk0x10 = temp_f0;
    temp_r11->unk0x4 = temp_f0;
    temp_r11->unk0x8 = temp_f0;
    ((Unk_4C649A8C *)temp_r11)->unk0xC = temp_f13;
    do {
        var_ctr--;
    } while (var_ctr != 0);
    temp_r10 = (char *)arg0 + 0x20;
    var_ctr_2 = 4;
    do {
        var_ctr_2--;
    } while (var_ctr_2 != 0);
    temp_f13 = lbl_8029C178;
    *((f32 *)&arg0->unk0x20) = temp_f13;
    temp_f0_2 = lbl_8029C17C;
    arg0->unk0x34 = temp_f13;
    arg0->unk0x24 = temp_f0_2;
    arg0->unk0x28 = temp_f0_2;
    arg0->unk0x2C = temp_f0_2;
    arg0->unk0x30 = temp_f0_2;
    arg0->unk0x38 = temp_f0_2;
    arg0->unk0x3C = temp_f0_2;
    temp_r10->unk0x20 = temp_f0_2;
    ((Unk_1D62F22E_2 *)temp_r10)->unk0x24 = temp_f0_2;
    ((Unk_1D62F22E_2 *)temp_r10)->unk0x28 = temp_f13;
    ((Unk_1D62F22E_2 *)temp_r10)->unk0x2C = temp_f0_2;
    arg0->unk0x50 = temp_f0_2;
    arg0->unk0x54 = temp_f0_2;
    arg0->unk0x58 = temp_f0_2;
    arg0->unk0x5C = temp_f13;
    arg0->unk0x60 = temp_f13;
    arg0->unk0x64 = temp_f0_2;
    arg0->unk0x68 = temp_f0_2;
    arg0->unk0x6C = temp_f0_2;
    arg0->unk0x70 = temp_f0_2;
    arg0->unk0x74 = temp_f13;
    arg0->unk0x78 = temp_f0_2;
    arg0->unk0x7C = temp_f0_2;
    *((f32 *)&arg0->unk0x80) = temp_f0_2;
    arg0->unk0x84 = temp_f0_2;
    arg0->unk0x88 = temp_f13;
    arg0->unk0x8C = temp_f0_2;
    arg0->unk0x90 = temp_f0_2;
    arg0->unk0x94 = temp_f0_2;
    arg0->unk0x98 = temp_f0_2;
    arg0->unk0x9C = temp_f13;
    return arg0;
}
