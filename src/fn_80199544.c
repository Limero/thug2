// range 0x80199544-0x80199558 (0x14 = 20B). Byte-identical.
// Identification: vtable install — self->4 = lbl_802AAA50 (.rodata2, size
// 0x64); returns self. The `return arg0` form (recipe 249) yields the
// `mr r11, r3` base copy with the vtable address in r9.
// Suggested rename: Fn_80199544_VtableInstall.
#include "types.h"
#include "structs.h"
extern char lbl_802AAA50[];
void *fn_80199544(CStruct *arg0) {
    arg0->unk0x4 = (s32)lbl_802AAA50;
    return arg0;
}
