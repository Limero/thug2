// range 0x80070E74-0x80070E90 (0x1C = 28B). Byte-identical.
// Identification: vtable install — self->4 = lbl_80295250 (.rodata2, size
// 0xB4), self->0 = 1 (an "active/valid" marker); returns self.
// Suggested rename: Fn_80070E74_VtableInitActive.
#include "types.h"
#include "structs.h"
extern char lbl_80295250[];
void *fn_80070E74(CStruct *arg0) {
    arg0->unk0x4 = (s32)lbl_80295250;
    arg0->unk0x0 = 1;
    return arg0;
}
