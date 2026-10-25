// range 0x80240B5C-0x80240B80 (0x24). Byte-identical.
// Identification: constructor/initializer in the vtable-install family.
// Installs the vtable lbl_802B1250 at +0xc and zeroes +0x4/+0x0/+0x8,
// returning the object.
//
// Matching key (recipe 249): zero stores emit rotated [a,b,c] -> [c,a,b],
// so the source writes [4, 0, 8] to land on want's [8, 4, 0].
#include "types.h"
#include "structs.h"
extern char lbl_802B1250[];
void *fn_80240B5C(CStruct *arg0) {
    arg0->unk0xC = (s32)lbl_802B1250;
    arg0->unk0x4 = 0;
    arg0->unk0x0 = 0;
    arg0->unk0x8 = 0;
    return arg0;
}
