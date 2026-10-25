// range 0x80054424-0x80054438 (0x14 = 20B). Byte-identical.
// Identification: zeroes self->8 and self->4 (s32 fields), returns self.
// Matching key (recipe 249): ngccc emits the zero stores in the REVERSE of
// source order, and a `void *` return type with `return arg0;` forces the
// `mr r9, r3` base copy (r3 stays live for the return, so no restore).
// Suggested rename: Fn_80054424_ZeroTwoFields.
#include "types.h"
#include "structs.h"
void *fn_80054424(CStruct *arg0) {
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    return arg0;
}
