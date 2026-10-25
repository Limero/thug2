// range 0x8005BEEC-0x8005BF08 (0x1C = 28B). Byte-identical.
// Identification: copies the u16 at self+6 into self->4 (zero-extended) and
// installs the vtable lbl_80293770 (.rodata2, size 0x19C) at self->8;
// returns self. The u16 load is hoisted early by the scheduler; the vtable
// store is written FIRST in source (recipe 249 rotation handles the rest).
// Suggested rename: Fn_8005BEEC_ShortCopyAndVtable.
#include "types.h"
#include "structs.h"
extern char lbl_80293770[];
void *fn_8005BEEC(Unk_2A7B74AF *arg0) {
    *((s32 *)&arg0->unk0x8) = (s32)lbl_80293770;
    arg0->unk0x4 = ((Unk_32A87CFA *)arg0)->unk0x6;
    return arg0;
}
