// range 0x8001B5B8-0x8001B5E4 (0x2C). Byte-identical.
// Identification: init-with-magic — zeroes +0x64/+0x68/+0x70/+0x74/+0x24
// and writes the magic 0x1234ABCD at +0x0, returning the object.
//
// Matching key (recipe 252): with a non-zero constant store mixed into a
// run of zero stores, write the constant store LAST in source and order the
// zeros so the rotate-right emit lands on want's order — source zeros
// [0x64,0x68,0x70,0x74,0x24] emit as [0x24,0x64,0x68,0x70,0x74] with the
// constant at +0 inserted after the first zero store (11/11).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_8001B5B8(Unk_A07EDCEF *arg0) {
    arg0->unk0x64 = 0;
    arg0->unk0x68 = 0;
    arg0->unk0x70 = 0;
    arg0->unk0x74 = 0;
    arg0->unk0x24 = 0;
    arg0->unk0x0 = QB_OBJ_MAGIC;
    return arg0;
}
