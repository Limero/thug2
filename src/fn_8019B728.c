// range 0x8019B728-0x8019B73C (0x14 = 20B). Byte-identical.
// Identification: equality test — returns 1 if arg == self->0x188, else 0.
// Matching key (recipe 250): `a == b` compiles to the
// xor/subfic/adde booleanize; writing the ARG FIRST (`arg == x`) puts the
// arg in the xor's rA (`xor r3, r4, r3`). A `!= 0` or `x == arg` form folds
// into a cmpw/branch instead.
// Suggested rename: Fn_8019B728_EqualsField.
#include "types.h"
#include "structs.h"
s32 fn_8019B728(Unk_31DE137E *self, s32 arg) {
    return arg == self->unk0x188;
}
