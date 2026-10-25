// range 0x8005EEFC-0x8005EF24 (0x28). Byte-identical.
// Identification: vtable/object header init — installs the table
// lbl_80293C78 (.rodata2, an object-header/vtable) at +0x14 and zeroes
// +0x4/+0x8/+0xc/+0x10, returning the object.
//
// Matching key (recipe 255/249): non-zero pointer store written FIRST with
// the zeros in the brute-forced order [4,8,0xc,0x10] (gives want's
// [0x14,0x10,4,8,0xc]).
#include "types.h"
#include "structs.h"
extern char lbl_80293C78[];
void *fn_8005EEFC(Unk_C8FEE62D *self) {
    self->unk0x14 = (s32)lbl_80293C78;
    self->unk0x4 = 0;
    self->unk0x8 = 0;
    self->unk0xC = 0;
    self->unk0x10 = 0;
    return self;
}