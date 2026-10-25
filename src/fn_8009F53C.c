// range 0x8009F53C-0x8009F558 (0x1C = 28B). Byte-identical.
// Identification: vtable install — self->0x18 = lbl_80297AB0 (.rodata2,
// size 0x78), self->8 = 0; returns self (recipe 249 return-arg form).
// Suggested rename: Fn_8009F53C_VtableInit.
#include "types.h"
#include "structs.h"
extern char lbl_80297AB0[];
void *fn_8009F53C(Unk_C8FEE62D *arg0) {
    arg0->unk0x18 = (s32)lbl_80297AB0;
    arg0->unk0x8 = 0;
    return arg0;
}
