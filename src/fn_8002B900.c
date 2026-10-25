// range 0x8002B900-0x8002B920 (0x20 = 32B). Byte-identical.
// Identification: vtable install — self->8 = lbl_80291808 (.rodata2,
// size 0x68), self->0 = arg1, self->4 = 0; returns self (recipe 249).
// Suggested rename: Fn_8002B900_VtableInitWithValue.
#include "types.h"
#include "structs.h"
extern char lbl_80291808[];
void *fn_8002B900(CStruct *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80291808;
    arg0->unk0x0 = arg1;
    arg0->unk0x4 = 0;
    return arg0;
}
