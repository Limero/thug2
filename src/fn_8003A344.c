// range 0x8003A344-0x8003A370 (0x2C). Byte-identical.
// Identification: table-value dispatch — calls fn_8003A390(self,
// self->0x108[idx]). Reads the function-arg table at self+0x108 indexed
// by idx.
//
// Matching key (recipe 66): materialize BOTH the scaled index and the
// base (`s32 off = idx * 4; u8 *base = self + 0x108; s32 val =
// *(s32*)(base+off);`) — this forces ngccc to emit want's
// `slwi r4,r4,2; addi r9,r3,0x108; lwzx r4,r9,r4`. Inlining the index as
// `base[idx]` merges base+idx into one register and adds 2 words.
#include "types.h"
#include "structs.h"
extern void fn_8003A390(CStruct *, s32);
void fn_8003A344(CStruct *self, s32 idx, s32 arg0, s32 arg1, s32 arg2) {
    s32 off = idx * 4;
    u8 *base = (u8 *)self + 0x108;
    s32 val = *(s32 *)(base + off);
    fn_8003A390(self, val);
}