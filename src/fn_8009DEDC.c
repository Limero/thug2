// range 0x8009DEDC-0x8009DEF8 (0x1C = 28B). Byte-identical.
// Identification: vtable install — self->8 = lbl_802979B0 (.rodata2,
// size 0x48), self->4 = 0; returns self (recipe 249 return-arg form).
// Suggested rename: Fn_8009DEDC_VtableInit.
#include "types.h"
#include "structs.h"
extern char lbl_802979B0[];
// CObject_ctor @ 0x8009DEDC
void *CObject_ctor(CStruct *arg0) {
    arg0->unk0x8 = (s32)lbl_802979B0;
    arg0->unk0x4 = 0;
    return arg0;
}
