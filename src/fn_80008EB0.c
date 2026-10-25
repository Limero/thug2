// range 0x80008EB0-0x80008ED4 (0x24). Byte-identical.
// Identification: constructor in the zero-fill family — zeroes +0x14/+0x0/
// +0x10/+0x8 and sets the +0xc capacity field to 0x20, returning the
// object.
//
// Matching key (recipe 255): non-zero constant store written LAST with the
// zeros ordered for the rotate-right emit — source zeros
// [0, 0x10, 8, 0x14] emit as [0x14, 0, 0x10, 8] with the 0x20 store
// inserted second (9/9).
#include "types.h"
#include "structs.h"
void *fn_80008EB0(Unk_DB0E2BAB *arg0) {
    arg0->unk0x0 = 0;
    arg0->unk0x10 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    arg0->unk0xC = 0x20;
    return arg0;
}
