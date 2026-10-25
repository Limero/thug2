// range 0x80059394-0x800593B4 (0x20 = 32B). Byte-identical.
// Identification: indexed float-pair writer (sibling of fn_80059380) —
// p1[idx] = f1; p2[idx] = f2 where p1/p2 are the pointers at lbl_80364C38
// + 0x14 / + 0x18. The two pointer LOADS must be inline in their stores
// (materializing both temps hoists both loads before both stfsx, 6/8);
// the shared base needs an explicit `char *b` (single lis/addi).
// Suggested rename: Fn_80059394_SetIndexedFloatPair.
#include "types.h"
#include "structs.h"
extern char lbl_80364C38[];
void fn_80059394(s32 idx, f32 f1, f32 f2) {
    char *b = lbl_80364C38;
    (((Unk_1A9D14A3_2 *)b)->unk0x14)[idx] = f1;
    (((Unk_1A9D14A3_2 *)b)->unk0x18)[idx] = f2;
}
