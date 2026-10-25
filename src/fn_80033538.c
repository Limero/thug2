// range 0x80033538-0x80033560 (0x28). Byte-identical.
// Identification: constructor in the vtable-install family. Installs the
// vtable lbl_80291BD8 at +0x14, stashes arg1 at +0x4, zeroes
// +0x10/+0x8/+0xc, returns the object.
//
// Matching key (recipe 249): the three zero stores emit rotated, so the
// source writes [0x10, 8, 0xc] to land on want's [0xc, 0x10, 8].
#include "types.h"
#include "structs.h"
extern char lbl_80291BD8[];
void *fn_80033538(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80291BD8;
    arg0->unk0x4 = arg1;
    arg0->unk0x10 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0xC = 0;
    return arg0;
}
