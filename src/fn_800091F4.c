// range 0x800091F4-0x80009218 (0x24). Byte-identical.
// Identification: counter-ID allocator — sibling of fn_80009218. Reads the
// shared counter lbl_802FFA34, stores it as the node ID at self+4, bumps
// the global, zeroes self+8. Returns self (no fn_80009314 init call,
// unlike 9218).
//
// Matching key: store order [self->8, self->4, global] with the c+1 addi
// computed between the first two stores; the want's exact interleave is
// produced by writing `self->8 = 0; self->4 = c; global = c + 1;`
// (9/9). Source [self->4, global, self->8] gives the reversed order.
#include "types.h"
#include "structs.h"
extern int lbl_802FFA34[];
void *fn_800091F4(CStruct *self) {
    int c = lbl_802FFA34[0];
    *((int *)&self->unk0x8) = 0;
    *((int *)&self->unk0x4) = c;
    lbl_802FFA34[0] = c + 1;
    return self;
}
