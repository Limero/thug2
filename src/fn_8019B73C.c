// range 0x8019B73C-0x8019B754 (0x18 = 24B). Byte-identical.
// Identification: equality test — returns 1 if arg == self->8 + 1, else 0.
// Recipe 250: `arg == (x + 1)` keeps the addi on the load and the arg in
// the xor's rA.
// Suggested rename: Fn_8019B73C_EqualsFieldPlusOne.
#include "types.h"
#include "structs.h"
s32 fn_8019B73C(Unk_9994C3F5 *self, s32 arg) {
    return arg == (self->unk0x8 + 1);
}
