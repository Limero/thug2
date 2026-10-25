// range 0x80058564-0x80058580 (0x1C = 28B). Byte-identical.
// Identification: vtable install — self->4 = lbl_80293400 (.rodata2, size
// 0x58), self->0 = 0; returns self (recipe 249 return-arg form).
// Suggested rename: Fn_80058564_VtableInit.
#include "types.h"
#include "structs.h"
extern char lbl_80293400[];
void *fn_80058564(CStruct *arg0) {
    arg0->unk0x4 = (s32)lbl_80293400;
    arg0->unk0x0 = 0;
    return arg0;
}
