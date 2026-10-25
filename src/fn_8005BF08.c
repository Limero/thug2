// range 0x8005BF08-0x8005BF2C (0x24). Byte-identical.
// Identification: object header / vtable install + 8-byte copy — sets
// self+8 to the shared table lbl_80293770 (.rodata2) and copies src->0
// and src->4 into self.
//
// Matching key: `return self` (recipe 249) forces the `mr r11,r3` base
// copy; the void form emits stores via r3 directly (1/8).
#include "types.h"
#include "structs.h"
extern char lbl_80293770[];
void *fn_8005BF08(CStruct *self, CStruct *src) {
    *((void * *)&self->unk0x8) = lbl_80293770;
    self->unk0x0 = src->unk0x0;
    self->unk0x4 = src->unk0x4;
    return self;
}