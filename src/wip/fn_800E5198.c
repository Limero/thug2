// PARKED 2026-10-13: DIFF ~25% (38/51 words), size-exact 204B.
// BLOCKER: callee-saved swap — want arg0->r30/tmp->r31, ngccc emits
// arg0->r31/tmp->r30; entire tail cascade (branch targets, mr r3 placement)
// follows from the swap. TRIED (all kept the swap): tmp declared first /
// inside block, no explicit arg0 copy, explicit a1 copy, split
// obj/tmp vars, swapped if-nesting, goto/block_5 control shape (worse: 40),
// -O1/-Os flags (worse: 40). The swap is an allocator-priority wall:
// temp's short range (ctor->delete) gets r31 over arg0's whole-function
// range. Next: probe how sibling E0030-family matches seated their regs.
// family=m2c range=0x800E5198-0x800E5264 size=204B
// INERT: not registered in splits.txt/configure.py — never compiled.
#include "types.h"
#include "qb_constants.h"
typedef struct { char pad0x0[0xC]; void *unk0xC; char pad0x10[0x64]; s32 unk0x74; char pad0x78[4]; f32 unk0x7C; s32 unk0x80; } A_E5198;
s32 CStruct_new(s32);
s32 CStruct_ctor();
void AddChecksum(void *, s32, s32);
void AddInteger(s32, s32, s32);
s32 fn_80152220(s32, s32);
void CStruct_delete(s32, s32);
extern f32 lbl_8029A9E8;
void fn_800E5198(A_E5198 *arg0, s32 arg1) {
    s32 tmp;
    if (arg0->unk0x80 != 0) {
        if (arg1 == 0) {
            tmp = CStruct_ctor(CStruct_new(8));
            AddChecksum(arg0, QB_NAME, *(s32 *)(*(s32 *)((char *)arg0 + 0xC) + 0x18));
            AddInteger(tmp, QB_COLOR, 0x808080);
            fn_80152220(*(s32 *)(*(s32 *)((char *)arg0 + 0xC) + 0x18), tmp);
            if (tmp != 0) {
                CStruct_delete(tmp, 3);
            }
        }
    }
    if (arg0->unk0x80 == 0 && arg1 != 0) {
        arg0->unk0x74 = 0;
        arg0->unk0x7C = lbl_8029A9E8;
    }
    arg0->unk0x80 = arg1;
}
